#ifndef AUTOMOBILE
#define AUTOMOBILE
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <time.h>
#include <stdio.h>
#include "Algorithm.h"

#define MINNAMESIZE 2
#define MAXNAMESIZE 64
#define MAXMILEAGE 5000.0
#define BRANDSIZE   17
#define DASH        '-'
#define SPACE       ' '
#define BRANDSYMBOLCOUNT ( 'Z' - 'A' + 1 + 'z' - 'a' + 1 + (1 + 1) )
#define ALPHABETSIZE ( 'Z' - 'A' + 1 + 'z' - 'a' + 1 )

typedef struct Automobile {
    char Brand[BRANDSIZE];
    char* OwnerFullName;
    float Mileage; // In thousands of kilometers
} Automobile;

Automobile* AutomobileNew();
char alphabetRand(int seed);
void brandRand(char* brand);
Automobile* AutomobileNewRand();
Automobile** AutomobileArrayNewRand(size_t n);
Automobile** copy_automobile_array(Automobile** arr, size_t n);
Automobile* AutomobileNewFromData(char* brand, char* ownerFullName, float mileage);
Automobile* AutomobileNewFromAutomobile(Automobile* automobile);
bool IsCharBrand(char* ch);
void AutomobileAssert(Automobile* automobile);
void AutomobileArrayAssert(Automobile** arr, size_t n);
void AutomobileFree(Automobile* automobile);
void AutomobileArrayFree(Automobile** arr, size_t n);

int AutomobileGreaterThanSign(Automobile** automobileLeft, Automobile** automobileRight); // need 
int AutomobileGreaterThanSignVoid(void** automobileLeft, void** automobileRight);
int AutomobileGreaterThanSignBrand(Automobile** automobileLeft, Automobile** automobileRight);
int AutomobileGreaterThanSignBrandVoid(void** automobileLeft, void** automobileRight);
int AutomobileGreaterThanSignOwnerFullName(Automobile** automobileLeft, Automobile** automobileRight);
int AutomobileGreaterThanSignOwnerFullNameVoid(void** automobileLeft, void** automobileRight);
int AutomobileGreaterThanSignMileage(Automobile** automobileLeft, Automobile** automobileRight);
int AutomobileGreaterThanSignMileageVoid(void** automobileLeft, void** automobileRight);

Automobile** AutomobileSort(Automobile** arr, size_t n, void (*sort) (intptr_t* arr, size_t n, bool (*greaterThanSign) (void*, void*) ) );
Automobile** AutomobileSortAnyGreaterThanSign(Automobile** arr, size_t n, void (*sort) (intptr_t* arr, size_t n, bool (*greaterThanSign) (void*, void*) ), bool (*greaterThanSign) (void*, void*) );

#endif
