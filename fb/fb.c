#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void *addPtr(const void *pointer, int bytes)
{
    return (((char *)pointer) + bytes);
}

typedef struct hashTable
{
    // hashTableEntry *table;
    void *data;
    int tableSize;
    int keySize;
    int valueSize;
} hashTable;

typedef struct hashTableEntry
{
    void *key;
    void *value;
    struct hashTableEntry *next;
} hashTableEntry;

int _htHashFunc(void *key, int size)
{
}

int _htGetIndex(hashTable table, void *key)
{
    return _htHashFunc(key, table.keySize) % table.tableSize;
}

int _htGetOffset(hashTable table, int index)
{
    return index * ((sizeof(hashTableEntry) + table.keySize + table.valueSize));
}

// // hashTableEntry *_htGetEntry(hashTable table, void *key)
// // {
// //     /* Recursive way
// //     // hashTableEntry *_htRecSearchEntry(hashTableEntry * entry, void *key)
// //     // {
// //     //     if (memcmp(entry->key, key) == 0)
// //     //     {
// //     //         return entry;
// //     //     }
// //     //     else if (entry->next != NULL)
// //     //     {
// //     //         return _htRecSearchEntry(entry->next, key);
// //     //     }
// //     //     else
// //     //     {
// //     //         return NULL
// //     //     }
// //     // }

// //     // hashTableEntry *entry = table.data + _htGetOffset(_htHashFunc(key, table.keySize));
// //     // return _htRecSearchEntry(entry, key);
// //     */

// //     hashTableEntry *entry = addPtr(table.data, _htGetOffset(_htHashFunc(key, table.keySize)));
// //     while (memcmp(entry->key, key) != 0)
// //     {
// //         if (entry->next != NULL)
// //         {
// //             entry = entry->next;
// //         }
// //         else
// //         {
// //             return NULL
// //         }
// //     }
// //     return entry;
// // }

hashTable htInitTable(int tableSize, int keySize, int valueSize)
{
    hashTable table = {.tableSize = tableSize, .keySize = keySize, .valueSize = valueSize};

    /*
    // table.table = malloc(tableSize * (sizeof(hashTableEntry)));
    // assert(table.table != NULL);

    // void *data = malloc(tableSize * (sizeof(hashTableEntry) + keySize + valueSize)); //Allocate the initial chunk of memory
    // assert(data != NULL);
    */

    table.data = malloc(tableSize * (sizeof(hashTableEntry) + keySize + valueSize)); /*Allocate the initial chunk of memory*/
    assert(table.data != NULL);

    for (size_t i = 0; i < table.tableSize; i++)
    {
        hashTableEntry *entry = addPtr(table.data, i * (sizeof(hashTableEntry) + keySize + valueSize));
        entry->key = NULL;
        entry->next = NULL;
    }

    return table;
}

void htDeleteTable(hashTable table)
{
    assert(0 && "Not implemented yet"); // TODO: implement
}

void *htGet(hashTable table, void *key)
{
    hashTableEntry *entry = addPtr(table.data, _htGetOffset(table, _htGetIndex(table, key)));
    if (entry->key == NULL)
        return NULL; /*Key not in table*/
    else
    {
        hashTableEntry *next = NULL;
        do
        {
            if (memcmp(entry->key, key, table.keySize) == 0) /*Founnd it*/
            {
                return entry->value;
            }
            next = entry->next;
        } while (next != NULL);

        return NULL; /*Didn't find it in the chain*/
    }
}

