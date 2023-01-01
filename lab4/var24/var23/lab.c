#include <stdio.h>
#include <stdlib.h>
int is_nul(char symbol)
{
    if (symbol == '\0' || symbol == EOF)
        return 1;
    return 0;
}
int contains(char symbol, char* str)
{
    if (str == NULL)
        return -1;
    for (size_t i = 0; !is_nul(str[i]); i++)
        if (str[i] == symbol)
            return 1;
    return 0;
}
size_t get_number_of_repetitive_sep(char* str, char* sep)
{
    if (str == NULL || sep == NULL)
        return -1;
    size_t res = 0;
    while (!is_nul(str[0])) {
        if (contains(str[0], sep) && contains(str[1], sep))
            res++;
        str++;
    }
    return res;
}
size_t strlen(char* str)
{
    if (str == NULL)
        return 0;
    size_t res = 0;
    while (!is_nul(str[0])) {
        res++;
        str++;
    }
    return res;
}
char* remove_repetitive_sep(char* str, char* sep)
{
    if (str == NULL || sep == NULL)
        return NULL;
    size_t repetitive_sep_number = get_number_of_repetitive_sep(str, sep);
    size_t len = strlen(str);
    char* res = calloc(len - repetitive_sep_number, sizeof(char));
    size_t u = 0;
    for (size_t i = 0; !is_nul(str[i]); i++) {
        if (!(contains(str[i], sep) && contains(str[i+1], sep))) {
            if (contains(str[i], sep))
                res[u] = ' ';
            else 
                res[u] = str[i];
            u++;
        }
    }
    return res;
}
size_t wordlen(char* str, char* sep)
{
    if (str == NULL || sep == NULL)
        return 0;
    size_t res = 0;
    while (!is_nul(str[0]) && contains(str[0], sep)) {
        res++;
        str++;
    }
    return res;
}
// end of word should be space
void cyclic_shift(char* word, size_t n)
{
    if (word == NULL)
        return;
    size_t len = wordlen(word, " ");
    n = n % len;
    for (size_t i = 0; i < n; i++) {
        size_t j = 1;
        char buf = word[0];
        for (j = 1;!is_nul(word[j]) && contains(word[j], " "); j++)
            word[j - 1] = word[j];
        word[j - 1] = buf;
    }
}
char* get_begin_word(char* str, char* sep)
{
    if (str == NULL || sep == NULL)
        return NULL;
    if (!contains(str[0], sep))
        return str;
    while (contains(str[0], sep))
        str++;
    return str;
}
// end of word should be space
void map_words_f_with_number(char* str, char* sep, void(*f)(char*, size_t n), int n)
{
    if (str == NULL || sep == NULL)
        return;
    str = get_begin_word(str, sep);
    f(str, n);
    while (!is_nul(str[0])) {
        if (contains(str[0], sep) && !contains(str[1], sep) && !is_nul(str[1]))
            f(str + 1, n);
        str++;
    }
}
int main()
{
    char* sep = " \t\n";
    char* str = "dshkfg fd  shfkhdsf sfd f\n\thgsdhgf hgsd";
    printf("str = %s\n", str);
    char* res = remove_repetitive_sep(str, sep);
    printf("res = %s", res);
    // map_words_f_with_number(res, sep, cyclic_shift, 1);
    // printf("left shift 1 (res) = %s", res);
    return 0;
}
