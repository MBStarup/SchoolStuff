/*Magnus B. Starup : 19/10/2021 : QuadraticFormula */
#define INPUTBUFFERSIZE 256
#define INPUTAMOUNT 3

/*Stolen from StackOverflow (19/10/2021): https://stackoverflow.com/questions/47346133/how-to-use-a-define-inside-a-format-string */
/* this converts to string */
#define STR_(X) #X
/* this makes sure the argument is expanded before converting to string */
#define STR(X) STR_(X)
/*End of stolen content */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>

void ClearInputBuffer();
float Diskriminant(float a, float b, float c);
void SolveQuadratic(float a, float b, float c);
float GetFirstRoot(float a, float b, float c);
float GetSecondRoot(float a, float b, float c);

char **SeperateString(char *string, int amount)
{
    printf("Allocated mem for %d char pointers. Total = %d\n", amount, sizeof(char *) * amount);
    char **strings = malloc(sizeof(char *) * amount);
    strings[0] = strtok(string, " ");
    size_t i;
    for (i = 1; i < amount; i++)
    {
        strings[i] = strtok(NULL, " ");
    }

    return strings;
}

int main(int argc, char *argv[])
{
    char input[INPUTBUFFERSIZE];
    size_t i;

    float values[3];

    if (argc >= 4)
    {
        char aids[100000];
        sscanf(strcat(strcat(strcat(strcat(strcat(aids, argv[1]), " "), argv[2]), " "), argv[3]), "%f %f %f", &values[0], &values[1], &values[2]);
        /*printf("\n%s\n\n", strcat(strcat(strcat(strcat(strcat(aids, argv[1]), " "), argv[2]), " "), argv[3]));
        printf("%d\n", sscanf(strcat(strcat(strcat(strcat(strcat(aids, argv[1]), " "), argv[2]), " "), argv[3]), "%f %f %f", &values[0], &values[1], &values[2]));*/

        char *endptr;
        float num;
        for (i = 1; i < 4; i++)
        {
            num = strtod(argv[i], &endptr);
            /* if (*endptr != '\0')
             {
                 values[i - 1] = num;
             } */
        }
    }
    else
    {
        printf("Input numbers:\n[a b c]\n");

        /*
        printf("input:%s\n", input);
        scanf("%" STR(INPUTBUFFERSIZE) "[^\n]", &input);
        char **args = SeperateString(input, INPUTAMOUNT);

        for (i = 0; i < INPUTAMOUNT; i++)
        {
            printf("%s\n", args[i]);
        } */

        while (scanf(" %f %f %f", &values[0], &values[1], &values[2]) != 3)
        {
            ClearInputBuffer();
            printf("Try again\n[a,b,c]\n");
        }
    }

    SolveQuadratic(values[0], values[1], values[2]);

    return 0;
}

void ClearInputBuffer()
{
    char c = getchar();
    while (c != 10)
    {
        c = getchar();
    }
    return;
}

float Diskriminant(float a, float b, float c)
{
    return (b * b) - (4 * a * c);
}

float GetFirstRoot(float a, float b, float c)
{
    return (-b + sqrt(Diskriminant(a, b, c))) / (2 * a);
}

float GetSecondRoot(float a, float b, float c)
{
    return (-b - sqrt(Diskriminant(a, b, c))) / (2 * a);
}

void SolveQuadratic(float a, float b, float c)
{
    printf("Solving: %.2f x² + %.2f x + %.2f\n", a, b, c);

    if (Diskriminant(a, b, c) > 0)
    {
        printf("There are two (2) roots\n");
        printf("Root 1: %.2f\n", GetFirstRoot(a, b, c));
        printf("Root 2: %.2f\n", GetSecondRoot(a, b, c));
    }
    else if (Diskriminant(a, b, c) == 0)
    {
        printf("There is one (1) root\n");
        printf("Root 1: %.2f\n", GetFirstRoot(a, b, c));
    }
    else
    {
        printf("There are no roots\n");
    }
}