/*
Inserts an value in the hashtable
If an value already exists at teh given key, it will be replaced

returns 1 for success and 0 for faliure
*/
int htInsert(hashTable table, void *key, void *value)
{
    hashTableEntry *entry = addPtr(table.data, _htGetOffset(table, _htGetIndex(table, key)));
    if (entry->key == NULL) /*Empty slot*/
    {
        entry->key = memcpy(addPtr(entry, sizeof(hashTableEntry)), key, table.keySize);                       /*Copy the key into the area after the entry*/
        entry->value = memcpy(addPtr(entry, sizeof(hashTableEntry) + table.keySize), value, table.valueSize); /*Copy the value into the area after the key*/
        entry->next = NULL;                                                                                   /*Make sure the next is set to NULL, to indicate that this is the last entry at the position*/
        return 1;
    }
    else
    {
        hashTableEntry *next = NULL;
        do
        {
            if (memcmp(entry->key, key, table.keySize) == 0) /*Already existing entry*/
            {
                memcpy(entry->value, value, table.valueSize); /*overide the value with the new value*/
                return 1;
            }
            next = entry->next;
        } while (next != NULL);

        next = malloc(sizeof(hashTableEntry) + table.keySize + table.valueSize);
        if (next == NULL)
            return 0;                                                                                       /*Failed to allocate memory for the new entry*/
        next->key = memcpy(addPtr(next, sizeof(hashTableEntry)), key, table.keySize);                       /*Copy the key into the area after the entry*/
        next->value = memcpy(addPtr(next, sizeof(hashTableEntry) + table.keySize), value, table.valueSize); /*Copy the value into the area after the key*/
        next->next = NULL;                                                                                  /*Make sure the next is set to NULL, to indicate that this is the last entry at the position*/
        entry->next = next;                                                                                 /*Set previosly last entry to point at the new entry*/
        return 1;
    }
}

void htDelete(hashTable table, void *key)
{
    hashTableEntry *entry = addPtr(table.data, _htGetOffset(table, _htGetIndex(table, key)));
    if (entry->key == NULL)
        return; /*Empty slot*/
    else
    {
        if (memcmp(entry->key, key, table.keySize) == 0) /*Found it, and it's the head*/
        {
            if (entry->next == NULL)
            {                      /*There are no others*/
                entry->key = NULL; /*Mark it as "not there"*/
                return;
            }
            else
            {
                hashTableEntry *next = entry->next;
                memcpy(entry->key, next->key, table.keySize + table.valueSize); /*override the entry with the next one*/
                entry->next = next->next;
                free(next);
                return;
            }
        }
        else
        {
            while (entry->next != NULL)
            {
                if (memcmp(entry->next->key, key, table.keySize) == 0) /*Found it*/
                {
                    hashTableEntry *next = entry->next;
                    entry->next = next->next;
                    free(next);
                    return;
                }
                else
                {
                    entry = entry->next;
                }
            }
            return; /*It wasn't in the table*/
        }
    }
}

void *htAggregate(hashTable table, void *(*f)(hashTableEntry, hashTableEntry))
{
}

/*Example area*/
void *htAggregateExamplePrint(hashTableEntry prev, hashTableEntry next)
{
    printf("adsasd");
    return NULL;
}

void assignString(char *outString, int outSize, const char *inString)
{
    int i = 0;
    char c = inString[0];
    while (i < outSize && (c != '\0'))
    {
        c = inString[i];
        outString[i++] = c;
    }
    while (i < outSize)
    {
        outString[i++] = c;
    }
}

void htExampleMain()
{
    hashTable table = htInitTable(10, sizeof(char[5]), sizeof(int));

    char key[5];
    int val;

    assignString(key, 5, "oooo");
    val = 3;
    htInsert(table, &key, &val);

    assignString(key, 5, "test");
    val = 6;
    htInsert(table, &key, &val);

    assignString(key, 5, "tet");
    val = 1;
    htInsert(table, &key, &val);

    assignString(key, 5, "asd");
    val = 90;
    htInsert(table, &key, &val);

    assignString(key, 5, "test");
    val = 5;
    htInsert(table, &key, &val);

    assignString(key, 5, "tet");
    // htDelete(table, &key);
}

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
    htExampleMain();
    return -1;

    char fileName[] = "kampe-2020-2021.txt";

    int count = lineCountOfFile(fileName);

    game *games = malloc(count * sizeof(game));
    assert(games != NULL);

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