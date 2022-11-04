#include "list.h"
void proces_error_list(list_error_t error)
{
        // LOGIC
}
void check_list_errors()
{
        if(sizeof(unsigned char) != 1)
                proces_error_list(CHAR_ERROR);
                exit(CHAR_ERROR);
}
list* calloc_list()
{
        list* res = (list*) calloc(1, sizeof(list));
        // printf("res == NULL: %d\n", res == NULL);
        // if (res == NULL)
        //         proces_error_list(NO_MEMORY);
        //         return NULL;
        // printf("res: %x\n", res);
        return res;
}
list* create_list(void* arr, size_t n, size_t size, copy_t copy)
{
        // printf("create_list\n");
        // if (arr == NULL || n == 0 || size == 0)
        //         return NULL;
        // printf("arr\n");
        list* res = calloc_list();
        // printf("res: %x\n", res);
        // if (res == NULL)
        //         return NULL;
        // printf("res\n");
        byte* byte_p = (byte*) arr;
        for (size_t i = 0; i < n; i++)
        {
                // printf("!");
                // printf("res: %x\n", res);
                insert_list(res, byte_p + i * size, copy);
        }
        return res;
}
void proces_list(list* cont, f_t f)
{
        // if (cont == NULL)
        //         proces_error_list(NULL_LIST);
        //         return;
        // if (f == NULL)
        //         proces_error_list(NULL_FUNC);
        //         return;
        node* elem = cont->head;
        while (elem != NULL)
        {
                f(elem->data);
                elem = elem->next;
        }
        
}
void free_list(list* cont)
{
        // if (cont == NULL)
        //         return;
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
        // if (cont == NULL)
        //         proces_error_list(NULL_LIST);
        //         return;
        // if (del == NULL)
        //         proces_error_list(NULL_FUNC);
        //         return;
        proces_list(cont, del);
        free_list(cont);
}
void insert_list(list* cont, void* data, copy_t copy)
{
        // if (cont == NULL)
        //         proces_error_list(NULL_LIST);
        //         printf("1");
        //         return;
        // if (copy == NULL)
        //         proces_error_list(NULL_FUNC);
        //         printf("2");
        //         return;
        node* new_node = (node*) calloc(1, sizeof(node));
        new_node->data = copy(data);
        new_node->next = NULL;
        // printf("cont: %x\n", cont);
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