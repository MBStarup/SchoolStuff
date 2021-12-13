#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define _BUFFER_SIZE 1024

typedef struct team
{
    char teamName[3];
    int points;
    int goals;
    int goalsAgainst;

} team;

typedef struct game
{
    char weekDay[4];
    int day;
    int month;
    int hour;
    int minute;
    char firstTeamName[4];
    char secondTeamName[4];
    int firstTeamScore;
    int secondTeamScore;
    int viewers;
} game;

void printArr(char **arr, int count)
{
    for (size_t i = 0; i < count; i++)
    {
        printf("%5d: %s\n", i, arr[i]);
    }
}

int lineCountOfFile(char *fileName)
{
    FILE *inputFile;
    int i = 0;

    inputFile = fopen(fileName, "r");

    if (inputFile == NULL)
    {
        perror("Unable to open the file");
        exit(1);
    }

    char inputLine[_BUFFER_SIZE];

    while (fgets(inputLine, _BUFFER_SIZE, inputFile) != NULL)
    {
        ++i;
    }
    fclose(inputFile);
    return i;
}

void parseLine(game *outGame, const char *line)
{
    sscanf(line, " %3s %2d/%2d %2d.%2d %3s - %3s %d - %d %d", outGame->weekDay, &outGame->month, &outGame->day, &outGame->hour, &outGame->minute, outGame->firstTeamName, outGame->secondTeamName, &outGame->firstTeamScore, &outGame->secondTeamScore, &outGame->viewers);
}

void printGame(game game)
{
    printf(" %3.3s %2.2d/%2.2d %2.2d.%2.2d %3.3s - %3.3s %d - %d %d\n", game.weekDay, game.month, game.month, game.hour, game.minute, game.firstTeamName, game.secondTeamName, game.firstTeamScore, game.secondTeamScore, game.viewers);
}

void calculateScore(const game games[], int count)
{
    for (size_t i = 0; i < count; i++)
    {
        // game[i];
    }
}

int main(void)
{
    char fileName[] = "kampe-2020-2021.txt";

    int count = lineCountOfFile(fileName);

    game *games = malloc(count * sizeof(game));
    assert(games != NULL);

    printf("SIZE %d\n", sizeof(games[0].weekDay));
    printf("SIZE %d\n", sizeof(char));
    printf("SIZE %d\n", sizeof(char *));
    printf("SIZE %d\n", sizeof(char[5]));
    printf("SIZE %d\n", sizeof(char[16]));

    FILE *inputFile = fopen(fileName, "r");
    assert(inputFile != NULL);

    /*Read and parse each line*/
    char inputLine[_BUFFER_SIZE];
    for (size_t i = 0; i < count; i++)
    {
        fgets(inputLine, _BUFFER_SIZE, inputFile);
        parseLine(&games[i], inputLine);
    }
    fclose(inputFile);
}