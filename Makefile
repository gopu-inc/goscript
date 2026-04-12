CC = gcc
CFLAGS = -Wall -g -O0 -march=i586 -I./src -I./src/ast -I./src/interpreter
LDFLAGS = -lm -ldl -lffi

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

# Scanner
$(SCANNER_C): src/lexer/scanner.l
	flex -o $(SCANNER_C) src/lexer/scanner.l

# Parser
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

.PHONY: all clean install
