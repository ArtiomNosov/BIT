#include "dog.h"
void print_dog(dog_t* cat)
{
        printf("Dog %x\n", cat);
}
void cry_dog(dog_t* cat)
{
        printf("Bark\n", cat);
}
dog_t* create_dog()
{
        dog_t* res = calloc(1, sizeof(dog_t));
        ((base_t*)res)->print = (print_t)print_dog;
        ((animal_t*)res)->cry = (print_t)cry_dog;
        return res;
}