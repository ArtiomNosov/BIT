#ifndef STRING_H 
#define STRING_H 
#include <stdio.h>
#include <string.h>
#include "base.h"
typedef struct string_t {
        base_t base;
        char* string;
        size_t len;
} string_t;
string_t* create_string(const char* string);
string_t* copy_string(string_t* string);
void delete_string(string_t* string);
char *get_str();
#endif