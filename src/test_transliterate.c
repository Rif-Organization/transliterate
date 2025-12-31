#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "transliterate.h"

// Test result tracking
static int tests_run = 0;
static int tests_passed = 0;
static int tests_failed = 0;

// ANSI color codes for output
#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED "\033[0;31m"
#define COLOR_RESET "\033[0m"

// Test helper function
bool assert_transliteration(const char *input, const char *expected, const char *test_name)
{
	tests_run++;
	
	char *result = transliterate(input);
	
	if (result == NULL && expected == NULL) {
		printf(COLOR_GREEN "✓ PASS" COLOR_RESET ": %s\n", test_name);
		tests_passed++;
		return true;
	}
	
	if (result == NULL || expected == NULL) {
		printf(COLOR_RED "✗ FAIL" COLOR_RESET ": %s\n", test_name);
		printf("  Expected: %s\n", expected ? expected : "NULL");
		printf("  Got:      %s\n", result ? result : "NULL");
		tests_failed++;
		if (result) free(result);
		return false;
	}
	
	if (strcmp(result, expected) == 0) {
		printf(COLOR_GREEN "✓ PASS" COLOR_RESET ": %s\n", test_name);
		tests_passed++;
		free(result);
		return true;
	} else {
		printf(COLOR_RED "✗ FAIL" COLOR_RESET ": %s\n", test_name);
		printf("  Input:    %s\n", input);
		printf("  Expected: %s\n", expected);
		printf("  Got:      %s\n", result);
		tests_failed++;
		free(result);
		return false;
	}
}

void test_basic_alphabet()
{
	printf("\n=== Testing Basic Alphabet ===\n");
	
	assert_transliteration("a", "ⴰ", "Single character: a");
	assert_transliteration("b", "ⴱ", "Single character: b");
	assert_transliteration("c", "ⵛ", "Single character: c");
	assert_transliteration("d", "ⴷ", "Single character: d");
	assert_transliteration("e", "ⴻ", "Single character: e");
	assert_transliteration("f", "ⴼ", "Single character: f");
	assert_transliteration("g", "ⴳ", "Single character: g");
	assert_transliteration("h", "ⵀ", "Single character: h");
	assert_transliteration("i", "ⵉ", "Single character: i");
	assert_transliteration("j", "ⵊ", "Single character: j");
	assert_transliteration("k", "ⴽ", "Single character: k");
	assert_transliteration("l", "ⵍ", "Single character: l");
	assert_transliteration("m", "ⵎ", "Single character: m");
	assert_transliteration("n", "ⵏ", "Single character: n");
	assert_transliteration("q", "ⵇ", "Single character: q");
	assert_transliteration("r", "ⵔ", "Single character: r");
	assert_transliteration("s", "ⵙ", "Single character: s");
	assert_transliteration("t", "ⵜ", "Single character: t");
	assert_transliteration("u", "ⵓ", "Single character: u");
	assert_transliteration("v", "ⵠ", "Single character: v");
	assert_transliteration("w", "ⵡ", "Single character: w");
	assert_transliteration("x", "ⵅ", "Single character: x");
	assert_transliteration("y", "ⵢ", "Single character: y");
	assert_transliteration("z", "ⵣ", "Single character: z");
}

void test_words()
{
	printf("\n=== Testing Words ===\n");
	
	assert_transliteration("azul", "ⴰⵣⵓⵍ", "Word: azul");
	assert_transliteration("tamazight", "ⵜⴰⵎⴰⵣⵉⴳⵀⵜ", "Word: tamazight");
	assert_transliteration("amzigh", "ⴰⵎⵣⵉⴳⵀ", "Word: amzigh");
}

void test_spirants()
{
	printf("\n=== Testing Spirants (Fricatives) ===\n");
	
	assert_transliteration("ṯ", "ⵝ", "Spirant: ṯ (t with line below)");
	assert_transliteration("ḏ", "ⴸ", "Spirant: ḏ (d with line below)");
	assert_transliteration("ḵ", "ⴿ", "Spirant: ḵ (k with line below)");
	assert_transliteration("ḇ", "ⴲ", "Spirant: ḇ (b with line below)");
	assert_transliteration("g̱", "ⴴ", "Spirant: g̱ (g with line below)");
}

void test_labialized()
{
	printf("\n=== Testing Labialized Consonants ===\n");
	
	assert_transliteration("g°", "ⴳⵯ", "Labialized: g°");
	assert_transliteration("k°", "ⴽⵯ", "Labialized: k°");
	assert_transliteration("g°k°", "ⴳⵯⴽⵯ", "Combined labialized: g°k°");
}

