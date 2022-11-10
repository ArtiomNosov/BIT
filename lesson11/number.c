#include "number.h"
void print_number(number_t* number)
{
        printf("%d ", number->number);
}
number_t* create_number(int number)
{
        number_t* res = calloc(1, sizeof(number_t));
        res->number = number;
        res->base.print = (print_t)print_number;
        return res;
}
number_t* copy_number(number_t* number)
{
        number_t* res = create_number(number->number);
        return res;
}