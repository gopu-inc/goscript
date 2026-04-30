


CC = gcc
CFLAGS = -Wall -g -O0 -I./src -I./src/ast -I./src/interpreter
LDFLAGS = -lm -ldl -lffi

# Détection automatique de l'architecture
UNAME_S := $(shell uname -s)
UNAME_M := $(shell uname -m)

# Pas de -march par défaut, on laisse gcc choisir
ifeq ($(UNAME_S),Linux)
    ifeq ($(UNAME_M),x86_64)
        MARCH = -march=x86-64
    else ifeq ($(UNAME_M),i686)
        MARCH = -march=i686
    else ifeq ($(UNAME_M),i586)
        MARCH = -march=i586
    else ifeq ($(UNAME_M),aarch64)
        MARCH = -march=armv8-a
    else ifeq ($(UNAME_M),armv7l)
        MARCH = -march=armv7-a
    else ifeq ($(UNAME_M),armv8l)
        MARCH = -march=armv8-a
    else
        MARCH =
    endif
else ifeq ($(UNAME_S),Darwin)
    ifeq ($(UNAME_M),arm64)
        MARCH = -arch arm64
    else
        MARCH = -arch x86_64
    endif
else
    MARCH =
endif

# Ajouter MARCH aux CFLAGS s'il est défini
ifneq ($(MARCH),)
    CFLAGS += $(MARCH)
endif

# Sources
SCANNER_C = scanner.c
PARSER_C = parser.c
PARSER_H = parser.h

SOURCES = $(SCANNER_C) $(PARSER_C) \
          src/ast/ast.c \
          src/main.c \
          src/interpreter/interpreter_env.c \
          src/interpreter/interpreter_import.c \
          src/interpreter/interpreter_ffi.c \
          src/interpreter/interpreter_eval.c

OBJECTS = scanner.o parser.o ast.o main.o \
          interpreter_env.o interpreter_import.o \
          interpreter_ffi.o interpreter_eval.o

TARGET = gd

all: $(SCANNER_C) $(PARSER_C) $(TARGET)

# Scanner - avec suppression du warning de règle non matchée
$(SCANNER_C): src/lexer/scanner.l
	flex -o $(SCANNER_C) src/lexer/scanner.l 2>&1 | grep -v "warning, rule cannot be matched" || true

# Parser - avec gestion des conflits (acceptable pour l'instant)
$(PARSER_C) $(PARSER_H): src/parser/parser.y
	bison -d -o $(PARSER_C) src/parser/parser.y

# AST
ast.o: src/ast/ast.c src/ast/ast.h
	$(CC) $(CFLAGS) -c src/ast/ast.c -o ast.o

# Main
main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o main.o

# Interpreter
interpreter_env.o: src/interpreter/interpreter_env.c src/interpreter/interpreter.h
	$(CC) $(CFLAGS) -c src/interpreter/interpreter_env.c -o interpreter_env.o

interpreter_import.o: src/interpreter/interpreter_import.c src/interpreter/interpreter.h
	$(CC) $(CFLAGS) -c src/interpreter/interpreter_import.c -o interpreter_import.o

interpreter_ffi.o: src/interpreter/interpreter_ffi.c src/interpreter/interpreter.h
	$(CC) $(CFLAGS) -c src/interpreter/interpreter_ffi.c -o interpreter_ffi.o

interpreter_eval.o: src/interpreter/interpreter_eval.c src/interpreter/interpreter.h
	$(CC) $(CFLAGS) -c src/interpreter/interpreter_eval.c -o interpreter_eval.o

# Scanner et Parser objects
scanner.o: $(SCANNER_C) $(PARSER_H)
	$(CC) $(CFLAGS) -c $(SCANNER_C) -o scanner.o

parser.o: $(PARSER_C) $(PARSER_H)
	$(CC) $(CFLAGS) -c $(PARSER_C) -o parser.o

# Link
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(SCANNER_C) $(PARSER_C) $(PARSER_H)
	rm -f $(OBJECTS)
	rm -f $(TARGET)

install:
	cp $(TARGET) /usr/local/bin/
	mkdir -p /usr/local/lib/goscript
	cp -r lib/* /usr/local/lib/goscript/ 2>/dev/null || true

# Afficher l'architecture détectée
debug:
	@echo "OS: $(UNAME_S)"
	@echo "Arch: $(UNAME_M)"
	@echo "MARCH: $(MARCH)"
	@echo "CFLAGS: $(CFLAGS)"

.PHONY: all clean install debug
