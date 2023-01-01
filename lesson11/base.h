#ifndef BASE_H 
#define BASE_H 
#include <stdlib.h>
#include <string.h>
typedef void(*f_t)(void*);
typedef f_t print_t;
typedef f_t free_t;
typedef void*(*calloc_t)();
typedef void*(*copy_t)(void*);
typedef struct base_t {
        print_t print; 
        free_t free_f;
        calloc_t calloc_f;
        copy_t copy;
} base_t;
void print_base(base_t* base);
void free_base(base_t* base);
void set_base(base_t* base, print_t print, free_t free_f, calloc_t calloc_f, copy_t copy);
void* calloc_base(base_t* base);
void* copy_base(base_t* base);
#endif