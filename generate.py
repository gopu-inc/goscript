#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Génère un fichier de spécification complet du langage Goscript
"""

import os
import glob
from datetime import datetime

def write_section(f, title, content):
    """Écrit une section dans le fichier"""
    f.write("=" * 80 + "\n")
    f.write(f"{title}\n")
    f.write("=" * 80 + "\n\n")
    f.write(content)
    f.write("\n\n")

def read_file(path):
    """Lit un fichier s'il existe"""
    try:
        with open(path, 'r', encoding='utf-8', errors='ignore') as file:
            return file.read()
    except Exception as e:
        return f"# Erreur de lecture: {e}\n"

def main():
    output_file = "goscript_language.txt"
    
    with open(output_file, 'w', encoding='utf-8') as f:
        # En-tête
        f.write("=" * 80 + "\n")
        f.write("                    GOSCRIPT LANGUAGE SPECIFICATION\n")
        f.write("=" * 80 + "\n\n")
        f.write(f"Date: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n")
        f.write("Contient TOUT le code source du langage Goscript\n\n")
        
        # 1. Scanner
        write_section(f, "1. CODE SOURCE - scanner.l", 
                     read_file("src/lexer/scanner.l"))
        
        # 2. Parser
        write_section(f, "2. CODE SOURCE - parser.y", 
                     read_file("src/parser/parser.y"))
        
        # 3. AST Header
        write_section(f, "3. CODE SOURCE - ast.h", 
                     read_file("src/ast/ast.h"))
        
        # 4. AST Implementation
        write_section(f, "4. CODE SOURCE - ast.c", 
                     read_file("src/ast/ast.c"))
        
        # 5. Interpreter Header
        write_section(f, "5. CODE SOURCE - interpreter.h", 
                     read_file("src/interpreter/interpreter.h"))
        
        # 6. Interpreter Eval
        write_section(f, "6. CODE SOURCE - interpreter_eval.c", 
                     read_file("src/interpreter/interpreter_eval.c"))
        
        # 7. Interpreter Env
        write_section(f, "7. CODE SOURCE - interpreter_env.c", 
                     read_file("src/interpreter/interpreter_env.c"))
        
        # 8. Interpreter FFI
        write_section(f, "8. CODE SOURCE - interpreter_ffi.c", 
                     read_file("src/interpreter/interpreter_ffi.c"))
        
        # 9. Interpreter Import
        write_section(f, "9. CODE SOURCE - interpreter_import.c", 
                     read_file("src/interpreter/interpreter_import.c"))
        
        # 10. Main
        write_section(f, "10. CODE SOURCE - main.c", 
                     read_file("src/main.c"))
        
        # 11. Makefile
        write_section(f, "11. MAKEFILE", 
                     read_file("Makefile"))
        
        # 12. Librairie standard
        f.write("=" * 80 + "\n")
        f.write("12. LIBRAIRIE STANDARD - Modules .gjs\n")
        f.write("=" * 80 + "\n\n")
        
        lib_files = glob.glob("lib/*.gjs")
        lib_files.sort()
        
        for gjs_file in lib_files:
            f.write("-" * 40 + "\n")
            f.write(f"MODULE: {gjs_file}\n")
            f.write("-" * 40 + "\n")
            f.write(read_file(gjs_file))
            f.write("\n\n")
        
        # 13. Exemples
        f.write("=" * 80 + "\n")
        f.write("13. EXEMPLES - Fichiers d'exemple\n")
        f.write("=" * 80 + "\n\n")
        
        exemple_files = glob.glob("exemples/*.gjs")
        exemple_files.sort()
        
        for gjs_file in exemple_files[:50]:  # Limiter à 50 exemples
            f.write("-" * 40 + "\n")
            f.write(f"EXEMPLE: {gjs_file}\n")
            f.write("-" * 40 + "\n")
            f.write(read_file(gjs_file))
            f.write("\n\n")
        
        # 14. Tests
        f.write("=" * 80 + "\n")
        f.write("14. FICHIERS DE TEST\n")
        f.write("=" * 80 + "\n\n")
        
        test_files = glob.glob("test*.gjs") + glob.glob("*.gjs")
        test_files = list(set(test_files))
        test_files.sort()
        
        for gjs_file in test_files[:30]:  # Limiter à 30 tests
            if os.path.isfile(gjs_file):
                f.write("-" * 40 + "\n")
                f.write(f"TEST: {gjs_file}\n")
                f.write("-" * 40 + "\n")
                f.write(read_file(gjs_file))
                f.write("\n\n")
        
        # 15. Résumé des tokens
        f.write("=" * 80 + "\n")
        f.write("15. RÉSUMÉ DES MOTS-CLÉS\n")
        f.write("=" * 80 + "\n\n")
        
        scanner_content = read_file("src/lexer/scanner.l")
        keywords = []
        for line in scanner_content.split('\n'):
            if line.strip().startswith('"') and 'return TOKEN_' in line:
                kw = line.split('"')[1]
                if kw and not kw.startswith('\\'):
                    keywords.append(kw)
        
        f.write("Mots-clés du langage:\n")
        f.write(", ".join(sorted(set(keywords))))
        f.write("\n\n")
        
        # Statistiques
        f.write("=" * 80 + "\n")
        f.write("STATISTIQUES\n")
        f.write("=" * 80 + "\n\n")
        f.write(f"Modules lib/: {len(lib_files)}\n")
        f.write(f"Exemples: {len(exemple_files)}\n")
        f.write(f"Tests: {len(test_files)}\n")
        
        # Taille du fichier
        f.seek(0, 2)
        size = f.tell()
        f.write(f"\nTaille totale du fichier: {size:,} octets\n")
    
    print(f"✅ Fichier {output_file} généré avec succès !")
    print(f"📦 Taille: {size:,} octets")
    
    # Compter les lignes
    with open(output_file, 'r') as f:
        lines = len(f.readlines())
    print(f"📝 Lignes: {lines:,}")

if __name__ == "__main__":
    main()