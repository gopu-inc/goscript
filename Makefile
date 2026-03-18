# GOScript - Makefile complet
# Compilateur et flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Iinc
LDFLAGS = -lm

# Répertoires
SRCDIR = src
INCDIR = inc
OBJDIR = obj
BINDIR = bin

# Nom de l'exécutable
TARGET = $(BINDIR)/goscript

# Fichiers sources et objets
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

# Fichiers d'en-tête
HEADERS = $(wildcard $(INCDIR)/*.h)

# Couleurs pour une sortie plus lisible
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RED = \033[0;31m
NC = \033[0m # No Color

# Cible par défaut
all: directories $(TARGET)
	@echo "$(GREEN)✓ Build terminé avec succès !$(NC)"

# Création des répertoires nécessaires
directories:
	@mkdir -p $(OBJDIR) $(BINDIR)
	@echo "$(BLUE)📁 Répertoires créés$(NC)"

# Compilation de l'exécutable
$(TARGET): $(OBJECTS)
	@echo "$(YELLOW)🔗 Édition des liens...$(NC)"
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo "$(GREEN)✓ Exécutable créé : $@$(NC)"

# Compilation des fichiers objets
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@echo "$(BLUE)⚙️  Compilation de $<...$(NC)"
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers générés
clean:
	@echo "$(YELLOW)🧹 Nettoyage...$(NC)"
	rm -rf $(OBJDIR) $(BINDIR)
	@echo "$(GREEN)✓ Nettoyage terminé$(NC)"

# Nettoyage complet (y compris les fichiers de backup)
distclean: clean
	@echo "$(YELLOW)🧹 Nettoyage profond...$(NC)"
	rm -f *~ $(SRCDIR)/*~ $(INCDIR)/*~
	find . -name "*.orig" -type f -delete
	find . -name "*.bak" -type f -delete
	@echo "$(GREEN)✓ Nettoyage profond terminé$(NC)"

# Recompilation complète
rebuild: clean all

# Exécution d'un fichier test
run: $(TARGET)
	@echo "$(BLUE)▶️  Exécution de $(TEST_FILE)...$(NC)"
	$(TARGET) $(TEST_FILE)

# Mode REPL
repl: $(TARGET)
	@echo "$(BLUE)💻 Démarrage du REPL...$(NC)"
	$(TARGET)

# Test avec un fichier spécifique (make test TEST_FILE=examples/test.gjs)
test: $(TARGET)
	@if [ -f "$(TEST_FILE)" ]; then \
		echo "$(BLUE)🧪 Test avec $(TEST_FILE)...$(NC)"; \
		$(TARGET) $(TEST_FILE); \
	else \
		echo "$(RED)❌ Fichier test non trouvé : $(TEST_FILE)$(NC)"; \
		exit 1; \
	fi

# Test de tous les fichiers dans le répertoire examples
test-all: $(TARGET)
	@echo "$(BLUE)🧪 Test de tous les exemples...$(NC)"
	@for file in examples/*.gjs; do \
		if [ -f "$$file" ]; then \
			echo "$(YELLOW)--- Test: $$file ---$(NC)"; \
			$(TARGET) $$file; \
			echo ""; \
		fi \
	done

# Vérification de la syntaxe (sans exécution)
check: $(TARGET)
	@echo "$(BLUE)🔍 Vérification syntaxique...$(NC)"
	@for file in examples/*.gjs; do \
		if [ -f "$$file" ]; then \
			echo "$(YELLOW)📄 $$file$(NC)"; \
			$(TARGET) --check $$file 2>/dev/null || echo "$(RED)❌ Erreur dans $$file$(NC)"; \
		fi \
	done

# Installation (optionnel)
install: $(TARGET)
	@echo "$(BLUE)📦 Installation...$(NC)"
	@if [ -w /usr/local/bin ]; then \
		cp $(TARGET) /usr/local/bin/; \
		echo "$(GREEN)✓ Installé dans /usr/local/bin/goscript$(NC)"; \
	else \
		echo "$(RED)❌ Permission refusée. Utilise 'sudo make install'$(NC)"; \
	fi

# Désinstallation
uninstall:
	@echo "$(BLUE)🗑️  Désinstallation...$(NC)"
	@if [ -f /usr/local/bin/goscript ]; then \
		rm -f /usr/local/bin/goscript; \
		echo "$(GREEN)✓ Désinstallé$(NC)"; \
	else \
		echo "$(YELLOW}⚠️  goscript n'est pas installé$(NC)"; \
	fi

# Analyse statique du code (nécessite cppcheck)
analyze:
	@echo "$(BLUE)🔬 Analyse statique avec cppcheck...$(NC)"
	@if command -v cppcheck >/dev/null 2>&1; then \
		cppcheck --enable=all --inconclusive --std=c99 \
			--suppress=missingIncludeSystem \
			-I$(INCDIR) $(SRCDIR)/*.c; \
	else \
		echo "$(YELLOW)⚠️  cppcheck n'est pas installé. Ignoré.$(NC)"; \
	fi

# Formatage du code avec clang-format
format:
	@echo "$(BLUE)✨ Formatage du code...$(NC)"
	@if command -v clang-format >/dev/null 2>&1; then \
		clang-format -i $(SRCDIR)/*.c $(INCDIR)/*.h; \
		echo "$(GREEN)✓ Code formaté$(NC)"; \
	else \
		echo "$(YELLOW)⚠️  clang-format n'est pas installé. Ignoré.$(NC)"; \
	fi

# Comptage des lignes de code
count:
	@echo "$(BLUE)📊 Statistiques du code :$(NC)"
	@echo "Fichiers source :"
	@wc -l $(SRCDIR)/*.c | sed 's/^/  /'
	@echo "Fichiers d'en-tête :"
	@wc -l $(INCDIR)/*.h | sed 's/^/  /'
	@echo "Total :"
	@cat $(SRCDIR)/*.c $(INCDIR)/*.h | wc -l | sed 's/^/  /'

# Documentation avec Doxygen (si installé)
docs:
	@echo "$(BLUE)📚 Génération de la documentation...$(NC)"
	@if command -v doxygen >/dev/null 2>&1; then \
		if [ ! -f Doxyfile ]; then \
			doxygen -g; \
		fi; \
		doxygen; \
		echo "$(GREEN)✓ Documentation générée dans docs/$(NC)"; \
	else \
		echo "$(YELLOW)⚠️  doxygen n'est pas installé. Ignoré.$(NC)"; \
	fi

# Debug avec valgrind (vérification des fuites mémoire)
memcheck: $(TARGET)
	@echo "$(BLUE)🕵️  Vérification mémoire avec valgrind...$(NC)"
	@if command -v valgrind >/dev/null 2>&1; then \
		valgrind --leak-check=full \
			--show-leak-kinds=all \
			--track-origins=yes \
			--verbose \
			$(TARGET) $(TEST_FILE); \
	else \
		echo "$(YELLOW)⚠️  valgrind n'est pas installé. Ignoré.$(NC)"; \
	fi

# Profilage avec gprof
profile: CFLAGS += -pg
profile: LDFLAGS += -pg
profile: clean all
	@echo "$(BLUE)📈 Exécution pour profilage...$(NC)"
	$(TARGET) $(TEST_FILE)
	@if [ -f gmon.out ]; then \
		gprof $(TARGET) > profile.txt; \
		echo "$(GREEN)✓ Profilage terminé. Voir profile.txt$(NC)"; \
	fi

# Création d'une archive pour distribution
dist:
	@echo "$(BLUE)📦 Création de l'archive de distribution...$(NC)"
	@VERSION=$$(grep -m1 "GOSCRIPT_VERSION" $(INCDIR)/common.h 2>/dev/null | cut -d'"' -f2 || echo "0.1"); \
	ARCHIVE="goscript-$$VERSION.tar.gz"; \
	tar --exclude='*.o' --exclude='$(OBJDIR)' --exclude='$(BINDIR)' \
		--exclude='*.tar.gz' --exclude='gmon.out' --exclude='profile.txt' \
		-czvf $$ARCHIVE \
		Makefile \
		$(SRCDIR) \
		$(INCDIR) \
		examples \
		README.md \
		LICENSE 2>/dev/null || true; \
	if [ -f $$ARCHIVE ]; then \
		echo "$(GREEN)✓ Archive créée : $$ARCHIVE$(NC)"; \
	else \
		echo "$(YELLOW)⚠️  Archive créée sans fichiers optionnels$(NC)"; \
	fi

# Aide
help:
	@echo "$(BLUE)GOScript - Makefile$(NC)"
	@echo ""
	@echo "Commandes disponibles :"
	@echo "  $(GREEN)make all$(NC)          - Compile le projet"
	@echo "  $(GREEN)make clean$(NC)        - Nettoie les fichiers générés"
	@echo "  $(GREEN)make distclean$(NC)    - Nettoyage profond"
	@echo "  $(GREEN)make rebuild$(NC)       - Recompile tout"
	@echo "  $(GREEN)make run$(NC)           - Exécute avec le fichier TEST_FILE"
	@echo "  $(GREEN)make repl$(NC)          - Lance le mode interactif"
	@echo "  $(GREEN)make test$(NC)          - Teste avec TEST_FILE"
	@echo "  $(GREEN)make test-all$(NC)      - Teste tous les fichiers examples/"
	@echo "  $(GREEN)make check$(NC)         - Vérification syntaxique"
	@echo "  $(GREEN)make install$(NC)       - Installe dans /usr/local/bin"
	@echo "  $(GREEN)make uninstall$(NC)     - Désinstalle"
	@echo "  $(GREEN)make analyze$(NC)       - Analyse statique (cppcheck)"
	@echo "  $(GREEN)make format$(NC)        - Formate le code (clang-format)"
	@echo "  $(GREEN)make count$(NC)         - Compte les lignes de code"
	@echo "  $(GREEN)make docs$(NC)          - Génère la documentation (doxygen)"
	@echo "  $(GREEN)make memcheck$(NC)      - Vérifie les fuites mémoire (valgrind)"
	@echo "  $(GREEN)make profile$(NC)       - Profilage (gprof)"
	@echo "  $(GREEN)make dist$(NC)           - Crée une archive de distribution"
	@echo ""
	@echo "Variables :"
	@echo "  $(YELLOW)TEST_FILE=$(NC)         - Fichier à tester (ex: make test TEST_FILE=test.gjs)"
	@echo ""
	@echo "Exemples :"
	@echo "  make test TEST_FILE=examples/test.gjs"
	@echo "  make memcheck TEST_FILE=test.gjs"
	@echo "  make run TEST_FILE=mon_programme.gjs"

# Cibles par défaut
.PHONY: all clean distclean rebuild run repl test test-all check install uninstall
.PHONY: analyze format count docs memcheck profile dist help directories

# Valeur par défaut pour TEST_FILE
TEST_FILE ?= test.gjs

# Pour éviter les conflits avec des fichiers du même nom
.PHONY: $(TARGET)
