#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include "ManualTestingAutomobile.h"
typedef int(*cmp_t)(const void *, const void *);
typedef enum Menu Menu;
typedef enum ErrorCodes ErrorCodes;

int main()
{
    AutomoblieMenu();
    return 0;
}

void AutomobilePrintf(Automobile* automobile)
{
    AutomobileAssert(automobile);
    printf("Brand: %s \t| Owner: %-64s | Mileage: %4.3f\n", automobile->Brand, automobile->OwnerFullName, automobile->Mileage);
    // Magic number 64 = MAXNAMESIZE from Automobile.h
    // Magic number 5 = count of numbers in MAXMILEAGE + 1 from Automobile.h
}
Automobile* AutomobileScanf()
{
    Automobile* res = AutomobileNew();
    AutomobileAssert(res);

    printf("Print Brand %d symbols or less: ", BRANDSIZE - 1);
    scanf("%s", res->Brand);
    while (AutomobileAssertUI(res) == BadBrand)
    {
        printf("Incorrect input!\nPrint Brand %d char or less: ", BRANDSIZE - 1);
        scanf("%s", res->Brand);
    }
    (res->Brand)[BRANDSIZE - 1] = '\0';
    printf("Print OwnerFullName: ");
    res->OwnerFullName = get_str();
    while (res->OwnerFullName == NULL)
    {
        printf("Incorrect input!\nPrint OwnerFullName: ");
        res->OwnerFullName = get_str();
    }
    printf("Print Mileage: ");
    scanf("%f", &(res->Mileage));
    while (AutomobileAssertUI(res) == BadMileage)
    {
        printf("Incorrect input!\nPrint Mileage: ");
        scanf("%f", &(res->Mileage));
    }

    if(AutomobileAssertUI(res) != OK)
    {
        printf("Fail to enter automobile");
        return NULL;
    }

    return res;
}
bool AutomobileBrendAssertUI(char* brand)
{
    bool res = true;
    for (int i = 0; i < BRANDSIZE-1; i++)
    {
        res &= IsCharBrand(brand + i);
        if(res == false)
        {
            return false;
        }
    }
    return true;

}
int AutomobileAssertUI(Automobile* automobile)
{
    if(automobile == NULL) 
    {
        return NoData;
    } 
    else if (AutomobileBrendAssertUI(automobile->Brand) == false)
    {
        return BadBrand;
    }
    else if (automobile->Mileage < 0.0 )
    {
        return BadMileage;
    }
    
    return OK;
}
void AutomobileArrayAssertUI(Automobile** arr, size_t n, const char* name)
{
    if(errorNoDataInAutomobileArray(arr) == NoData)
    {
        return;
    }

    ErrorCodes err;

    for (size_t i = 0; i < n; i++)
    {
        err = AutomobileAssertUI(arr[i]);
        if(err != OK)
        {
            printf("Ошибка среди автомобилей %s в позиции %ld не корректный автомобиль!\n", name, i);
            scanf("%*c");
            return;
        }

    }

}
int comp (Automobile **i, Automobile **j)
{
    if ((*i)->Mileage > (*j)->Mileage )
        return -1;
    else if ((*i)->Mileage < (*j)->Mileage)
        return 1;
    else 
        return 0;
}
int comp_int(const void* a, const void* b)
{
    int a_i = *(const int*)a;
    int b_i = *(const int*)b;
    if (a_i > b_i)
        return 1;
    else if (a_i < b_i)
        return -1;
    else
        return 0;
}
void AutomoblieMenu()
{
    // int arr[] = {1, 2, 1, 44, 34, 33};
    // size_t n = 6;
    // heapSort(arr, n, sizeof(int), comp_int);
    // for (size_t i = 0; i < n; i++)
    //     printf("%d\n", arr[i]);
    
    Menu menu = SHOW;
    int ui;
    Automobile** source = NULL, ** automobiles = NULL;
    size_t sourceN = 0, automobilesN = 0;
    time_t t0 = 0, t1 = 0;

    while (menu == SHOW)
    {
        printf("***Choice variant***");
        printOptionsAutomoblieMenu();
        scanf("%d%*c", &ui);
        t0 = time(NULL);
        switch (ui)
        {
        case RandomGenerate:
            source = deleteAutomobileArray(source, sourceN);
            source = RandomGenerateAutomobiles(&sourceN);
            break;
        case WriteSourceInConsole:
            WriteAutomobileArrayInConsole(source, sourceN, "source");
            break;
        case WriteResultInConsole:
            WriteAutomobileArrayInConsole(automobiles, automobilesN, "processed");
            break;
        case MenuQuickSortBrand:
            automobiles = deleteAutomobileArray(automobiles, automobilesN);
            automobiles = copy_automobile_array(source, sourceN);
            qsort(automobiles, sourceN, sizeof(Automobile*), (cmp_t)AutomobileGreaterThanSignBrandVoid);
            automobilesN = sourceN;
            printf("Success sort %s\n", "Quick");
            break;
        case MenuHeapSortBrand:
            automobiles = deleteAutomobileArray(automobiles, automobilesN);
            automobiles = copy_automobile_array(source, sourceN);
            heapSort(automobiles, sourceN, sizeof(Automobile*), (cmp_t)AutomobileGreaterThanSignBrandVoid);
            automobilesN = sourceN;
            printf("Success sort %s\n", "Heap");
            break;
        case MenuQuickSortOwnerFullName:
            automobiles = deleteAutomobileArray(automobiles, automobilesN);
            automobiles = copy_automobile_array(source, sourceN);
            qsort(automobiles, sourceN, sizeof(Automobile*), (cmp_t)AutomobileGreaterThanSignOwnerFullNameVoid);
            automobilesN = sourceN;
            printf("Success sort %s\n", "Quick");
            break;
        case MenuHeapSortOwnerFullName:
            automobiles = deleteAutomobileArray(automobiles, automobilesN);
            automobiles = copy_automobile_array(source, sourceN);
            heapSort(automobiles, sourceN, sizeof(Automobile*), (cmp_t)AutomobileGreaterThanSignOwnerFullNameVoid);
            automobilesN = sourceN;
            printf("Success sort %s\n", "Heap");
            break;
        case MenuQuickSortMileage:
            automobiles = deleteAutomobileArray(automobiles, automobilesN);
            automobiles = copy_automobile_array(source, sourceN);
            qsort(automobiles, sourceN, sizeof(Automobile*), (cmp_t)comp);
            automobilesN = sourceN;
            printf("Success sort %s\n", "Quick");
            break;
        case MenuHeapSortMileage:
            automobiles = deleteAutomobileArray(automobiles, automobilesN);
            automobiles = copy_automobile_array(source, sourceN);
            heapSort(automobiles, sourceN, sizeof(Automobile*), (cmp_t)AutomobileGreaterThanSignMileageVoid);
            automobilesN = sourceN;
            printf("Success sort %s\n", "Heap");
            break;
        case EXIT:
            menu = EXIT;
            break;
        default:
            printf("Wrong choice!\n");
            break;
        }
        t1 = time(NULL);
        printf("Time for process %ld seconds\n", t1 - t0);
    }
    automobiles = deleteAutomobileArray(automobiles, automobilesN);
    source = deleteAutomobileArray(source, sourceN);
    printf("\n");

}

