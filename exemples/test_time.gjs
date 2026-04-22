// test_time.gjs
// Test du module time avec use

import time
import time.ft

// Utilisation de use pour importer des fonctions spécifiques
use time::now
use time::timestamp
use time::ft::sleep_ms
use time::ft::sleep

fn main() {
    println("=== TEST MODULE TIME ===\n")
    
    // Test 1: Utilisation directe avec namespace complet
    println("1. Time::now(): " + time::now())
    println("   Timestamp: " + time::timestamp())
    println("")
    
    // Test 2: Utilisation avec use (fonctions importées directement)
    println("2. Fonctions importées via use:")
    println("   now(): " + now())
    println("   timestamp(): " + timestamp())
    println("")
    
    // Test 3: Sous-module ft
    println("3. Test du sous-module ft:")
    println("   sleep_ms(500) - attendez 0.5s...")
    sleep_ms(500)
    println("   Fait!")
    println("")
    
    println("4. Test avec namespace complet:")
    println("   time::ft::sleep(1) - attendez 1s...")
    time::ft::sleep(1)
    println("   Fait!")
    println("")
    
    println("=== TEST TERMINÉ ===")
    
    ret 0
}
