#include <stdio.h>
#include <math.h>
#define DELTA 0.2

void clearInputBuffer() {
    char c = getchar();
    while (c != 10) {
        c = getchar();
    }
    return;
}

int main() {
    float x, y, r, l;
    int inputIsUsable = 0;
    printf("Hvor stor er din circle?\n");
    inputIsUsable = scanf(" %f", &r);
    while (!inputIsUsable) {
        clearInputBuffer();
        printf("Prøv igen\n");
        inputIsUsable = scanf(" %f", &r);
    }
    clearInputBuffer();

    printf("Hvor er dit punkt? [x,y]\n");
    inputIsUsable = scanf(" %f,%f", &x, &y);
        while (!inputIsUsable) {
        clearInputBuffer();
        printf("Prøv igen\n");
        inputIsUsable = scanf(" %f,%f", &x, &y);
    }
    printf("%f ; %f\n", x, y);


    l = sqrt(x*x + y*y);

    (l > r + DELTA) ? printf("Ude\n") : ((l < r - DELTA) ? printf("Inde\n") : printf("På\n"));

    return 0;
}