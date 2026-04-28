# Makefile
CC = gcc
CFLAGS = -Wall -Wextra -O2 -I./include
LDFLAGS = -lcurl -ljansson -lssl -lcrypto -lpthread

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
TARGET = $(BIN_DIR)/gpm

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS = $(OBJECTS:.o=.d)

.PHONY: all clean install uninstall test debug

all: $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "  CC $<"
	@$(CC) $(CFLAGS) -MMD -c $< -o $@

$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	@echo "  LD $@"
	@$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "✅ GPM compilé avec succès!"

install: $(TARGET)
	@echo "Installation de GPM..."
	@mkdir -p /usr/local/bin /usr/local/lib/gpm
	@cp $(TARGET) /usr/local/bin/gpm
	@echo "✅ GPM installé dans /usr/local/bin/gpm"

uninstall:
	@rm -f /usr/local/bin/gpm
	@echo "✅ GPM désinstallé"

test: $(TARGET)
	@./$(TARGET) --version
	@./$(TARGET) help

debug: CFLAGS += -g -O0 -DDEBUG
debug: all

clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "✅ Nettoyé"

-include $(DEPS)
