#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct istr {
	const char *s;
	const size_t len;
} istr;

istr cstr(const char * cstring);

istr istr_cat(istr *a, istr *b);
void istr_free(istr *str);
uint64_t istr_index_of(istr *str, char c); //TODO: add support to get index of a string
bool istr_cmp(istr *a, istr *b);
istr istr_remove(istr *str, uint64_t index);

// TODO: create istr_builder type
// TODO: add istr_remove_all function that removes all instances of a character from a string

#ifdef ISTR_IMPLEMENT

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

istr cstr(const char *cstring) {
	istr res = {.len = strlen(cstring)};
	res.s = malloc(sizeof(char) * (res.len + 1));
	if (res.s == NULL) {
		puts("Error allocating string");
		exit(EXIT_FAILURE);
	}

	memcpy((void*) res.s, cstring, res.len + 1);

	return res;
}

istr istr_cat(istr *a, istr *b) {
	istr res = {.len = a->len + b->len};
	res.s = malloc(sizeof(char) * (res.len + 1));
	if (res.s == NULL) {
		puts("Error allocating string");
		exit(EXIT_FAILURE);
	}

	memcpy((void*) res.s, a->s, a->len);
	memcpy((void*) (res.s + a->len), b->s, b->len + 1);

	return res;	
}

void istr_free(istr *str) {
	free((void*) str->s);
}

unsigned long istr_index_of(istr *str, char c) {
	for (size_t i = 0; i < str->len; i++) {
		if (str->s[i] == c) return i;
	}
	printf("Error: %c not found in string\n", c);
	exit(EXIT_FAILURE);
}

bool istr_cmp(istr *a, istr *b) {
    if (a->len != b->len) return false;
    for (size_t i = 0; i < a->len; i++) {
        if (a->s[i] != b->s[i]) return false;
    }
    return true;
}

istr istr_remove(istr *str, uint64_t index) {
	istr res = {.s = malloc(sizeof(char) * str->len), .len = str->len - 1};
	if (res.s == NULL) {
		puts("Error allocating string");
		exit(EXIT_FAILURE);
	}

	memcpy((void*)res.s, str->s, index);
	memcpy((void*)&res.s[index], &str->s[index + 1], str->len - index);
	return res;
}

#endif
