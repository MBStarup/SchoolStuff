/*Skriv et program som oversætter udvalgte engelske navneord fra ental til flertal. Følgende regler skal overholdes:

Hvis et navneord ender i et "y" fjernes "y" og der tilføjes "ies".
Hvis et navneord ender i et "s", "ch" eller "sh" tilføjes et "es".
I alle andre tilfælde tilføjes et "s" til navneordet.
Udskriv hvert navneord i både ental og flertal.

Som altid skal du designe en funktion med et passende navn, og med parametre (input og evt. output). Og som altid laver vi top-down programmering ved trinvis forfinelse. Ønsker du at bruge returværdien af funktionen til noget?

Afprøv dit program på følgende engelske navneord:

chair dairy boss circus fly dog church clue dish
Alloker plads til disse i en passende array af tekststrenge.

Denne opgave svarer til opgave 5 side 532 i 6. udgave af lærebogen

Hints: Måske er funktionen strrchr fra string.h nyttig i denne opgave. Den søger efter et tegn fra bagenden af strengen. Husk også at du blot kan tilgå tegn i en tekststreng med array subscripting operatoren: str[i].
Du kan teste om et tegn i din streng svarer til et bestemt tegn: str[i] == 'y'.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define AMOUNT_OF_WORDS 9
#define STRING_SIZE 10

void printWords(const char *arrayOfWords[STRING_SIZE], int size);
char *getLastCharInWord(char *word);
char *makeWordPlural(const char *word);
char **makeAllWordsPlural(const char **arrayOfWords, int size);

int main(void)
{
    int i;

    char inWords[AMOUNT_OF_WORDS][STRING_SIZE] = {"char", "dairy", "boss", "circus", "fly", "dog", "church", "clue", "dish"};

    printWords(inWords, AMOUNT_OF_WORDS);
    printf("\n");
    makeAllWordsPlural(inWords, 9);
    printf("\n");
    printWords(inWords, 9);
    printf("\n");

    return EXIT_SUCCESS;
}

void printWords(const char *arrayOfWords[STRING_SIZE], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%s, ", arrayOfWords[i]);
    }
}

char *getLastCharInWord(char *word)
{
    char *last = strrchr(word, '\0');
    return (last - 1);
}

char *makeWordPlural(const char *word)
{
    char *lastChar = getLastCharInWord(word);
    int stringSize = lastChar - word + 1;

    char *newString;

    if (*lastChar == 'y')
    {
        newString = malloc((stringSize + 4) * sizeof(char));
        strcpy(newString, word);
        *(newString + stringSize) = 'i';
        *(newString + stringSize + 1) = 'e';
        *(newString + stringSize + 2) = 's';
        *(newString + stringSize + 3) = '\0';
    }
    else if (*lastChar == 's' || (*(lastChar - 1) == 'c' && *lastChar == 'h') || (*(lastChar - 1) == 's' && *lastChar == 'h'))
    {
        newString = malloc((stringSize + 3) * sizeof(char));
        strcpy(newString, word);
        *(newString + stringSize + 1) = 'e';
        *(newString + stringSize + 2) = 's';
        *(newString + stringSize + 3) = '\0';
    }
    else
    {
        newString = malloc((stringSize + 2) * sizeof(char));
        strcpy(newString, word);
        *(newString + stringSize + 1) = 's';
        *(newString + stringSize + 2) = '\0';
    }
}

char **makeAllWordsPlural(char *arrayOfWords[], int size)
{
    char **newArray = malloc(size * size(char *));
    for (int i = 0; i < size; i++)
    {
        newArray[i] = makeWordPlural(arrayOfWords[i]);
    }
    return newArray;
}
