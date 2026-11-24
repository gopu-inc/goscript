/* Safe process and filesystem primitives used by the Goscript package manager. */
#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE 700
#include "interpreter.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>
#include <termios.h>
#include <signal.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <grp.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <sys/ioctl.h>
#include <poll.h>
#include <locale.h>
#include <langinfo.h>
#include <wchar.h>
#include <wctype.h>
#include <zlib.h>

#define GPM_RESPONSE_LIMIT (16u * 1024u * 1024u)
extern int goscript_argc;
extern char **goscript_argv;
static char *gpm_read_file(const char *path);
static int gpm_archive_extract(const char *archive,const char *dest);
static char *gpm_json_get(const char *json,const char *key);

static char *run_capture(char *const argv[], int *status) {
    int p[2]; if (pipe(p) != 0) return NULL;
    pid_t pid = fork();
    if (pid == 0) {
        close(p[0]); dup2(p[1], STDOUT_FILENO); close(p[1]);
        int nullfd = open("/dev/null", O_WRONLY); if (nullfd >= 0) { dup2(nullfd, STDERR_FILENO); close(nullfd); }
        execvp(argv[0], argv); _exit(127);
    }
    close(p[1]); if (pid < 0) { close(p[0]); return NULL; }
    size_t cap = 4096, len = 0; char *buf = malloc(cap); if (!buf) { close(p[0]); waitpid(pid, NULL, 0); return NULL; }
    for (;;) {
        if (len + 2048 + 1 > cap) { if (cap >= GPM_RESPONSE_LIMIT) { free(buf); buf = NULL; break; } cap *= 2; if (cap > GPM_RESPONSE_LIMIT) cap = GPM_RESPONSE_LIMIT; char *n = realloc(buf, cap); if (!n) { free(buf); buf = NULL; break; } buf = n; }
        ssize_t n = read(p[0], buf ? buf + len : (char[2048]){0}, buf ? cap - len - 1 : 2048);
        if (n <= 0) break;
        if (buf) len += (size_t)n;
    }
    close(p[0]); int ws = 0; waitpid(pid, &ws, 0); if (status) *status = WIFEXITED(ws) ? WEXITSTATUS(ws) : 128;
    if (!buf) return NULL;
    buf[len] = 0;
    return buf;
}

static int run_quiet(char *const argv[]) { int s = 0; char *out = run_capture(argv, &s); free(out); return s == 0; }
static const char *nz(const char *s) { return s ? s : ""; }

static char *gpm_http_get_impl(const char *url,const char *token,int include_error_body) {
    char *argv[12];int n=0;argv[n++]="curl";if(!include_error_body)argv[n++]="--fail";argv[n++]="--silent";argv[n++]="--show-error";argv[n++]="--location";argv[n++]="--max-time";argv[n++]="60";
    char auth[4096]; if (token && *token) { snprintf(auth,sizeof(auth),"Authorization: Bearer %s",token); argv[n++]="--header"; argv[n++]=auth; }
    argv[n++]=(char*)nz(url); argv[n]=NULL; int status=0; char *body=run_capture(argv,&status); if(status!=0){free(body);return strdup("");} return body?body:strdup("");
}
static char *gpm_http_get(const char *url,const char *token){return gpm_http_get_impl(url,token,0);}
static char *gpm_http_get_response(const char *url,const char *token){return gpm_http_get_impl(url,token,1);}
static char *gpm_http_post_json(const char *url,const char *body,const char *token) {
    char *argv[14]; int n=0; char auth[4096]; argv[n++]="curl";argv[n++]="--fail";argv[n++]="--silent";argv[n++]="--show-error";argv[n++]="--location";argv[n++]="--max-time";argv[n++]="60";argv[n++]="--header";argv[n++]="Content-Type: application/json";
    if(token&&*token){snprintf(auth,sizeof(auth),"Authorization: Bearer %s",token);argv[n++]="--header";argv[n++]=auth;}
    argv[n++]="--data-binary";argv[n++]=(char*)nz(body);argv[n++]=(char*)nz(url);argv[n]=NULL;int status=0;char*out=run_capture(argv,&status);if(status){free(out);return strdup("");}return out?out:strdup("");
}
static int gpm_http_download(const char *url,const char *path,const char *token) {
    char *argv[14];int n=0;char auth[4096];argv[n++]="curl";argv[n++]="--fail";argv[n++]="--silent";argv[n++]="--show-error";argv[n++]="--location";argv[n++]="--max-time";argv[n++]="300";if(token&&*token){snprintf(auth,sizeof(auth),"Authorization: Bearer %s",token);argv[n++]="--header";argv[n++]=auth;}argv[n++]="--output";argv[n++]=(char*)nz(path);argv[n++]=(char*)nz(url);argv[n]=NULL;return run_quiet(argv);
}
static int gpm_http_upload(const char *url,const char *path,const char *filename,const char *token,const char *version,const char *release,const char *arch) {
    char *argv[24];int n=0;char auth[4096],filearg[8192],varg[4096],rarg[4096],aarg[4096];argv[n++]="curl";argv[n++]="--silent";argv[n++]="--show-error";argv[n++]="--location";argv[n++]="--max-time";argv[n++]="600";argv[n++]="--write-out";argv[n++]="\n__GOLEM_STATUS__%{http_code}";
    if(token&&*token){snprintf(auth,sizeof(auth),"Authorization: Bearer %s",token);argv[n++]="--header";argv[n++]=auth;}
    snprintf(filearg,sizeof(filearg),"file=@%s;filename=%s",nz(path),nz(filename));snprintf(varg,sizeof(varg),"version=%s",nz(version));snprintf(rarg,sizeof(rarg),"release=%s",nz(release));snprintf(aarg,sizeof(aarg),"arch=%s",nz(arch));
    argv[n++]="--form";argv[n++]=filearg;argv[n++]="--form";argv[n++]=varg;argv[n++]="--form";argv[n++]=rarg;argv[n++]="--form";argv[n++]=aarg;argv[n++]=(char*)nz(url);argv[n]=NULL;
    int command_status=0;char*response=run_capture(argv,&command_status);
    if(command_status!=0||!response){free(response);fprintf(stderr,"golem: upload failed; check the network and registry URL\n");return 0;}
    char*marker=strstr(response,"\n__GOLEM_STATUS__");
    if(!marker){fprintf(stderr,"golem: registry returned an unreadable upload response\n");free(response);return 0;}
    *marker=0;long http_code=strtol(marker+strlen("\n__GOLEM_STATUS__"),NULL,10);
    if(http_code>=200&&http_code<300){free(response);return 1;}
    char*message=gpm_json_get(response,"error");char*owner=gpm_json_get(response,"owner");
    if(*message&&*owner)fprintf(stderr,"golem: %s (owner: %s, HTTP %ld)\n",message,owner,http_code);
    else if(*message)fprintf(stderr,"golem: %s (HTTP %ld)\n",message,http_code);
    else fprintf(stderr,"golem: publish rejected by registry (HTTP %ld)\n",http_code);
    free(message);free(owner);free(response);return 0;
}
static char *gpm_json_get(const char *json,const char *key) {
    if(!json||!key)return strdup("");
    size_t kl=strlen(key);const char*p=json;
    while((p=strchr(p,'"'))){p++;if(strncmp(p,key,kl)==0&&p[kl]=='"'){const char*q=p+kl+1;while(isspace((unsigned char)*q))q++;if(*q!=':'){continue;}q++;while(isspace((unsigned char)*q))q++;if(*q=='"'){q++;size_t cap=strlen(q)+1;char*out=malloc(cap);if(!out)return strdup("");size_t i=0;while(*q&&*q!='"'){if(*q=='\\'&&q[1]){q++;switch(*q){case 'n':out[i++]='\n';break;case 'r':out[i++]='\r';break;case 't':out[i++]='\t';break;default:out[i++]=*q;}}else out[i++]=*q;q++;}out[i]=0;return out;}const char*e=q;while(*e&&*e!=','&&*e!='}'&&!isspace((unsigned char)*e))e++;return strndup(q,(size_t)(e-q));} }
    return strdup("");
}
static const char *gpm_json_key_value(const char *json,const char *key){
    if(!json||!key)return NULL;
    size_t key_len=strlen(key);
    for(const char*p=json;*p;){
        if(*p!='"'){p++;continue;}
        const char*start=++p;
        int escaped=0;
        while(*p){
            if(escaped){escaped=0;p++;continue;}
            if(*p=='\\'){escaped=1;p++;continue;}
            if(*p=='"')break;
            p++;
        }
        if(!*p)return NULL;
        const char*end=p++;
        if((size_t)(end-start)!=key_len||memcmp(start,key,key_len)!=0)continue;
        while(isspace((unsigned char)*p))p++;
        if(*p++!=':')continue;
        while(isspace((unsigned char)*p))p++;
        return p;
    }
    return NULL;
}
static const char *gpm_json_value_end(const char *start){
    if(!start||!*start)return NULL;
    if(*start=='"'){
        int escaped=0;
        for(const char*p=start+1;*p;p++){
            if(escaped){escaped=0;continue;}
            if(*p=='\\'){escaped=1;continue;}
            if(*p=='"')return p+1;
        }
        return NULL;
    }
    if(*start=='{'||*start=='['){
        int depth=0,in_string=0,escaped=0;
        for(const char*p=start;*p;p++){
            if(in_string){
                if(escaped)escaped=0;
                else if(*p=='\\')escaped=1;
                else if(*p=='"')in_string=0;
                continue;
            }
            if(*p=='"'){in_string=1;continue;}
            if(*p=='{'||*p=='[')depth++;
            else if(*p=='}'||*p==']'){
                if(--depth==0)return p+1;
                if(depth<0)return NULL;
            }
        }
        return NULL;
    }
    const char*p=start;
    while(*p&&*p!=','&&*p!=']'&&*p!='}'&&!isspace((unsigned char)*p))p++;
    return p==start?NULL:p;
}
static char *gpm_json_array_item(const char *json,const char *key,int index){
    if(index<0)return strdup("");
    const char*p=gpm_json_key_value(json,key);
    if(!p||*p!='[')return strdup("");
    p++;
    int current=0;
    while(*p){
        while(isspace((unsigned char)*p)||*p==',')p++;
        if(*p==']'||!*p)return strdup("");
        const char*end=gpm_json_value_end(p);
        if(!end)return strdup("");
        if(current==index)return strndup(p,(size_t)(end-p));
        current++;
        p=end;
        while(isspace((unsigned char)*p))p++;
        if(*p==']'||!*p)return strdup("");
        if(*p!=',')return strdup("");
        p++;
    }
    return strdup("");
}
static char *gpm_json_quote(const char *s){const unsigned char*p=(const unsigned char*)nz(s);size_t cap=strlen((const char*)p)*6+3;char*out=malloc(cap);if(!out)return strdup("\"\"");size_t n=0;out[n++]='"';for(;*p;p++){if(*p=='"'||*p=='\\'){out[n++]='\\';out[n++]=(char)*p;}else if(*p=='\n'){out[n++]='\\';out[n++]='n';}else if(*p=='\r'){out[n++]='\\';out[n++]='r';}else if(*p=='\t'){out[n++]='\\';out[n++]='t';}else if(*p<32){n+=(size_t)snprintf(out+n,cap-n,"\\u%04x",*p);}else out[n++]=(char)*p;}out[n++]='"';out[n]=0;return out;}
static char *gpm_url_encode(const char *input){static const char hex[]="0123456789ABCDEF";const unsigned char*p=(const unsigned char*)nz(input);size_t len=strlen((const char*)p);if(len>(SIZE_MAX-1)/3)return strdup("");char*out=malloc(len*3+1);if(!out)return strdup("");size_t n=0;for(;*p;p++){if(isalnum(*p)||*p=='-'||*p=='_'||*p=='.'||*p=='~')out[n++]=(char)*p;else{out[n++]='%';out[n++]=hex[*p>>4];out[n++]=hex[*p&15];}}out[n]=0;return out;}
static char *gpm_tui_repeat(const char *text,int count){text=nz(text);if(count<0||count>4096)return strdup("");size_t step=strlen(text);if(step==0||(size_t)count>(SIZE_MAX-1)/step)return strdup("");size_t len=step*(size_t)count;char*out=malloc(len+1);if(!out)return strdup("");for(size_t i=0;i<(size_t)count;i++)memcpy(out+i*step,text,step);out[len]=0;return out;}
static int gpm_tui_width(void){struct winsize ws={0};if(ioctl(STDOUT_FILENO,TIOCGWINSZ,&ws)==0&&ws.ws_col>0)return (int)ws.ws_col;const char*columns=getenv("COLUMNS");if(columns){char*end=NULL;long value=strtol(columns,&end,10);if(end!=columns&&value>0&&value<=4096)return (int)value;}return 80;}
static struct termios curse_saved_termios;
static int curse_raw_mode_active;
static int curse_alternate_screen_active;
static volatile sig_atomic_t curse_resize_pending;
static int curse_handlers_installed;
static int curse_locale_initialized;
static const int curse_exit_signals[] = {SIGHUP, SIGINT, SIGQUIT, SIGTERM};
static struct sigaction curse_old_exit_actions[4];
static struct sigaction curse_old_winch_action;

