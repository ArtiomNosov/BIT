#include "base.h"
void print_exeption(void* ptr)
{
        printf("Try to print structure with adress %x that do not have print function\n");
}
void print_base_option(base_t* base, print_t print)
{
        if (base->print == NULL) {
                print(base);
        } else {
                base->print(base);
        }
}
void print_base(base_t* base)
{
        print_base_option(base, print_exeption);
}
void free_exeption(void* ptr)
{
        free(ptr);
}
void free_base_option(base_t* base, free_t free_f)
{
        if (base->free_f == NULL) {
                free_f(base);
        } else {
                base->free_f(base);
        }
}
void free_base(base_t* base)
{
        free_base_option(base, free_exeption);
}
void set_base(base_t* base, print_t print, free_t free_f, calloc_t calloc_f, copy_t copy)
{
        if (base == NULL)
                return;
        base->print = print;
        base->free_f = free_f;
        base->calloc_f = calloc_f;
        base->copy = copy;
}
void* calloc_exeption()
{
        return (base_t*) calloc(1, sizeof(base_t));
}
void* calloc_base_option(base_t* base, calloc_t calloc_f)
{
        if (base->calloc_f == NULL) {
                return calloc_f();
        } else {
                return base->calloc_f();
        }
}
void* calloc_base(base_t* base)
{
        return calloc_base_option(base, calloc_exeption);
}
void* copy_exeption(void* ptr)
{
        base_t* res = (base_t*) calloc(1, sizeof(base_t));
        memcpy(res, ptr, sizeof(base_t));
        return res;
}
void* copy_base_option(base_t* base, copy_t copy)
{
        if (base->copy == NULL) {
                return copy(base);
        } else {
                return base->copy(base);
        }
}
void* copy_base(base_t* base)
{
        return copy_base_option(base, copy_exeption);
}