/* Safe process and filesystem primitives used by the Goscript package manager. */
#define _POSIX_C_SOURCE 200809L
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

#define GPM_RESPONSE_LIMIT (16u * 1024u * 1024u)
static char *gpm_read_file(const char *path);

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

static char *gpm_http_get(const char *url, const char *token) {
    char *argv[12]; int n=0; argv[n++]="curl"; argv[n++]="--fail"; argv[n++]="--silent"; argv[n++]="--show-error"; argv[n++]="--location"; argv[n++]="--max-time"; argv[n++]="60";
    char auth[4096]; if (token && *token) { snprintf(auth,sizeof(auth),"Authorization: Bearer %s",token); argv[n++]="--header"; argv[n++]=auth; }
    argv[n++]=(char*)nz(url); argv[n]=NULL; int status=0; char *body=run_capture(argv,&status); if(status!=0){free(body);return strdup("");} return body?body:strdup("");
}
static char *gpm_http_post_json(const char *url,const char *body,const char *token) {
    char *argv[14]; int n=0; char auth[4096]; argv[n++]="curl";argv[n++]="--fail";argv[n++]="--silent";argv[n++]="--show-error";argv[n++]="--location";argv[n++]="--max-time";argv[n++]="60";argv[n++]="--header";argv[n++]="Content-Type: application/json";
    if(token&&*token){snprintf(auth,sizeof(auth),"Authorization: Bearer %s",token);argv[n++]="--header";argv[n++]=auth;}
    argv[n++]="--data-binary";argv[n++]=(char*)nz(body);argv[n++]=(char*)nz(url);argv[n]=NULL;int status=0;char*out=run_capture(argv,&status);if(status){free(out);return strdup("");}return out?out:strdup("");
}
static int gpm_http_download(const char *url,const char *path,const char *token) {
    char *argv[14];int n=0;char auth[4096];argv[n++]="curl";argv[n++]="--fail";argv[n++]="--silent";argv[n++]="--show-error";argv[n++]="--location";argv[n++]="--max-time";argv[n++]="300";if(token&&*token){snprintf(auth,sizeof(auth),"Authorization: Bearer %s",token);argv[n++]="--header";argv[n++]=auth;}argv[n++]="--output";argv[n++]=(char*)nz(path);argv[n++]=(char*)nz(url);argv[n]=NULL;return run_quiet(argv);
}
static int gpm_http_upload(const char *url,const char *path,const char *filename,const char *token,const char *version,const char *release,const char *arch) {
    char *argv[24];int n=0;char auth[4096],filearg[8192],varg[4096],rarg[4096],aarg[4096];argv[n++]="curl";argv[n++]="--fail";argv[n++]="--silent";argv[n++]="--show-error";argv[n++]="--location";argv[n++]="--max-time";argv[n++]="600";
    if(token&&*token){snprintf(auth,sizeof(auth),"Authorization: Bearer %s",token);argv[n++]="--header";argv[n++]=auth;}
    snprintf(filearg,sizeof(filearg),"file=@%s;filename=%s",nz(path),nz(filename));snprintf(varg,sizeof(varg),"version=%s",nz(version));snprintf(rarg,sizeof(rarg),"release=%s",nz(release));snprintf(aarg,sizeof(aarg),"arch=%s",nz(arch));
    argv[n++]="--form";argv[n++]=filearg;argv[n++]="--form";argv[n++]=varg;argv[n++]="--form";argv[n++]=rarg;argv[n++]="--form";argv[n++]=aarg;argv[n++]=(char*)nz(url);argv[n]=NULL;return run_quiet(argv);
}
static char *gpm_json_get(const char *json,const char *key) {
    if(!json||!key)return strdup("");
    size_t kl=strlen(key);const char*p=json;
    while((p=strchr(p,'"'))){p++;if(strncmp(p,key,kl)==0&&p[kl]=='"'){const char*q=p+kl+1;while(isspace((unsigned char)*q))q++;if(*q!=':'){continue;}q++;while(isspace((unsigned char)*q))q++;if(*q=='"'){q++;size_t cap=strlen(q)+1;char*out=malloc(cap);if(!out)return strdup("");size_t i=0;while(*q&&*q!='"'){if(*q=='\\'&&q[1]){q++;switch(*q){case 'n':out[i++]='\n';break;case 'r':out[i++]='\r';break;case 't':out[i++]='\t';break;default:out[i++]=*q;}}else out[i++]=*q;q++;}out[i]=0;return out;}const char*e=q;while(*e&&*e!=','&&*e!='}'&&!isspace((unsigned char)*e))e++;return strndup(q,(size_t)(e-q));} }
    return strdup("");
}
static char *gpm_json_quote(const char *s){const unsigned char*p=(const unsigned char*)nz(s);size_t cap=strlen((const char*)p)*6+3;char*out=malloc(cap);if(!out)return strdup("\"\"");size_t n=0;out[n++]='"';for(;*p;p++){if(*p=='"'||*p=='\\'){out[n++]='\\';out[n++]=(char)*p;}else if(*p=='\n'){out[n++]='\\';out[n++]='n';}else if(*p=='\r'){out[n++]='\\';out[n++]='r';}else if(*p=='\t'){out[n++]='\\';out[n++]='t';}else if(*p<32){n+=(size_t)snprintf(out+n,cap-n,"\\u%04x",*p);}else out[n++]=(char)*p;}out[n++]='"';out[n]=0;return out;}
static char *gpm_sha256_file(const char *path){char *argv[]={"sha256sum","--",(char*)nz(path),NULL};int st=0;char*out=run_capture(argv,&st);if(st||!out){free(out);return strdup("");}char*sp=strchr(out,' ');if(sp)*sp=0;return out;}
static int gpm_mkdirs(const char *path){if(!path||!*path)return 0;char *s=strdup(path);if(!s)return 0;for(char*p=s+1;*p;p++)if(*p=='/'){*p=0;if(mkdir(s,0755)&&errno!=EEXIST){free(s);return 0;}*p='/';}int ok=(mkdir(s,0755)==0||errno==EEXIST);free(s);return ok;}
static int unsafe_archive_name(const char *s){if(!s||!*s||*s=='/')return 1;const char*p=s;while(*p){while(*p=='/')p++;const char*b=p;while(*p&&*p!='/')p++;size_t n=(size_t)(p-b);if(n==2&&b[0]=='.'&&b[1]=='.')return 1;}return 0;}
static char *gpm_manifest_files_list(const char *text){char*copy=strdup(nz(text));if(!copy)return strdup("");char section[128]="";char*save=NULL;for(char*line=strtok_r(copy,"\n",&save);line;line=strtok_r(NULL,"\n",&save)){while(isspace((unsigned char)*line))line++;if(*line=='['){char*e=strchr(line,']');if(e){*e=0;snprintf(section,sizeof(section),"%s",line+1);}continue;}if(strcmp(section,"metadata"))continue;char*eq=strchr(line,'=');if(!eq)continue;*eq=0;char*k=line;while(isspace((unsigned char)*k))k++;char*e=k+strlen(k);while(e>k&&isspace((unsigned char)e[-1]))*--e=0;if(!strcmp(k,"files")){char*out=strdup(eq+1);free(copy);return out?out:strdup("");}}free(copy);return strdup("");}
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
    if(f){char *lb=strchr(f,'['),*rb=lb?strchr(lb,']'):NULL;if(lb&&rb){for(char*p=lb+1;p<rb;){while(p<rb&&(*p==','||isspace((unsigned char)*p)))p++;if(p>=rb)break;if(*p!='\"'&&*p!='\''){free(f);free(manifest);for(size_t i=0;i<count;i++)free(files[i]);free(files);return 0;}char q=*p++;char*e=p;while(e<rb&&*e!=q)e++;if(e==rb)break;char*item=strndup(p,(size_t)(e-p));if(unsafe_archive_name(item)||strchr(item,'\\')){free(item);free(f);free(manifest);for(size_t i=0;i<count;i++)free(files[i]);free(files);return 0;}size_t plen=strlen(root)+strlen(item)+2;char*full=malloc(plen);if(!full){free(item);break;}snprintf(full,plen,"%s/%s",root,item);struct stat fst;int regular=lstat(full,&fst)==0&&S_ISREG(fst.st_mode);free(full);if(!regular){free(item);free(f);free(manifest);for(size_t i=0;i<count;i++)free(files[i]);free(files);return 0;}if(count==cap){cap*=2;char**nf=realloc(files,cap*sizeof(char*));if(!nf){free(item);break;}files=nf;}files[count++]=item;p=e+1;}}free(f);}
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
static int gpm_write_secret(const char *path,const char *content){if(!gpm_write_file(path,content))return 0;return chmod(path,0600)==0;}
static int gpm_move(const char *from,const char *to){return rename(nz(from),nz(to))==0;}
static int gpm_path_exists(const char *path){struct stat st;return path&&*path&&lstat(path,&st)==0;}
static int gpm_valid_component(const char *s){if(!s||!*s||!strcmp(s,".")||!strcmp(s,".."))return 0;for(const unsigned char*p=(const unsigned char*)s;*p;p++)if(!(isalnum(*p)||*p=='-'||*p=='_'||*p=='.'||*p=='@'))return 0;return 1;}
static char *gpm_manifest_get(const char *path,const char *key){char*data=gpm_read_file(path);char section[128]="";char*save=NULL;for(char*line=strtok_r(data,"\n",&save);line;line=strtok_r(NULL,"\n",&save)){while(isspace((unsigned char)*line))line++;if(*line=='['){char*end=strchr(line,']');if(end){*end=0;snprintf(section,sizeof(section),"%s",line+1);}continue;}if(strcmp(section,"metadata"))continue;char*eq=strchr(line,'=');if(!eq)continue;*eq=0;char*k=line;while(*k&&isspace((unsigned char)*k))k++;char*ke=k+strlen(k);while(ke>k&&isspace((unsigned char)ke[-1]))*--ke=0;if(strcmp(k,key))continue;char*v=eq+1;while(isspace((unsigned char)*v))v++;char*e=v+strlen(v);while(e>v&&isspace((unsigned char)e[-1]))*--e=0;if(e-v>=2&&((*v=='"'&&e[-1]=='"')||(*v=='\''&&e[-1]=='\''))){v++;e[-1]=0;}char*out=strdup(v);free(data);return out;}free(data);return strdup("");}
static char *gpm_manifest_dependencies(const char *path){char*data=gpm_read_file(path);size_t cap=256,len=0;char*out=malloc(cap);if(!out){free(data);return strdup("");}out[0]=0;char section[128]="";char*save=NULL;for(char*line=strtok_r(data,"\n",&save);line;line=strtok_r(NULL,"\n",&save)){while(isspace((unsigned char)*line))line++;if(*line=='['){char*e=strchr(line,']');if(e){*e=0;snprintf(section,sizeof(section),"%s",line+1);}continue;}if(strcmp(section,"dependencies"))continue;char*eq=strchr(line,'=');if(!eq)continue;*eq=0;char*k=line;char*ke=k+strlen(k);while(ke>k&&isspace((unsigned char)ke[-1]))*--ke=0;while(isspace((unsigned char)*k))k++;char*v=eq+1;while(isspace((unsigned char)*v))v++;char*ve=v+strlen(v);while(ve>v&&isspace((unsigned char)ve[-1]))*--ve=0;if(ve-v>=2&&*v=='"'&&ve[-1]=='"'){v++;ve[-1]=0;}size_t add=strlen(k)+strlen(v)+2;if(len+add+1>cap){cap=(len+add+1)*2;char*n=realloc(out,cap);if(!n)break;out=n;}len+=(size_t)snprintf(out+len,cap-len,"%s|%s\n",k,v);}free(data);return out;}
static char *gpm_list_packages(const char *path){DIR*d=opendir(path);if(!d)return strdup("");size_t cap=256,len=0;char*out=malloc(cap);if(!out){closedir(d);return strdup("");}out[0]=0;struct dirent*e;while((e=readdir(d))){if(e->d_name[0]=='.')continue;size_t add=strlen(e->d_name)+2;if(len+add>cap){cap=(len+add)*2;char*n=realloc(out,cap);if(!n)break;out=n;}len+=(size_t)snprintf(out+len,cap-len,"%s\n",e->d_name);}closedir(d);return out;}

