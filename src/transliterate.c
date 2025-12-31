#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "transliterate.h"


static const TranslitRule mapping_table[] = {
    // --- 1. Spirants (Fricatives) ---
    // The image maps underlined Latin chars to specific Tifinagh spirants.
    { "ṯ",   "ⵝ" },  // t with line below -> ⵝ (Yath)
    { "ḏ",   "ⴸ" },  // d with line below -> ⴸ (Yadh)
    { "ḵ",   "ⴿ" },  // k with line below -> ⴿ (Yakhh/Spirant K)
    { "ḇ",   "ⴲ" },  // b with line below -> ⴲ (Yabh/Spirant B)
    { "g̱",   "ⴴ" },  // g with line below -> ⴴ (Yaghh/Spirant G)

    // --- 2. Labialized Consonants ---
    { "g°",  "ⴳⵯ" }, // g + degree symbol
    { "k°",  "ⴽⵯ" }, // k + degree symbol

    // --- 3. Affricates & Specific Glyphs ---
    { "č",   "ⵞ" },  // c caron -> ⵞ (Yach)
    { "ğ",   "ⴵ" },  // g breve -> ⴵ (Yadj)
    { "ɣ",   "ⵖ" },  // Gamma -> ⵖ (Yagh)
    { "ε",   "ⵄ" },  // Epsilon -> ⵄ (Ayin)

    // --- 4. Emphatic Consonants (Dotted) ---
    { "ḍ",   "ⴹ" },  // Emphatic D
    { "ṭ",   "ⵟ" },  // Emphatic T
    { "ṣ",   "ⵚ" },  // Emphatic S
    { "ẓ",   "ⵥ" },  // Emphatic Z
    { "ṛ",   "ⵕ" },  // Emphatic R
    { "ḥ",   "ⵃ" },  // Emphatic H

    // --- 5. Base Alphabet ---
    { "a",   "ⴰ" },  //
    { "b",   "ⴱ" },  // Standard B
    { "c",   "ⵛ" },  // c -> Sheen
    { "d",   "ⴷ" },  // Standard D
    { "e",   "ⴻ" },  // Schwa
    { "f",   "ⴼ" },  //
    { "g",   "ⴳ" },  // Standard G
    { "h",   "ⵀ" },  //
    { "i",   "ⵉ" },  //
    { "j",   "ⵊ" },  //
    { "k",   "ⴽ" },  // Standard K
    { "l",   "ⵍ" },  //
    { "m",   "ⵎ" },  //
    { "n",   "ⵏ" },  //
    { "q",   "ⵇ" },  //
    { "r",   "ⵔ" },  // Standard R
    { "s",   "ⵙ" },  // Standard S
    { "t",   "ⵜ" },  // Standard T
    { "u",   "ⵓ" },  //
    { "v",   "ⵠ" },  //
    { "w",   "ⵡ" },  //
    { "x",   "ⵅ" },  // x -> Kh
    { "y",   "ⵢ" },  //
    { "z",   "ⵣ" },  //

    { NULL, NULL }
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
			const int len = strlen(mapping_table[i].src);
			
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
