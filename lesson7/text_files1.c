#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#define BUF_SIZE 128
typedef const char str[];
void main()
{
        FILE* file = NULL;
        str file_name = "file1.txt";
        str hello_world = "Hello, World!";
        char buffer[BUF_SIZE] = {0};
        file = fopen(file_name, "w");
        fprintf(file, hello_world);
        fclose(file);
        file = fopen(file_name, "r");
        fgets(buffer, BUF_SIZE - 1, file);
        fclose(file);
        printf("%s", buffer);
        fclose(file);
        getch();
}