#ifndef ANIMAL_H 
#define ANIMAL_H
#include "base.h"
#include <stdio.h>
typedef struct animal_t {
        base_t base;
        print_t cry;
} animal_t;
void cry_animal(animal_t* animal);
void set_animal(animal_t* animal, print_t cry);
#endif