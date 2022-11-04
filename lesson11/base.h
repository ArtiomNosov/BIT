#ifndef BASE_H 
#define BASE_H   
typedef void(*f_t)(void*);
typedef f_t print_t;
typedef struct base_t {
        print_t print; 
} base_t;
#endif