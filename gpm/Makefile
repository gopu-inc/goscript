# =========================================================================
# GPM (Goscript Package Manager) Makefile
# =========================================================================

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -O2 -march=native
LDFLAGS = -lcurl -larchive -lssl -lcrypto -ljansson -lpthread

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    CFLAGS += -DPLATFORM_LINUX
else ifeq ($(UNAME_S),Darwin)
    CFLAGS += -DPLATFORM_MACOS -I/usr/local/opt/openssl/include
    LDFLAGS += -L/usr/local/opt/openssl/lib
endif

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = /usr/local/bin
INCLUDE_DIRS = -I$(SRC_DIR)

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS = $(OBJECTS:.o=.d)

TARGET = $(BUILD_DIR)/gpm
INSTALL_TARGET = $(BIN_DIR)/gpm

.PHONY: all clean install uninstall test debug release help

all: $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE_DIRS) -MMD -c $< -o $@
	@echo "  CC  $<"

$(TARGET): $(OBJECTS)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "  LD  $@"
	@echo ""
	@echo "$(COLOR_GREEN)✓ Build successful!$(COLOR_RESET)"
	@echo "  Binary: $(TARGET)"
	@echo ""

install: $(TARGET)
	@mkdir -p $(BIN_DIR)
	@cp $(TARGET) $(INSTALL_TARGET)
	@chmod 755 $(INSTALL_TARGET)
	@mkdir -p /usr/local/lib/goscript/modules
	@mkdir -p /usr/local/lib/goscript/std
	@mkdir -p /usr/local/lib/goscript/builtin
	@mkdir -p /var/cache/gpm
	@mkdir -p /etc/gpm
	@echo "$(COLOR_GREEN)✓ GPM installed to $(INSTALL_TARGET)$(COLOR_RESET)"

uninstall:
	@rm -f $(INSTALL_TARGET)
	@echo "$(COLOR_YELLOW)GPM uninstalled$(COLOR_RESET)"

test: $(TARGET)
	@./$(TARGET) --version
	@./$(TARGET) --help

clean:
	@rm -rf $(BUILD_DIR)
	@echo "$(COLOR_YELLOW)Cleaned$(COLOR_RESET)"

debug: CFLAGS += -g -O0 -DDEBUG
debug: all

release: CFLAGS += -O3 -DNDEBUG -flto
release: LDFLAGS += -flto
release: all

help:
	@echo "GPM Build System"
	@echo "Targets:"
	@echo "  all      - Build GPM"
	@echo "  install  - Install to /usr/local/bin"
	@echo "  uninstall- Remove installation"
	@echo "  clean    - Clean build files"
	@echo "  debug    - Debug build"
	@echo "  release  - Optimized release build"
	@echo "  test     - Run tests"
	@echo "  help     - Show this help"

-include $(DEPS)
