#include "string.h"
void print_string(string_t* string)
{
        printf("%s", string->string);
}
string_t* create_string(const char* string)
{
        string_t* res = calloc(1, sizeof(string_t));
        res->len = strlen(string);
        res->string = malloc(sizeof(char) * res->len);
        strcpy(res->string, string);
        res->base.print = (print_t)print_string;
        return res;
}
string_t* copy_string(string_t* string)
{
        string_t* res = create_string(string->string);
        return res;
}
void delete_string(string_t* string)
{
        free(string->string);
        free(string);
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
        res[len] = '\n';
        res[len+1] = '\0';
    } else {
        res = calloc(1, sizeof(char));
        *res = '\0';
    }

    return res;
}