void printOptionsAutomoblieMenu()
{
    printf("\n0. Quit\n");
    // printf("1. Ввести исходные автомобили из стандартного потока\n");
    // printf("2. Ввести исходные автомобили из бинарного файла\n");
    printf("1. Random source automobiles\n");

    printf("2. Print source automobiles\n");
    
    
    printf("3. Print res automobiles\n");
    // printf("6. Сохранить исходные автомобили\n");
    // printf("7. Сохранить результат\n");

    printf("4. Quick sort on Brand\n");
    printf("5. Heap sort on Brand\n");

    printf("6. Quick sort on name\n");
    printf("7. Heap sort on name\n");

    printf("8. Quick sort on Mileage\n");
    printf("9. Heap sort on Mileage\n");

}
Automobile**  RandomGenerateAutomobiles(size_t* n)
{
    printf("Input n: ");
    scanf("%u", (unsigned int*)n);

    return AutomobileArrayNewRand(*n);
}

void WriteAutomobileArrayInConsole(Automobile** arr, size_t n, const char* name)
{
    if(errorNoDataInAutomobileArray(arr) == NoData)
    {
        return;
    }

    AutomobileArrayAssertUI(arr, n, name);

    printf("Автомобили %s:\n", name);
    
    for (int i = 0; i < n; i++)
    {
        AutomobilePrintf(arr[i]);
    }
    
}
// void WriteAutomobileArrayInBinaryFile(Automobile** arr, size_t n, const char* name);
int errorNoDataInAutomobileArray(Automobile** arr)
{
    if (arr == NULL)
    {
        printf("Error! You are not input automobiles!\n");
        scanf("%*c");
        return NoData;
    }
    return OK;
}

void* deleteAutomobileArray(Automobile** arr, size_t n)
{
    if(arr != NULL)
    {
        AutomobileArrayFree(arr, n);
    }

    return NULL;
}
