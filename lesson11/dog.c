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
        set_base(res, print_dog, free, create_dog, NULL);
        set_animal(res, cry_dog);
        return res;
}