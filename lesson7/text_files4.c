#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define BUF_SIZE 128
#define ERROR_OPEN_FILE -3
typedef const char str[];

void check_file(FILE *file)
{
        if (file == NULL) {
                printf("Error opening file");
                getch();
                exit(ERROR_OPEN_FILE);
        }
}
void main() {
        FILE *file;
        char buffer[BUF_SIZE];
        str file_name = "file4.txt";
        str hello_world = "Hello, World!";
        file = fopen(file_name, "w");
        check_file(file);
        fprintf(file, hello_world);
        freopen(file_name, "r", file);
        check_file(file); // trouble
        fgets(buffer, BUF_SIZE - 1, file);
        printf("%s", buffer);
        fclose(file);
        getch();
}