static void curse_restore_terminal(void){
    if(curse_alternate_screen_active){
        static const char restore_screen[]="\033[0m\033[?25h\033[?2004l\033[?1006l\033[?1000l\033[?1049l";
        (void)write(STDOUT_FILENO,restore_screen,sizeof(restore_screen)-1);
        curse_alternate_screen_active=0;
    }
    if(curse_raw_mode_active){
        (void)tcsetattr(STDIN_FILENO,TCSAFLUSH,&curse_saved_termios);
        curse_raw_mode_active=0;
    }
    if(curse_handlers_installed){
        for(size_t i=0;i<sizeof(curse_exit_signals)/sizeof(curse_exit_signals[0]);i++)
            (void)sigaction(curse_exit_signals[i],&curse_old_exit_actions[i],NULL);
        (void)sigaction(SIGWINCH,&curse_old_winch_action,NULL);
        curse_handlers_installed=0;
    }
}

static void curse_exit_signal_handler(int signal_number){
    curse_restore_terminal();
    _exit(128+signal_number);
}

static void curse_winch_signal_handler(int signal_number){
    (void)signal_number;
    curse_resize_pending=1;
}

static int curse_install_signal_handlers(void){
    if(curse_handlers_installed)return 1;
    struct sigaction exit_action;
    memset(&exit_action,0,sizeof(exit_action));
    exit_action.sa_handler=curse_exit_signal_handler;
    sigemptyset(&exit_action.sa_mask);
    struct sigaction resize_action;
    memset(&resize_action,0,sizeof(resize_action));
    resize_action.sa_handler=curse_winch_signal_handler;
    sigemptyset(&resize_action.sa_mask);
    size_t installed=0;
    for(;installed<sizeof(curse_exit_signals)/sizeof(curse_exit_signals[0]);installed++){
        if(sigaction(curse_exit_signals[installed],&exit_action,&curse_old_exit_actions[installed])!=0)
            break;
    }
    if(installed==sizeof(curse_exit_signals)/sizeof(curse_exit_signals[0])&&
       sigaction(SIGWINCH,&resize_action,&curse_old_winch_action)==0){
        curse_handlers_installed=1;
        return 1;
    }
    while(installed>0){
        installed--;
        (void)sigaction(curse_exit_signals[installed],&curse_old_exit_actions[installed],NULL);
    }
    return 0;
}

static int curse_terminal_write_once(const char *text){
    if(!text)return 1;
    size_t length=strlen(text);
    if(length==0)return 1;
    size_t offset=0;
    while(offset<length){
        ssize_t written=write(STDOUT_FILENO,text+offset,length-offset);
        if(written<0&&errno==EINTR)continue;
        if(written<=0){
            int saved_errno=written<0?errno:EIO;
            fprintf(stderr,"curse: terminal frame write failed: %s\n",strerror(saved_errno));
            return 0;
        }
        offset+=(size_t)written;
    }
    return 1;
}

