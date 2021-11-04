#include <stdio.h>
#include <stdlib.h>

typedef struct doubleArrWithSize
{
    int size;
    double *arr;
} doubleArrWithSize;

void printArr(doubleArrWithSize a)
{
    if (a.size > 0)
    {
        printf("%.0f", a.arr[0]);

        for (size_t i = 1; i < a.size; i++)
        {
            printf(", %.0f", a.arr[i]);
        }
    }
    return;
}

doubleArrWithSize weaveArrs(doubleArrWithSize a1, doubleArrWithSize a2)
{
    double *arr = malloc((a1.size + a2.size) * sizeof(double));
    int size = 0;

    int i = 0;
    int j = 0;
    int k = 0;

    while (i < a1.size && j < a2.size)
    {
        if (a1.arr[i] < a2.arr[j])
        {
            arr[k++] = a1.arr[i++];
        }
        else if (a1.arr[i] > a2.arr[j])
        {
            arr[k++] = a2.arr[j++];
        }
        else
        {
            arr[k++] = a1.arr[i++];
            ++j;
        }
        ++size;
    }
    // only one of these last two whiles will run, copying over the tail of one array, when the other has run out of thigs to compare to
    while (i < a1.size)
    {
        arr[k++] = a1.arr[i++];
        ++size;
    }
    while (j < a2.size)
    {
        arr[k++] = a2.arr[j++];
        ++size;
    }

    arr = (double *)realloc(arr, size * sizeof(double)); // downsize array

    doubleArrWithSize res = {.size = size, .arr = arr}; // pack neatly for return
    return res;
}

int main()
{
    double arr1[] = {-123, -122, -33, 0, 1, 100, 1332, 12311, 12333, 12334};
    double arr2[] = {-123, -122, -45, -29, 0, 1, 23, 322, 533, 1553};

    doubleArrWithSize in1 = {
        .size = 10,
        .arr = arr1,
    };

    doubleArrWithSize in2 = {
        .size = 10,
        .arr = arr2,
    };

    doubleArrWithSize weaved = weaveArrs(in1, in2);

    printf("in1   : ");
    printArr(in1);

    printf("\nin2   : ");
    printArr(in2);

    printf("\nweaved: ");
    printArr(weaved);
    printf("\n");
}