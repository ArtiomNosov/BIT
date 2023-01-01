#include <stdio.h>
#include "list.h"
#include "number.h"
#include "cat.h"
#include "dog.h"
#define TYPE int
#define TYPE_SIZE sizeof(TYPE)
#define N 10
// gcc animal.c base.c cat.c dog.c list.c list_up.c number.c list_manual_test.c -o list_manual_test.exe
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
        list* list_int = create_list(arr, n, TYPE_SIZE, (copy_t)copy);
        proces_list(list_int, (f_t)proces);
        free_base(list_int);
        list* list_numbers = calloc_list();
        for (size_t i = 0; i < N; i++) {
                number_t* buf = create_number(arr[i]);
                insert_list(list_numbers, buf);
                free(buf);
        }
        printf("\n");
        print_list(list_numbers);
        free_base(list_numbers);
        animal_t* cat = (animal_t*)create_cat();
        animal_t* dog = (animal_t*)create_dog();
        printf("\n");
        cry_animal(cat);
        cry_animal(dog);
        print_base(cat);
        free_base(cat);
        free_base(dog);
        return 0;
}