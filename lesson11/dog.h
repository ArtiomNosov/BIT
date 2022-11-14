#ifndef DOG_H 
#define DOG_h 
#include "animal.h"
typedef struct dog_t {
        animal_t animal;
} dog_t;
dog_t* create_dog();
#endif