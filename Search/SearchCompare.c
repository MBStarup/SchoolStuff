#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 500

void LinSearch(int array[], int x, int print);
void BinSearch(int array[], int x, int print);

int main(void)
{
    printf("%d", CLOCK_MONOTONIC);
    int x;
    char filename[20];
    FILE *myFile;
    int array[N];
    int k;
    int runs = pow(10, 2);
    int i;

    sprintf(filename, "List%d.txt", N);
    printf("What number are we searching for?\n"); /* Feel free to alter this*/
    scanf("%d", &x);

    myFile = fopen(filename, "r");

    /* iList is read into array */
    for (k = 0; k < N; k++)
    {
        fscanf(myFile, "%d", &array[k]);
    }
    fclose(myFile);

    printf("The size of the list is %d\n", N);

    /* start time */
    struct timespec startTime, endTime;
    clock_gettime(CLOCK_MONOTONIC, &startTime);

    for (i = 0; i < runs; i++)
    {
        BinSearch(array, x, 0);
    }

    /* stop time and print */
    clock_gettime(CLOCK_MONOTONIC, &endTime);
    double duration = (double)(endTime.tv_sec - startTime.tv_sec) +
                      1e-9 * (endTime.tv_nsec - startTime.tv_nsec);
    printf("BinSearch brugte: %.7fs\n", duration);

    /* start time */
    clock_gettime(CLOCK_MONOTONIC, &startTime);

    for (i = 0; i < runs; i++)
    {
        LinSearch(array, x, 0);
    }

    /* stop time and print */
    clock_gettime(CLOCK_MONOTONIC, &endTime);
    duration = (double)(endTime.tv_sec - startTime.tv_sec) +
               1e-9 * (endTime.tv_nsec - startTime.tv_nsec);
    printf("LinSearch brugte: %.7fs\n", duration);

    /* Prints the result */
    LinSearch(array, x, 1);
    BinSearch(array, x, 1);
    printf("Done!\n"); /* Feel free to be more creative here */
    return 0;
}

void LinSearch(int array[], int x, int print)
{

    /* Fill in your code HERE! */
    int i = 0;

    if (print == 1)
    {
        if (x == array[i])
        {
            printf("%d er på position %d\n", x, i + 1);
        }
        else
        {
            printf("%d er ikke i listen \n", x);
        }
    }
}

void BinSearch(int array[], int x, int print)
{

    /* Fill in your code HERE */

    int i = 0;

    if (print == 1)
    {
        if (x == array[i])
        {
            printf("%d is in position %d\n", x, i + 1);
        }
        else
        {
            printf("%d is not in the list \n", x);
        }
    }
}
