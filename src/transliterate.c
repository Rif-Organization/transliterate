#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "transliterate.h"


static const TranslitRule mapping_table[] = {
    // --- 1. Spirants (Fricatives) ---
    // The image maps underlined Latin chars to specific Tifinagh spirants.
    { "ṯ",   "ⵝ", 3, 3 },  // t with line below -> ⵝ (Yath)
    { "ḏ",   "ⴸ", 3, 3 },  // d with line below -> ⴸ (Yadh)
    { "ḵ",   "ⴿ", 3, 3 },  // k with line below -> ⴿ (Yakhh/Spirant K)
    { "ḇ",   "ⴲ", 3, 3 },  // b with line below -> ⴲ (Yabh/Spirant B)
    { "g̱",   "ⴴ", 3, 3 },  // g with line below -> ⴴ (Yaghh/Spirant G)

    // --- 2. Labialized Consonants ---
    { "g°",  "ⴳⵯ", 3, 6 }, // g + degree symbol
    { "k°",  "ⴽⵯ", 3, 6 }, // k + degree symbol

    // --- 3. Affricates & Specific Glyphs ---
    { "č",   "ⵞ", 2, 3 },  // c caron -> ⵞ (Yach)
    { "ğ",   "ⴵ", 2, 3 },  // g breve -> ⴵ (Yadj)
    { "ɣ",   "ⵖ", 2, 3 },  // Gamma -> ⵖ (Yagh)
    { "ε",   "ⵄ", 2, 3 },  // Epsilon -> ⵄ (Ayin)

    // --- 4. Emphatic Consonants (Dotted) ---
    { "ḍ",   "ⴹ", 3, 3 },  // Emphatic D
    { "ṭ",   "ⵟ", 3, 3 },  // Emphatic T
    { "ṣ",   "ⵚ", 3, 3 },  // Emphatic S
    { "ẓ",   "ⵥ", 3, 3 },  // Emphatic Z
    { "ṛ",   "ⵕ", 3, 3 },  // Emphatic R
    { "ḥ",   "ⵃ", 3, 3 },  // Emphatic H

    // --- 5. Base Alphabet ---
    { "a",   "ⴰ", 1, 3 },  //
    { "b",   "ⴱ", 1, 3 },  // Standard B
    { "c",   "ⵛ", 1, 3 },  // c -> Sheen
    { "d",   "ⴷ", 1, 3 },  // Standard D
    { "e",   "ⴻ", 1, 3 },  // Schwa
    { "f",   "ⴼ", 1, 3 },  //
    { "g",   "ⴳ", 1, 3 },  // Standard G
    { "h",   "ⵀ", 1, 3 },  //
    { "i",   "ⵉ", 1, 3 },  //
    { "j",   "ⵊ", 1, 3 },  //
    { "k",   "ⴽ", 1, 3 },  // Standard K
    { "l",   "ⵍ", 1, 3 },  //
    { "m",   "ⵎ", 1, 3 },  //
    { "n",   "ⵏ", 1, 3 },  //
    { "q",   "ⵇ", 1, 3 },  //
    { "r",   "ⵔ", 1, 3 },  // Standard R
    { "s",   "ⵙ", 1, 3 },  // Standard S
    { "t",   "ⵜ", 1, 3 },  // Standard T
    { "u",   "ⵓ", 1, 3 },  //
    { "v",   "ⵠ", 1, 3 },  //
    { "w",   "ⵡ", 1, 3 },  //
    { "x",   "ⵅ", 1, 3 },  // x -> Kh
    { "y",   "ⵢ", 1, 3 },  //
    { "z",   "ⵣ", 1, 3 },  //

    { NULL, NULL, 0, 0 }
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

	// Calculate maximum dst_len once (static to avoid recomputation)
	static size_t max_dst_len = 0;
	if (max_dst_len == 0)
	{
		for (int i = 0; mapping_table[i].src != NULL; i++)
		{
			if (mapping_table[i].dst_len > max_dst_len)
				max_dst_len = mapping_table[i].dst_len;
		}
	}

	size_t input_len = strlen(input);
	char *output = calloc((input_len * max_dst_len + 1), sizeof(char));

	if (output == NULL)
		return NULL;


	bool matchFound = false;
	const char *cursor = input;
	char *out_pos = output;

	while (*cursor != '\0')
	{
		for (int i = 0; mapping_table[i].src != NULL; i++)
		{
			const size_t len = mapping_table[i].src_len;
			
			if (strncmp(cursor, mapping_table[i].src, len) == 0)
			{
				cursor += len;
				memcpy(out_pos, mapping_table[i].dst, mapping_table[i].dst_len);
				out_pos += mapping_table[i].dst_len;
				matchFound = true;
				break;
			}
		}


		if (matchFound == false)
		{
			*out_pos = *cursor;
			out_pos++;
			cursor += 1;
		}

		matchFound = false;
	}

	*out_pos = '\0';

	return output;
}
