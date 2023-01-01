void delete_triple_spaces(list* cont, del_t del)
{
        if (cont == NULL || cont->n < 2)
                return;
        node* curr = cont->head;
        while(curr->next->next) {
                if (!if_signal(curr->data) && !if_signal(curr->next->data) && !if_signal(curr->next->next->data)) {
                        node* buf = curr->next;
                        curr->next = curr->next->next;
                        del(buf->data);
                        free(buf);
                } else {
                        curr = curr->next;
                }
        }
        
}
void write_english(list* cont)
{
        if (cont == NULL)
                return;
        int state = 'r';
        while (state != '=')
        {
                state = getch();
                if (state == '+')
                        break;
                printf("%c", state);
                insert_int_in_list(cont, state);
        }
}
void start_lisen(list* cont)
{
        char state = 'r';
        printf("s - stop\n");
        time_t space_time = 0;
        while(state != 's') {
                while(!kbhit()) {
                        if (clock() - space_time > 500) {
                                insert_int_in_list(cont, ' ');
                                printf(" ");
                        }
                        Sleep(time_wait_for_button);
                        
                }   
                state = getch();
                if (state == ' ') {
                        space_time = clock();
                        insert_int_in_list(cont, '.');
                        printf(".");
                } 
        }
        insert_int_in_list(cont, ' ');
        insert_int_in_list(cont, ' ');
        printf("\n");
}
int if_signal(number_t* number)
{
        if (number->number == '.' || number->number == '_')
                return TRUE;
        return FALSE;
}
void set_underscore(number_t* number)
{
        number->number = '_';
}
void process_signal_delete_many_symbols(list* cont, del_t del)
{
        if (cont == NULL || cont->n < 2)
                return;
        node* curr = cont->head;
        while(curr->next) {
                if (if_signal(curr->data) && if_signal(curr->next->data)) {
                        node* buf = curr->next;
                        curr->next = curr->next->next;
                        del(buf->data);
                        free(buf);
                        set_underscore(curr->data);
                        // printf("underscore ");
                } else if (if_signal(curr->data)) {
                        // printf("dot ");
                        curr = curr->next;
                } else {
                        // printf("space ");
                        curr = curr->next;
                }
        }
}
void print_symbol(number_t* number)
{
        printf("%c", number->number);
}
void write_signal_morse(list* cont)
{
        if (cont == NULL)
                return;
        int state = 'r';
        while (state != 's')
        {
                state = getch();
                if (state == '_') {
                        insert_int_in_list(cont, '_');
                        printf("_");
                } else if (state == '.') {
                        insert_int_in_list(cont, '.');
                        printf(".");
                } else {
                        insert_int_in_list(cont, ' ');
                        printf(" ");
                }
        }
        insert_int_in_list(cont, ' ');
        insert_int_in_list(cont, ' ');
}
int get_number(number_t* number)
{
        return number->number;
}
char get_english_symbol(const char* buf, const char** morse, int i)
{
        for (size_t i = 0; i < morse_size; i++) {
                printf("%sand%s[\n", buf, morse[i] + 2);
                if (strcmp(morse[i] + 2, buf) == 0)
                        return morse[i][0];
        }
                
        return 0;
}
void buf_null(char* buf, int n)
{
        for (size_t i = 0; i < n; i++)
        {
                buf[i] = 0;
        }
        
}
list* translate_morse_to_english(list* cont)
{
        list* res = calloc_list();
        node* curr = cont->head;
        char buf[125] = {0};
        int i = 0;
        char english_symbol = 0;
        while(curr->next) {
                // printf("%c", buf[i]);
                buf[i] = get_number(curr->data);
                if (!if_signal(curr->data) && !if_signal(curr->next->data)) {
                        // printf("buf: %s\n", buf);
                        english_symbol = get_english_symbol(buf, morse, i);
                        insert_int_in_list(res, english_symbol);
                        i = 0;
                        buf_null(buf, 125);
                } else if (if_signal(curr->data)) {
                        i++;
                }
                curr = curr->next;
        }
        return res;
}
void write_morse_letter_to_list(list* cont, const char* letter)
{
        for (size_t i = 0; letter[i]; i++)
        {
                if (letter[i] == '_') {
                        insert_int_in_list(cont, '_');
                        insert_int_in_list(cont, ' ');
                        insert_int_in_list(cont, '_');
                        insert_int_in_list(cont, ' ');
                        insert_int_in_list(cont, '_');
                        insert_int_in_list(cont, ' ');
                } else if (letter[i] == '.') {
                        insert_int_in_list(cont, '.');
                        insert_int_in_list(cont, ' ');
                }
                insert_int_in_list(cont, ' ');
                insert_int_in_list(cont, ' ');
        }
        
}

