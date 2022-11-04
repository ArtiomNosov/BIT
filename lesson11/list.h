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
typedef void(*del_t)(void*);
typedef enum list_error_t {
        NO_MEMORY,
        NULL_LIST,
        NULL_FUNC,
        CHAR_ERROR,
} list_error_t;
void check_list_errors();
list* calloc_list();
list* create_list(void* arr, size_t n, size_t size, copy_t copy);
void proces_list(list* cont, f_t f);
void delete_list(list* cont, del_t del);
void insert_list(list* cont, void* data, copy_t copy);
#endif