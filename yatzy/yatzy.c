/*Magnus B. Starup; Datalogi; mstaru21@student.aau.dk; Yatzy*; 05/11/2021*/
/*This is not great...*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N 10            //Adjustable as long as N >= 5
#define SCORE_AMOUNT 16 //NOT

typedef enum bool
{
    false,
    true
} bool;

int rollDie(int eyes)
{
    return (rand() % (eyes)) + 1;
}

void rollDice(int eyes, int length, int *out)
{
    for (size_t i = 0; i < length; i++)
    {
        out[i] = rollDie(eyes);
    }
}

void printList(const int *list, int length)
{
    for (size_t i = 0; i < length; i++)
    {
        printf("%d ", list[i]);
    }
    printf("\n");
}

int amountOfNum(const int *arr, int length, int num)
{
    int res = 0;
    for (size_t i = 0; i < length; i++)
    {
        if (arr[i] == num)
        {
            ++res;
        }
    }
    return res;
}

/*
replaces all instances of instances of a with b in arr
returns the amount replaced
*/
int replaceInList(int *arr, int length, int a, int b)
{
    int res = 0;
    for (size_t i = 0; i < length; ++i)
    {
        if (arr[i] == a)
        {
            arr[i] = b;
            ++res;
        }
    }
    return res;
}

int sumList(const int *arr, int length)
{
    int res = 0;
    for (size_t i = 0; i < length; ++i)
    {
        res += arr[i];
    }
    return res;
}

/*
Expects and int[] with length 16
*/
void printYatzyScoreboard(const int *scoreBoard)
{
    char *categories[] =
        {
            "Ones",
            "Twos",
            "Threes",
            "Fours",
            "Fives",
            "Sixes",
            "Upper Section Bonus",

            "One Pair",
            "Two Pairs",
            "Three Of A Kind",
            "Four Of A Kind",
            "Small Straight",
            "Large Straight",
            "Full House",
            "Chance",
            "Yatzy",
        };

    char line[54] = {[0 ... 25] = 45, '|', [27 ... 52] = 45, '\0'}; //This apparently only works on gcc, so complile with that :)
    printf("%s\n", line);
    printf("%25s |\n", "Upper Section");
    printf("%s\n", line);
    for (size_t i = 0; i <= 6; i++)
    {
        printf("%25s | %-25d\n", categories[i], scoreBoard[i]);
    }
    printf("%s\n", line);
    printf("%25s |\n", "Lower Section");
    printf("%s\n", line);
    for (size_t i = 7; i < 16; i++)
    {
        printf("%25s | %-25d\n", categories[i], scoreBoard[i]);
    }
    printf("%s\n", line);
}

/*
Returns the largest int X, where there are 'n' or more Xs in 'arr', and X <= 'start'
*/
int largest_N_Of_A_Kind(const int *arr, int size, int start, int n)
{
    int *larr = malloc(sizeof(int) * size);
    memcpy(larr, arr, sizeof(int) * size);
    for (size_t i = start; i > 0; --i)
    {
        if (replaceInList(larr, size, i, -1) >= n)
        {
            free(larr);
            return i;
        }
    }
    free(larr);
    return 0;
}

/*
Returns wheter or not there is a straight of length 'length' starting from 'start' and going up in 'arr'
Also this is a stupid fuction..
*/
bool straight(const int *arr, int size, int start, int length)
{
    int *larr = malloc(sizeof(int) * size);
    memcpy(larr, arr, sizeof(int) * size);
    int count = 0;
    int i = start;
    while (i <= start + length)
    {
        if (replaceInList(larr, size, i, -1) > 0)
        {
            ++count;
        }
        ++i;
    }
    if (count >= length)
    {
        free(larr);
        return true;
    }
    free(larr);
    return false;
}

