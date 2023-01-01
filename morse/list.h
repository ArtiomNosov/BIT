#ifndef LIST_H 
#define LIST_H 
#include <stdlib.h>
#include <stdio.h>
#include "base.h"
typedef struct node node;
typedef struct node {
        node* next;
        void* data;
} node;
typedef struct list {
        size_t n;
        node* head;
        node* tail;
} list;
typedef unsigned char byte;
typedef void*(*copy_t)(void*);
typedef f_t del_t;
typedef enum list_error_t {
        NO_MEMORY,
        NULL_LIST,
        NULL_FUNC,
        CHAR_ERROR,
} list_error_t;
void check_list_errors();
list* calloc_list();
void proces_list(list* cont, f_t f);
void delete_list(list* cont, del_t del);
void insert_list(list* cont, void* data, copy_t copy);
// list_up
void print_list(list* cont);
#endif