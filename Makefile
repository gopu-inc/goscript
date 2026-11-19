CC = gcc
CFLAGS ?= -Wall -g -O0
CFLAGS += \
	-I./src \
	-I./src/ast \
	-I./src/interpreter \
	-I./src/gc \
	-I./src/vm \
	-I./src/hal \
	-I./src/ffi

UNAME_S := $(shell uname -s)
UNAME_M := $(shell uname -m)

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
	endif
else ifeq ($(UNAME_S),Darwin)
	ifeq ($(UNAME_M),arm64)
		MARCH = -arch arm64
	else
		MARCH = -arch x86_64
	endif
endif

ifneq ($(MARCH),)
	CFLAGS += $(MARCH)
endif

ifneq ($(filter CYGWIN% MINGW% MSYS%,$(UNAME_S)),)
	EXEEXT = .exe
endif

ifeq ($(UNAME_S),Darwin)
	LIBFFI_PREFIX := $(shell brew --prefix libffi 2>/dev/null)
	ifneq ($(strip $(LIBFFI_PREFIX)),)
		CFLAGS += -I$(LIBFFI_PREFIX)/include
		LDFLAGS = -L$(LIBFFI_PREFIX)/lib -lm -lffi -lpthread -lz
	else
		LDFLAGS = -lm -lffi -lpthread -lz
	endif
else
	LDFLAGS = -lm -ldl -lffi -lpthread -lz
endif

BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
GEN_DIR = $(BUILD_DIR)/generated
BIN_DIR = $(BUILD_DIR)/bin
SCANNER_C = $(GEN_DIR)/scanner.c
PARSER_C = $(GEN_DIR)/parser.c
PARSER_H = $(GEN_DIR)/parser.h
TARGET = $(BIN_DIR)/gd$(EXEEXT)
ALIASES = $(BIN_DIR)/gbc$(EXEEXT) $(BIN_DIR)/gld$(EXEEXT)

SOURCES = \
	src/ast/ast.c \
	src/bytecode/bytecode.c \
	src/gc/gc.c \
	src/tensor.c \
	src/nn.c \
	src/vm/vm.c \
	src/hal/hal.c \
	src/ffi/ffi_sandbox.c \
	src/main.c \
	src/interpreter/interpreter_env.c \
	src/interpreter/interpreter_import.c \
	src/interpreter/interpreter_ffi.c \
	src/interpreter/interpreter_eval.c \
	src/interpreter/interpreter_net.c \
	src/interpreter/interpreter_gpm.c

OBJECTS = \
	$(patsubst %.c,$(OBJ_DIR)/%.o,$(SOURCES)) \
	$(OBJ_DIR)/scanner.o \
	$(OBJ_DIR)/parser.o

PREFIX ?= /usr/local
DESTDIR ?=
INSTALL_ROOT = $(DESTDIR)$(PREFIX)

CFLAGS += -I$(GEN_DIR)

.PHONY: all all-binaries binaries gd gbc gld gpm test clean install standard-packages publish-standard-packages debug

all: binaries

all-binaries: binaries gpm

binaries: $(TARGET) $(ALIASES)

# Keep `make gd` compatible with source installers without writing a root binary.
gd: $(TARGET)

gbc: $(BIN_DIR)/gbc$(EXEEXT)

gld: $(BIN_DIR)/gld$(EXEEXT)

gpm:
	$(MAKE) -C gpm

$(GEN_DIR) $(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

$(GEN_DIR)/parser.stamp: src/parser/parser.y | $(GEN_DIR)
	bison -d -o $(PARSER_C) $<
	touch $@

$(PARSER_C) $(PARSER_H): src/parser/parser.y | $(GEN_DIR)/parser.stamp
	@test -f $@ || { echo "Missing generated parser file: $@" >&2; exit 1; }

$(SCANNER_C): src/lexer/scanner.l | $(GEN_DIR)
	flex -o $@ $<

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(OBJ_DIR)/scanner.o: $(SCANNER_C) $(PARSER_H) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $(SCANNER_C) -o $@

$(OBJ_DIR)/parser.o: $(PARSER_C) $(PARSER_H) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $(PARSER_C) -o $@

$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

$(BIN_DIR)/gbc$(EXEEXT): $(TARGET) | $(BIN_DIR)
	ln -sf $(notdir $(TARGET)) $@

$(BIN_DIR)/gld$(EXEEXT): $(TARGET) | $(BIN_DIR)
	ln -sf $(notdir $(TARGET)) $@

test: $(TARGET)
	GOSCRIPT_BIN="$(TARGET)" SKIP_BUILD=1 bash tests/run_tests.sh

clean:
	rm -rf $(OBJ_DIR) $(GEN_DIR)
	rm -f $(TARGET) $(ALIASES)
	rmdir $(BIN_DIR) 2>/dev/null || true
	rm -f ast.o bytecode.o gc.o tensor.o nn.o vm.o hal.o ffi_sandbox.o \
		main.o interpreter_env.o interpreter_import.o interpreter_ffi.o \
		interpreter_eval.o interpreter_net.o interpreter_gpm.o scanner.o parser.o
	$(MAKE) -C gpm clean

install: $(TARGET)
	install -d $(INSTALL_ROOT)/bin $(INSTALL_ROOT)/share/goscript/golem
	install -m 755 $(TARGET) $(INSTALL_ROOT)/bin/gd$(EXEEXT)
	install -m 755 $(BIN_DIR)/gbc$(EXEEXT) $(INSTALL_ROOT)/bin/gbc$(EXEEXT)
	install -m 755 $(BIN_DIR)/gld$(EXEEXT) $(INSTALL_ROOT)/bin/gld$(EXEEXT)
	install -m 755 golem-launcher.sh $(INSTALL_ROOT)/bin/golem
	install -m 644 golem-cli.gjs $(INSTALL_ROOT)/share/goscript/golem-cli.gjs
	install -m 644 lib/golem/__self__.gjs $(INSTALL_ROOT)/share/goscript/golem/__self__.gjs
	install -m 644 lib/__builtin__.gjs $(INSTALL_ROOT)/share/goscript/__builtin__.gjs
	install -m 755 install.sh $(INSTALL_ROOT)/share/goscript/install.sh

standard-packages: $(TARGET)
	$(MAKE) -C packages/stdlib build
	cd packages/base && PATH="$(CURDIR)/$(BIN_DIR):$$PATH" ../../golem build

publish-standard-packages: standard-packages
	@set -e; \
	for package in b64 config crypto db error fmt fs gcsv gsql http httplib io json math net nn os random s256 sqlite std strings tar tensor time tui ui urllib xzip; do \
		printf 'Publishing standard package %s\n' "$$package"; \
		(cd "packages/stdlib/$$package" && PATH="$(CURDIR)/$(BIN_DIR):$$PATH" "$(CURDIR)/golem" publish); \
	done
	cd packages/base && PATH="$(CURDIR)/$(BIN_DIR):$$PATH" ../../golem publish

debug:
	@echo "OS: $(UNAME_S)"
	@echo "Arch: $(UNAME_M)"
	@echo "MARCH: $(MARCH)"
	@echo "CFLAGS: $(CFLAGS)"

-include $(OBJECTS:.o=.d)
