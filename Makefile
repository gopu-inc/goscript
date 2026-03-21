CC = gcc
CFLAGS = -Wall -g -O2 -I./src -I./src/ast
LDFLAGS = -lm -ldl -lffi -lreadline

OBJS = scanner.o parser.o ast.o main.o interpreter_env.o interpreter_ffi.o interpreter_eval.o

all: gd

gd: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o gd

scanner.o: scanner.c parser.h
	$(CC) $(CFLAGS) -c scanner.c -o scanner.o

parser.o: parser.c
	$(CC) $(CFLAGS) -c parser.c -o parser.o

ast.o: src/ast/ast.c parser.h
	$(CC) $(CFLAGS) -c src/ast/ast.c -o ast.o

main.o: src/main.c parser.h
	$(CC) $(CFLAGS) -c src/main.c -o main.o

interpreter_env.o: src/interpreter/interpreter_env.c src/interpreter/interpreter.h
	$(CC) $(CFLAGS) -c src/interpreter/interpreter_env.c -o interpreter_env.o

interpreter_ffi.o: src/interpreter/interpreter_ffi.c src/interpreter/interpreter.h
	$(CC) $(CFLAGS) -c src/interpreter/interpreter_ffi.c -o interpreter_ffi.o

interpreter_eval.o: src/interpreter/interpreter_eval.c src/interpreter/interpreter.h
	$(CC) $(CFLAGS) -c src/interpreter/interpreter_eval.c -o interpreter_eval.o

clean:
	rm -f scanner.c parser.c parser.h
	rm -f *.o
	rm -f gd

.PHONY: all clean
