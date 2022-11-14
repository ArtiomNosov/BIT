#include "base.h"
void print_base(base_t* base, print_t print)
{
        if (base->print == NULL) {
                print(base);
        } else {
                base->print(base);
        }
}