#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
typedef struct vector_t vector_t;
#define my_type size_t
typedef struct vector_t {
        size_t* data;
        size_t size;
        size_t ind;
} vector_t;
// done
vector_t* create_array()
{
       vector_t* res = calloc(1, sizeof(vector_t));
       res->size = 4;
       res->data = calloc(res->size, sizeof(my_type));
       return res;
}
// done
void delete_array(vector_t* array)
{
        if (array == NULL)
                return;
        free(array->data);
        free(array);
}
// done
int min_val(int a, int b)
{
        if (a > b)
                return b;
        else if (b >= a)
                return a;
}
// done
void memcpy(void* dest, const void* source, size_t size)
{
        char* d = (char*)dest;
        const char* s = (const char*)source;
        for (size_t i = 0; i < size; i++)
                d[i] = s[i];        
}
// done
void resize(vector_t* array, size_t new_size)
{
        if (array == NULL || new_size == 0)
                return;
        size_t size = new_size * 2;
        my_type* new_data = calloc(size, sizeof(my_type));
        size_t new_ind = min_val(array->ind, new_size);
        memcpy(new_data, array->data, sizeof(my_type) * new_ind);
        free(array->data);
        array->data = new_data;
        array->size = size;
        array->ind = new_ind;
}
// done
void append(vector_t* array, my_type val)
{
        if (array == NULL || array->data == NULL)
                return;
        if (array->ind == array->size) {
                resize(array, array->size);
        }
        array->data[array->ind] = val;
        array->ind++;
}
// done
void process_array(vector_t* array, void(*f)(my_type))
{
        if (array == NULL || array->data == NULL)
                return;
        for (size_t i = 0; i < array->ind; i++)
                f(array->data[i]);
}
void free_array(vector_t* array)
{
        if (array == NULL)
                return;
        for (size_t i = 0; i < array->ind; i++)
                free((void*)array->data[i]);
        delete_array(array);
}
// done
void copy_string(char* dest, const char* source, size_t n)
{
        if (dest == NULL)
                return;
        for (size_t i = 0; i < n; i++)
                dest[i] = source[i];
        
}
// done
size_t strlen(const char* str)
{
        size_t res = 0;
        for (size_t i = 0; str[i]!='\0'; i++)
                res++;
        return res;  
}
// done
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
// done
char* copy_word(const char* str)
{
        if (str == NULL)
                return NULL;
        char* res = NULL;
        size_t n = 0;
        for (size_t i = 0; str[i]!=' '&&str[i] != '\n'&&str[i]!='\t'&&str[i]!='\0'; i++)
                n++;
        res = calloc(n + 1, sizeof(char));
        copy_string(res, str, n);
        res[n] = '\0';
        return res;
}
// done
vector_t* map_string(const char* str)
{
        vector_t* res = create_array();
        char* buf = NULL;
        for (size_t i = 0; str[i]!='\0';)
        {
                for (; str[i] == ' ' || str[i] == '\n' || str[i]=='\t'; i++)
                        ;
                buf = copy_word(str + i);
                for (; str[i] != ' ' && str[i] != '\n' && str[i]!='\t' && str[i]!='\0'; i++)
                        ;
                for (; str[i] == ' ' || str[i] == '\n' || str[i]=='\t'; i++)
                        ;
                append(res, (size_t)buf);
        }
        return res;
}
// done
int find_elem(vector_t* arr, my_type elem) 
{
        if(arr == NULL)
                return -1;
        for(size_t i = 0; i < arr->ind;i++)
                if(arr->data[i] == elem)
                        return i;
        return -1;
}
// done
vector_t* create_unique_array(const char* str)
{
        vector_t* unique_arr = create_array();
        for(size_t i = 0; str[i] != '\0'; i++) {
                if(find_elem(unique_arr, str[i]) == -1)
                        append(unique_arr, (size_t)str[i]);
        }
        return unique_arr;
}
// done
int comp (const int *i, const int *j)
{
    return *i - *j;
}
// done
void print_array_int(vector_t* arr)
{
        if (arr == NULL)
                return;
        for (size_t i = 0; i < arr->ind; i++)
                printf("%d ", arr->data[i]);
        printf("\n");
}
// done
vector_t* get_unique_symbols(vector_t* words)
{
        if(words ==NULL)
                return NULL;
        vector_t* res = create_array();
        for(size_t i =0; i < words->ind; i++) {
                vector_t* unique_array = create_unique_array((const char*)words->data[i]);
                qsort(unique_array->data, unique_array->ind, sizeof(my_type), (int(*)(const void*, const void*))comp);
                // print_array_int(unique_array);
                append(unique_array, (size_t)'\0');
                char* buf = calloc(unique_array->ind, sizeof(char));
                for (size_t i = 0; i < unique_array->ind; i++)
                        buf[i] = unique_array->data[i];
                delete_array(unique_array);
                append(res, (size_t)buf);
        }
        return res;
}
// done
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
vector_t* get_indexes_of_repeated_elems(vector_t* arr)
{
        if(arr == NULL)
                return NULL;
        vector_t* res = create_array();
        size_t n = arr->ind;
        int has_repeated = 0;
        for(size_t i= 0; i < n; i++) {
                has_repeated=0;
                for(size_t j = i+1; j<n;j++) {
                        if(strcmp((char*)arr->data[i],(char*)arr->data[j])==0){
                                has_repeated = 1;
                                append(res, j);
                        }
                }
                if(has_repeated==1)
                        append(res, i);
        }
        return res;
}
vector_t* delete_elems_array(vector_t* arr, vector_t* delete_ind)
{
        vector_t* res = create_array();
        for (size_t i = 0; i < arr->ind; i++)
                if (find_elem(delete_ind, i)==-1)
                        append(res, (size_t)copy_word((const char*)arr->data[i]));
        return res;
}
void print_array_string(vector_t* arr)
{
        if (arr == NULL)
                return;
        for (size_t i = 0; i < arr->ind; i++)
                printf("%s ", arr->data[i]);
        printf("\n");
        
}
// int main()
// {
//         // get_str
//         // char* input_test = get_str();
//         // printf("get_str: %s", input_test);
//         // copy_string
//         // int n = strlen(input_test);
//         // printf("%d\n", n);
//         // char* copy_str = calloc(n, sizeof(char));
//         // copy_string(copy_str, input_test, n);
//         // printf("copy_string: %s", copy_str);
//         // copy_word
//         // char* a = "fgnfgjfsd mdfm ";
//         // char* b = copy_word(a);
//         // printf("%s\n", b);
//         // map_string
//         // array_t* a1 = create_array();
//         // append_array(a1, 1);
//         // append_array(a1, 2);
//         // append_array(a1, 3);
//         // append_array(a1, 4);
//         // append_array(a1, 5);
//         // append_array(a1, 6);
//         // append_array(a1, 7);
//         // print_array_int(a1);
//         // printf("\n%d\n", find_elem(a1, 0));
//         // create_unique_array
//         // char* test_str = "ff gkfgkjkd ff fjsd fjffsssd lfjldjl fldl fkljsdkf";
//         // array_t* test_arr = map_string(test_str);
//         // array_t* at2 = get_unique_symbols(test_arr);
//         // array_t* at3 = get_indexes_of_repeated_elems(at2);
//         // qsort(at3->data, at3->ind, sizeof(my_type), comp);
//         // print_array_int(at3);
//         // strcmp
//         // printf("%d\n", strcmp("123", "123"));
//         // printf("%d\n", strcmp("123", "12"));
//         // printf("\n%d", sizeof(size_t));
//         // printf("\n%d", sizeof(array_t*));
        
        
//         return 0;
// }
const char* menu_options[] = {
        "***Menu***",
        "1) quit",
        "2) scanf strings",
        "3) delete each word that consists the same letters"
};
void print_menu(const char** menu, size_t n)
{
        for (size_t i = 0; i < n; i++)
                printf("%s\n", menu[i]);
}
void print_chose_option(const char** menu, int option)
{
        printf("You chose \"%s\"\n", menu[option - '0']);    
}
vector_t* delete_each_word_that_consists_the_same_letters(char* str)
{
        if (str == NULL)
                return NULL;
        vector_t* words = map_string(str);
        vector_t* unique_symbols_arrays = get_unique_symbols(words);
        vector_t* indexes_of_repeated_elems = get_indexes_of_repeated_elems(unique_symbols_arrays);
        qsort(indexes_of_repeated_elems->data, indexes_of_repeated_elems->ind, sizeof(my_type), (int(*)(const void*, const void*))comp);
        vector_t* res = delete_elems_array(words, indexes_of_repeated_elems);
        free_array(words);
        free_array(unique_symbols_arrays);
        delete_array(indexes_of_repeated_elems);
        return res;
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
                        printf("Write strings: ");
                        input = get_str();
                } else if (state == '3') {
                        vector_t* res = delete_each_word_that_consists_the_same_letters(input);
                        print_array_string(res);
                        // free_array(res);
                } else if (state == '1') {
                        printf("exit\n");
                } else {
                        printf("Wrong\n");
                }
        }
}