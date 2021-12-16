#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void Merge(int *L, int start, int end, int mid);
void MergeSort(int *L, int start, int end);
void printList(int *L, int size);

int main(void)
{
    int L[] = {5, 3, 8, 1, 6, 10, 7, 2, 4, 9, 42, 12, 31, 123, 12, 31, 3, 123, 13, 12, 31, 4, 4, 4, 54, 4, 2, 4, 6, 2, 41, 3, 13, 53, 45, 25, 2, 4, 25, 2, 4234};
    int L_size = sizeof(L) / sizeof(L[0]);

    printf("Given list \n");
    printList(L, L_size);
    printf("\n");

    MergeSort(L, 0, L_size - 1);

    printf("The sorted list \n");
    printList(L, L_size);
    printf("\n");
    return 0;
}

void Merge(int *L, int start, int mid, int end)
{
    int *result = malloc(((end - start) + 1) * sizeof(int));
    int i = 0;

    int *a = L + start;
    int a_len = (mid - start) + 1;
    int a_i = 0;

    int *b = L + mid + 1;
    int b_len = end - mid;
    int b_i = 0;

    while (a_i < a_len && b_i < b_len)
    {
        if (a[a_i] < b[b_i])
            result[i++] = a[a_i++];

        else
            result[i++] = b[b_i++];
    }

    if (a_i < a_len) /*Not done with a*/
        memcpy(result + i, a + a_i, (a_len - a_i) * sizeof(int));

    else /*Not done with b*/
        memcpy(result + i, b + b_i, (b_len - b_i) * sizeof(int));

    memcpy(L + start, result, ((end - start) + 1) * sizeof(int));
    free(result);
}

void MergeSort(int *L, int start, int end)
{
    int mid;
    if (end != start)
    {
        mid = (start + end) / 2;

        MergeSort(L, start, mid);
        MergeSort(L, mid + 1, end);
        Merge(L, start, mid, end);
    }
}

void printList(int *L, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", L[i]);
}