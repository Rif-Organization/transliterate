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


char *transliterate(const char *input)
{
	char *output = calloc(sizeof(input), sizeof(input));
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
				strcat(output, mapping_table[i].dst);
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
