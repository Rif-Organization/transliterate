#include <stdio.h>
#include <stdlib.h>

#include "transliterate.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		puts("Provide text to transliterate to Tifinagh");
		return 0;
	}

	char *transliteratedText = transliterate(argv[1]);
	puts(transliteratedText);
	free(transliteratedText);
	return 0;
}
