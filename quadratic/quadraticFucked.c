/*Magnus B. Starup : 19/10/2021 : QuadraticFormula */
/*NOTE: Good thing this program is short, cuz I don't free any memory :)*/
#define INPUTBUFFERSIZE 200
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

// TODO: make amount an out parameter instead
char **SeperateString(char *string, int amount)
{
    char **strings = malloc(amount);

    strings[0] = strtok(string, " ");
    size_t i;
    for (i = 1; i < amount; i++)
    {
        strings[i] = strtok(NULL, " ");
    }

    return strings;
}

float *StringsToFloats(char **strings, int amount)
{
    float *values = malloc(sizeof(float) * amount);
    char *endptr;
    float num;
    size_t i;

    for (i = 0; i < amount; i++)
    {
        num = strtod(strings[i], &endptr);
        if (endptr == strings[i])
        {
            //*success = 0;
            return NULL;
        }
        else
        {
            values[i] = num;
        }
    }

    return values;
}

char *GetInput()
{
    char *input = malloc(sizeof(char) * INPUTBUFFERSIZE);

    printf("Input numbers:\n[a b c]\n");

    printf("input:%s\n", input);
    scanf("%" STR(INPUTBUFFERSIZE) "[^\n]", input);

    return input;
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

int main(int argc, char *argv[])
{

    float *values;
    if (argc >= 4)
    {
        values = StringsToFloats(argv + 1, INPUTAMOUNT);
    }
    else
    {

        char **args = SeperateString(GetInput(), INPUTAMOUNT);

        values = StringsToFloats(args, INPUTAMOUNT);

        while (0)
        {
            ClearInputBuffer();
            printf("Try again\n[a,b,c]\n");
        }
    }

    SolveQuadratic(values[0], values[1], values[2]);

    return 0;
}