#include <stdio.h>
#include <stdlib.h>
typedef struct cow_t {
        int eat;
        int milk;
} cow_t;
typedef struct farm_t {
        int n;
        cow_t** arr;
} farm_t;
farm_t* create_random_farm(size_t n)
{
        farm_t* res = calloc(1, sizeof(farm_t));
        res->n = n;
        res->arr = calloc(n, sizeof(cow_t*));
        for (size_t i = 0; i < n; i++)
        {
                res->arr[i] = calloc(1, sizeof(cow_t));
                res->arr[i]->eat = rand() % 10;
                res->arr[i]->milk = rand() % 100;
        }
        return res;
}
int comp_milk(const void* a, const void* b)
{
        return (*(cow_t**)a)->milk - (*(cow_t**)b)->milk;
}
void print_farm(farm_t* farm)
{
        for (size_t i = 0; i < farm->n; i++)
        {
                printf("Cow %d\n", i);
                printf("Eat: %d\n", farm->arr[i]->eat);
                printf("Milk: %d\n", farm->arr[i]->milk);
        }
        
}
int sum_milk(farm_t* farm)
{
        int res = 0;
        for (size_t i = 0; i < farm->n; i++)
        {
                res += farm->arr[i]->milk;
        }
        return res;
}
int sum_eat(farm_t* farm)
{
        int res = 0;
        for (size_t i = 0; i < farm->n; i++)
        {
                res += farm->arr[i]->eat;
        }
        return res;
}
int main()
{
        farm_t* farm = create_random_farm(10);
        print_farm(farm);
        qsort(farm->arr, farm->n, sizeof(farm_t*), comp_milk);
        printf("Sort:\n");
        print_farm(farm);
        printf("Sum eat: %d\n", sum_eat(farm));
        printf("Sum milk: %d\n", sum_milk(farm));
        return 0;
}
