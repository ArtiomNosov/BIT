#include "list.h"
void print_elem(void* elem)
{
        print_t print = ((base_t*)elem)->print;
        if (print == NULL) {
                printf("%x", elem);
        } else {
                print(elem);
        }
}
void print_list(list* cont)
{
        // ERROR PROCESSING
        proces_list(cont, print_elem);
}