void test_affricates()
{
	printf("\n=== Testing Affricates & Specific Glyphs ===\n");
	
	assert_transliteration("č", "ⵞ", "Affricate: č (c caron)");
	assert_transliteration("ğ", "ⴵ", "Affricate: ğ (g breve)");
	assert_transliteration("ɣ", "ⵖ", "Gamma: ɣ");
	assert_transliteration("ε", "ⵄ", "Epsilon: ε");
}

void test_emphatic()
{
	printf("\n=== Testing Emphatic Consonants ===\n");
	
	assert_transliteration("ḍ", "ⴹ", "Emphatic: ḍ");
	assert_transliteration("ṭ", "ⵟ", "Emphatic: ṭ");
	assert_transliteration("ṣ", "ⵚ", "Emphatic: ṣ");
	assert_transliteration("ẓ", "ⵥ", "Emphatic: ẓ");
	assert_transliteration("ṛ", "ⵕ", "Emphatic: ṛ");
	assert_transliteration("ḥ", "ⵃ", "Emphatic: ḥ");
}

void test_edge_cases()
{
	printf("\n=== Testing Edge Cases ===\n");
	
	assert_transliteration(NULL, NULL, "NULL input");
	assert_transliteration("", "", "Empty string");
	assert_transliteration(" ", " ", "Single space");
	assert_transliteration("  ", "  ", "Multiple spaces");
	assert_transliteration("123", "123", "Numbers (unmapped)");
	assert_transliteration("!@#", "!@#", "Special characters (unmapped)");
	assert_transliteration("hello world", "ⵀⴻⵍⵍo ⵡoⵔⵍⴷ", "Mixed mapped and unmapped");
}

void test_priority()
{
	printf("\n=== Testing Multi-byte Priority (longer matches first) ===\n");
	
	// Test that multi-byte characters are matched before single-byte
	// For example, "g°" should match as labialized, not as "g" + "°"
	assert_transliteration("g°a", "ⴳⵯⴰ", "Labialized g° followed by a");
	assert_transliteration("ag°", "ⴰⴳⵯ", "a followed by labialized g°");
}

void test_memory_safety()
{
	printf("\n=== Testing Memory Safety ===\n");
	
	// Test with longer strings to ensure proper memory allocation
	char *long_input = "abcdefghijklmnopqrstuvwxyz";
	char *result = transliterate(long_input);
	
	tests_run++;
	if (result != NULL) {
		printf(COLOR_GREEN "✓ PASS" COLOR_RESET ": Long string memory allocation\n");
		tests_passed++;
		free(result);
	} else {
		printf(COLOR_RED "✗ FAIL" COLOR_RESET ": Long string memory allocation\n");
		tests_failed++;
	}
	
	// Test with string containing only multi-byte UTF-8 characters
	char *utf8_input = "ṯḏḵḇ";
	result = transliterate(utf8_input);
	
	tests_run++;
	if (result != NULL) {
		printf(COLOR_GREEN "✓ PASS" COLOR_RESET ": UTF-8 multi-byte string memory allocation\n");
		tests_passed++;
		free(result);
	} else {
		printf(COLOR_RED "✗ FAIL" COLOR_RESET ": UTF-8 multi-byte string memory allocation\n");
		tests_failed++;
	}
}

int main()
{
	printf("\n");
	printf("╔════════════════════════════════════════════════════════════╗\n");
	printf("║         Transliterate Function Test Suite                 ║\n");
	printf("╚════════════════════════════════════════════════════════════╝\n");
	
	test_basic_alphabet();
	test_words();
	test_spirants();
	test_labialized();
	test_affricates();
	test_emphatic();
	test_edge_cases();
	test_priority();
	test_memory_safety();
	
	// Print summary
	printf("\n");
	printf("╔════════════════════════════════════════════════════════════╗\n");
	printf("║                      Test Summary                          ║\n");
	printf("╚════════════════════════════════════════════════════════════╝\n");
	printf("  Total tests:  %d\n", tests_run);
	printf("  " COLOR_GREEN "Passed:       %d" COLOR_RESET "\n", tests_passed);
	printf("  " COLOR_RED "Failed:       %d" COLOR_RESET "\n", tests_failed);
	printf("\n");
	
	if (tests_failed == 0) {
		printf(COLOR_GREEN "✓ All tests passed!" COLOR_RESET "\n\n");
		return 0;
	} else {
		printf(COLOR_RED "✗ Some tests failed!" COLOR_RESET "\n\n");
		return 1;
	}
}
