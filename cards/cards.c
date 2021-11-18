#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define SMALL_STRING_SIZE 255
#define DECK_SIZE 55
#define MAX_VAL 13

typedef struct
{
    char string[SMALL_STRING_SIZE];
} smallString;

smallString SString(const char *in)
{
    smallString res;
    assert(strlen(in) < SMALL_STRING_SIZE);
    strcpy(res.string, in);

    return res;
}

typedef enum
{
    clubs,
    diamonds,
    hearts,
    spades,
    joker //Keep the joker as the last enum
} suit;

typedef struct
{
    suit suit;
    int value;
} card;

typedef struct
{
    card cards[DECK_SIZE];
} deck;

deck getStandardDeck()
{
    static_assert(DECK_SIZE >= (joker * MAX_VAL), "getStandardDeck() assumes that the DECK_SIZE at least has space for one of each value of each suit, not including the joker"); //This function assumes that the DECK_SIZE at least has space for one of each value of each suit, not including the joker
    deck res;

    int counter = 0;
    for (size_t suit = 0; suit < joker; suit++)
    {
        for (size_t val = 1; val <= MAX_VAL; val++)
        {
            card card = {.suit = suit, .value = val};
            res.cards[counter++] = card;
        }
    }

    card card = {.suit = joker};
    while (counter < DECK_SIZE)
    {
        res.cards[counter++] = card;
    }

    return res;
}

smallString suitName(suit s)
{
    switch (s)
    {
    case clubs:
        return SString("clubs ♣");
    case diamonds:
        return SString("diamonds ♦");
    case hearts:
        return SString("hearts ♥");
    case spades:
        return SString("spades ♠");
    case joker:
        return SString("joker 🃏");

    default:
    {
        char string[SMALL_STRING_SIZE] = {"unknown "};
        char num[SMALL_STRING_SIZE];
        sprintf(num, "%d", s);
        return SString(strncat(string, num, SMALL_STRING_SIZE - strlen(string)));
    }
    }
}

void printDeck(deck d)
{
    for (size_t i = 0; i < DECK_SIZE; i++)
    {
        if (d.cards[i].suit != joker)
        {
            printf("%15s | %d\n", suitName(d.cards[i].suit).string, d.cards[i].value);
        }
        else
        {
            printf("%15s\n", suitName(d.cards[i].suit).string);
        }
    }
}

int main()
{
    deck d = getStandardDeck();
    printDeck(d);
}