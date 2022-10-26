#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
typedef const char str[];
void main() {
        FILE *file;
        char c;
        str file_name = "file5.txt"; 
        file = fopen(file_name, "w");
        do {
                c = getch();
                fprintf(file, "%c", c);
                fprintf(stdout, "%c", c);
                // fflush(file);
        } while(c != 'q');
        fclose(file);
        getch();
}