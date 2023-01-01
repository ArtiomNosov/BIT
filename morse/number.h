#ifndef NUMBER_H 
#define NUMBER_H 
#include "base.h"
#include <stdio.h>
typedef struct number_t {
        base_t base;
        int number;
} number_t;
number_t* create_number(int number);
number_t* copy_number(number_t* number);
#endif