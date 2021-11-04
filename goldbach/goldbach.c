#include <stdio.h>
#include <math.h>

void isPrime(int in) {
    for (int i = sqrt(in); i > 0; i--)
    {
        printf("%d\n", in%i);
    }
    
}

int main() {
    int in1, in2;
    int temp;


    printf("[x,y]\n");
    scanf(" %d,%d", &in1, &in2);

    isPrime(in1);
    //Do stuff here

    printf("%d\n", in1);

}


