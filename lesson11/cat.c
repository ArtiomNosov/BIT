#include "cat.h"
void print_cat(cat_t* cat)
{
        printf("Cat %x\n", cat);
}
void cry_cat(cat_t* cat)
{
        printf("Meow\n", cat);
}
cat_t* create_cat()
{
        cat_t* res = calloc(1, sizeof(cat_t));
        ((base_t*)res)->print = (print_t)print_cat;
        ((animal_t*)res)->cry = (print_t)cry_cat;
        return res;
}