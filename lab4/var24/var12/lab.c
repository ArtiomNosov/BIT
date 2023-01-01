#include <stdlib.h>
#include <stdio.h>
typedef int(*cmpt_t)(const void*, const void*);
// done
void memcpy(void* dest, const void* source, size_t size)
{
        if (dest == NULL || source == NULL)
                return;
        char* d = (char*)dest;
        const char* s = (const char*)source;
        for (size_t i = 0; i < size; i++)
                d[i] = s[i];        
}
int isEnd(char ch)
{
        return ch == '\0' || ch == -1;
}
// done
size_t strlen(const char* str)
{
        if (str == NULL)
                return 0;
        size_t res = 0;
        for (size_t i = 0; !isEnd(str[i]); i++)
                res++;
        return res;  
}
// done +-
char *get_str()
{
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int n = 0;

    do {

        n = scanf("%80[^\n]", buf);
        
        if (n<0)
        {
            if (!res)
            {
                return NULL;
            }
        } else if (n > 0) {

            int chunk_len = strlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 2);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            scanf("%*c");
        }
    } while (n > 0);


    if (len > 0)
    {
        res[len] = '\0';
        res[len+1] = '\0';
    } else {
        res = calloc(1, sizeof(char));
        *res = '\0';
    }

    return res;
}
// done
int cmp (const char *i, const char *j)
{
    return *i - *j;
}
// done
void print_array_int(int* arr, int n)
{
        if (arr == NULL)
                return;
        for (size_t i = 0; i < n; i++)
                printf("%d ", arr[i]);
        printf("\n");
}
// done +-
int strcmp(char* str1, char* str2)
{
        for (size_t i = 0; ; i++) {
                if(str1[i]!=str2[i])
                        return 1;
                if (str1[i]=='\0' && str2[i]=='\0')
                        return 0;
                if (str1[i]=='\0')
                        return -1;
                if (str2[i]=='\0')
                        return 1;
        }
        return 0;
} 
// done
void print_array_string(char** arr, int n)
{
        if (arr == NULL)
                return;
        for (size_t i = 0; i < n; i++)
                printf("%s ", arr[i]);
        printf("\n");
}
const char* menu_options[] = {
        "***Menu***",
        "1) Quit the programm",
        "2) Input strings",
        "3) Delete words that consists the same letters"
};
// done
void printMenu(const char** menu, size_t n)
{
        if (menu == NULL)
                return;
        for (size_t i = 0; i < n; i++)
                printf("%s\n", menu[i]);
}
// done +-
void print_chose_option(const char** menu, int option)
{
        if (menu == NULL)
                return;
        printf("You chose \"%s\"\n", menu[option - '0']);    
}
// done +-
int have(char ch, char* string)
{
        if (string == NULL)
                return 0;
        while (!isEnd(string[0]))
        {
                if (ch == string[0])
                        return 1;
                string++;
        }
        return 0;
        
}
// done +-
char* returnBeginWord(char* string, char* seps)
{
        if (!have(string[0], seps))
                return string;
        char* cur = string;
        while (have(cur[0], seps)) {
                cur++;
                if (isEnd(cur[0]))
                        return string;
        }
        return cur;
}
// done
int returnWordLen(char* word, char* seps)
{
        if (word == NULL)
                return 0;
        int res = 0;
        while(!have(word[0], seps) && !isEnd(word[0])) {
                word++;
                res++;
        }
        return res;
}
// done
char* setFromWord(char* word, char* seps)
{
        if (word == NULL)
                return NULL;
        int len = returnWordLen(word, seps);
        char* res = calloc(len + 1, sizeof(char));
        size_t v = 0;
        for (size_t i = 0; !have(word[i], seps) && !isEnd(word[i]); i++)
        {
                if (!have(word[i], res)) {
                        res[v] = word[i];
                        v++;
                        // printf("%c", word[i]);
                }
        }
        // printf(" ");
        return res;
}
// done. each word have only one sep and last one don't have sep
int returnCountWords(char* string, char* seps)
{
        if (string == NULL || seps == NULL)
                return 0;
        int res = 0;
        while (!isEnd(string[0]))
        {
                if (have(string[0], seps))
                        res++;
                string++;
        }
        return res + 1;
}
// done +-
char* nextWord(char* word, char* seps)
{
        if (word == NULL || seps == NULL)
                return NULL;
        if (isEnd(word[1]))
                return NULL;
        if (have(word[0], seps))
                return ++word;
        char* cur = word;
        while (!have(cur[0], seps)) {
                cur++;
                if (isEnd(cur[0]))
                        return NULL;
        }
        return ++cur;
}
// done
char** returnSetsOfLettersFromWords(char* string, char* seps, int countWords)
{
        if (string == NULL || seps == NULL)
                return NULL;
        char* begin = returnBeginWord(string, seps);
        char** res = calloc(countWords, sizeof(char*));
        size_t v = 0;
        for (size_t i = 0; i < countWords; i++) {
                // printf("begin: %s\n", begin);
                res[v] = setFromWord(begin, seps);
                v++;
                begin = nextWord(begin, seps);
                if (begin == NULL)
                        break;
        }
        return res;
}
// done
int haveInt(int a, int* arr, int n)
{
        if (arr == NULL || n == 0)
                return 0;
        for (size_t i = 0; i < n; i++)
        {
                if (a == arr[i])
                        return 1;
        }
        return 0;
}
// done
void appendIfDontHave(int a, int* arr, int *n)
{
        if (arr == NULL || n == NULL)
                return;
        if (!haveInt(a, arr, *n)) {
                arr[*n] = a;
                (*n)++;
        }
}
// done
int* returnIndexesRepeatsOfSets(char** arr, int n)
{
        
        int* res = calloc(n, sizeof(int));
        for (size_t i = 0; i < n; i++)
        {
                res[i]=-1;
        }
        
        int flag = 0;
        int v = 0;
        for (size_t i = 0; i < n; i++)
        {
                flag = 0;
                for (size_t j = i + 1; j < n; j++)
                {
                        if (strcmp(arr[i], arr[j]) == 0) {
                                appendIfDontHave(j, res, &v);
                                flag = 1;
                        }
                                
                }
                if (flag == 1) {
                        appendIfDontHave(i, res, &v);
                }
                
        }
        return res;
}
// done +-
char* copy_word(char* str, char* seps)
{
        if (str == NULL || seps == NULL)
                return NULL;
        char* res = NULL;
        size_t n = returnWordLen(str, seps);
        res = calloc(n + 1, sizeof(char));
        memcpy(res, str, n);
        return res;
}
// done +-
char** splitString(char* string, char* seps, int countWords)
{
        if (string == NULL || seps == NULL)
                return NULL;
        char** res = calloc(countWords, sizeof(char*));
        size_t v = 0;
        char* begin = string;
        for (size_t i = 0; i < countWords; i++) {
                res[v] = copy_word(begin, seps);
                v++;
                begin = nextWord(begin, seps);
                if (begin == NULL)
                        return res;
        }
        return res;
}
// done
int intCmp(const int* a, const int* b)
{
        return *a - *b;
}
// done +-. repeats is sorted
void printAnswerOfTheTask(char** arr, int n, int* repeats)
{
        
        int flag = 0;
        size_t v = 0;
        for (size_t i = 0; i < n; i++)
        {
                if (!haveInt(i, repeats, n)) {
                        printf("%s ", arr[i]);
                }
        }
        printf("\n");
}
// done +-
void delLastSeps(char* string, char* seps)
{
        if (string == NULL || seps == NULL)
                return;
        char* cur = string;
        while (!isEnd(cur[0]))
        {
                cur++;
        }
        cur--;
        while (have(cur[0], seps))
        {
                cur[0] = '\0';
                if (cur == string)
                        break;
                cur--;

        }
        
}
// done +-
size_t count_double_sep(char* str, char* sep)
{
        if (str == NULL)
                return 0;
        size_t res = 0;
        for (size_t i = 0; !isEnd(str[i]); i++)
                if (have(str[i], sep) && have(str[i+1], sep))
                        res++;
        return res;
}
// done +-
char* del_double_sep(char* str, char* sep)
{
        if (str == NULL)
                return NULL;
        size_t count_sep = count_double_sep(str, sep);
        size_t len = strlen(str);
        char* res = calloc(len - count_sep, sizeof(char));
        size_t u = 0;
        for (size_t i = 0; !isEnd(str[i]); i++)
                if (!(have(str[i], sep) && have(str[i+1], sep))) {
                        if (have(str[i], sep))
                                res[u] = ' ';
                        else
                                res[u] = str[i];
                        u++;
                }
        return res;
}
// done +-
int returnFirstMunusOneElemIndex(int* arr, int n)
{
        if (arr == NULL || n == 0)
                return 0;
        for (size_t i = 0; i < n; i++)
        {
                if (arr[i] == -1 && i != 0)
                        return i;
        }
        return 0;
}
void doTask(char* input)
{
        char* seps = " \t\n";
        delLastSeps(input, seps);
        char* newInput = del_double_sep(input, seps);
        char* begin = returnBeginWord(newInput, seps);
        // printf("input2: %s", newInput);
        printf("input:\n%s\n", begin);
        int countWords = returnCountWords(begin, seps);
        char** splitWords = splitString(begin, seps, countWords);
        char** testRes = returnSetsOfLettersFromWords(begin, seps, countWords);
        free(newInput);
        //printf("len = %ld\n", strlen(testRes[1]));
        for (size_t i = 0; i < countWords; i++)
                qsort(testRes[i], strlen(testRes[i]), sizeof(char), (int(*)(const void*, const void*))cmp);
        // print_array_string(testRes, countWords);
        // printf("%d\n", countOfRepeatSets);
        int* delIndexes = returnIndexesRepeatsOfSets(testRes, countWords);
        
        
        //print_array_int(setDelIndexes, v);
        //print_array_string(splitWords, countWords);
        printf("Res:\n");
        size_t v = returnFirstMunusOneElemIndex(delIndexes, countWords);
        // printf("v = %ld", v);
        // print_array_int(delIndexes, v);
        printAnswerOfTheTask(splitWords, countWords, delIndexes);
        for (size_t i = 0; i < countWords; i++)
        {
                free(splitWords[i]);
                free(testRes[i]);
        }
        free(splitWords);
        free(testRes);
        free(delIndexes);
}
int main()
{
        // print_array_int();
        // print_array_string();
        // printf("%d\n", isEnd('\0'));
        // printf("%d\n", isEnd('a'));
        // printf("%d\n", have('a', "abba"));
        // printf("%d\n", have('b', "xcv"));
        // printf("%s\n", returnBeginWord("afdfdf fssdfsd", seps));
        // printf("%s\n", returnBeginWord(" fssdfsd", seps));
        // printf("%s\n", returnBeginWord("dsddddd", seps));
        // printf("%s\n", setFromWord("gfhdsfsdhf", seps));
        // printf("%d\n", returnCountWords("afdfdf fssdfsd", seps));

        
        char* state = NULL;
        char* input = NULL;
        while(1) {
                size_t n = sizeof(menu_options)/sizeof(menu_options[0]);
                printMenu(menu_options, n);
                if (state != NULL) {
                        free(state);
                        state = NULL;
                }
                state = get_str();
                if (state != NULL)
                        print_chose_option(menu_options, state[0]);
                if        (state[0] == '2') {
                        printf("Write strings: ");
                        if (input != NULL) {
                                free(input);
                                input = NULL;
                        }
                        input = get_str();
                } else if (state[0] == '3') {
                        if (input != NULL) {
                                doTask(input);
                        }
                } else if (state[0] == '1') {
                        printf("exit\n");
                        break;
                } else {
                        printf("Wrong\n");
                }
        }
}