int playYatzy(int rollAmount)
{
    srand(time(NULL)); //seed the rng
    int scoreBoard[SCORE_AMOUNT] = {0};
    int *amounts = malloc(sizeof(int) * (6 + 1));
    int *rolls = malloc(sizeof(int) * rollAmount);

    for (size_t i = 1; i <= 6; i++) // rolls from 1 to 6
    {
        rollDice(6, rollAmount, rolls);
        printf("\n%ds: ", i);
        printList(rolls, rollAmount);
        int a = amountOfNum(rolls, rollAmount, i);
        int p = (a < 6 ? a : 5) * i;
        scoreBoard[i - 1] = p;
    }

    //top part bonus thing
    if (sumList(scoreBoard, SCORE_AMOUNT) >= 63)
    {
        scoreBoard[6] = 50;
    }

    //one pair
    rollDice(6, rollAmount, rolls);
    printf("\nPairs: ");
    printList(rolls, rollAmount);
    scoreBoard[7] = 2 * largest_N_Of_A_Kind(rolls, rollAmount, 6, 2);

    //two pairs
    rollDice(6, rollAmount, rolls);
    printf("\nTwo Pairs: ");
    printList(rolls, rollAmount);
    {
        int firstPair = -1;
        int i = 6;
        while (i > 0)
        {
            if (replaceInList(rolls, rollAmount, i, -1) >= 2)
            {
                if (firstPair == -1)
                {
                    firstPair = i;
                }
                else
                {
                    scoreBoard[8] = 2 * i + 2 * firstPair;
                    i = 0; //end the for loop
                }
            }
            --i;
        }
        printf("\n");
    }

    //three of a kind
    rollDice(6, rollAmount, rolls);
    printf("\nTrips: ");
    printList(rolls, rollAmount);
    scoreBoard[9] = 3 * largest_N_Of_A_Kind(rolls, rollAmount, 6, 3);

    //four of a kind
    rollDice(6, rollAmount, rolls);
    printf("\nQuads: ");
    printList(rolls, rollAmount);
    scoreBoard[10] = 4 * largest_N_Of_A_Kind(rolls, rollAmount, 6, 4);

    //small straight
    rollDice(6, rollAmount, rolls);
    printf("\nS_Straight: ");
    printList(rolls, rollAmount);
    scoreBoard[11] = straight(rolls, rollAmount, 1, 5) == true ? 15 : 0;

    // {
    //     int count = 0;
    //     int i = 1;
    //     while (i <= 5)
    //     {
    //         if (replaceInList(rolls, rollAmount, i, -1) > 0)
    //         {
    //             ++count;
    //         }
    //         ++i;
    //     }
    //     if (count >= 5)
    //     {
    //         scoreBoard[11] = 15;
    //     }
    // }

    //large straight
    rollDice(6, rollAmount, rolls);
    printf("\nL_Straight: ");
    printList(rolls, rollAmount);
    scoreBoard[12] = straight(rolls, rollAmount, 2, 5) == true ? 20 : 0;
    // {
    //     int count = 0;
    //     int i = 2;
    //     while (i <= 6)
    //     {
    //         if (replaceInList(rolls, rollAmount, i, -1) > 0)
    //         {
    //             ++count;
    //         }
    //         ++i;
    //     }
    //     if (count >= 5)
    //     {
    //         scoreBoard[12] = 20;
    //     }
    // }

    //full house
    rollDice(6, rollAmount, rolls);
    printf("\nHouse: ");
    printList(rolls, rollAmount);
    {
        int threes = -1;
        int i = 6;
        while (i > 0)
        {
            if (threes == -1)
            {
                if (replaceInList(rolls, rollAmount, i, -1) >= 3)
                {
                    threes = i;
                }
            }
            else
            {
                if (replaceInList(rolls, rollAmount, i, -1) >= 2)
                {
                    scoreBoard[13] = 2 * i + 3 * threes;
                    i = 0; //end the for loop
                }
            }
            --i;
        }
        printf("\n");
    }

    //chance
    rollDice(6, rollAmount, rolls);
    printf("\nChance: ");
    printList(rolls, rollAmount);
    {
        int count = 0;
        int i = 6;
        while (count < 5 && i > 0)
        {
            int amount = replaceInList(rolls, rollAmount, i, -1);
            while (count < 5 && amount > 0)
            {
                ++count;
                --amount;
                printf("%d, ", i);
                scoreBoard[14] += i;
            }
            --i;
        }
        printf("\n");
    }

    //yatzy
    rollDice(6, rollAmount, rolls);
    printf("\nYatzy: ");
    printList(rolls, rollAmount);
    scoreBoard[15] = largest_N_Of_A_Kind(rolls, rollAmount, 6, 5) == 0 ? 0 : 50;

    free(amounts);
    free(rolls);

    printYatzyScoreboard(scoreBoard);

    return sumList(scoreBoard, SCORE_AMOUNT);
}

int main()
{
    printf("Final score is %d\n", playYatzy(N));
}