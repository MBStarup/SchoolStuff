#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
#define DIE_EYES 6

int rollDie(int eyes)
{
    return (rand() % (eyes)) + 1;
}

int *rollDice(int eyes, int amount)
{
    int *res = malloc(sizeof(int) * amount);
    for (size_t i = 0; i < amount; i++)
    {
        res[i] = rollDie(eyes);
    }

    return res;
}

void printList(int *list, int size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf("%d ", list[i]);
    }
    printf("\n");
}

int amountOfNum(int *arr, int size, int num)
{
    int res = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] == num)
        {
            ++res;
        }
    }
    return res;
}

void playYatzy(int rollAmount, int eyes)
{
    srand(time(NULL));
    int points = 0;

    for (size_t i = 1; i <= eyes; i++) // rolls from 1 to eyes
    {
        int *rolls = rollDice(eyes, rollAmount);
        int a = amountOfNum(rolls, rollAmount, i);
        int p = (a < 6 ? a : 5) * i;
        points += p;

        printf("\n");
        printList(rolls, rollAmount);
        printf("There are %d %d's\n", a, i);
        printf("You get %d points, and now have %d points\n", p, points);

        free(rolls);
    }

    // et par
    int *rolls = rollDice(eyes, rollAmount);
    printf("\n");
    printList(rolls, rollAmount);
    for (size_t i = eyes; i > 0; i--)
    {
        if (amountOfNum(rolls, rollAmount, i) >= 2)
        {
            int p = 2 * i;
            points += p;
            printf("There is a pair of %d's\n", i);
            printf("You get %d points, and now have %d points\n", p, points);
            break;
        }
    }
    free(rolls);

    // two par
    rolls = rollDice(eyes, rollAmount);
    printf("\n");
    printList(rolls, rollAmount);
    int pairs = 0;
    int firstPair = 0;
    for (size_t i = eyes; i > 0 && pairs < 2; i--)
    {
        if (amountOfNum(rolls, rollAmount, i) >= 2)
        {
            ++pairs;
            if (pairs == 1)
            {
                firstPair = i;
            }
            if (pairs == 1 && amountOfNum(rolls, rollAmount, i) >= 4)
            {
                ++pairs;
                int p = 4 * i;
                points += p;
                printf("There is two pair of %d's\n", i);
                printf("You get %d points, and now have %d points\n", p, points);
            }
            else if (pairs == 2)
            {
                int p = 2 * i + 2 * firstPair;
                points += p;
                printf("There is a pair of %d's and a pair of %d's\n", firstPair, i);
                printf("You get %d points, and now have %d points\n", p, points);
            }
        }
    }
    free(rolls);

    // tre ens
    rolls = rollDice(eyes, rollAmount);
    printf("\n");
    printList(rolls, rollAmount);
    for (size_t i = eyes; i > 0; i--)
    {
        if (amountOfNum(rolls, rollAmount, i) >= 3)
        {
            int p = 3 * i;
            points += p;
            printf("There is three of %d's\n", i);
            printf("You get %d points, and now have %d points\n", p, points);
            break;
        }
    }
    free(rolls);

    // fire ens
    rolls = rollDice(eyes, rollAmount);
    printf("\n");
    printList(rolls, rollAmount);
    for (size_t i = eyes; i > 0; i--)
    {
        if (amountOfNum(rolls, rollAmount, i) >= 4)
        {
            int p = 4 * i;
            points += p;
            printf("There is four of %d's\n", i);
            printf("You get %d points, and now have %d points\n", p, points);
            break;
        }
    }
    free(rolls);
}

int main()
{
    playYatzy(N, DIE_EYES);
}