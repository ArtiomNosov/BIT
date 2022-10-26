#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
typedef const char str[];
void main()
{
        FILE *file = NULL;
        str file_name = "file0.txt";
        str hello_world = "Hello, World!";
        file = fopen(file_name, "w+");
        fprintf(file, hello_world);
        fclose(file);
        getch();
}