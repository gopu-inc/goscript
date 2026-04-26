CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c11 -D_GNU_SOURCE
LDFLAGS = -lcurl -lssl -lcrypto -ljansson -larchive -lm -lpthread -ldl

# Architecture detection
UNAME_S := $(shell uname -s)
UNAME_M := $(shell uname -m)

ifeq ($(UNAME_S),Linux)
    ifeq ($(UNAME_M),x86_64)
        MARCH = -march=x86-64-v2
    else ifeq ($(UNAME_M),aarch64)
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

ifneq ($(MARCH),)
    CFLAGS += $(MARCH)
endif

PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin
LIBDIR = $(PREFIX)/lib/goscript

SRCDIR = src
OBJDIR = obj
BINDIR_LOCAL = bin

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))
TARGET = $(BINDIR_LOCAL)/gpm

.PHONY: all clean install uninstall debug release

all: dirs $(TARGET)

dirs:
	@mkdir -p $(OBJDIR) $(BINDIR_LOCAL)

$(OBJDIR)/%.o: $(SRCDIR)/%.c gpm.h
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "$(COLOR_GREEN)✓ GPM compiled successfully!$(COLOR_RESET)"

debug: CFLAGS += -g -O0 -DDEBUG
debug: clean all

release: CFLAGS += -O3 -DNDEBUG
release: clean all

install: all
	install -d $(DESTDIR)$(BINDIR)
	install -m 755 $(TARGET) $(DESTDIR)$(BINDIR)/gpm
	install -d $(DESTDIR)$(LIBDIR)
	install -d $(DESTDIR)$(LIBDIR)/modules
	install -d $(DESTDIR)$(LIBDIR)/cache
	install -d $(DESTDIR)$(LIBDIR)/config
	install -d $(DESTDIR)$(LIBDIR)/packages
	@echo "$(COLOR_GREEN)✓ GPM installed to $(BINDIR)/gpm$(COLOR_RESET)"

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/gpm
	@echo "$(COLOR_YELLOW)GPM uninstalled$(COLOR_RESET)"

clean:
	rm -rf $(OBJDIR) $(BINDIR_LOCAL)
	@echo "$(COLOR_YELLOW)Cleaned build files$(COLOR_RESET)"

distclean: clean
	rm -f $(DESTDIR)$(BINDIR)/gpm
	@echo "$(COLOR_YELLOW)Full clean done$(COLOR_RESET)"
