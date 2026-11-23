CC = gcc
CFLAGS ?= -Wall -g -O2
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

.PHONY: all all-binaries binaries gd gbc gld gpm test clean install test-install standard-packages publish-standard-packages debug

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

# Bibliothèque standard installée dans share/goscript : tout lib/ (modules .gjs et
# sous-dossiers, y compris golem/ et __builtin__.gjs), sans les tests ni les exemples.
SHARE_DIR = $(INSTALL_ROOT)/share/goscript
STDLIB_FILES = $(shell find lib -type f -name '*.gjs' ! -name 'test*.gjs' ! -path 'lib/flout/examples/*' | sort)

# `install` dépend de `binaries` (et pas seulement de gd) : gbc et gld sont installés aussi.
install: binaries
	install -d $(INSTALL_ROOT)/bin $(SHARE_DIR)
	install -m 755 $(TARGET) $(INSTALL_ROOT)/bin/gd$(EXEEXT)
	install -m 755 $(BIN_DIR)/gbc$(EXEEXT) $(INSTALL_ROOT)/bin/gbc$(EXEEXT)
	install -m 755 $(BIN_DIR)/gld$(EXEEXT) $(INSTALL_ROOT)/bin/gld$(EXEEXT)
	install -m 755 golem-launcher.sh $(INSTALL_ROOT)/bin/golem
	install -m 755 golem-launcher.sh $(SHARE_DIR)/golem-launcher.sh
	install -m 644 golem-cli.gjs $(SHARE_DIR)/golem-cli.gjs
	install -m 755 install.sh $(SHARE_DIR)/install.sh
	@set -e; count=0; for f in $(STDLIB_FILES); do \
		rel=$${f#lib/}; \
		install -d "$(SHARE_DIR)/$$(dirname "$$rel")"; \
		install -m 644 "$$f" "$(SHARE_DIR)/$$rel"; \
		count=$$((count + 1)); \
	done; \
	echo "Bibliothèque standard : $$count fichiers installés dans $(SHARE_DIR)"

# Installe dans un préfixe temporaire puis vérifie, hors du dépôt, que le lanceur golem
# et les modules de la bibliothèque standard se chargent depuis l'installation.
test-install: binaries
	@set -e; tmp=$$(mktemp -d); trap 'rm -rf "$$tmp"' EXIT; \
	$(MAKE) --no-print-directory install DESTDIR="$$tmp" PREFIX=/usr/local >/dev/null; \
	share="$$tmp/usr/local/share/goscript"; gd="$$tmp/usr/local/bin/gd$(EXEEXT)"; \
	for f in golem-cli.gjs golem-launcher.sh install.sh __builtin__.gjs golem/__self__.gjs math.gjs json.gjs fs.gjs os/env.gjs net/__self__.gjs; do \
		test -f "$$share/$$f" || { echo "FAIL: $$f manquant dans l'installation"; exit 1; }; \
	done; \
	work=$$(mktemp -d); trap 'rm -rf "$$tmp" "$$work"' EXIT; \
	printf 'import math\nimport json\nimport os.env\nprintln(math::sqrt(16.0))\n' > "$$work/t.gjs"; \
	out=$$(cd "$$work" && env -u GOSCRIPT_LIB GOSCRIPT_SHARE_DIR="$$share" "$$gd" t.gjs 2>&1); \
	case "$$out" in 4*) ;; *) echo "FAIL: import de la bibliothèque standard : $$out"; exit 1;; esac; \
	(cd "$$work" && GOSCRIPT_SHARE_DIR="$$share" "$$tmp/usr/local/bin/golem" help >/dev/null) \
		|| { echo "FAIL: golem help"; exit 1; }; \
	echo "OK: installation vérifiée ($$(find "$$share" -type f | wc -l) fichiers)"

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
