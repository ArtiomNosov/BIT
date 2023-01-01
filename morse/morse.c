#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#define a_size 37
const char* english_alphabet[] = {
        "e", "t", "i", "a", "n", "m", "s", "u",      
        "o", "r", "d", "g", "k", "w", "f", "h",    
        "j", "l", "p", "q", "v", "x", "y", "z",    
        "b", "c", "1", "2", "3", "4", "5", "6",  
        "7", "8", "9", "0", " "   
};
const char* morse_alphabet[] = {
        ".",         "_",         ". .",       ". _",       
        "_ .",       "_ _",       ". . .",     ". . _",     
        "_ _ _",     ". _ .",     "_ . .",     "_ _ .",      
        "_ . _",     ". _ _",     ". . _ .",   ". . . .",    
        ". _ _ _",   ". _ . .",   ". _ _ .",   "_ _ . _",    
        ". . . _",   "_ . . _",   "_ . . _",   "_ _ . .",    
        "_ . . .",   "_ . _ .",   ". _ _ _ _", ". . _ _ _",  
        ". . . _ _", ". . . . _", ". . . . .", "_ . . . .",  
        "_ _ . . .", "_ _ _ . .", "_ _ _ _ .", 
        "_ _ _ _ _", "    "
};
const char* menu_options[] = {
        "***Menu***",
        "1) quit",
        "2) scanf english in english_array",
        "3) scanf morse in morse_array",
        "4) printf english_array",
        "5) printf morse_array",
        "6) printf english_array in morse",
        "7) printf morse_array in english",
        "8) sound english_array",
        "9) sound morse_array"
};
typedef struct vector_t {
        int* data;
        size_t size;
        size_t ind;
} vector_t;
vector_t* create_array()
{
       vector_t* res = calloc(1, sizeof(vector_t));
       res->size = 4;
       res->data = calloc(res->size, sizeof(int));
       return res;
}
void delete_array(vector_t* array)
{
        if (array == NULL)
                return;
        free(array->data);
        free(array);
}
void resize(vector_t* array, size_t new_size)
{
        if (array == NULL || new_size == 0)
                return;
        size_t size = new_size * 2;
        int* new_data = calloc(size, sizeof(int));
        size_t new_ind = min(array->ind, new_size);
        memcpy(new_data, array->data, new_ind * sizeof(int));
        free(array->data);
        array->data = new_data;
        array->size = size;
        array->ind = new_ind;
}
void append_array_int(vector_t* array, int val)
{
        if (array == NULL || array->data == NULL)
                return;
        if (array->ind == array->size) {
                resize(array, array->size);
        }
        array->data[array->ind] = val;
        array->ind++;
}
void process_array_int(vector_t* array, void(*f)(int*))
{
        if (array == NULL || array->data == NULL)
                return;
        for (size_t i = 0; i < array->ind; i++)
                f(array->data + i);
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
int find_ind(const char** alphabet, size_t size, const char* string)
{
        
        for (size_t i = 0; i < size; i++)
                if (strcmp(string, alphabet[i]) == 0)
                        return i;
        return -1;
}
void printf_morse(int* val)
{
        const char* res = "NaN";
        if (*val != -1)
                res = morse_alphabet[*val];
        printf("%s   ", res);
}
void printf_english(int* val)
{
        const char* res = "NaN";
        if (*val != -1)
                res = english_alphabet[*val];
        printf("%s", res);
}
char* scanf_string()
{
        char* res = NULL;
        res = get_str();
        while(res == NULL || strlen(res) == 0) {
                printf("You need to write smth!\n");
                res = get_str();
        }
        return res;
}
void scanf_english(vector_t* array)
{
        if (array == NULL)
                return;
        printf("Start to scanf_english\n");
        char buf[2]={0};
        char* str = scanf_string();
        for (size_t i = 0; str[i]; i++) {
                buf[0] = str[i];
                int ind = find_ind(english_alphabet, a_size, buf);
                append_array_int(array, ind);
        }
        printf("\nEnd to scanf_english\n");
}
void scanf_morse(vector_t* array)
{
        printf("Start to scanf_morse\n");
        if (array == NULL)
                return;
        int state = -1;
        char* morse_letter = NULL;
        int ind = -1;
        while(state != 27) {
                printf("Write morse letter:\n");
                morse_letter = scanf_string();
                ind = find_ind(morse_alphabet, a_size, morse_letter);
                append_array_int(array, ind);
                printf("Press esc button to stop scanf or any button to continue\n");
                state = getch();
        }
        printf("\nEnd to scanf_morse\n");
}
void print_menu(const char** menu, size_t n)
{
        for (size_t i = 0; i < n; i++)
                printf("%s\n", menu[i]);
}
void my_beep(int* val)
{
        const char* symbol = NULL;
        if (*val == -1 || *val > a_size)
                return;
        symbol = morse_alphabet[*val];
        for (size_t i = 0; symbol[i]; i++)
        {
                if      (symbol[i] == '.')
                        Beep(1000, 300);
                else if (symbol[i]== '_')
                        Beep(1000, 900);
                Sleep(37);
        }
}
void sound(vector_t* array)
{
        if (array == NULL || array->ind < 1)
                return;
        process_array_int(array, printf_morse);
        process_array_int(array, my_beep);
}
void print_example_morse(const char* a1[], const char* a2[], size_t size)
{
        for (size_t i = 0; i < size; i++) {
                printf("%s|%s\n", a1[i], a2[i]);
        }
}
void print_chose_option(const char** menu, int option)
{
        printf("You chose \"%s\"\n", menu[option - '0']);    
}
int main()
{
        int state = '0';
        vector_t* english_array = create_array();
        vector_t* morse_array = create_array();
        while(state != '1') {
                size_t n = sizeof(menu_options)/sizeof(menu_options[0]);
                print_menu(menu_options, n);
                state = getch();
                print_chose_option(menu_options, state);
                if        (state == '2') {
                        delete_array(english_array);
                        english_array = create_array();
                        scanf_english(english_array);
                } else if (state == '3') {
                        delete_array(morse_array);
                        print_example_morse(morse_alphabet, english_alphabet, a_size);
                        morse_array = create_array();
                        scanf_morse(morse_array);
                } else if (state == '4') {
                        printf("english_list:\n");
                        process_array_int(english_array, printf_english);
                        printf("\n");
                } else if (state == '5') {
                        printf("morse_array:\n");
                        process_array_int(morse_array, printf_morse);
                        printf("\n");
                } else if (state == '6') {
                        printf("english_list in morse:\n");
                        process_array_int(english_array, printf_morse);
                        printf("\n");
                } else if (state == '7') {
                        printf("morse_array in english:\n");
                        process_array_int(morse_array, printf_english);
                        printf("\n");
                } else if (state == '8') {
                        printf("sound english_list:\n");
                        sound(english_array);
                        printf("\n");
                } else if (state == '9') {
                        printf("sound morse_array:\n");
                        sound(morse_array);
                        printf("\n");
                } else if (state == '1') {
                        printf("exit\n");
                } else {
                        printf("Wrong\n");
                }
        }
}
