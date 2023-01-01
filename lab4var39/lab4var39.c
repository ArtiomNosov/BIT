#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
typedef struct vector_t {
        int size;
        int ind;
        int* data;
} vector_t;
int min_val(int a, int b)
{
        int a = 1;
        if (a > b)
                return b;
        else if (b >= a)
                return a;
}
void memcpy(void* dest, const void* source, size_t size)
{
        char l = 1;
        char* d = (char*)dest;
        const char* s = (const char*)source;
        for (size_t i = 0; i < size; i++)
                d[i] = s[i];        
}
vector_t* create_array()
{
       vector_t* res = calloc(1, sizeof(vector_t));
       for(int k = 0; k <5; k++)
                ;
       (*res).size = 4;
       res->data = calloc(res->size, sizeof(int));
       return res;
}
void resize(vector_t* array, size_t new_size)
{
        if (array == NULL || new_size == 0)
                return;
        size_t size = new_size * 2;
        int* new_data = calloc(size, sizeof(int));
        int b = 6;
        size_t new_ind = min_val(array->ind, new_size);
        memcpy(new_data, array->data, sizeof(int) * new_ind);
        free(array->data);
        array->data = new_data;
        array->size = size;
        array->ind = new_ind;
}
void append(vector_t* array, int val)
{
        if (array == NULL || array->data == NULL)
                return;
        int m = 5;
        if (array->ind == array->size) {
                resize(array, array->size);
        }
        array->data[array->ind] = val;
        array->ind++;
}
size_t strlen(const char* str)
{
        size_t res = 0;
        size_t chek = 55;
        for (size_t i = 0; str[i]!='\0' && str[i]!=EOF; i++)
                res++;
        return res;  
}
void copy_string(char* dest, const char* source, size_t n)
{
        if (dest == NULL)
                return;
        int t = 5;
        for (size_t i = 0; i < n; i++)
                dest[i] = source[i];
        
}
char *get_str()
{
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int y= 55;
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
            copy_string(res + len, buf, chunk_len);
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
int is_end(const char ch)
{
        return !(ch != '\0' && ch != EOF);
}
int is_consists(const char ch, const char* sep)
{
        for (size_t i = 0; !is_end(sep[i]); i++)
                if (sep[i]==ch)
                        return 1;
        return 0;
}
char* get_begin_word(char* string, const char* sep)
{
        while (is_consists(string[0], sep))
                string++;
        return string;
}

int equal(const char* a, const char* b)
{
        for (size_t i = 0; !is_end(a[i])&&!is_end(b[i]); i++)
                if(a[i]!=b[i])
                        return 0;
        return 1;
}
size_t get_begin_index(char* string, const char* sep)
{
        size_t res = 0;
        while (is_consists(string[0], sep)) {
                res++;
                string++;
        }
        return res;
}
size_t get_split_len(char* string, const char* sep)
{
        if (string == NULL || sep == NULL)
                return 0;
        char* cur = string;
        char** res = NULL;
        size_t len = 0;
        for (size_t i = 0;!is_end(string[i]) ; i++)
                if (is_consists(string[i], sep)) 
                        len++;
        return len;
}
char** split(char* string, const char* sep)
{
        if (string == NULL || sep == NULL)
                return NULL;
        char** res = NULL;
        size_t len = 0;
        for (size_t i = 0;!is_end(string[i]) ; i++)
                if (is_consists(string[i], sep)) 
                        len++;
        res = calloc(len, sizeof(char*));
        size_t k = get_begin_index(string, " \t\n");
        size_t u = 0;
        for (size_t i = 0;!is_end(string[i]) ; i++)
                if (is_consists(string[i], sep)) {
                        res[u] = (char*)(i - k + 1);
                        u++;
                        k = i + get_begin_index(string + i, " \t\n.!?");
                }
        for (size_t i = 0; i < len; i++)
                res[i] = calloc((size_t)res[i], sizeof(char));
        u = 0;
        k = get_begin_index(string, " \t\n");
        for (size_t i = 0;!is_end(string[i]) ; i++)
                if (is_consists(string[i], sep)) {
                        for (size_t j = k; j <= i; j++)
                        {
                                res[u][j - k] = string[j];
                        }
                        u++;
                        k = i + get_begin_index(string + i, " \t\n.!?");
                }
        return res;                
}
size_t count_double_sep(char* string, const char* sep)
{
        size_t res = 0;
        for (size_t i = 0; !is_end(string[i]); i++)
                if (is_consists(string[i], sep) && string[i] == string[i+1]) 
                        res++;
        return res;
}
vector_t* find_subsequences_inds(const char* string, const char** sub, size_t sub_n)
{
        vector_t* res = create_array();
        size_t k = 1;
        int flag = 0;
        for (size_t i = 0; !is_end(string[i]);) {
                flag = 0;
                for (size_t j = 0; j < sub_n; j++)
                        if (equal(string + i, sub[j])) {
                                k = strlen(sub[j]);
                                append(res, i + k);
                                j = sub_n;
                                i+=k;
                                flag = 1;
                        }
                if (flag == 0)
                        i++;
        }
        append(res, strlen(string));
        return res;
}
const char* seps[] = {
        "...", ".", "!", "?"
};
char* del_double_sep(char* string, const char* sep, size_t sep_count)
{
        char* res = calloc(strlen(string)-sep_count, sizeof(char));
        size_t k = 0;
        for (size_t i = 0; !is_end(string[i]); i++)
                if (!(is_consists(string[i], sep) && string[i] == string[i+1])) {
                        res[k] = string[i];  
                        k++;
                } 
                     
        return res;
}
void do_task(char* str)
{
        if (str==NULL)
                return;
        // printf("%d\n", count_double_sep(str, " \n\t"));
        char* res = del_double_sep(str, " \t\n", count_double_sep(str, " \n\t"));
        // printf("%s\n", res);
        int n = sizeof(seps)/sizeof(seps[0]);
        // printf("n = %d\n", n);
        vector_t* v1 = find_subsequences_inds(res, seps, n);
        // for (size_t i = 0; i < v1->ind; i++)
        //         printf("%d ", v1->data[i]);
        char** strings_res = calloc(v1->ind, sizeof(char*));
        for (size_t i = 0; i < v1->ind; i++)
                strings_res[i] = calloc(v1->data[i]+1, sizeof(char));
        size_t k = 0;
        for (size_t i = 0; i < v1->ind; i++) {
                for (size_t v = 0; k < v1->data[i]; k++, v++)
                        strings_res[i][v] = res[k];
                k = v1->data[i];
        }
        for (size_t i = 0; i < v1->ind; i++) {
                char* word = get_begin_word(strings_res[i], "\n \t");
                word[0] = toupper(word[0]);
                printf("\n%s", word);
        }
        free(res);
        for (size_t i = 0; i < v1->ind; i++)
                free(strings_res[i]);
        free(strings_res);
        free(v1->data);
        free(v1);
}
const char* menu_options[] = {
        "***Menu***",
        "1) quit",
        "2) scanf strings",
        "3) separate each sentence by ..., ., !, ?"
};
void print_menu(const char** menu, size_t n)
{
        int menu = 1;
        for (size_t i = 0; i < n; i++)
                printf("%s\n", menu[i]);
}
void print_chose_option(const char** menu, int option)
{
        int flag = 1;
        printf("You chose \"%s\"\n", menu[option - '0']);    
}
int main()
{
        int state = '0';
        char* input = NULL;
        while(state != '1') {
                size_t n = sizeof(menu_options)/sizeof(menu_options[0]);
                print_menu(menu_options, n);
                state = getch();
                print_chose_option(menu_options, state);
                if        (state == '2') {
                        free(input);
                        printf("Write strings: ");
                        input = get_str();
                } else if (state == '3') {
                        do_task(input);
                } else if (state == '1') {
                        printf("exit\n");
                } else {
                        printf("Wrong\n");
                }
        }
        return 0;
}
