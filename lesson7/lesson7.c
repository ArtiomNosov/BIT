// Разные алгоритмы сортировок. O-символика. Шаблон STD qsort(...)
#include <stdio.h>
#include <stdlib.h>

int num[10] = {
1,3,6,5,8,7,9,6,2,0
};

int comp (const int *, const int *);

int main(void)
{
    int i;
    printf("Original array: ");
    for (i=0; i<10; i++) 
        printf("%d ",num[i]);
    printf ("\n");
    // qsort(num, 10, sizeof (int), (int(*) (const void *, const void *)) comp);
    int tmp = 0;
    for(int i = 0; i < 10; i++) {
	    for(int j = 1; j < 10 - i; j++) {
  		    if (num[j-1] > num[j]) {
                tmp = num[j];
                num[j] = num[j-1];
                num[j-1] = tmp;
            }
        }
    }
    printf("Sorted array: ");
    for(i = 0; i <10; i++) 
        printf("%d ", num[i]);
    return 0;
}

/* сравнение двух целых */
int comp (const int *i, const int *j)
{
    return *i - *j;
}