static void curse_restore_terminal_at_exit(void){
    curse_restore_terminal();
}
static int curse_terminal_raw(int enabled){
    if(enabled){
        if(curse_raw_mode_active)return 1;
        if(!isatty(STDIN_FILENO)||!isatty(STDOUT_FILENO))return 0;
        struct termios current;
        if(tcgetattr(STDIN_FILENO,&current)!=0)return 0;
        curse_saved_termios=current;
        current.c_iflag&=(tcflag_t)~(BRKINT|ICRNL|INPCK|ISTRIP|IXON);
        current.c_cflag|=CS8;
        current.c_lflag&=(tcflag_t)~(ECHO|ICANON|IEXTEN|ISIG);
        current.c_cc[VMIN]=1;
        current.c_cc[VTIME]=0;
        if(tcsetattr(STDIN_FILENO,TCSAFLUSH,&current)!=0)return 0;
        curse_raw_mode_active=1;
        if(!curse_install_signal_handlers()){
            (void)tcsetattr(STDIN_FILENO,TCSAFLUSH,&curse_saved_termios);
            curse_raw_mode_active=0;
            return 0;
        }
        atexit(curse_restore_terminal_at_exit);
        return 1;
    }
    if(!curse_raw_mode_active)return 1;
    curse_restore_terminal();
    return 1;
}
static int curse_terminal_start(void){
    static const char enter_screen[]="\033[?1049h\033[?25l\033[2J\033[H";
    if(!curse_terminal_raw(1))return 0;
    if(!curse_terminal_write_once(enter_screen)){
        (void)curse_terminal_raw(0);
        return 0;
    }
    curse_alternate_screen_active=1;
    return 1;
}
static int curse_terminal_stop(void){
    curse_restore_terminal();
    return 1;
}
static int curse_terminal_write_frame(const char *frame){return curse_terminal_write_once(frame);}
static int curse_terminal_take_resize(void){
    sig_atomic_t pending=curse_resize_pending;
    curse_resize_pending=0;
    return pending?1:0;
}
static int curse_terminal_read_byte(int timeout_ms){
    if(timeout_ms < -1)return -1;
    struct pollfd descriptor={STDIN_FILENO,POLLIN,0};
    int ready;
    do{ready=poll(&descriptor,1,timeout_ms);}while(ready<0&&errno==EINTR);
    if(ready==0)return -1;
    if(ready<0||(descriptor.revents&(POLLERR|POLLNVAL)))return -2;
    if(!(descriptor.revents&POLLIN))return (descriptor.revents&POLLHUP)?-2:-1;
    unsigned char byte;
    ssize_t count;
    do{count=read(STDIN_FILENO,&byte,1);}while(count<0&&errno==EINTR);
    return count==1?(int)byte:-2;
}
static char *curse_terminal_read_utf8_char(int first_byte,int timeout_ms){
    static const char replacement[]="\xEF\xBF\xBD";
    unsigned char bytes[5]={0};
    if(first_byte<0x80||first_byte>0xF4)return strdup(replacement);
    int expected=first_byte<=0xDF?2:first_byte<=0xEF?3:4;
    if(first_byte<0xC2)return strdup(replacement);
    bytes[0]=(unsigned char)first_byte;
    for(int i=1;i<expected;i++){
        int next=curse_terminal_read_byte(timeout_ms);
        if(next<0||(next&0xC0)!=0x80)return strdup(replacement);
        bytes[i]=(unsigned char)next;
    }
    if((bytes[0]==0xE0&&bytes[1]<0xA0)||(bytes[0]==0xED&&bytes[1]>=0xA0)||
       (bytes[0]==0xF0&&bytes[1]<0x90)||(bytes[0]==0xF4&&bytes[1]>0x8F))
        return strdup(replacement);
    bytes[expected]=0;
    return strdup((const char*)bytes);
}
static int curse_terminal_monotonic_ms(void){
    struct timespec now;
    if(clock_gettime(CLOCK_MONOTONIC,&now)!=0)return 0;
    return (int)((now.tv_sec%2000000)*1000+now.tv_nsec/1000000);
}
static int curse_terminal_dimension(int rows){
    struct winsize size={0};
    if(ioctl(STDOUT_FILENO,TIOCGWINSZ,&size)==0){
        int value=rows?(int)size.ws_row:(int)size.ws_col;
        if(value>0)return value;
    }
    const char*name=rows?"LINES":"COLUMNS";
    const char*value=getenv(name);
    if(value){
        char*end=NULL;
        long parsed=strtol(value,&end,10);
        if(end!=value&&parsed>0&&parsed<=4096)return (int)parsed;
    }
    return rows?24:80;
}
static int curse_terminal_width(void){return curse_terminal_dimension(0);}
static int curse_terminal_height(void){return curse_terminal_dimension(1);}
static int curse_terminal_capability(int capability){
    const char*term=getenv("TERM");
    const char*color=getenv("COLORTERM");
    if(capability==0)
        return color&&(!strcasecmp(color,"truecolor")||!strcasecmp(color,"24bit"));
    if(capability==1)
        return curse_terminal_capability(0)||(term&&strstr(term,"256color"));
    if(capability==2){
        if(!isatty(STDOUT_FILENO)||(term&&!strcmp(term,"dumb")))return 0;
        const char*locale_name=setlocale(LC_CTYPE,"");
        curse_locale_initialized=1;
        const char*codeset=nl_langinfo(CODESET);
        return locale_name&&codeset&&!strcasecmp(codeset,"UTF-8");
    }
    return 0;
}
static int curse_terminal_utf8_length(const char*text,int offset){
    if(!text||offset<0)return 0;
    if(!curse_locale_initialized){
        (void)setlocale(LC_CTYPE,"");
        curse_locale_initialized=1;
    }
    size_t length=strlen(text);
    if((size_t)offset>=length)return 0;
    mbstate_t state;
    memset(&state,0,sizeof(state));
    wchar_t character;
    size_t count=mbrtowc(&character,text+offset,length-(size_t)offset,&state);
    if(count==(size_t)-1||count==(size_t)-2||count==0)return 1;
    return count>INT_MAX?0:(int)count;
}
static int curse_terminal_unicode_width(const char*text,int offset){
    if(!text||offset<0)return 0;
    if(!curse_locale_initialized){
        (void)setlocale(LC_CTYPE,"");
        curse_locale_initialized=1;
    }
    size_t length=strlen(text);
    if((size_t)offset>=length)return 0;
    mbstate_t state;
    memset(&state,0,sizeof(state));
    wchar_t character;
    size_t count=mbrtowc(&character,text+offset,length-(size_t)offset,&state);
    if(count==(size_t)-1||count==(size_t)-2)return 1;
    if(count==0)return 0;
    int width=wcwidth(character);
    return width<0?1:width;
}
static int curse_terminal_flush(void){
    if(fflush(stdout)==0)return 1;
    fprintf(stderr,"curse: failed to flush terminal output: %s\n",strerror(errno));
    return 0;
}
static char *gpm_tui_rgb(int red,int green,int blue,const char *text){if(red<0||red>255||green<0||green>255||blue<0||blue>255)return strdup(nz(text));char prefix[32];snprintf(prefix,sizeof(prefix),"\033[38;2;%d;%d;%dm",red,green,blue);size_t n=strlen(prefix)+strlen(nz(text))+5;char*out=malloc(n);if(!out)return strdup(nz(text));snprintf(out,n,"%s%s\033[0m",prefix,nz(text));return out;}
static int gpm_tui_color_enabled(int unused){(void)unused;const char*no_color=getenv("NO_COLOR");const char*term=getenv("TERM");return !no_color&&(!term||strcmp(term,"dumb"))&&isatty(STDOUT_FILENO);}
static char *gpm_tui_bg_rgb(int red,int green,int blue,const char *text){if(red<0||red>255||green<0||green>255||blue<0||blue>255)return strdup(nz(text));char prefix[32];snprintf(prefix,sizeof(prefix),"\033[48;2;%d;%d;%dm",red,green,blue);size_t n=strlen(prefix)+strlen(nz(text))+5;char*out=malloc(n);if(!out)return strdup(nz(text));snprintf(out,n,"%s%s\033[0m",prefix,nz(text));return out;}
static char *gpm_tui_truncate(const char *text,int width){text=nz(text);if(width<=0)return strdup("");size_t n=strlen(text);if(n<=((size_t)width))return strdup(text);if(width==1)return strdup(".");if(width==2)return strdup("..");if(n>(((size_t)width)-3))n=((size_t)width)-3;char*out=malloc(n+4);if(!out)return strdup("");memcpy(out,text,n);memcpy(out+n,"...",4);return out;}
static char *gpm_tui_number(int value){char*out=malloc(32);if(!out)return strdup("");snprintf(out,32,"%d",value);return out;}
static char *gpm_sha256_file(const char *path){char *argv[]={"sha256sum","--",(char*)nz(path),NULL};int st=0;char*out=run_capture(argv,&st);if(st||!out){free(out);return strdup("");}char*sp=strchr(out,' ');if(sp)*sp=0;return out;}
static char *gpm_hash_file(const char *path,const char *algorithm){const char*tool=!strcmp(nz(algorithm),"md5")?"md5sum":"sha256sum";char*argv[]={(char*)tool,"--",(char*)nz(path),NULL};int st=0;char*out=run_capture(argv,&st);if(st||!out){free(out);return strdup("");}char*sp=strchr(out,' ');if(sp)*sp=0;return out;}
static char *gpm_hash_data(const char *data,const char *algorithm){char path[]="/tmp/goscript-hash-XXXXXX";int fd=mkstemp(path);if(fd<0)return strdup("");const char*p=nz(data);size_t len=strlen(p),off=0;while(off<len){ssize_t n=write(fd,p+off,len-off);if(n<=0){close(fd);unlink(path);return strdup("");}off+=(size_t)n;}close(fd);char*out=gpm_hash_file(path,algorithm);unlink(path);return out;}
static char *gpm_http_get_public(const char *url){return gpm_http_get(url,"");}
static char *gpm_http_post_public(const char *url,const char *body){return gpm_http_post_json(url,body,"");}
static char *gpm_http_get_headers(const char *url,const char *header){char *argv[]={"curl","--fail","--silent","--show-error","--location","--max-time","60","--header",(char*)nz(header),(char*)nz(url),NULL};int status=0;char*out=run_capture(argv,&status);if(status){free(out);return strdup("");}return out?out:strdup("");}
static char *gpm_http_get_timeout(const char *url,int seconds){if(seconds<1||seconds>3600)return strdup("");char timeout[16];snprintf(timeout,sizeof(timeout),"%d",seconds);char *argv[]={"curl","--fail","--silent","--show-error","--location","--max-time",timeout,(char*)nz(url),NULL};int status=0;char*out=run_capture(argv,&status);if(status){free(out);return strdup("");}return out?out:strdup("");}
static char *gpm_http_post_auth(const char *url,const char *body,const char *username,const char *password){size_t n=strlen(nz(username))+strlen(nz(password))+2;char*credentials=malloc(n);if(!credentials)return strdup("");snprintf(credentials,n,"%s:%s",nz(username),nz(password));char *argv[]={"curl","--fail","--silent","--show-error","--location","--max-time","60","--request","POST","--user",credentials,"--data-binary",(char*)nz(body),(char*)nz(url),NULL};int status=0;char*out=run_capture(argv,&status);free(credentials);if(status){free(out);return strdup("");}return out?out:strdup("");}
static char *gpm_http_post_form(const char *url,const char *form){char *argv[]={"curl","--fail","--silent","--show-error","--location","--max-time","60","--request","POST","--form",(char*)nz(form),(char*)nz(url),NULL};int status=0;char*out=run_capture(argv,&status);if(status){free(out);return strdup("");}return out?out:strdup("");}
static char *gpm_http_post_file(const char *url,const char *path){size_t n=strlen(nz(path))+7;char*form=malloc(n);if(!form)return strdup("");snprintf(form,n,"file=@%s",nz(path));char*out=gpm_http_post_form(url,form);free(form);return out;}
static char *gpm_http_request(const char*method,const char*url,const char*body){if(strcmp(nz(method),"GET")&&strcmp(nz(method),"POST")&&strcmp(nz(method),"PUT")&&strcmp(nz(method),"DELETE")&&strcmp(nz(method),"PATCH"))return strdup("");char*argv[16];int n=0;argv[n++]="curl";argv[n++]="--fail";argv[n++]="--silent";argv[n++]="--show-error";argv[n++]="--location";argv[n++]="--max-time";argv[n++]="60";argv[n++]="--request";argv[n++]=(char*)method;if(*nz(body)){argv[n++]="--data-binary";argv[n++]=(char*)body;}argv[n++]=(char*)nz(url);argv[n]=NULL;int status=0;char*out=run_capture(argv,&status);if(status){free(out);return strdup("");}return out?out:strdup("");}
static char *gpm_http_get_auth(const char*url,const char*user,const char*password){size_t n=strlen(nz(user))+strlen(nz(password))+2;char*credentials=malloc(n);if(!credentials)return strdup("");snprintf(credentials,n,"%s:%s",nz(user),nz(password));char*argv[]={"curl","--fail","--silent","--show-error","--location","--max-time","60","--user",credentials,(char*)nz(url),NULL};int status=0;char*out=run_capture(argv,&status);free(credentials);if(status){free(out);return strdup("");}return out?out:strdup("");}
static char *gpm_http_get_proxy(const char*url,const char*proxy){char*argv[]={"curl","--fail","--silent","--show-error","--location","--max-time","60","--proxy",(char*)nz(proxy),(char*)nz(url),NULL};int status=0;char*out=run_capture(argv,&status);if(status){free(out);return strdup("");}return out?out:strdup("");}
static char *gpm_http_get_no_follow(const char*url){char*argv[]={"curl","--fail","--silent","--show-error","--max-time","60",(char*)nz(url),NULL};int status=0;char*out=run_capture(argv,&status);if(status){free(out);return strdup("");}return out?out:strdup("");}
static char *gpm_http_cookie_request(const char*url,const char*cookie_file,int save){char*argv[]={"curl","--fail","--silent","--show-error","--location","--max-time","60",save?"--cookie-jar":"--cookie",(char*)nz(cookie_file),(char*)nz(url),NULL};int status=0;char*out=run_capture(argv,&status);if(status){free(out);return strdup("");}return out?out:strdup("");}
static int gpm_tar_pack(const char *source,const char *output){char*argv[]={"tar","-czf",(char*)nz(output),"--",(char*)nz(source),NULL};return run_quiet(argv);}
static int gpm_tar_unpack(const char *archive,const char *destination){return gpm_archive_extract(archive,destination);}
static const char b64_alphabet[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static char *gpm_base64_encode(const char *input){const unsigned char*s=(const unsigned char*)nz(input);size_t len=strlen((const char*)s),outlen=((len+2)/3)*4;char*out=malloc(outlen+1);if(!out)return strdup("");size_t i=0,j=0;while(i<len){size_t remain=len-i;uint32_t a=s[i++],b=remain>1?s[i++]:0,c=remain>2?s[i++]:0;out[j++]=b64_alphabet[a>>2];out[j++]=b64_alphabet[((a&3)<<4)|(b>>4)];out[j++]=remain>1?b64_alphabet[((b&15)<<2)|(c>>6)]:'=';out[j++]=remain>2?b64_alphabet[c&63]:'=';}out[j]=0;return out;}
static char *gpm_base64_decode(const char *input){const unsigned char*s=(const unsigned char*)nz(input);size_t len=strlen((const char*)s);char*out=malloc((len*3)/4+2);if(!out)return strdup("");int val=0,bits=-8;size_t j=0;for(size_t i=0;i<len;i++){unsigned char c=s[i];if(isspace(c))continue;if(c=='=')break;const char*p=strchr(b64_alphabet,c);if(!p){free(out);return strdup("");}val=(val<<6)|(int)(p-b64_alphabet);bits+=6;if(bits>=0){out[j++]=(char)((val>>bits)&255);bits-=8;}}out[j]=0;return out;}
static int gpm_b64_decode_bytes(const char*input,unsigned char**output,size_t*outlen){size_t cap=(strlen(nz(input))*3)/4+4;unsigned char*out=malloc(cap);if(!out)return 0;int val=0,bits=-8;size_t n=0;for(const unsigned char*p=(const unsigned char*)nz(input);*p;p++){if(isspace(*p))continue;if(*p=='=')break;const char*q=strchr(b64_alphabet,*p);if(!q){free(out);return 0;}val=(val<<6)|(int)(q-b64_alphabet);bits+=6;if(bits>=0){out[n++]=(unsigned char)((val>>bits)&255);bits-=8;}}*output=out;*outlen=n;return 1;}
static char *gpm_b64_encode_bytes(const unsigned char*s,size_t len){size_t outlen=((len+2)/3)*4;char*out=malloc(outlen+1);if(!out)return strdup("");size_t i=0,j=0;while(i<len){size_t r=len-i;uint32_t a=s[i++],b=r>1?s[i++]:0,c=r>2?s[i++]:0;out[j++]=b64_alphabet[a>>2];out[j++]=b64_alphabet[((a&3)<<4)|(b>>4)];out[j++]=r>1?b64_alphabet[((b&15)<<2)|(c>>6)]:'=';out[j++]=r>2?b64_alphabet[c&63]:'=';}out[j]=0;return out;}
static char *gpm_gzip_compress(const char*input){size_t inlen=strlen(nz(input));if(inlen>GPM_RESPONSE_LIMIT||inlen>UINT_MAX)return strdup("");uLong bound=compressBound((uLong)inlen);if(bound>GPM_RESPONSE_LIMIT)return strdup("");unsigned char*out=malloc(bound+32);if(!out)return strdup("");z_stream stream={0};if(deflateInit2(&stream,Z_DEFAULT_COMPRESSION,Z_DEFLATED,15+16,8,Z_DEFAULT_STRATEGY)!=Z_OK){free(out);return strdup("");}stream.next_in=(Bytef*)nz(input);stream.avail_in=(uInt)inlen;stream.next_out=out;stream.avail_out=(uInt)(bound+32);int status=deflate(&stream,Z_FINISH);size_t outlen=stream.total_out;deflateEnd(&stream);if(status!=Z_STREAM_END){free(out);return strdup("");}char*encoded=gpm_b64_encode_bytes(out,outlen);free(out);return encoded;}
static char *gpm_gzip_decompress(const char*input){unsigned char*compressed=NULL;size_t inlen=0;if(!gpm_b64_decode_bytes(input,&compressed,&inlen)||inlen>UINT_MAX||inlen>GPM_RESPONSE_LIMIT){free(compressed);return strdup("");}size_t cap=inlen<256?256:inlen*4;if(cap>GPM_RESPONSE_LIMIT)cap=GPM_RESPONSE_LIMIT;char*out=malloc(cap+1);if(!out){free(compressed);return strdup("");}z_stream stream={0};if(inflateInit2(&stream,15+32)!=Z_OK){free(compressed);free(out);return strdup("");}stream.next_in=compressed;stream.avail_in=(uInt)inlen;int status;do{if(stream.total_out>=cap){if(cap>=GPM_RESPONSE_LIMIT){status=Z_MEM_ERROR;break;}size_t next=cap>GPM_RESPONSE_LIMIT/2?GPM_RESPONSE_LIMIT:cap*2;char*p=realloc(out,next+1);if(!p){status=Z_MEM_ERROR;break;}out=p;cap=next;}stream.next_out=(Bytef*)out+stream.total_out;stream.avail_out=(uInt)(cap-stream.total_out);status=inflate(&stream,Z_NO_FLUSH);}while(status==Z_OK);size_t outlen=stream.total_out;inflateEnd(&stream);free(compressed);if(status!=Z_STREAM_END){free(out);return strdup("");}out[outlen]=0;return out;}
static int gpm_is_json(const char*data){const unsigned char*p=(const unsigned char*)nz(data);while(isspace(*p))p++;return *p=='{'||*p=='[';}
static int gpm_buf_char(char **buffer,size_t *length,size_t *capacity,char c){if(*length+1>=*capacity){size_t next=*capacity?*capacity*2:64;if(next<=*capacity)return 0;char*p=realloc(*buffer,next);if(!p)return 0;*buffer=p;*capacity=next;}(*buffer)[(*length)++]=c;return 1;}
static char *gpm_json_format(const char*data){const char*s=nz(data);size_t len=strlen(s),n=0,cap=0;char*out=NULL;int depth=0,in_string=0,escape=0;for(size_t i=0;i<len;i++){char c=s[i];if(in_string){if(!gpm_buf_char(&out,&n,&cap,c))goto fail;if(escape)escape=0;else if(c=='\\')escape=1;else if(c=='"')in_string=0;continue;}if(c=='"'){in_string=1;if(!gpm_buf_char(&out,&n,&cap,c))goto fail;}else if(c=='{'||c=='['){if(!gpm_buf_char(&out,&n,&cap,c))goto fail;depth++;if(i+1<len&&s[i+1]!=(c=='{'?'}':']')){if(!gpm_buf_char(&out,&n,&cap,'\n'))goto fail;for(int k=0;k<depth;k++)if(!gpm_buf_char(&out,&n,&cap,' '))goto fail;}}else if(c=='}'||c==']'){depth--;if(n&&out[n-1]!='{'&&out[n-1]!='['){if(!gpm_buf_char(&out,&n,&cap,'\n'))goto fail;for(int k=0;k<depth;k++)if(!gpm_buf_char(&out,&n,&cap,' '))goto fail;}if(!gpm_buf_char(&out,&n,&cap,c))goto fail;}else if(c==','){if(!gpm_buf_char(&out,&n,&cap,c)||!gpm_buf_char(&out,&n,&cap,'\n'))goto fail;for(int k=0;k<depth;k++)if(!gpm_buf_char(&out,&n,&cap,' '))goto fail;}else if(c==':'){if(!gpm_buf_char(&out,&n,&cap,':')||!gpm_buf_char(&out,&n,&cap,' '))goto fail;}else if(!isspace((unsigned char)c)&&!gpm_buf_char(&out,&n,&cap,c))goto fail;}if(!gpm_buf_char(&out,&n,&cap,0))goto fail;return out;fail:free(out);return strdup("");}
static int gpm_mkdirs(const char *path){if(!path||!*path)return 0;char *s=strdup(path);if(!s)return 0;for(char*p=s+1;*p;p++)if(*p=='/'){*p=0;if(mkdir(s,0755)&&errno!=EEXIST){free(s);return 0;}*p='/';}int ok=(mkdir(s,0755)==0||errno==EEXIST);free(s);return ok;}
static int unsafe_archive_name(const char *s){if(!s||!*s||*s=='/')return 1;const char*p=s;while(*p){while(*p=='/')p++;const char*b=p;while(*p&&*p!='/')p++;size_t n=(size_t)(p-b);if(n==2&&b[0]=='.'&&b[1]=='.')return 1;}return 0;}
static char *gpm_manifest_files_list(const char *text){char*copy=strdup(nz(text));if(!copy)return strdup("");char section[128]="";char*save=NULL;for(char*line=strtok_r(copy,"\n",&save);line;line=strtok_r(NULL,"\n",&save)){while(isspace((unsigned char)*line))line++;if(*line=='['){char*e=strchr(line,']');if(e){*e=0;snprintf(section,sizeof(section),"%s",line+1);}continue;}if(strcmp(section,"metadata"))continue;char*eq=strchr(line,'=');if(!eq)continue;*eq=0;char*k=line;while(isspace((unsigned char)*k))k++;char*e=k+strlen(k);while(e>k&&isspace((unsigned char)e[-1]))*--e=0;if(!strcmp(k,"files")){char*out=strdup(eq+1);free(copy);return out?out:strdup("");}}free(copy);return strdup("");}
static int gpm_is_cache_path(const char *relative){
    const char *p=nz(relative);
    while(*p){const char *end=strchr(p,'/');size_t n=end?(size_t)(end-p):strlen(p);if(n==11&&!memcmp(p,"__gocache__",11))return 1;if(!end)break;p=end+1;}
    return 0;
}
static int gpm_add_package_path(const char *root,const char *relative,char ***files,size_t *count,size_t *cap){
    if(gpm_is_cache_path(relative))return 1;
    if(unsafe_archive_name(relative)||strchr(relative,'\\'))return 0;
    size_t n=strlen(root)+strlen(relative)+2;char *full=malloc(n);if(!full)return 0;snprintf(full,n,"%s/%s",root,relative);
    struct stat st;if(lstat(full,&st)!=0){free(full);return 0;}
    if(S_ISREG(st.st_mode)){
        if(*count==*cap){size_t next=*cap?*cap*2:32;char **grown=realloc(*files,next*sizeof(char*));if(!grown){free(full);return 0;}*files=grown;*cap=next;}
        (*files)[(*count)++]=strdup(relative);free(full);return (*files)[*count-1]!=NULL;
    }
    if(!S_ISDIR(st.st_mode)){free(full);return 0;}
    DIR *dir=opendir(full);if(!dir){free(full);return 0;}int ok=1;struct dirent *entry;
    while(ok&&(entry=readdir(dir))){if(!strcmp(entry->d_name,".")||!strcmp(entry->d_name,".."))continue;size_t rn=strlen(relative)+strlen(entry->d_name)+2;char *child=malloc(rn);if(!child){ok=0;break;}snprintf(child,rn,"%s/%s",relative,entry->d_name);ok=gpm_add_package_path(root,child,files,count,cap);free(child);}
    closedir(dir);free(full);return ok;
}
static int gpm_archive_extract(const char *archive,const char *dest){
    char *listv[]={"tar","-tf",(char*)nz(archive),NULL};int st=0;char*list=run_capture(listv,&st);if(st||!list){free(list);return 0;}
    char *save=NULL;for(char*line=strtok_r(list,"\n",&save);line;line=strtok_r(NULL,"\n",&save))if(unsafe_archive_name(line)){free(list);return 0;}free(list);if(!gpm_mkdirs(dest))return 0;
    char *argv[]={"tar","-xf",(char*)nz(archive),"-C",(char*)nz(dest),"--no-same-owner","--no-same-permissions",NULL};return run_quiet(argv);
}
static int gpm_archive_build(const char *root,const char *output){
    if(!root||!*root||!output||!*output)return 0;
    size_t mplen=strlen(root)+sizeof("/Manifest.toml");char *manifest_path=malloc(mplen);if(!manifest_path)return 0;snprintf(manifest_path,mplen,"%s/Manifest.toml",root);
    char *manifest=gpm_read_file(manifest_path);free(manifest_path);
    size_t cap=32,count=0;char **files=calloc(cap,sizeof(char*));if(!files){free(manifest);return 0;}
    files[count++]=strdup("Manifest.toml");
    char *f=gpm_manifest_files_list(manifest);
    if(f){char *lb=strchr(f,'['),*rb=lb?strchr(lb,']'):NULL;if(lb&&rb){for(char*p=lb+1;p<rb;){while(p<rb&&(*p==','||isspace((unsigned char)*p)))p++;if(p>=rb)break;if(*p!='\"'&&*p!='\''){free(f);free(manifest);for(size_t i=0;i<count;i++)free(files[i]);free(files);return 0;}char q=*p++;char*e=p;while(e<rb&&*e!=q)e++;if(e==rb)break;char*item=strndup(p,(size_t)(e-p));if(item){size_t item_len=strlen(item);while(item_len>0&&item[item_len-1]=='/')item[--item_len]=0;}if(!item||!gpm_add_package_path(root,item,&files,&count,&cap)){free(item);free(f);free(manifest);for(size_t i=0;i<count;i++)free(files[i]);free(files);return 0;}free(item);p=e+1;}}free(f);}
    char vendor_path[PATH_MAX];
    snprintf(vendor_path,sizeof(vendor_path),"%s/vendor",root);
    struct stat vendor_stat;
    int vendor_listed=0;
    for(size_t i=0;i<count;i++)if(!strcmp(files[i],"vendor"))vendor_listed=1;
    if(!vendor_listed&&stat(vendor_path,&vendor_stat)==0&&S_ISDIR(vendor_stat.st_mode)){
        if(!gpm_add_package_path(root,"vendor",&files,&count,&cap)){free(manifest);for(size_t i=0;i<count;i++)free(files[i]);free(files);return 0;}
    }
    free(manifest);
    /* Without an explicit allowlist, package only root-level Goscript sources and common docs. */
    if(count==1){DIR*d=opendir(root);if(d){struct dirent*e;while((e=readdir(d))){size_t n=strlen(e->d_name);int include=(n>4&&!strcmp(e->d_name+n-4,".gjs"))||!strcmp(e->d_name,"README.md")||!strcmp(e->d_name,"LICENSE");if(!include||unsafe_archive_name(e->d_name))continue;if(count==cap){cap*=2;char**nf=realloc(files,cap*sizeof(char*));if(!nf)break;files=nf;}files[count++]=strdup(e->d_name);}closedir(d);}}
    if(count==1){for(size_t i=0;i<count;i++)free(files[i]);free(files);return 0;}
    size_t argc=count+7;char**argv=calloc(argc,sizeof(char*));if(!argv){for(size_t i=0;i<count;i++)free(files[i]);free(files);return 0;}
    size_t n=0;argv[n++]="tar";argv[n++]="-czf";argv[n++]=(char*)output;argv[n++]="-C";argv[n++]=(char*)root;argv[n++]="--";for(size_t i=0;i<count;i++)argv[n++]=files[i];argv[n]=NULL;
    int ok=run_quiet(argv);free(argv);for(size_t i=0;i<count;i++)free(files[i]);free(files);return ok;
}
static int gpm_remove_tree(const char *path){if(!path||!*path||!strcmp(path,"/")||!strcmp(path,"."))return 0;struct stat st;if(lstat(path,&st)!=0)return errno==ENOENT;if(!S_ISDIR(st.st_mode)||S_ISLNK(st.st_mode))return unlink(path)==0;DIR*d=opendir(path);if(!d)return 0;struct dirent*e;int ok=1;while((e=readdir(d))){if(!strcmp(e->d_name,".")||!strcmp(e->d_name,".."))continue;size_t n=strlen(path)+strlen(e->d_name)+2;char*c=malloc(n);if(!c){ok=0;break;}snprintf(c,n,"%s/%s",path,e->d_name);if(!gpm_remove_tree(c))ok=0;free(c);}closedir(d);return rmdir(path)==0&&ok;}
static char *gpm_home(void){const char*h=getenv("HOME");return strdup(h?h:"");}
static char *gpm_prompt_secret(const char *prompt){
    if(!isatty(STDIN_FILENO))return strdup("");
    fputs(nz(prompt),stderr);fflush(stderr);struct termios oldt,newt;
    if(tcgetattr(STDIN_FILENO,&oldt)!=0)return strdup("");
    newt=oldt;newt.c_lflag&=(tcflag_t)~ECHO;
    if(tcsetattr(STDIN_FILENO,TCSAFLUSH,&newt)!=0)return strdup("");
    size_t cap=256,n=0;char*out=malloc(cap);if(!out){tcsetattr(STDIN_FILENO,TCSAFLUSH,&oldt);return strdup("");}
    int c;while((c=getchar())!=EOF&&c!='\n'&&c!='\r'){if(n+1>=cap){cap*=2;char*x=realloc(out,cap);if(!x)break;out=x;}out[n++]=(char)c;}
    tcsetattr(STDIN_FILENO,TCSAFLUSH,&oldt);fputc('\n',stderr);out[n]=0;return out;
}
static char *gpm_read_file(const char *path){FILE*f=fopen(path,"rb");if(!f)return strdup("");if(fseek(f,0,SEEK_END)){fclose(f);return strdup("");}long z=ftell(f);if(z<0||z>GPM_RESPONSE_LIMIT){fclose(f);return strdup("");}rewind(f);char*b=malloc((size_t)z+1);if(!b){fclose(f);return strdup("");}size_t n=fread(b,1,(size_t)z,f);b[n]=0;fclose(f);return b;}
static int gpm_write_file(const char *path,const char *content){FILE*f=fopen(path,"wb");if(!f)return 0;size_t n=strlen(nz(content));int ok=fwrite(nz(content),1,n,f)==n;if(fclose(f)!=0)ok=0;return ok;}
static int gpm_append_file(const char *path,const char *content){FILE*f=fopen(path,"ab");if(!f)return 0;size_t n=strlen(nz(content));int ok=fwrite(nz(content),1,n,f)==n;if(fclose(f)!=0)ok=0;return ok;}
static int gpm_file_size(const char *path){struct stat st;if(!path||stat(path,&st)!=0||!S_ISREG(st.st_mode)||st.st_size>INT_MAX)return -1;return (int)st.st_size;}
static int gpm_mkdir(const char *path){return gpm_mkdirs(path);}
static int gpm_file_remove(const char *path){return gpm_remove_tree(path);}
static char *gpm_cwd(void){size_t n=256;for(;;){char*b=malloc(n);if(!b)return strdup("");if(getcwd(b,n))return b;free(b);if(errno!=ERANGE||n>1024*1024)return strdup("");n*=2;}}
static char *gpm_env_get(const char *name){const char*v=name&&*name?getenv(name):NULL;return strdup(v?v:"");}
static int gpm_sleep_seconds(int seconds){if(seconds<0)return 0;while(seconds>0){seconds=sleep((unsigned)seconds);}return 1;}
static int gpm_epoch_seconds(void){return (int)time(NULL);}
static char *gpm_time_format(const char *format){time_t now=time(NULL);struct tm tmv;if(!localtime_r(&now,&tmv))return strdup("");char out[256];if(!strftime(out,sizeof(out),nz(format),&tmv))return strdup("");return strdup(out);}
static char *gpm_read_line(void){size_t cap=256,n=0;char*out=malloc(cap);if(!out)return strdup("");int c;while((c=getchar())!=EOF&&c!='\n'&&c!='\r'){if(n+1>=cap){cap*=2;char*p=realloc(out,cap);if(!p){free(out);return strdup("");}out=p;}out[n++]=(char)c;}out[n]=0;return out;}
static int gpm_line_count(const char *path){FILE*f=fopen(nz(path),"rb");if(!f)return 0;int lines=0,c,last='\n';while((c=fgetc(f))!=EOF){if(c=='\n')lines++;last=c;}if(last!='\n')lines++;fclose(f);return lines;}
static char *gpm_config_find(const char *path,const char *search){FILE*f=fopen(nz(path),"rb");if(!f)return strdup("");char*line=NULL;size_t cap=0;char*out=strdup("");while(getline(&line,&cap,f)>=0){if(strstr(line,nz(search))){char*eq=strchr(line,'=');if(eq){eq++;char*end=strpbrk(eq,"\r\n");if(end)*end=0;free(out);out=strdup(eq);break;}}}free(line);fclose(f);return out;}
static char *gpm_kv_get(const char *path,const char *key){FILE*f=fopen(nz(path),"rb");if(!f)return strdup("");char*line=NULL;size_t cap=0;size_t klen=strlen(nz(key));char*out=strdup("");while(getline(&line,&cap,f)>=0){if(!strncmp(line,nz(key),klen)&&line[klen]==':'){char*val=line+klen+1;char*end=strpbrk(val,"\r\n");if(end)*end=0;free(out);out=strdup(val);break;}}free(line);fclose(f);return out;}
static int gpm_kv_exists(const char *path,const char *key){FILE*f=fopen(nz(path),"rb");if(!f)return 0;char*line=NULL;size_t cap=0,klen=strlen(nz(key));int found=0;while(getline(&line,&cap,f)>=0)if(!strncmp(line,nz(key),klen)&&line[klen]==':'){found=1;break;}free(line);fclose(f);return found;}
static int gpm_kv_set(const char *path,const char *key,const char *value){if(!path||!*path||!key||!*key||strchr(key,':')||strchr(key,'\n'))return 0;FILE*in=fopen(path,"rb");size_t plen=strlen(path)+16;char*tmp=malloc(plen);if(!tmp){if(in)fclose(in);return 0;}snprintf(tmp,plen,"%s.tmpXXXXXX",path);int fd=mkstemp(tmp);if(fd<0){free(tmp);if(in)fclose(in);return 0;}FILE*out=fdopen(fd,"wb");if(!out){close(fd);unlink(tmp);free(tmp);if(in)fclose(in);return 0;}char*line=NULL;size_t cap=0,klen=strlen(key);if(in){while(getline(&line,&cap,in)>=0)if(strncmp(line,key,klen)||line[klen]!=':')if(fputs(line,out)==EOF)break;fclose(in);}free(line);int ok=fprintf(out,"%s:%s\n",key,nz(value))>=0;if(fflush(out)!=0)ok=0;if(fsync(fd)!=0)ok=0;if(fclose(out)!=0)ok=0;if(ok)ok=rename(tmp,path)==0;if(!ok)unlink(tmp);free(tmp);return ok;}
static int gpm_kv_delete(const char *path,const char *key){FILE*in=fopen(nz(path),"rb");if(!in)return errno==ENOENT;size_t plen=strlen(path)+16;char*tmp=malloc(plen);if(!tmp){fclose(in);return 0;}snprintf(tmp,plen,"%s.tmpXXXXXX",path);int fd=mkstemp(tmp);if(fd<0){free(tmp);fclose(in);return 0;}FILE*out=fdopen(fd,"wb");if(!out){close(fd);unlink(tmp);free(tmp);fclose(in);return 0;}char*line=NULL;size_t cap=0,klen=strlen(nz(key));int removed=0,ok=1;while(getline(&line,&cap,in)>=0){if(!strncmp(line,nz(key),klen)&&line[klen]==':'){removed=1;continue;}if(fputs(line,out)==EOF)ok=0;}free(line);fclose(in);if(fflush(out)!=0)ok=0;if(fsync(fd)!=0)ok=0;if(fclose(out)!=0)ok=0;if(ok)ok=rename(tmp,path)==0;if(!ok)unlink(tmp);free(tmp);return ok&&removed;}
static int gpm_contains_casefold(const char *text,const char *pattern){if(!*pattern)return 1;size_t n=strlen(pattern);for(const char*p=text;*p;p++)if(!strncasecmp(p,pattern,n))return 1;return 0;}
static char *gpm_kv_search(const char *path,const char *pattern){FILE*f=fopen(nz(path),"rb");if(!f)return strdup("");char*line=NULL;size_t cap=0,outcap=256,len=0;char*out=malloc(outcap);if(!out){fclose(f);return strdup("");}out[0]=0;while(getline(&line,&cap,f)>=0){if(gpm_contains_casefold(line,nz(pattern))){size_t n=strcspn(line,"\r\n");size_t need=len+n+(len?2:1);if(need>outcap){outcap=need*2;char*p=realloc(out,outcap);if(!p)break;out=p;}if(len){out[len++]=',';out[len++]=' ';}memcpy(out+len,line,n);len+=n;out[len]=0;}}free(line);fclose(f);return out;}
static double gpm_math_sqrt(double value){return value<0?NAN:sqrt(value);}
static double gpm_math_pow(double value,double exponent){return pow(value,exponent);}
static double gpm_math_abs(double value){return fabs(value);}
static int gpm_math_round(double value){return (int)llround(value);}
static int gpm_random_int(int upper){if(upper<=0)return 0;return (int)((unsigned)rand()%(unsigned)upper);}
static char *gpm_string_case(const char*s,int upper){s=nz(s);char*out=strdup(s);if(!out)return strdup("");for(unsigned char*p=(unsigned char*)out;*p;p++)*p=(unsigned char)(upper?toupper(*p):tolower(*p));return out;}
static char *gpm_string_trim(const char*s){s=nz(s);while(isspace((unsigned char)*s))s++;size_t n=strlen(s);while(n&&isspace((unsigned char)s[n-1]))n--;return strndup(s,n);}
static int gpm_string_contains(const char*s,const char*sub){return strstr(nz(s),nz(sub))!=NULL;}
static int gpm_string_starts(const char*s,const char*prefix){s=nz(s);prefix=nz(prefix);size_t n=strlen(prefix);return strncmp(s,prefix,n)==0;}
static int gpm_string_ends(const char*s,const char*suffix){s=nz(s);suffix=nz(suffix);size_t n=strlen(s),m=strlen(suffix);return m<=n&&!memcmp(s+n-m,suffix,m);}
static char *gpm_string_slice(const char*s,const char*start,const char*end){s=nz(s);long a=strtol(nz(start),NULL,10),b=strtol(nz(end),NULL,10);size_t n=strlen(s);if(a<1)a=1;if(b<0||a>(long)n||b<a)return strdup("");if(b>(long)n)b=(long)n;return strndup(s+a-1,(size_t)(b-a+1));}
static char *gpm_string_replace(const char*s,const char*old,const char*replacement,int all){s=nz(s);old=nz(old);replacement=nz(replacement);size_t sl=strlen(s),ol=strlen(old),rl=strlen(replacement);if(!ol)return strdup(s);size_t count=0;const char*p=s;while((p=strstr(p,old))){count++;p+=ol;if(!all)break;}if(!count)return strdup(s);size_t outlen;if(rl>=ol){size_t delta=rl-ol;if(delta&&count>(SIZE_MAX-sl-1)/delta)return strdup("");outlen=sl+count*delta;}else outlen=sl-count*(ol-rl);char*out=malloc(outlen+1);if(!out)return strdup("");const char*src=s;char*dst=out;while((p=strstr(src,old))){size_t prefix=(size_t)(p-src);memcpy(dst,src,prefix);dst+=prefix;memcpy(dst,replacement,rl);dst+=rl;src=p+ol;if(!all)break;}size_t tail=strlen(src);memcpy(dst,src,tail);dst[tail]=0;return out;}
static char *gpm_string_reverse(const char*s){s=nz(s);size_t n=strlen(s);char*out=malloc(n+1);if(!out)return strdup("");for(size_t i=0;i<n;i++)out[i]=s[n-i-1];out[n]=0;return out;}
static int gpm_string_count(const char*s,const char*sub){s=nz(s);sub=nz(sub);size_t n=strlen(sub);if(!n)return 0;int count=0;const char*p=s;while((p=strstr(p,sub))){count++;p+=n;}return count;}
static int gpm_is_integer_text(const char*s){s=nz(s);if(*s=='+'||*s=='-')s++;if(!*s)return 0;for(;*s;s++)if(!isdigit((unsigned char)*s))return 0;return 1;}
static int gpm_is_float_text(const char*s){s=nz(s);if(*s=='+'||*s=='-')s++;int digits=0,dot=0;for(;*s;s++){if(isdigit((unsigned char)*s)){digits++;continue;}if(*s=='.'&&!dot){dot=1;continue;}return 0;}return dot&&digits>0;}
static int gpm_random_bytes(unsigned char *out,size_t count){FILE*f=fopen("/dev/urandom","rb");if(f){size_t n=fread(out,1,count,f);fclose(f);if(n==count)return 1;}for(size_t i=0;i<count;i++)out[i]=(unsigned char)(rand()&255);return count>0;}
static char *gpm_random_string(int length){if(length<0||length>4096)return strdup("");static const char alphabet[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";unsigned char*bytes=malloc((size_t)length+1);char*out=malloc((size_t)length+1);if(!bytes||!out){free(bytes);free(out);return strdup("");}gpm_random_bytes(bytes,(size_t)length);for(int i=0;i<length;i++)out[i]=alphabet[bytes[i]%(sizeof(alphabet)-1)];out[length]=0;free(bytes);return out;}
static char *gpm_uuid(void){unsigned char b[16];gpm_random_bytes(b,sizeof(b));b[6]=(unsigned char)((b[6]&0x0f)|0x40);b[8]=(unsigned char)((b[8]&0x3f)|0x80);char*out=malloc(37);if(!out)return strdup("");snprintf(out,37,"%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",b[0],b[1],b[2],b[3],b[4],b[5],b[6],b[7],b[8],b[9],b[10],b[11],b[12],b[13],b[14],b[15]);return out;}
static int gpm_write_secret(const char *path,const char *content){if(!gpm_write_file(path,content))return 0;return chmod(path,0600)==0;}
static int gpm_copy_node(const char *source,const char *destination){
    struct stat st;
    if(lstat(source,&st)!=0||S_ISLNK(st.st_mode))return 0;
    if(S_ISDIR(st.st_mode)){
        if(!gpm_mkdirs(destination))return 0;
        DIR *dir=opendir(source);if(!dir)return 0;
        int ok=1;struct dirent *entry;
        while(ok&&(entry=readdir(dir))){
            if(!strcmp(entry->d_name,".")||!strcmp(entry->d_name,".."))continue;
            size_t src_len=strlen(source)+strlen(entry->d_name)+2;
            size_t dst_len=strlen(destination)+strlen(entry->d_name)+2;
            char *src=malloc(src_len),*dst=malloc(dst_len);
            if(!src||!dst){free(src);free(dst);ok=0;break;}
            snprintf(src,src_len,"%s/%s",source,entry->d_name);
            snprintf(dst,dst_len,"%s/%s",destination,entry->d_name);
            ok=gpm_copy_node(src,dst);free(src);free(dst);
        }
        closedir(dir);return ok;
    }
    if(!S_ISREG(st.st_mode))return 0;
    FILE *in=fopen(source,"rb");if(!in)return 0;
    FILE *out=fopen(destination,"wb");if(!out){fclose(in);return 0;}
    char buffer[16384];int ok=1;size_t count;
    while((count=fread(buffer,1,sizeof(buffer),in))>0)if(fwrite(buffer,1,count,out)!=count){ok=0;break;}
    if(ferror(in))ok=0;
    if(fclose(in)!=0)ok=0;
    if(fclose(out)!=0)ok=0;
    if(ok&&chmod(destination,0644)!=0)ok=0;
    return ok;
}
static int gpm_copy_tree(const char *source,const char *destination){return gpm_copy_node(nz(source),nz(destination));}
static int gpm_make_executable(const char *path){return chmod(nz(path),0755)==0;}
static int gpm_move(const char *from,const char *to){return rename(nz(from),nz(to))==0;}
static int gpm_path_exists(const char *path){struct stat st;return path&&*path&&lstat(path,&st)==0;}
static int gpm_valid_component(const char *s){if(!s||!*s||!strcmp(s,".")||!strcmp(s,".."))return 0;for(const unsigned char*p=(const unsigned char*)s;*p;p++)if(!(isalnum(*p)||*p=='-'||*p=='_'||*p=='.'||*p=='@'))return 0;return 1;}
static char *gpm_manifest_get(const char *path,const char *key){char*data=gpm_read_file(path);char section[128]="";char*save=NULL;for(char*line=strtok_r(data,"\n",&save);line;line=strtok_r(NULL,"\n",&save)){while(isspace((unsigned char)*line))line++;if(*line=='['){char*end=strchr(line,']');if(end){*end=0;snprintf(section,sizeof(section),"%s",line+1);}continue;}if(strcmp(section,"metadata"))continue;char*eq=strchr(line,'=');if(!eq)continue;*eq=0;char*k=line;while(*k&&isspace((unsigned char)*k))k++;char*ke=k+strlen(k);while(ke>k&&isspace((unsigned char)ke[-1]))*--ke=0;if(strcmp(k,key))continue;char*v=eq+1;while(isspace((unsigned char)*v))v++;char*e=v+strlen(v);while(e>v&&isspace((unsigned char)e[-1]))*--e=0;if(e-v>=2&&((*v=='"'&&e[-1]=='"')||(*v=='\''&&e[-1]=='\''))){v++;e[-1]=0;}char*out=strdup(v);free(data);return out;}free(data);return strdup("");}
static char *gpm_manifest_dependencies(const char *path){char*data=gpm_read_file(path);size_t cap=256,len=0;char*out=malloc(cap);if(!out){free(data);return strdup("");}out[0]=0;char section[128]="";char*save=NULL;for(char*line=strtok_r(data,"\n",&save);line;line=strtok_r(NULL,"\n",&save)){while(isspace((unsigned char)*line))line++;if(*line=='['){char*e=strchr(line,']');if(e){*e=0;snprintf(section,sizeof(section),"%s",line+1);}continue;}if(strcmp(section,"dependencies"))continue;char*eq=strchr(line,'=');if(!eq)continue;*eq=0;char*k=line;char*ke=k+strlen(k);while(ke>k&&isspace((unsigned char)ke[-1]))*--ke=0;while(isspace((unsigned char)*k))k++;char*v=eq+1;while(isspace((unsigned char)*v))v++;char*ve=v+strlen(v);while(ve>v&&isspace((unsigned char)ve[-1]))*--ve=0;if(ve-v>=2&&*v=='"'&&ve[-1]=='"'){v++;ve[-1]=0;}size_t add=strlen(k)+strlen(v)+2;if(len+add+1>cap){cap=(len+add+1)*2;char*n=realloc(out,cap);if(!n)break;out=n;}len+=(size_t)snprintf(out+len,cap-len,"%s|%s\n",k,v);}free(data);return out;}
static char *gpm_list_packages(const char *path){DIR*d=opendir(path);if(!d)return strdup("");size_t cap=256,len=0;char*out=malloc(cap);if(!out){closedir(d);return strdup("");}out[0]=0;struct dirent*e;while((e=readdir(d))){if(e->d_name[0]=='.')continue;size_t path_len=strlen(path),name_len=strlen(e->d_name);char*full=malloc(path_len+name_len+2);if(!full)break;snprintf(full,path_len+name_len+2,"%s/%s",path,e->d_name);struct stat st;int is_package=lstat(full,&st)==0&&S_ISDIR(st.st_mode);free(full);if(!is_package)continue;size_t add=name_len+2;if(len+add>cap){cap=(len+add)*2;char*n=realloc(out,cap);if(!n)break;out=n;}len+=(size_t)snprintf(out+len,cap-len,"%s\n",e->d_name);}closedir(d);return out;}
static char *gpm_list_dir(const char *path){DIR*d=opendir(nz(path));if(!d)return strdup("");size_t cap=256,len=0;char*out=malloc(cap);if(!out){closedir(d);return strdup("");}out[0]=0;struct dirent*e;while((e=readdir(d))){if(!strcmp(e->d_name,".")||!strcmp(e->d_name,".."))continue;size_t add=strlen(e->d_name)+(len?2:1);if(len+add>cap){cap=(len+add)*2;char*n=realloc(out,cap);if(!n)break;out=n;}if(len)out[len++]=',';size_t n=strlen(e->d_name);memcpy(out+len,e->d_name,n);len+=n;out[len]=0;}closedir(d);return out;}
static char *gpm_find_executable(const char *name){if(!name||!*name)return strdup("");if(strchr(name,'/'))return access(name,X_OK)==0?strdup(name):strdup("");const char*path=getenv("PATH");if(!path)return strdup("");char*copy=strdup(path);if(!copy)return strdup("");char*save=NULL;for(char*dir=strtok_r(copy,":",&save);dir;dir=strtok_r(NULL,":",&save)){size_t n=strlen(dir)+strlen(name)+2;char*c=malloc(n);if(!c)break;snprintf(c,n,"%s/%s",*dir?dir:".",name);if(access(c,X_OK)==0){free(copy);return c;}free(c);}free(copy);return strdup("");}
static char *gpm_argv(void){size_t cap=256,len=0;char*out=malloc(cap);if(!out)return strdup("");out[0]=0;for(int i=0;i<goscript_argc;i++){const char*a=goscript_argv&&goscript_argv[i]?goscript_argv[i]:"";size_t n=strlen(a)+(i?2:1);if(len+n>=cap){cap=(len+n+1)*2;char*p=realloc(out,cap);if(!p){free(out);return strdup("");}out=p;}if(i){out[len++]=',';out[len++]=' ';}size_t z=strlen(a);memcpy(out+len,a,z);len+=z;out[len]=0;}return out;}
static char *gpm_platform(void){struct utsname u;if(uname(&u)!=0)return strdup("unknown");return strdup(u.sysname);}
static char *gpm_hostname(void){char name[256];if(gethostname(name,sizeof(name))!=0)return strdup("");name[sizeof(name)-1]=0;return strdup(name);}
static char *gpm_kernel_release(void){struct utsname u;if(uname(&u)!=0)return strdup("");return strdup(u.release);}
static char *gpm_architecture(void){struct utsname u;if(uname(&u)!=0)return strdup("");return strdup(u.machine);}
static char *gpm_current_user(void){struct passwd*p=getpwuid(geteuid());return strdup(p?p->pw_name:"");}
static char *gpm_user_id(void){char out[128];snprintf(out,sizeof(out),"uid=%lu gid=%lu",(unsigned long)geteuid(),(unsigned long)getegid());return strdup(out);}
static int gpm_is_root(void){return geteuid()==0;}
static char *gpm_user_groups(void){int n=getgroups(0,NULL);if(n<=0)return strdup("");gid_t*ids=malloc((size_t)n*sizeof(gid_t));if(!ids)return strdup("");n=getgroups(n,ids);size_t cap=128,len=0;char*out=malloc(cap);if(!out){free(ids);return strdup("");}out[0]=0;for(int i=0;i<n;i++){struct group*g=getgrgid(ids[i]);if(!g)continue;size_t z=strlen(g->gr_name);if(len+z+3>cap){cap=(len+z+3)*2;char*p=realloc(out,cap);if(!p)break;out=p;}if(len){out[len++]=',';out[len++]=' ';}memcpy(out+len,g->gr_name,z);len+=z;out[len]=0;}free(ids);return out;}
static char *gpm_user_list(void){FILE*f=fopen("/etc/passwd","rb");if(!f)return strdup("");size_t cap=256,len=0;char*out=malloc(cap);if(!out){fclose(f);return strdup("");}out[0]=0;char*line=NULL;size_t linecap=0;while(getline(&line,&linecap,f)>=0){char*colon=strchr(line,':');if(!colon)continue;size_t z=(size_t)(colon-line);if(len+z+2>cap){cap=(len+z+2)*2;char*p=realloc(out,cap);if(!p)break;out=p;}memcpy(out+len,line,z);len+=z;out[len++]='\n';out[len]=0;}free(line);fclose(f);return out;}
static char *gpm_system_uptime(void){FILE*f=fopen("/proc/uptime","rb");if(!f)return strdup("");char b[128];if(!fgets(b,sizeof(b),f)){fclose(f);return strdup("");}fclose(f);char*space=strchr(b,' ');if(space)*space=0;return strdup(b);}
static char *gpm_temp_dir(void){const char*t=getenv("TMPDIR");return strdup(t&&*t?t:"/tmp");}
static int gpm_process_pid(void){return (int)getpid();}
static int gpm_process_parent_id(void){return (int)getppid();}
static char *gpm_process_list(void){DIR*d=opendir("/proc");if(!d)return strdup("");size_t cap=512,len=0;char*out=malloc(cap);if(!out){closedir(d);return strdup("");}out[0]=0;struct dirent*e;while((e=readdir(d))){if(!isdigit((unsigned char)e->d_name[0]))continue;char path[512];snprintf(path,sizeof(path),"/proc/%s/comm",e->d_name);FILE*f=fopen(path,"rb");char name[256];if(!f)continue;if(!fgets(name,sizeof(name),f)){fclose(f);continue;}fclose(f);size_t z=strcspn(name,"\r\n"),need=strlen(e->d_name)+z+4;if(len+need>=cap){cap=(len+need+1)*2;char*p=realloc(out,cap);if(!p)break;out=p;}len+=(size_t)snprintf(out+len,cap-len,"%s %.*s\n",e->d_name,(int)z,name);}closedir(d);return out;}
static char *gpm_process_run(const char*program){if(!program||!*program)return strdup("");char*argv[]={(char*)program,NULL};int status=0;char*out=run_capture(argv,&status);if(status){free(out);return strdup("");}return out?out:strdup("");}
static int gpm_process_background(const char*program){if(!program||!*program)return 0;pid_t pid=fork();if(pid<0)return 0;if(pid==0){pid_t child=fork();if(child<0)_exit(127);if(child>0)_exit(0);setsid();int fd=open("/dev/null",O_RDWR);if(fd>=0){dup2(fd,STDIN_FILENO);dup2(fd,STDOUT_FILENO);dup2(fd,STDERR_FILENO);if(fd>2)close(fd);}char*argv[]={(char*)program,NULL};execvp(program,argv);_exit(127);}while(waitpid(pid,NULL,0)<0&&errno==EINTR){}return 1;}

void register_gpm_functions(Environment *env){
#define R(name,fn,ret,n,...) register_c_function(env,name,(void*)fn,ret,n,##__VA_ARGS__)
 R("gs_http_post_json",gpm_http_post_json,"string",3,"string","string","string");R("gs_http_post_multipart_file",gpm_http_upload,"int",7,"string","string","string","string","string","string","string");
 R("gs_json_quote",gpm_json_quote,"string",1,"string");R("gs_archive_build",gpm_archive_build,"int",2,"string","string");R("gs_manifest_get",gpm_manifest_get,"string",2,"string","string");R("gs_manifest_dependencies",gpm_manifest_dependencies,"string",1,"string");
 R("gs_fs_copy_tree",gpm_copy_tree,"int",2,"string","string");R("gs_fs_executable",gpm_make_executable,"int",1,"string");R("gs_fs_move",gpm_move,"int",2,"string","string");R("gs_fs_valid_component",gpm_valid_component,"int",1,"string");R("gs_fs_write_private",gpm_write_secret,"int",2,"string","string");R("gs_fs_list_dirs",gpm_list_packages,"string",1,"string");R("gs_prompt_secret",gpm_prompt_secret,"string",1,"string");
 R("gpm_http_get",gpm_http_get,"string",2,"string","string");R("gpm_http_get_response",gpm_http_get_response,"string",2,"string","string");R("gpm_http_post_json",gpm_http_post_json,"string",3,"string","string","string");
 R("gpm_http_download",gpm_http_download,"int",3,"string","string","string");R("gpm_http_upload",gpm_http_upload,"int",7,"string","string","string","string","string","string","string");
 R("gpm_json_get",gpm_json_get,"string",2,"string","string");R("gpm_json_array_item",gpm_json_array_item,"string",3,"string","string","int");R("gpm_sha256_file",gpm_sha256_file,"string",1,"string");R("gpm_archive_extract",gpm_archive_extract,"int",2,"string","string");R("gpm_archive_build",gpm_archive_build,"int",2,"string","string");
 R("gpm_mkdirs",gpm_mkdirs,"int",1,"string");R("gpm_remove_tree",gpm_remove_tree,"int",1,"string");R("gpm_home",gpm_home,"string",0);R("gpm_read_file",gpm_read_file,"string",1,"string");R("gpm_write_file",gpm_write_file,"int",2,"string","string");
 R("gpm_move",gpm_move,"int",2,"string","string");R("gpm_valid_component",gpm_valid_component,"int",1,"string");R("gpm_manifest_get",gpm_manifest_get,"string",2,"string","string");
 R("gpm_path_exists",gpm_path_exists,"int",1,"string");
 R("gpm_prompt_secret",gpm_prompt_secret,"string",1,"string");
 R("gpm_manifest_dependencies",gpm_manifest_dependencies,"string",1,"string");R("gpm_list_packages",gpm_list_packages,"string",1,"string");
 R("gpm_json_quote",gpm_json_quote,"string",1,"string");
 R("gpm_url_encode",gpm_url_encode,"string",1,"string");
 R("gpm_tui_repeat",gpm_tui_repeat,"string",2,"string","int");R("gpm_tui_width",gpm_tui_width,"int",0);R("gpm_tui_rgb",gpm_tui_rgb,"string",4,"int","int","int","string");R("gpm_tui_bg_rgb",gpm_tui_bg_rgb,"string",4,"int","int","int","string");R("gpm_tui_truncate",gpm_tui_truncate,"string",2,"string","int");R("gpm_tui_color_enabled",gpm_tui_color_enabled,"int",1,"int");
 R("gpm_tui_number",gpm_tui_number,"string",1,"int");
 R("curse_host_raw",curse_terminal_raw,"int",1,"int");R("curse_host_start",curse_terminal_start,"int",0);R("curse_host_stop",curse_terminal_stop,"int",0);R("curse_host_read_byte",curse_terminal_read_byte,"int",1,"int");R("curse_host_read_utf8_char",curse_terminal_read_utf8_char,"string",2,"int","int");R("curse_host_monotonic_ms",curse_terminal_monotonic_ms,"int",0);R("curse_host_write_frame",curse_terminal_write_frame,"int",1,"string");R("curse_host_take_resize",curse_terminal_take_resize,"int",0);R("curse_host_width",curse_terminal_width,"int",0);R("curse_host_height",curse_terminal_height,"int",0);R("curse_host_capability",curse_terminal_capability,"int",1,"int");R("curse_host_utf8_length",curse_terminal_utf8_length,"int",2,"string","int");R("curse_host_unicode_width",curse_terminal_unicode_width,"int",2,"string","int");R("curse_host_flush",curse_terminal_flush,"int",0);
 R("gpm_write_secret",gpm_write_secret,"int",2,"string","string");
 R("gs_fs_read",gpm_read_file,"string",1,"string");R("gs_fs_write",gpm_write_file,"int",2,"string","string");R("gs_fs_append",gpm_append_file,"int",2,"string","string");
 R("gs_fs_exists",gpm_path_exists,"int",1,"string");R("gs_fs_size",gpm_file_size,"int",1,"string");R("gs_fs_mkdir",gpm_mkdir,"int",1,"string");R("gs_fs_remove",gpm_file_remove,"int",1,"string");
 R("gs_fs_list_dir",gpm_list_dir,"string",1,"string");R("gs_which",gpm_find_executable,"string",1,"string");R("gs_file_line_count",gpm_line_count,"int",1,"string");R("gs_config_find",gpm_config_find,"string",2,"string","string");
 R("gs_kv_get",gpm_kv_get,"string",2,"string","string");R("gs_kv_exists",gpm_kv_exists,"int",2,"string","string");R("gs_kv_set",gpm_kv_set,"int",3,"string","string","string");R("gs_kv_delete",gpm_kv_delete,"int",2,"string","string");R("gs_kv_count",gpm_line_count,"int",1,"string");R("gs_kv_search",gpm_kv_search,"string",2,"string","string");
 R("gs_cwd",gpm_cwd,"string",0);R("gs_env_get",gpm_env_get,"string",1,"string");R("gs_time_epoch",gpm_epoch_seconds,"int",0);R("gs_time_format",gpm_time_format,"string",1,"string");R("gs_sleep",gpm_sleep_seconds,"int",1,"int");R("gs_read_line",gpm_read_line,"string",0);
 R("gs_math_sqrt",gpm_math_sqrt,"double",1,"double");R("gs_math_pow",gpm_math_pow,"double",2,"double","double");R("gs_math_abs",gpm_math_abs,"double",1,"double");R("gs_math_round",gpm_math_round,"int",1,"double");R("gs_random_int",gpm_random_int,"int",1,"int");
 R("gs_random_string",gpm_random_string,"string",1,"int");R("gs_uuid",gpm_uuid,"string",0);
 R("gs_string_upper",gpm_string_case,"string",2,"string","int");R("gs_string_lower",gpm_string_case,"string",2,"string","int");
 R("gs_string_trim",gpm_string_trim,"string",1,"string");R("gs_string_contains",gpm_string_contains,"int",2,"string","string");R("gs_string_starts",gpm_string_starts,"int",2,"string","string");R("gs_string_ends",gpm_string_ends,"int",2,"string","string");
 R("gs_string_slice",gpm_string_slice,"string",3,"string","string","string");R("gs_string_replace_first",gpm_string_replace,"string",4,"string","string","string","int");R("gs_string_replace_all",gpm_string_replace,"string",4,"string","string","string","int");R("gs_string_reverse",gpm_string_reverse,"string",1,"string");R("gs_string_count",gpm_string_count,"int",2,"string","string");
 R("gs_is_integer_text",gpm_is_integer_text,"int",1,"string");R("gs_is_float_text",gpm_is_float_text,"int",1,"string");
 R("gs_base64_encode",gpm_base64_encode,"string",1,"string");R("gs_base64_decode",gpm_base64_decode,"string",1,"string");
 R("gs_gzip_compress",gpm_gzip_compress,"string",1,"string");R("gs_gzip_decompress",gpm_gzip_decompress,"string",1,"string");R("gs_json_is",gpm_is_json,"int",1,"string");R("gs_json_format",gpm_json_format,"string",1,"string");R("gs_json_get",gpm_json_get,"string",2,"string","string");
 R("gs_hash_data",gpm_hash_data,"string",2,"string","string");R("gs_hash_file",gpm_hash_file,"string",2,"string","string");
 R("gs_http_get",gpm_http_get_public,"string",1,"string");R("gs_http_get_headers",gpm_http_get_headers,"string",2,"string","string");R("gs_http_get_timeout",gpm_http_get_timeout,"string",2,"string","int");R("gs_http_post",gpm_http_post_public,"string",2,"string","string");R("gs_http_post_auth",gpm_http_post_auth,"string",4,"string","string","string","string");R("gs_http_post_form",gpm_http_post_form,"string",2,"string","string");R("gs_http_post_file",gpm_http_post_file,"string",2,"string","string");
 R("gs_http_request",gpm_http_request,"string",3,"string","string","string");R("gs_http_get_auth",gpm_http_get_auth,"string",3,"string","string","string");R("gs_http_get_proxy",gpm_http_get_proxy,"string",2,"string","string");R("gs_http_get_no_follow",gpm_http_get_no_follow,"string",1,"string");R("gs_http_cookie_request",gpm_http_cookie_request,"string",3,"string","string","int");
 R("gs_http_download",gpm_http_download,"int",3,"string","string","string");
 R("gs_tar_pack",gpm_tar_pack,"int",2,"string","string");R("gs_tar_unpack",gpm_tar_unpack,"int",2,"string","string");
 R("gs_argv",gpm_argv,"string",0);R("gs_platform",gpm_platform,"string",0);R("gs_hostname",gpm_hostname,"string",0);
 R("gs_kernel_release",gpm_kernel_release,"string",0);R("gs_architecture",gpm_architecture,"string",0);R("gs_current_user",gpm_current_user,"string",0);R("gs_user_id",gpm_user_id,"string",0);R("gs_user_groups",gpm_user_groups,"string",0);R("gs_users_list",gpm_user_list,"string",0);R("gs_is_root",gpm_is_root,"int",0);R("gs_system_uptime",gpm_system_uptime,"string",0);R("gs_temp_dir",gpm_temp_dir,"string",0);
 R("gs_process_pid",gpm_process_pid,"int",0);R("gs_process_parent_id",gpm_process_parent_id,"int",0);R("gs_process_list",gpm_process_list,"string",0);R("gs_process_run",gpm_process_run,"string",1,"string");R("gs_process_background",gpm_process_background,"int",1,"string");
#undef R
}
