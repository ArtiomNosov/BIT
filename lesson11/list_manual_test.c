#include <stdio.h>
#include "list.h"
#define TYPE int
#define TYPE_SIZE sizeof(TYPE)
TYPE* copy(TYPE* p)
{
        TYPE* res = calloc(1, sizeof(TYPE));
        *res = *p;
        return res;
}
void proces(TYPE* p)
{
        printf("%d ", *p);
}
int main()
{
        int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        size_t n = sizeof(arr)/TYPE_SIZE;
        // printf("%d\n", n);
        // printf("%d\n", TYPE_SIZE);
        list* list_int = create_list(arr, n, TYPE_SIZE, (copy_t)copy);
        // printf("%d\n", list_int->n);
        proces_list(list_int, (f_t)proces);
        delete_list(list_int, (del_t)free);
        return 0;
}