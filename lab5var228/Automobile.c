#include "Automobile.h"

Automobile* AutomobileNew()
{
    Automobile* res = NULL;

    res = malloc(sizeof(Automobile));
    for (int i = 0; i < BRANDSIZE-1; i++)
    {
        (res->Brand)[i] = SPACE;
    }
    (res->Brand)[BRANDSIZE-1] = '\0';
    res->OwnerFullName = NULL;
    res->Mileage = 0.0;

    AutomobileAssert(res);

    return res;
}
char alphabetRand(int seed)
{
    char tmpCh = (ALPHABETSIZE - 1) * ((float)rand()/(RAND_MAX));
    if(tmpCh < 'Z' - 'A' + 1)
    {
        tmpCh = tmpCh + 'A';
    }
    else
    {
        tmpCh = tmpCh - ('Z' - 'A') + 'a';
    }

    return tmpCh;
}
void brandRand(char* brand)
{
    char tmpCh = 0;
    for (int i = 0; i < BRANDSIZE-1; i++)
    {
        tmpCh = (BRANDSYMBOLCOUNT-1) * ((float)rand()/(RAND_MAX - RAND_MAX/10));
        if(tmpCh < 'Z' - 'A' + 1)
        {
            tmpCh = tmpCh + 'A';
        }
        else if(tmpCh < BRANDSYMBOLCOUNT - 2)
        {
            tmpCh = tmpCh - ('Z' - 'A' + 1) + 'a';
        }
        else if(tmpCh == BRANDSYMBOLCOUNT - 2)
        {
            tmpCh = DASH;
        }
        else
        {
            tmpCh = SPACE;
        }
        brand[i] = tmpCh;

    }

}
Automobile* AutomobileNewRand()
{
    Automobile* res = NULL;
    char ownerFullNameSize;

    static int seed = 0;
    seed++;
    srand(seed * time(NULL));

    res = AutomobileNew();

    brandRand(res->Brand);

    ownerFullNameSize = (MAXNAMESIZE - MINNAMESIZE) * ((float)rand()/RAND_MAX) + 1;
    assert(ownerFullNameSize >= 0);
    res->OwnerFullName = malloc((ownerFullNameSize+1) * sizeof(char));
    assert(res->OwnerFullName != NULL);
    for (int i = 0; i < ownerFullNameSize; i++)
    {
        (res->OwnerFullName)[i] = alphabetRand(i);
    }
    (res->OwnerFullName)[ownerFullNameSize] = '\0';
    
    res->Mileage = MAXMILEAGE * ((float)rand()/RAND_MAX);

    AutomobileAssert(res);

    return res;
}
Automobile** AutomobileArrayNewRand(size_t n)
{
    Automobile** res = NULL;
    res = malloc(n * sizeof(Automobile*));

    assert(res != NULL);

    for (int i = 0; i < n; i++)
    {
        res[i] = AutomobileNewRand();
    }
    
    return res;
}
Automobile* AutomobileNewFromData(char* brand, char* ownerFullName, float mileage)
{
    assert(brand != NULL);
    assert(ownerFullName != NULL);
    assert(mileage >= 0.0);

    Automobile* res = NULL;
    size_t ownerFullNameSize = 0;

    res = AutomobileNew();

    memcpy(res->Brand, brand, BRANDSIZE * sizeof(char));
    ownerFullNameSize = strlen(ownerFullName);
    assert(ownerFullNameSize >= 0);
    res->OwnerFullName = malloc( (ownerFullNameSize + 1) * sizeof(char) );
    assert(res->OwnerFullName != NULL);
    memcpy(res->OwnerFullName, ownerFullName, (ownerFullNameSize + 1) * sizeof(char));
    res->Mileage = mileage;

    AutomobileAssert(res);

    return res;
}
Automobile* AutomobileNewFromAutomobile(Automobile* automobile)
{
    AutomobileAssert(automobile);

    Automobile* res = NULL;
    size_t ownerFullNameSize = 0;

    res = AutomobileNew();

    memcpy(res->Brand, automobile->Brand, BRANDSIZE * sizeof(char));
    ownerFullNameSize = strlen(automobile->OwnerFullName);
    assert(ownerFullNameSize >= 0);
    res->OwnerFullName = malloc( (ownerFullNameSize + 1) * sizeof(char) );
    assert(res->OwnerFullName != NULL);
    memcpy(res->OwnerFullName, automobile->OwnerFullName, (ownerFullNameSize + 1) * sizeof(char));
    res->Mileage = automobile->Mileage;

    AutomobileAssert(res);

    return res;
}
bool IsCharBrand(char* ch)
{
    if( *ch == DASH  || \
        *ch == SPACE || \
        *ch >= 'A'   && \
        *ch <= 'Z'   || \
        *ch >= 'a'   && \
        *ch <= 'z'      )
    {
        return true;
    }
    else
    {
        return false;
    }

}
void AutomobileAssert(Automobile* automobile)
{
    assert(automobile != NULL && \
        "automobile is equal to NULL");
    for (int i = 0; i < BRANDSIZE-1; i++)
    {
        assert( (IsCharBrand(automobile->Brand + i) == true) && \
            "automobile has bad Brand");
    }
    assert((automobile->Brand)[BRANDSIZE-1] == '\0');
    assert(automobile->Mileage >= 0.0 && \
        "automobile has negative Mileage");
}
void AutomobileArrayAssert(Automobile** arr, size_t n)
{
    for (int i = 0; i < n; i++)
    {
        AutomobileAssert(arr[i]);
    }
    
}
void AutomobileFree(Automobile* automobile)
{
    AutomobileAssert(automobile);

    if (automobile->OwnerFullName != NULL)
    {
        free(automobile->OwnerFullName);
    }
    free(automobile);

    automobile = NULL;
    
}
void AutomobileArrayFree(Automobile** arr, size_t n)
{
    
    AutomobileArrayAssert(arr, n);

    for (int i = 0; i < n; i++)
    {
        AutomobileFree(arr[i]);
        arr[i] = NULL;
    }
    
    free(arr);

    arr = NULL;
    
}

