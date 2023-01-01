#include "animal.h"
void cry_animal(animal_t* animal)
{
        animal->cry(animal);
}
void set_animal(animal_t* animal, print_t cry)
{
        animal->cry = cry;
}
