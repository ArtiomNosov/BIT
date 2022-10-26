#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
 
void main() {
    int a, b;
    fprintf(stdout, "Enter two numbers\n");
    fscanf(stdin, "%d", &a);
    fscanf(stdin, "%d", &b);
    if (b == 0) {
        fprintf(stderr, "Error: divide by zero");
    } else {
        fprintf(stdout, "%.3f", (float) a / (float) b);
    }
    getch();
}
