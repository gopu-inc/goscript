# gpm/Makefile
CC = gcc
CFLAGS = -Wall -Wextra -O2 -I./include
LDFLAGS = -lcurl -ljansson -lssl -lcrypto

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
TARGET = $(BIN_DIR)/gpm

SOURCES = $(SRC_DIR)/main.c \
          $(SRC_DIR)/config.c \
          $(SRC_DIR)/semver.c \
          $(SRC_DIR)/manifest.c \
          $(SRC_DIR)/resolve.c \
          $(SRC_DIR)/network.c \
          $(SRC_DIR)/install.c \
          $(SRC_DIR)/lockfile.c \
          $(SRC_DIR)/utils.c

OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS = $(OBJECTS:.o=.d)

.PHONY: all clean install uninstall test debug

all: $(TARGET)
	@echo ""
	@echo "✅ GPM v3.0 compilé avec succès !"
	@echo "   Exécutable: $(TARGET)"
	@echo "   Lancez './$(TARGET) help' pour commencer"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "  CC  $<"
	@$(CC) $(CFLAGS) -MMD -c $< -o $@

$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	@echo "  LD  $@"
	@$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

install: $(TARGET)
	@echo "Installation de GPM..."
	@mkdir -p /usr/local/bin /usr/local/lib/gpm /etc/gpm
	@cp $(TARGET) /usr/local/bin/gpm
	@echo "✅ GPM installé dans /usr/local/bin/gpm"
	@echo "   Exécutez 'gpm help' pour commencer"

uninstall:
	@rm -f /usr/local/bin/gpm
	@echo "✅ GPM désinstallé"

test: $(TARGET)
	@./$(TARGET) help
	@echo ""
	@./$(TARGET) doctor

debug: CFLAGS += -g -O0 -DDEBUG
debug: all

clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "✅ Nettoyé"

-include $(DEPS)
