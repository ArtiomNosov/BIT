#ifndef CAT_H 
#define CAT_H
#include "animal.h"
typedef struct cat_t {
        animal_t animal;
} cat_t;
cat_t* create_cat();
#endif