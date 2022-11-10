#ifndef BASE_H 
#define BASE_H 
#include <stdlib.h>
typedef void(*f_t)(void*);
typedef f_t print_t;
typedef struct base_t {
        print_t print; 
} base_t;
#endif