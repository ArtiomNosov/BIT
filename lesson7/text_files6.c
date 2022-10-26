#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
typedef const char str[];
void main() {
    FILE *input = NULL;
    char c;
    char buffer[BUFSIZ * 2] = {0};
    str file_name = "file4.txt"; 
    input = fopen(file_name, "rt");
    setbuf(input, buffer);
 
    while (!feof(input)) {
        c = fgetc(input);
        printf("%c\n", c);
        printf("%s\n", buffer);
        _getch();
    }
 
    fclose(input);
}