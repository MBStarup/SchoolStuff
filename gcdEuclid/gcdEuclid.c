#include <stdio.h>

int main() {
    int in1, in2;
    int temp;


    printf("[x,y]\n");
    scanf(" %d,%d", &in1, &in2);

    while (in2 != 0) {
        temp = in2;
        in2 = in1 % in2;
        in1 = temp;
    }

    printf("%d\n", in1);

}