list* english_to_morse(list* cont)
{
        if (cont == NULL)
                return NULL;
        list* res = calloc_list();
        node* curr = cont->head;
        while(curr->next) {
                int elem = get_number(curr->data);
                if (elem == 'e') {
                        write_morse_letter_to_list(res, morse[0]);
                } else if (elem == 't') {
                        write_morse_letter_to_list(res, morse[1]);
                } else if (elem == 'i') {
                        write_morse_letter_to_list(res, morse[2]);
                } else if (elem == 'a') {
                        write_morse_letter_to_list(res, morse[3]);
                } else if (elem == 'n') {
                        write_morse_letter_to_list(res, morse[4]);
                } else if (elem == 'm') {
                        write_morse_letter_to_list(res, morse[5]);
                } else if (elem == 's') {
                        write_morse_letter_to_list(res, morse[6]);
                } else if (elem == 'u') {
                        write_morse_letter_to_list(res, morse[7]);
                } else if (elem == 'o') {
                        write_morse_letter_to_list(res, morse[8]);
                } else if (elem == 'r') {
                        write_morse_letter_to_list(res, morse[9]);
                } else if (elem == 'd') {
                        write_morse_letter_to_list(res, morse[10]);
                } else if (elem == 'g') {
                        write_morse_letter_to_list(res, morse[11]);
                } else if (elem == 'k') {
                        write_morse_letter_to_list(res, morse[12]);
                } else if (elem == 'w') {
                        write_morse_letter_to_list(res, morse[13]);
                } else if (elem == 'f') {
                        write_morse_letter_to_list(res, morse[14]);
                } else if (elem == 'h') {
                        write_morse_letter_to_list(res, morse[15]);
                } else if (elem == 'j') {
                        write_morse_letter_to_list(res, morse[16]);
                } else if (elem == 'l') {
                        write_morse_letter_to_list(res, morse[17]);
                } else if (elem == 'p') {
                        write_morse_letter_to_list(res, morse[18]);
                } else if (elem == 'q') {
                        write_morse_letter_to_list(res, morse[19]);
                } else if (elem == 'v') {
                        write_morse_letter_to_list(res, morse[20]);
                } else if (elem == 'x') {
                        write_morse_letter_to_list(res, morse[21]);
                } else if (elem == 'y') {
                        write_morse_letter_to_list(res, morse[22]);
                } else if (elem == 'z') {
                        write_morse_letter_to_list(res, morse[23]);
                }else if (elem == 'b') {
                        write_morse_letter_to_list(res, morse[24]);
                }else if (elem == 'c') {
                        write_morse_letter_to_list(res, morse[25]);
                } else if (elem == '1') {
                        write_morse_letter_to_list(res, morse[26]);
                } else if (elem == '2') {
                        write_morse_letter_to_list(res, morse[27]);
                } else if (elem == '3') {
                        write_morse_letter_to_list(res, morse[28]);
                } else if (elem == '4') {
                        write_morse_letter_to_list(res, morse[29]);
                }else if (elem == '5') {
                        write_morse_letter_to_list(res, morse[30]);
                }else if (elem == '6') {
                        write_morse_letter_to_list(res, morse[31]);
                } else if (elem == '7') {
                        write_morse_letter_to_list(res, morse[32]);
                } else if (elem == '8') {
                        write_morse_letter_to_list(res, morse[33]);
                } else if (elem == '9') {
                        write_morse_letter_to_list(res, morse[34]);
                } else if (elem == '0') {
                        write_morse_letter_to_list(res, morse[35]);
                } else if (elem == ' ') {
                        insert_int_in_list(res, ' ');
                        insert_int_in_list(res, ' ');
                        insert_int_in_list(res, ' ');
                        insert_int_in_list(res, ' ');
                } 
                curr = curr->next;
        
        }
        return res;
}
list* morse_to_numbers(list* morse_list) 
{
        if (morse_list == NULL || morse_list->n < 1)
                return NULL;
        list* res = calloc_list();
        node* curr = morse_list->head;
        size_t ind = 0;
        while (curr)
        {
                ind = find_ind(morse_alphabet, a_size, curr->data);
                insert_number_in_list(res, ind);
                curr = curr->next;
        }
        return res;
}
list* english_to_numbers(list* english_list) 
{
        if (english_list == NULL || english_list->n < 1)
                return NULL;
        list* res = calloc_list();
        node* curr = english_list->head;
        size_t ind = 0;
        while (curr)
        {
                ind = find_ind(english_alphabet, a_size, curr->data);
                insert_number_in_list(res, ind);
                curr = curr->next;
        }
        return res;
}
void insert_string_in_list(list* cont, const char* arr)
{
        string_t* string = create_string(arr);
        insert_list(cont, string, (copy_t)copy_string);
        delete_string(string);
}
void insert_number_in_list(list* cont, int n)
{
        if (cont == NULL)
                return;
        number_t* number = create_number(n);
        insert_list(cont, number, (copy_t)copy_number);
        free(number);
}