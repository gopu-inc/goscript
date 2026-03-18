#include "common.h"
#include "lexer.h"

typedef struct {
    const char* start;
    const char* current;
    int line;
} Lexer;

static Lexer scanner;

void init_lexer(const char* source) {
    scanner.start = source;
    scanner.current = source;
    scanner.line = 1;
}

static bool is_at_end() {
    return *scanner.current == '\0';
}

static Token make_token(TokenType type) {
    Token token;
    token.type = type;
    token.start = scanner.start;
    token.length = (int)(scanner.current - scanner.start);
    token.line = scanner.line;
    return token;
}

static Token error_token(const char* message) {
    Token token;
    token.type = TOKEN_ERROR;
    token.start = message;
    token.length = (int)strlen(message);
    token.line = scanner.line;
    return token;
}

static char advance() {
    scanner.current++;
    return scanner.current[-1];
}

static char peek() {
    return *scanner.current;
}

static char peek_next() {
    if (is_at_end()) return '\0';
    return scanner.current[1];
}

static bool match(char expected) {
    if (is_at_end()) return false;
    if (*scanner.current != expected) return false;
    scanner.current++;
    return true;
}

static void skip_whitespace() {
    for (;;) {
        char c = peek();
        switch (c) {
            case ' ':
            case '\r':
            case '\t':
                advance();
                break;
            case '\n':
                scanner.line++;
                advance();
                break;
            case '/':
                if (peek_next() == '/') {
                    // Commentaire jusqu'à la fin de la ligne
                    while (peek() != '\n' && !is_at_end()) advance();
                } else {
                    return;
                }
                break;
            default:
                return;
        }
    }
}

static TokenType check_keyword(int start, int length, const char* rest, TokenType type) {
    if (scanner.current - scanner.start == start + length &&
        memcmp(scanner.start + start, rest, length) == 0) {
        return type;
    }
    return TOKEN_IDENTIFIER;
}

static TokenType identifier_type() {
    switch (scanner.start[0]) {
        case 'a':
            if (scanner.current - scanner.start > 1) {
                switch (scanner.start[1]) {
                    case 's': return check_keyword(2, 4, "sync", TOKEN_ASYNC);
                    case 'w': return check_keyword(2, 4, "ait", TOKEN_AWAIT);
                }
            }
            break;
        case 'c':
            if (scanner.current - scanner.start > 1) {
                switch (scanner.start[1]) {
                    case 'l': return check_keyword(2, 3, "ass", TOKEN_CLASS);
                    case 'o': {
                        if (scanner.current - scanner.start > 2) {
                            switch (scanner.start[2]) {
                                case 'n': return check_keyword(3, 3, "st", TOKEN_CONST);
                            }
                        }
                        break;
                    }
                }
            }
            break;
        case 'e':
            if (scanner.current - scanner.start > 1) {
                switch (scanner.start[1]) {
                    case 'l': return check_keyword(2, 2, "se", TOKEN_ELSE);
                    case 'n': return check_keyword(2, 2, "um", TOKEN_ENUM);
                }
            }
            break;
        case 'f':
            if (scanner.current - scanner.start > 1) {
                switch (scanner.start[1]) {
                    case 'n': return check_keyword(2, 0, "", TOKEN_FN);
                    case 'o': return check_keyword(2, 1, "r", TOKEN_FOR);
                }
            }
            break;
        case 'g': return check_keyword(1, 4, "etlf", TOKEN_GETLF);
        case 'i':
            if (scanner.current - scanner.start > 1) {
                switch (scanner.start[1]) {
                    case 'f': return check_keyword(2, 0, "", TOKEN_IF);
                    case 'n': return check_keyword(2, 3, "put", TOKEN_INPUT);
                }
            }
            break;
        case 'l': return check_keyword(1, 2, "et", TOKEN_LET);
        case 'p': return check_keyword(1, 4, "rint", TOKEN_PRINT);
        case 'r': return check_keyword(1, 5, "eturn", TOKEN_RETURN);
        case 'u': return check_keyword(1, 2, "se", TOKEN_USE);
        case 'w': return check_keyword(1, 4, "hile", TOKEN_WHILE);
    }
    return TOKEN_IDENTIFIER;
}

static Token identifier() {
    while (isalnum(peek()) || peek() == '_') advance();
    return make_token(identifier_type());
}

static Token number() {
    while (isdigit(peek())) advance();
    
    // Partie fractionnaire
    if (peek() == '.' && isdigit(peek_next())) {
        advance();
        while (isdigit(peek())) advance();
    }
    
    return make_token(TOKEN_NUMBER);
}

static Token string() {
    while (peek() != '"' && !is_at_end()) {
        if (peek() == '\n') scanner.line++;
        advance();
    }
    
    if (is_at_end()) return error_token("Chaîne non terminée");
    
    // Le guillemet fermant
    advance();
    return make_token(TOKEN_STRING);
}

Token scan_token() {
    skip_whitespace();
    scanner.start = scanner.current;
    
    if (is_at_end()) return make_token(TOKEN_EOF);
    
    char c = advance();
    
    if (isalpha(c) || c == '_') return identifier();
    if (isdigit(c)) return number();
    
    switch (c) {
        case '(': return make_token(TOKEN_LPAREN);
        case ')': return make_token(TOKEN_RPAREN);
        case '{': return make_token(TOKEN_LBRACE);
        case '}': return make_token(TOKEN_RBRACE);
        case '[': return make_token(TOKEN_LBRACKET);
        case ']': return make_token(TOKEN_RBRACKET);
        case ';': return make_token(TOKEN_SEMICOLON);
        case ',': return make_token(TOKEN_COMMA);
        case '.': return make_token(TOKEN_DOT);
        case ':': return make_token(TOKEN_COLON);
        case '+': return make_token(TOKEN_PLUS);
        case '-': return make_token(TOKEN_MINUS);
        case '*': return make_token(TOKEN_STAR);
        case '/': return make_token(TOKEN_SLASH);
        case '!': return make_token(match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
        case '=': return make_token(match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
        case '<': return make_token(match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
        case '>': return make_token(match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
        case '"': {
            Token str = string();
            // Enlève les guillemets pour le stockage
            str.start++;
            str.length -= 2;
            return str;
        }
    }
    
    return error_token("Caractère inattendu");
}
