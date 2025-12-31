#pragma once


typedef struct {
	const char *src;
	const char *dst;
} TranslitRule;

char* transliterate(const char *input);
