#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "transliterate.h"


static const TranslitRule mapping_table[] = {
    // --- 1. Spirants (Fricatives) ---
    // The image maps underlined Latin chars to specific Tifinagh spirants.
    { "ṯ",   "ⵝ", 3 },  // t with line below -> ⵝ (Yath)
    { "ḏ",   "ⴸ", 3 },  // d with line below -> ⴸ (Yadh)
    { "ḵ",   "ⴿ", 3 },  // k with line below -> ⴿ (Yakhh/Spirant K)
    { "ḇ",   "ⴲ", 3 },  // b with line below -> ⴲ (Yabh/Spirant B)
    { "g̱",   "ⴴ", 4 },  // g with line below -> ⴴ (Yaghh/Spirant G)

    // --- 2. Labialized Consonants ---
    { "g°",  "ⴳⵯ", 3 }, // g + degree symbol
    { "k°",  "ⴽⵯ", 3 }, // k + degree symbol

    // --- 3. Affricates & Specific Glyphs ---
    { "č",   "ⵞ", 2 },  // c caron -> ⵞ (Yach)
    { "ğ",   "ⴵ", 2 },  // g breve -> ⴵ (Yadj)
    { "ɣ",   "ⵖ", 2 },  // Gamma -> ⵖ (Yagh)
    { "ε",   "ⵄ", 2 },  // Epsilon -> ⵄ (Ayin)

    // --- 4. Emphatic Consonants (Dotted) ---
    { "ḍ",   "ⴹ", 3 },  // Emphatic D
    { "ṭ",   "ⵟ", 3 },  // Emphatic T
    { "ṣ",   "ⵚ", 3 },  // Emphatic S
    { "ẓ",   "ⵥ", 3 },  // Emphatic Z
    { "ṛ",   "ⵕ", 3 },  // Emphatic R
    { "ḥ",   "ⵃ", 3 },  // Emphatic H

    // --- 5. Base Alphabet ---
    { "a",   "ⴰ", 1 },  //
    { "b",   "ⴱ", 1 },  // Standard B
    { "c",   "ⵛ", 1 },  // c -> Sheen
    { "d",   "ⴷ", 1 },  // Standard D
    { "e",   "ⴻ", 1 },  // Schwa
    { "f",   "ⴼ", 1 },  //
    { "g",   "ⴳ", 1 },  // Standard G
    { "h",   "ⵀ", 1 },  //
    { "i",   "ⵉ", 1 },  //
    { "j",   "ⵊ", 1 },  //
    { "k",   "ⴽ", 1 },  // Standard K
    { "l",   "ⵍ", 1 },  //
    { "m",   "ⵎ", 1 },  //
    { "n",   "ⵏ", 1 },  //
    { "q",   "ⵇ", 1 },  //
    { "r",   "ⵔ", 1 },  // Standard R
    { "s",   "ⵙ", 1 },  // Standard S
    { "t",   "ⵜ", 1 },  // Standard T
    { "u",   "ⵓ", 1 },  //
    { "v",   "ⵠ", 1 },  //
    { "w",   "ⵡ", 1 },  //
    { "x",   "ⵅ", 1 },  // x -> Kh
    { "y",   "ⵢ", 1 },  //
    { "z",   "ⵣ", 1 },  //

    { NULL, NULL, 0 }
};


/**
 * Transliterate a UTF-8 encoded Latin-based input string to Tifinagh.
 *
 * This function scans the input from left to right and, at each position,
 * tries to match substrings against the entries in the static mapping_table.
 * When a mapping entry's `src` sequence matches the current position in the
 * input, the corresponding `dst` sequence is appended to the output, and the
 * input cursor advances by the length of the matched `src`.
 *
 * If no mapping entry matches at the current position, the single byte at
 * the cursor is copied unchanged to the output, and the cursor advances by
 * one byte. Characters or sequences that are not explicitly listed in
 * mapping_table are therefore preserved as-is in the result.
 *
 * Memory management:
 *   - The function allocates a new, null-terminated output buffer on the heap
 *     using calloc.
 *   - Ownership of the returned buffer is transferred to the caller.
 *   - The caller is responsible for freeing the returned pointer with free()
 *     when it is no longer needed.
 *
 * \param input  Null-terminated UTF-8 string to transliterate. Can be NULL.
 * \return       Pointer to a newly allocated, null-terminated UTF-8 string
 *               containing the transliterated text, or NULL if input is NULL.
 */
char *transliterate(const char *input)
{
	if (input == NULL)
		return NULL;

	char *output = calloc((strlen(input) * 6 + 1), sizeof(char));

	if (output == NULL)
		return NULL;


	bool matchFound = false;
	const char *cursor = input;

	while (*cursor != '\0')
	{
		for (int i = 0; mapping_table[i].src != NULL; i++)
		{
			const size_t len = mapping_table[i].src_len;
			
			if (strncmp(cursor, mapping_table[i].src, len) == 0)
			{
				cursor += len;
				strncat(output, mapping_table[i].dst, len);
				matchFound = true;
				break;
			}
		}


		if (matchFound == false)
		{
			strncat(output, cursor, 1);
			cursor += 1;
		}

		matchFound = false;
	}

	return output;
}
