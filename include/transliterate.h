#pragma once


typedef struct {
	const char *src;
	const char *dst;
	size_t src_len;
} TranslitRule;

char* transliterate(const char *input);