int AutomobileGreaterThanSign(Automobile** automobileLeft, Automobile** automobileRight)
{
    AutomobileAssert(*automobileLeft);
    AutomobileAssert(*automobileRight);

    int expression1, expression2;

    if( (expression1 = strcmp((*automobileLeft)->Brand, (*automobileRight)->Brand)) > 0 )
    {
        return true;
    }
    else if( (expression2 = strcmp((*automobileLeft)->OwnerFullName, (*automobileRight)->OwnerFullName)) > 0 && expression1 == 0)
    {
        return true;
    }
    else if(((*automobileLeft)->Mileage > (*automobileRight)->Mileage) && expression1 == 0 && expression2 == 0)
    {
        return true;
    }

    return false;
}
int AutomobileGreaterThanSignVoid(void** automobileLeft, void** automobileRight)
{
    return AutomobileGreaterThanSign((Automobile**)automobileLeft, (Automobile**)automobileRight);
}

int AutomobileGreaterThanSignBrand(Automobile** automobileLeft, Automobile** automobileRight)
{
    AutomobileAssert(*automobileLeft);
    AutomobileAssert(*automobileRight);

    if( strcmp((*automobileLeft)->Brand, (*automobileRight)->Brand) > 0 )
    {
        return true;
    }

    return -1;
}
int AutomobileGreaterThanSignBrandVoid(void** automobileLeft, void** automobileRight)
{
    return AutomobileGreaterThanSignBrand((Automobile**)automobileLeft, (Automobile**)automobileRight);
}

int AutomobileGreaterThanSignOwnerFullName(Automobile** automobileLeft, Automobile** automobileRight)
{
    AutomobileAssert(*automobileLeft);
    AutomobileAssert(*automobileRight);

    if( strcmp((*automobileLeft)->OwnerFullName, (*automobileRight)->OwnerFullName) > 0 )
    {
        return true;
    }

    return -1;
}
int AutomobileGreaterThanSignOwnerFullNameVoid(void** automobileLeft, void** automobileRight)
{
    return AutomobileGreaterThanSignOwnerFullName((Automobile**)automobileLeft, (Automobile**)automobileRight);
}

int AutomobileGreaterThanSignMileage(Automobile** automobileLeft, Automobile** automobileRight)
{
    AutomobileAssert(*automobileLeft);
    AutomobileAssert(*automobileRight);

    if((*automobileLeft)->Mileage > (*automobileRight)->Mileage)
    {
        return true;
    }

    return -1;
}
int AutomobileGreaterThanSignMileageVoid(void** automobileLeft, void** automobileRight)
{
    return AutomobileGreaterThanSignMileage((Automobile**)automobileLeft, (Automobile**)automobileRight);
}

Automobile** AutomobileSort(Automobile** arr, size_t n, void (*sort) (intptr_t* arr, size_t n, bool (*greaterThanSign) (void*, void*) ) )
{
    for (int i = 0; i < n; i++)
    {
        AutomobileAssert(arr[i]);
    }

    Automobile** res = malloc(n * sizeof(Automobile*));
    
    assert(res != NULL);

    for (int i = 0; i < n; i++)
    {
        res[i] = AutomobileNewFromAutomobile(arr[i]);
    }
    
    sort((intptr_t*)res, n, (bool(*)(void*, void*))AutomobileGreaterThanSignVoid);

    for (int i = 0; i < n; i++)
    {
        AutomobileAssert(res[i]);
    }

    return res;
}
Automobile** copy_automobile_array(Automobile** arr, size_t n)
{
    if (arr == NULL)
        return NULL;
    Automobile** res = malloc(n * sizeof(Automobile*));
    
    assert(res != NULL);

    for (int i = 0; i < n; i++)
    {
        res[i] = AutomobileNewFromAutomobile(arr[i]);
    }
    return res;
}
Automobile** AutomobileSortAnyGreaterThanSign(Automobile** arr, size_t n, void (*sort) (intptr_t* arr, size_t n, bool (*greaterThanSign) (void*, void*) ), bool (*greaterThanSign) (void*, void*) )
{
    for (int i = 0; i < n; i++)
    {
        AutomobileAssert(arr[i]);
    }

    Automobile** res = malloc(n * sizeof(Automobile*));
    
    assert(res != NULL);

    for (int i = 0; i < n; i++)
    {
        res[i] = AutomobileNewFromAutomobile(arr[i]);
    }
    
    sort((intptr_t*)res, n, greaterThanSign);

    for (int i = 0; i < n; i++)
    {
        AutomobileAssert(res[i]);
    }

    return res;
}