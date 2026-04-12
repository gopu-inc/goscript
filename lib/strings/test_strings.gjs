import strings from "./strings"

fn test_basic() {
    println("=== TEST BASIC ===")
    lt s = "Hello World"
    println(f"String: '{s}'")
    println(f"Length: {strings::len(s)}")
    println(f"Is empty: {strings::is_empty(s)}")
    println(f"Is empty (''): {strings::is_empty('')}")
    println("")
}

fn test_case() {
    println("=== TEST CASE ===")
    lt s = "Hello World"
    println(f"Original: '{s}'")
    println(f"Upper: '{strings::to_upper(s)}'")
    println(f"Lower: '{strings::to_lower(s)}'")
    println(f"Capitalize: '{strings::capitalize('hello')}'")
    println("")
}

fn test_search() {
    println("=== TEST SEARCH ===")
    lt s = "Hello World"
    println(f"Contains 'World': {strings::contains(s, 'World')}")
    println(f"Contains 'xyz': {strings::contains(s, 'xyz')}")
    println(f"Index of 'o': {strings::index_of_char(s, 'o')}")
    println(f"Last index of 'o': {strings::last_index_of_char(s, 'o')}")
    println(f"Index of 'World': {strings::index_of(s, 'World')}")
    println(f"Starts with 'Hello': {strings::starts_with(s, 'Hello')}")
    println(f"Ends with 'World': {strings::ends_with(s, 'World')}")
    println("")
}

fn test_trim() {
    println("=== TEST TRIM ===")
    lt s = "  Hello World  "
    println(f"Original: '{s}'")
    println(f"Trim: '{strings::trim(s)}'")
    println(f"Trim left: '{strings::trim_left(s)}'")
    println(f"Trim prefix '  He': '{strings::trim_prefix(s, '  He')}'")
    println("")
}

fn test_slice() {
    println("=== TEST SLICE ===")
    lt s = "Hello World"
    println(f"Original: '{s}'")
    println(f"Slice(0,5): '{strings::slice(s, 0, 5)}'")
    println(f"Slice(6,11): '{strings::slice(s, 6, 11)}'")
    println(f"Char at 1: '{strings::char_at(s, 1)}'")
    println("")
}

fn test_replace() {
    println("=== TEST REPLACE ===")
    lt s = "Hello Hello Hello"
    println(f"Original: '{s}'")
    println(f"Replace all 'Hello' with 'Hi': '{strings::replace_all(s, 'Hello', 'Hi')}'")
    println(f"Replace first 'Hello' with 'Hi': '{strings::replace_first(s, 'Hello', 'Hi')}'")
    println("")
}

fn test_predicates() {
    println("=== TEST PREDICATES ===")
    println(f"'123': is_number = {strings::is_number('123')}")
    println(f"'12a': is_number = {strings::is_number('12a')}")
    println(f"'abc': is_alpha = {strings::is_alpha('abc')}")
    println(f"'ab12': is_alnum = {strings::is_alnum('ab12')}")
    println("")
}

fn test_repeat_reverse() {
    println("=== TEST REPEAT & REVERSE ===")
    lt s = "Hi"
    println(f"Repeat '{s}' 3x: '{strings::repeat(s, 3)}'")
    println(f"Reverse 'Hello': '{strings::reverse('Hello')}'")
    println("")
}

fn test_hash() {
    println("=== TEST HASH ===")
    lt s = "hello"
    println(f"MD5('{s}'): {strings::md5(s)}")
    println(f"SHA256('{s}'): {strings::sha256(s)}")
    println("")
}

fn test_base64() {
    println("=== TEST BASE64 ===")
    lt s = "Hello World"
    lt encoded = strings::base64_encode(s)
    lt decoded = strings::base64_decode(encoded)
    println(f"Original: '{s}'")
    println(f"Encoded: '{encoded}'")
    println(f"Decoded: '{decoded}'")
    println("")
}

fn main() {
    test_basic()
    test_case()
    test_search()
    test_trim()
    test_slice()
    test_replace()
    test_predicates()
    test_repeat_reverse()
    test_hash()
    test_base64()
    
    println("✅ All tests completed!")
}
