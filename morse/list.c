#include "list.h"
#define tprint(A) \
{\
        static int b = 0;\
        b++;\
        printf("%s\n", A);\
}
void proces_error_list(list_error_t error)
{
        // LOGIC
}
void check_list_errors()
{
        // tprint("check_list_errors");
        if(sizeof(unsigned char) != 1)
                proces_error_list(CHAR_ERROR);
                exit(CHAR_ERROR);
}
list* calloc_list()
{
        // tprint("calloc_list");
        list* res = calloc(1, sizeof(list));
        if (res == NULL) {
                proces_error_list(NO_MEMORY);
                return NULL;
        }
        return res;
}
void proces_list(list* cont, f_t f)
{
        // tprint("proces_list");
        if (cont == NULL) {
                proces_error_list(NULL_LIST);
                return;
        }
        node* elem = cont->head;
        while (elem != NULL)
        {
                f(elem->data);
                elem = elem->next;
        }
        
}
void free_list(list* cont)
{
        // tprint("free_list");
        if (cont == NULL)
                return;
        node* elem = cont->head, *cur = NULL;
        while (elem)
        {
                cur = elem;
                elem = elem->next;
                free(cur);
        }
        free(cont);
}
void delete_list(list* cont, del_t del)
{
        // tprint("delete_list");
        if (cont == NULL)
                return;
        proces_list(cont, del);
        free_list(cont);
}
void insert_list(list* cont, void* data, copy_t copy)
{
        // tprint("insert_list");
        if (cont == NULL) {
                proces_error_list(NULL_LIST);
                return;
        }
        node* new_node = (node*) calloc(1, sizeof(node));
        new_node->data = copy(data);
        new_node->next = NULL;
        cont->n = cont->n + 1;
        // head = tail = NULL
        if (cont->head == NULL) {
                cont->head = new_node;
                cont->tail = new_node;
                return;
        }
        // head = tail != NULL
        if (cont->head == cont->tail) {
                cont->head->next = new_node;
                cont->tail = new_node;
                return;
        }
        // head != NULL, tail != NULL, head != tail
        cont->tail->next = new_node;
        cont->tail = new_node;
        return;
}
