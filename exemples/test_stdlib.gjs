// ============================================
// TEST COMPLET DE LA BIBLIOTHÈQUE STANDARD
// Goscript v0.3.0
// ============================================

fn main() {
    println(colorize("╔══════════════════════════════════════════════════════════╗", COLOR_CYAN))
    println(colorize("║     Goscript Standard Library - Complete Test Suite     ║", COLOR_CYAN))
    println(colorize("╚══════════════════════════════════════════════════════════╝", COLOR_CYAN))
    println("")
    
    muts tests_passed = 0
    muts tests_failed = 0
    
    // ==========================================
    // TEST 1: CONSTANTES ET VERSION
    // ==========================================
    println(colorize("📦 TEST 1: Constants & Version", COLOR_YELLOW))
    
    assert(VERSION == "0.3.0", "Version should be 0.3.0")
    assert(PI > 3.14 && PI < 3.15, "PI should be ~3.14159")
    assert(E > 2.71 && E < 2.72, "E should be ~2.71828")
    tests_passed = tests_passed + 1
    
    println(colorize("  ✓ Constants OK", COLOR_GREEN))
    println("")
    
    // ==========================================
    // TEST 2: MATHÉMATIQUES
    // ==========================================
    println(colorize("🧮 TEST 2: Mathematics", COLOR_YELLOW))
    
    assert(abs(-10) == 10, "abs(-10) should be 10")
    assert(abs(5) == 5, "abs(5) should be 5")
    assert(max(10, 20) == 20, "max(10,20) should be 20")
    assert(min(10, 20) == 10, "min(10,20) should be 10")
    assert(clamp(15, 0, 10) == 10, "clamp(15,0,10) should be 10")
    assert(clamp(-5, 0, 10) == 0, "clamp(-5,0,10) should be 0")
    
    muts sqrt_val = sqrt(16)
    assert(sqrt_val == 4, "sqrt(16) should be 4, got " + sqrt_val)
    
    muts sin_val = sin(PI/2)
    assert(sin_val > 0.99 && sin_val < 1.01, "sin(PI/2) should be ~1")
    
    muts pow_val = pow(2, 3)
    assert(pow_val == 8, "pow(2,3) should be 8")
    
    tests_passed = tests_passed + 1
    println(colorize("  ✓ Mathematics OK", COLOR_GREEN))
    println("")
    
    // ==========================================
    // TEST 3: MANIPULATION DE CHAÎNES
    // ==========================================
    println(colorize("📝 TEST 3: String Manipulation", COLOR_YELLOW))
    
    muts test_str = "Hello, World!"
    assert(strlen(test_str) == 13, "Length should be 13")
    assert(contains(test_str, "World"), "Should contain 'World'")
    assert(!contains(test_str, "Mars"), "Should not contain 'Mars'")
    
    muts upper_test = toupper(97)  // 'a'
    assert(upper_test == 65, "toupper('a') should be 'A'")
    
    muts lower_test = tolower(65)  // 'A'
    assert(lower_test == 97, "tolower('A') should be 'a'")
    
    assert(isalpha(65), "isalpha('A') should be true")
    assert(isdigit(48), "isdigit('0') should be true")
    assert(!isdigit(65), "isdigit('A') should be false")
    
    tests_passed = tests_passed + 1
    println(colorize("  ✓ String functions OK", COLOR_GREEN))
    println("")
    
    // ==========================================
    // TEST 4: FILE I/O
    // ==========================================
    println(colorize("📁 TEST 4: File I/O", COLOR_YELLOW))
    
    // Write to file
    muts test_file = fopen("test_output.txt", "w")
    if test_file.fd > 0 {
        fwrite(test_file, "Line 1: Hello Goscript!\n")
        fwrite(test_file, "Line 2: This is a test\n")
        fwrite(test_file, "Line 3: File I/O works!\n")
        fclose(test_file)
        println(colorize("  ✓ File written successfully", COLOR_GREEN))
    } else {
        println(colorize("  ✗ Failed to create file", COLOR_RED))
        tests_failed = tests_failed + 1
    }
    
    // Read from file
    muts read_file = fopen("test_output.txt", "r")
    if read_file.fd > 0 {
        muts content = fread(read_file, 1, 200)
        assert(contains(content, "Hello Goscript"), "Should co
   }
   ret 0;
}
