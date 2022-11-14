#include <stdio.h>
#include "list.h"
#include "number.h"
#include "cat.h"
#include "dog.h"
#define TYPE int
#define TYPE_SIZE sizeof(TYPE)
#define N 10
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
        list* list_numbers = calloc_list();
        for (size_t i = 0; i < N; i++) {
                number_t* buf = create_number(arr[i]);
                insert_list(list_numbers, buf, (copy_t)copy_number);
                free(buf);
        }
        printf("\n");
        print_list(list_numbers);
        delete_list(list_numbers, (del_t)free);
        animal_t* cat = (animal_t*)create_cat();
        animal_t* dog = (animal_t*)create_dog();
        printf("\n");
        cry_animal(cat);
        cry_animal(dog);
        ((base_t*)cat)->print(cat);
        free(cat);
        free(dog);
        return 0;
}