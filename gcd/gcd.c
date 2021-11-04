//Magnus B. Starup : 27/09/2021 : GCD
#include <stdio.h>

void clearInputBuffer() {
    char c = getchar();
    while (c != 10) {
        c = getchar();
    }
    return;
}

int main() {
    int in1 = 0, in2 = 0;

    while (1) {
        printf("[x,y] to find the GCD, or a negative number to exit\n");

        while(!scanf(" %d,%d", &in1, &in2)) {
            clearInputBuffer();
            printf("Try again\n[x,y]\n");
        }

        //printf("Input: %d,%d\n", in1, in2);

        //handle negative case
        if ((in1 < 0) || (in2 < 0)) {
            return 0;
        }

        //handle 0 cases
        if (!in1 && !in2) {
            printf("undefinded");
        }
        else if (!in1) {
            printf("%d\n", in2);
        }
        else if (!in2) {
            printf("%d\n", in1);
        }
        //handle positive case
        else {
            int i = in1 < in2 ? in1 : in2;

            while (i > 0 && !(in1%i == 0 && in2%i == 0)) {
                //printf("%d mod %d = %d & %d mod %d = %d\n",in1, i, in1%i, in2, i, in2%i);
                --i;
            }  

            printf("GCD: %d\n", i);
        }
        printf("\n");
    }
}


