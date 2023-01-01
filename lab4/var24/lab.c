#include <stdlib.h>
#include <stdio.h>
int is_end(char ch)
{
        if (ch == '\0' || ch == EOF)
                return 1;
        else
                return 0;
}
int is_have(char ch, char* str)
{
        if (str == NULL)
                return -1;
        for (size_t i = 0; !is_end(str[i]); i++)
                if (str[i] == ch)
                        return 1;
        return 0;
}
size_t count_double_sep(char* str, char* sep)
{
        if (str == NULL)
                return 0;
        size_t res = 0;
        for (size_t i = 0; !is_end(str[i]); i++)
                if (is_have(str[i], sep) && is_have(str[i+1], sep))
                        res++;
        return res;
}
size_t strlen(char* str)
{
        if (str == NULL)
                return 0;
        size_t res = 0;
        for (size_t i = 0; !is_end(str[i]); i++)
                res++;
        return res;
}
char* del_double_sep(char* str, char* sep)
{
        if (str == NULL)
                return NULL;
        size_t count_sep = count_double_sep(str, sep);
        size_t len = strlen(str);
        char* res = calloc(len - count_sep, sizeof(char));
        size_t u = 0;
        for (size_t i = 0; !is_end(str[i]); i++)
                if (!(is_have(str[i], sep) && is_have(str[i+1], sep))) {
                        if (is_have(str[i], sep))
                                res[u] = ' ';
                        else
                                res[u] = str[i];
                        u++;
                }
        return res;
}
char* get_begin(char* str, char* sep)
{
        if (str == NULL)
                return NULL;
        if (!is_have(str[0], sep))
                return str;
        while (is_have(str[0], sep))
                str++;
        return str;
}
// this function work only with strings where we have one sep between words
void process_words(char* str, void(*f)(char*), char* sep)
{
        if (str == NULL)
                return;
        str = get_begin(str, sep);
        f(str);
        while(!is_end(str[0])) {
                if (is_have(str[0], sep))
                     f(str + 1); 
                str++;
        }
                 
}
size_t wordlen(char* str)
{
        if (str == NULL)
                return 0;
        size_t res = 0;
        for (size_t i = 0; !is_end(str[i]) && !is_have(str[i], " "); i++)
                res++;
        return res;
}
int cmp(const char* a, const char* b)
{
        if      (*a > *b) {
                return 1;
        } else if (*a < *b) {
                return -1;
        } else {
                return 0;
        }
}
// this function think that end of word its space
void sort_word(char* word)
{
        size_t len = wordlen(word);
        qsort(word, len, sizeof(char), (int(*)(const void*, const void*))cmp);
}
void memcpy(void* dest, void* source, size_t size)
{
        if (dest == NULL || source == NULL)
                return;
        for (size_t i = 0; i < size; i++)
                ((char*)dest)[i] = ((char*)source)[i];
        
}
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
int main()
{
        char seps[] = "\n \t";
        char* str = get_str();
        char* res = del_double_sep(str, seps);
        process_words(res, sort_word, seps);
        printf("%s", res);
        free(str);
        free(res);
        return 0;
}
