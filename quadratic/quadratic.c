/*Magnus B. Starup : 27/09/2021 : QuadraticFormula*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void clearInputBuffer();
float getDiscriminant(float a, float b, float c);
int solveQuadraticEquation(float a, float b, float c);
float getFirstRoot(float a, float b, float c);
float getSecondRoot(float a, float b, float c);

int main()
{
    float in1, in2, in3;
    int inputIsValid;

    while (1)
    {
        inputIsValid = 0;
        printf("\nInput numbers (use 0 0 0 to quit):\n[a b c]\n");

        /*
            Jeg føler mig lidt tvunget til at have denne if-else kæde og et flag controlled loop,
            da jeg er tvunget til at aceptere in1 == 0 som et valid input for at kunne afslutte hvis alle tre er 0,
            men gerne vil undgå at aceptere in1 == 0 i alle andre tilfælde.

            Jeg ville hellere have noget lignende:
            while(scanf(" %f %f %f", &in1, &in2, &in3) != 3 || in1 == 0)
            {
                clearInputBuffer();
                printf("\nTry again\nInput has to be numbers\n[a b c]\n");
            }
            og så have haft en anden måde at terminere programmet på, helst bare ved at løse et udtryk per program.

            Man kunne også gøre dette
            while(scanf(" %f %f %f", &in1, &in2, &in3) != 3 || in1 == 0 && !(in1 == 0 && in2 == 0 && in3 == 0)))
            {
                clearInputBuffer();
                printf("\nTry again\nInput has to be numbers\n[a b c]\n");
            }
            if (in1 == 0 && in2 == 0 && in3 == 0)
            {
                exit(0);
            }
            men her ender vi med at tjekke om alle input er nul to gange, og så er det lidt ulæseligt imo.

            Er der nogen bestemt grund til at vores program skal ende ved et 0-0-0 input?
        */

        while (!inputIsValid)
        {
            if (scanf(" %f %f %f", &in1, &in2, &in3) != 3)
            {
                clearInputBuffer();
                printf("\nTry again\nInput has to be numbers\n[a b c]\n");
            }
            else if (in1 == 0 && in2 == 0 && in3 == 0)
            {
                exit(0);
            }
            else if (in1 == 0)
            {
                clearInputBuffer();
                printf("\nTry again\nFirst input cannot be zero\n[a b c]\n");
            }
            else
            {
                inputIsValid = 1;
            }
        }

        solveQuadraticEquation(in1, in2, in3);
    }

    return 0;
}

void clearInputBuffer()
{
    char c = getchar();
    while (c != 10)
    {
        c = getchar();
    }
    return;
}

float getDiscriminant(float a, float b, float c)
{
    return (b * b) - (4 * a * c);
}

float getFirstRoot(float a, float b, float c)
{
    return (-b + sqrt(getDiscriminant(a, b, c))) / (2 * a);
}

float getSecondRoot(float a, float b, float c)
{
    return (-b - sqrt(getDiscriminant(a, b, c))) / (2 * a);
}

/*Solves for the roots of a quadratic equation and outputs teh results. Returns the amount of roots*/
int solveQuadraticEquation(float a, float b, float c)
{
    printf("\nSolving: %.2f x² + %.2f x + %.2f\n", a, b, c);
    float d = getDiscriminant(a, b, c);

    if (d > 0)
    {
        printf("There are two (2) roots\n");
        printf("Root 1: %.2f\n", getFirstRoot(a, b, c));
        printf("Root 2: %.2f\n", getSecondRoot(a, b, c));
        return 2;
    }
    else if (d == 0)
    {
        printf("There is one (1) root\n");
        printf("Root 1: %.2f\n", getFirstRoot(a, b, c));
        return 1;
    }
    else
    {
        printf("There are no roots\n");
        return 0;
    }
}