CC = gcc
CFLAGS = -Wall -g -O2 -I./src -I./src/ast
LDFLAGS = -lm -lreadline

SRC_DIR = src
LEXER_DIR = $(SRC_DIR)/lexer
PARSER_DIR = $(SRC_DIR)/parser
AST_DIR = $(SRC_DIR)/ast
INTERPRETER_DIR = $(SRC_DIR)/interpreter
MAIN_SRC = $(SRC_DIR)/main.c
REPL_SRC = $(SRC_DIR)/repl.c

# Fichiers générés
SCANNER_C = scanner.c
PARSER_C = parser.c
PARSER_H = parser.h

OBJS = $(SCANNER_C:.c=.o) $(PARSER_C:.c=.o) interpreter.o ast.o repl.o main.o

all: $(PARSER_H) $(SCANNER_C) $(PARSER_C) $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o gd

$(SCANNER_C): $(LEXER_DIR)/scanner.l
	flex -o $(SCANNER_C) $(LEXER_DIR)/scanner.l

$(PARSER_C) $(PARSER_H): $(PARSER_DIR)/parser.y
	bison -d -o $(PARSER_C) $(PARSER_DIR)/parser.y

scanner.o: $(SCANNER_C) $(PARSER_H)
	$(CC) $(CFLAGS) -c $(SCANNER_C) -o scanner.o

interpreter.o: $(INTERPRETER_DIR)/interpreter.c $(PARSER_H)
	$(CC) $(CFLAGS) -c $(INTERPRETER_DIR)/interpreter.c -o interpreter.o

parser.o: $(PARSER_C) $(PARSER_H)
	$(CC) $(CFLAGS) -c $(PARSER_C) -o parser.o

ast.o: $(AST_DIR)/ast.c $(PARSER_H)
	$(CC) $(CFLAGS) -c $(AST_DIR)/ast.c -o ast.o

repl.o: $(REPL_SRC) $(PARSER_H)
	$(CC) $(CFLAGS) -c $(REPL_SRC) -o repl.o

main.o: $(MAIN_SRC) $(PARSER_H)
	$(CC) $(CFLAGS) -c $(MAIN_SRC) -o main.o

clean:
	rm -f $(SCANNER_C) $(PARSER_C) $(PARSER_H)
	rm -f *.o
	rm -f gd

.PHONY: all clean