void register_gpm_functions(Environment *env){
#define R(name,fn,ret,n,...) register_c_function(env,name,(void*)fn,ret,n,##__VA_ARGS__)
 R("gpm_http_get",gpm_http_get,"string",2,"string","string");R("gpm_http_post_json",gpm_http_post_json,"string",3,"string","string","string");
 R("gpm_http_download",gpm_http_download,"int",3,"string","string","string");R("gpm_http_upload",gpm_http_upload,"int",7,"string","string","string","string","string","string","string");
 R("gpm_json_get",gpm_json_get,"string",2,"string","string");R("gpm_sha256_file",gpm_sha256_file,"string",1,"string");R("gpm_archive_extract",gpm_archive_extract,"int",2,"string","string");R("gpm_archive_build",gpm_archive_build,"int",2,"string","string");
 R("gpm_mkdirs",gpm_mkdirs,"int",1,"string");R("gpm_remove_tree",gpm_remove_tree,"int",1,"string");R("gpm_home",gpm_home,"string",0);R("gpm_read_file",gpm_read_file,"string",1,"string");R("gpm_write_file",gpm_write_file,"int",2,"string","string");
 R("gpm_move",gpm_move,"int",2,"string","string");R("gpm_valid_component",gpm_valid_component,"int",1,"string");R("gpm_manifest_get",gpm_manifest_get,"string",2,"string","string");
 R("gpm_path_exists",gpm_path_exists,"int",1,"string");
 R("gpm_prompt_secret",gpm_prompt_secret,"string",1,"string");
 R("gpm_manifest_dependencies",gpm_manifest_dependencies,"string",1,"string");R("gpm_list_packages",gpm_list_packages,"string",1,"string");
 R("gpm_json_quote",gpm_json_quote,"string",1,"string");
 R("gpm_write_secret",gpm_write_secret,"int",2,"string","string");
#undef R
}
