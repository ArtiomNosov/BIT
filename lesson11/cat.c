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
        set_base(res, print_cat, free, create_cat, NULL);
        set_animal(res, cry_cat);
        return res;
}