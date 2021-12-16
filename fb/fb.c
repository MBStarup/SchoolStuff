/*Magnus B. Starup; Datalogi; mstaru21@student.aau.dk; Fodbold; 16/12/2021*/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
Main can be found at the bottom of the file. :)
*/

/*SECTION ht.h*/
/*
Adds bytes amount of bytes to pointer
*/
void *addPtr(const void *pointer, int bytes)
{
    return (((char *)pointer) + bytes);
}

/*
The struct representing a hashtable
This struct does not actually contain the data of the hashtable, only the metadate about the hashtable and a reference to the actual data

void* data: the reference to the data, this will be dynamically allocated in htInit()
int tableSize: The amount of first order entries in the table, this
*/
typedef struct hashTable
{
    const void *data;
    const int tableSize;
    const int keySize;
    const int valueSize;
    int count;
} hashTable;

typedef struct hashTableEntry
{
    void *key;
    void *value;
    struct hashTableEntry *next;
} hashTableEntry;

static unsigned int _htHashFunc(void *key, int size)
{
    /*quite probably bad hashing function*/
    /*TODO: Implement a real one*/
    unsigned int res = 0;
    for (size_t i = 0; i < size; i++)
    {
        res += (unsigned int)*(char *)(addPtr(key, i));
    }
    return res;
}

/*Returns the "index" for a given key*/
static unsigned int _htGetIndex(const hashTable *table, void *key)
{
    return _htHashFunc(key, table->keySize) % table->tableSize;
}

/*Returns the byte offset to get to a specific index*/
static int _htGetOffset(const hashTable *table, int index)
{
    return index * ((sizeof(hashTableEntry) + table->keySize + table->valueSize));
}

/*
Initializes the hashtable
Remember to clean up with htDeleteTable() when you're done, as the data is dynamically allocated
*/
hashTable htInitTable(int tableSize, int keySize, int valueSize)
{
    void *ptr = malloc(tableSize * (sizeof(hashTableEntry) + keySize + valueSize)); /*Allocate the initial chunk of memory*/
    assert(ptr != NULL);
    hashTable table = {.data = ptr, .tableSize = tableSize, .keySize = keySize, .valueSize = valueSize, .count = 0};

    for (size_t i = 0; i < table.tableSize; i++)
    {
        hashTableEntry *entry = addPtr(table.data, i * (sizeof(hashTableEntry) + keySize + valueSize));
        entry->key = NULL;
        entry->next = NULL;
    }

    return table;
}

/*
Frees up the memory used by the hashtable
Never use the hashtable after this function
The count is set to -1
*/
void htDeleteTable(hashTable table)
{
    for (size_t i = 0; i < table.tableSize; i++)
    {
        hashTableEntry *entry = addPtr(table.data, _htGetOffset(&table, i));
        hashTableEntry *next = entry->next;
        while (next != NULL)
        {
            hashTableEntry *temp = next;
            next = next->next;
            free(temp);
        }
    }

    free(table.data);
    table.count = -1;
}

/*
Returns a pointer to the value at the given key in the given hashtable, or NULL if no suitable key was found
*/
void *htGet(const hashTable *table, void *key)
{
    hashTableEntry *entry = addPtr(table->data, _htGetOffset(table, _htGetIndex(table, key)));
    if (entry->key == NULL)
        return NULL; /*Key not in table*/
    else
    {
        hashTableEntry *next = NULL;
        do
        {
            if (memcmp(entry->key, key, table->keySize) == 0) /*Found it*/
            {
                return entry->value;
            }
            next = entry->next;
        } while (next != NULL && (entry = next) /*Funky code: only assign entry to next if next is not NULL*/);

        return NULL; /*Didn't find it in the chain*/
    }
}

/*
Inserts an value in the hashtable
If an value already exists at teh given key, it will be replaced

returns 1 for success and 0 for faliure
*/
int htInsert(hashTable *table, void *key, void *value)
{
    hashTableEntry *entry = addPtr(table->data, _htGetOffset(table, _htGetIndex(table, key)));
    if (entry->key == NULL) /*Empty slot*/
    {
        entry->key = memcpy(addPtr(entry, sizeof(hashTableEntry)), key, table->keySize);                        /*Copy the key into the area after the entry*/
        entry->value = memcpy(addPtr(entry, sizeof(hashTableEntry) + table->keySize), value, table->valueSize); /*Copy the value into the area after the key*/
        entry->next = NULL;                                                                                     /*Make sure the next is set to NULL, to indicate that this is the last entry at the position*/
        table->count += 1;
        return 1;
    }
    else
    {
        hashTableEntry *next = NULL;
        do
        {
            if (memcmp(entry->key, key, table->keySize) == 0) /*Already existing entry*/
            {
                memcpy(entry->value, value, table->valueSize); /*overide the value with the new value*/
                return 1;
            }
            next = entry->next;
        } while (next != NULL && (entry = next) /*Funky code: only assign entry to next if next is not NULL*/);

        next = malloc(sizeof(hashTableEntry) + table->keySize + table->valueSize);
        if (next == NULL)
            return 0;                                                                                         /*Failed to allocate memory for the new entry*/
        next->key = memcpy(addPtr(next, sizeof(hashTableEntry)), key, table->keySize);                        /*Copy the key into the area after the entry*/
        next->value = memcpy(addPtr(next, sizeof(hashTableEntry) + table->keySize), value, table->valueSize); /*Copy the value into the area after the key*/
        next->next = NULL;                                                                                    /*Make sure the next is set to NULL, to indicate that this is the last entry at the position*/
        entry->next = next;                                                                                   /*Set previosly last entry to point at the new entry*/
        table->count += 1;
        return 1;
    }
}

/*
Deletes a given entry from the hashtable
*/
void htDelete(hashTable *table, void *key)
{
    hashTableEntry *entry = addPtr(table->data, _htGetOffset(table, _htGetIndex(table, key)));
    if (entry->key == NULL)
        return; /*Empty slot*/
    else
    {
        if (memcmp(entry->key, key, table->keySize) == 0) /*Found it, and it's the head*/
        {
            if (entry->next == NULL)
            {                      /*There are no others*/
                entry->key = NULL; /*Mark it as "not there"*/
                return;
            }
            else
            {
                hashTableEntry *next = entry->next;
                memcpy(entry->key, next->key, table->keySize + table->valueSize); /*override the entry with the next one*/
                entry->next = next->next;
                free(next);
                table->count -= 1;
                return;
            }
        }
        else
        {
            while (entry->next != NULL)
            {
                if (memcmp(entry->next->key, key, table->keySize) == 0) /*Found it*/
                {
                    hashTableEntry *next = entry->next;
                    entry->next = next->next;
                    free(next);
                    table->count -= 1;
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

/*
Works kinda like strtok
Provide it with a hashtable to get the first entry in that table
Provide it with NULL to get the next entry in the last provided hashtable
Returns NULL when there are no more entries in the hashtable

please only read the data, don't start changing it with this function, use the appropriate fuctions for that (htInsert, htDelete)
*/
hashTableEntry *htEnumerate(const hashTable *table)
{
    static int i = 0;
    static int lastChainDepth = -1;
    static hashTable *lastTablePtr = NULL;

    if (table != NULL)
    {
        i = 0;
        lastChainDepth = -1;
        lastTablePtr = table;
    }

    if (lastTablePtr == NULL)
        return NULL;

    hashTable lastTable = *lastTablePtr;
    if (i < lastTable.tableSize)
    {
        hashTableEntry *entry = addPtr(lastTable.data, _htGetOffset(&lastTable, i));

        while (entry->key == NULL) /*Move to the next non empty slot in the table*/
        {
            ++i;
            if (i < lastTable.tableSize)
                entry = addPtr(lastTable.data, _htGetOffset(&lastTable, i));
            else
                return NULL;
        }

        int currentChainDepth = -1;

        while (entry->next != NULL && currentChainDepth < lastChainDepth) /*Move to the last returned chain link*/
        {
            entry = entry->next;
            ++currentChainDepth;
        }
        if (entry->next != NULL) /*Return next link in chain*/
        {
            lastChainDepth += 1;
            return entry;
        }
        else /*We've reached the end of the chain*/
        {
            ++i;
            lastChainDepth = -1;
            return entry;
        }
    }
    else
    {
        return NULL;
    }
}

/*END_SECTION ht.h*/

/* PROGRAM START */
#define _BUFFER_SIZE 1024
#define WEEKDAY_SIZE 3
#define TEAMNAME_SIZE 3
#define WINNER_POINTS 3
#define STALEMATE_POINTS 1
#define PRINT_WIDTH 9
#define _TO_STRING(v) #v
#define TO_STRING(v) _TO_STRING(v)

typedef struct team
{
    char teamName[TEAMNAME_SIZE + 1];
    int points;
    int goals;
    int goalsAgainst;

} team;

typedef struct game
{
    char weekDay[WEEKDAY_SIZE + 1];
    int day;
    int month;
    int hour;
    int minute;
    char firstTeamName[TEAMNAME_SIZE + 1];
    char secondTeamName[TEAMNAME_SIZE + 1];
    int firstTeamScore;
    int secondTeamScore;
    int viewers;
} game;

/*
Initializes a string of size count, to be all '\0'
*/
void initString(char *out, int count)
{
    for (size_t i = 0; i < count; i++)
    {
        out[i] = '\0';
    }
}

/*
Prints an array of strings
*/
void printArr(char **arr, int count)
{
    for (size_t i = 0; i < count; i++)
    {
        printf("%5d: %s\n", i, arr[i]);
    }
}

/*
Counts the amount of lines in a text file
*/
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

/*
Parses a string into a game, following the specific format of the file given by the problem
*/
void parseLine(game *outGame, const char *line)
{
    initString(outGame->firstTeamName, TEAMNAME_SIZE + 1);
    initString(outGame->secondTeamName, TEAMNAME_SIZE + 1);
    initString(outGame->weekDay, WEEKDAY_SIZE + 1);
    sscanf(line, " %" TO_STRING(WEEKDAY_SIZE) "s %2d/%2d %2d.%2d %" TO_STRING(TEAMNAME_SIZE) "s - %" TO_STRING(TEAMNAME_SIZE) "s %d - %d %d", outGame->weekDay, &outGame->month, &outGame->day, &outGame->hour, &outGame->minute, outGame->firstTeamName, outGame->secondTeamName, &outGame->firstTeamScore, &outGame->secondTeamScore, &outGame->viewers);
}

/*
Prints a game to the standard out with nice formatting
*/
void printGame(game game)
{
    printf(" %*.*s %2.2d/%2.2d %2.2d.%2.2d %*.*s - %*.*s %d - %d %d\n", WEEKDAY_SIZE, WEEKDAY_SIZE, game.weekDay, game.month, game.month, game.hour, game.minute, TEAMNAME_SIZE, TEAMNAME_SIZE, game.firstTeamName, TEAMNAME_SIZE, TEAMNAME_SIZE, game.secondTeamName, game.firstTeamScore, game.secondTeamScore, game.viewers);
}

/*
Prints a team to the standard out with foratting as part of a table
*/
void printTeamLine(team t)
{
    printf("%*.*s | %-*d || %*d | %-*d\n", PRINT_WIDTH, PRINT_WIDTH, t.teamName, PRINT_WIDTH, t.points, PRINT_WIDTH, t.goals, PRINT_WIDTH, t.goalsAgainst);
}

/*
A wrapper aroung htGet() that intializes the team and converts the output for me
*/
team my_htGet(hashTable table, char teamName[TEAMNAME_SIZE + 1])
{
    team res = {.points = 0, .goals = 0, .goalsAgainst = 0};

    initString(res.teamName, TEAMNAME_SIZE + 1);
    memcpy(res.teamName, teamName, strlen(teamName));

    void *temp = htGet(&table, teamName);
    if (temp != NULL)
    {
        res = *((team *)temp);
    }

    return res;
}

/*
A comparing function to use when sorting teams
*/
int compareTeams(const void *a, const void *b)
{
    team teamA = *(team *)a;
    team teamB = *(team *)b;

    if (teamA.points > teamB.points)
        return -1;
    else if (teamA.points < teamB.points)
        return 1;
    else
    {
        if ((teamA.goals - teamA.goalsAgainst) > (teamB.goals - teamB.goalsAgainst))
            return -1;
        else if ((teamA.goals - teamA.goalsAgainst) < (teamB.goals - teamB.goalsAgainst))
            return 1;
        else
            return 0;
    }
}

int main(void)
{
    char fileName[] = "kampe-2020-2021.txt";

    int count = lineCountOfFile(fileName);

    game *games = malloc(count * sizeof(game));
    assert(games != NULL);

    { /*Read and parse each line*/
        FILE *inputFile = fopen(fileName, "r");
        assert(inputFile != NULL);

        char inputLine[_BUFFER_SIZE];
        for (size_t i = 0; i < count; i++)
        {
            fgets(inputLine, _BUFFER_SIZE, inputFile);
            parseLine(&games[i], inputLine);
        }
        fclose(inputFile);
    }

    /*Calculate scores*/
    hashTable table = htInitTable(25, sizeof(char) * (TEAMNAME_SIZE + 1), sizeof(team));
    for (size_t i = 0; i < count; i++)
    {
        team first = my_htGet(table, games[i].firstTeamName);
        team second = my_htGet(table, games[i].secondTeamName);

        first.goals += games[i].firstTeamScore;
        first.goalsAgainst += games[i].secondTeamScore;

        second.goals += games[i].secondTeamScore;
        second.goalsAgainst += games[i].firstTeamScore;

        if (games[i].firstTeamScore > games[i].secondTeamScore)
        {
            first.points += WINNER_POINTS;
        }
        else if (games[i].firstTeamScore < games[i].secondTeamScore)
        {
            second.points += WINNER_POINTS;
        }
        else
        {
            first.points += STALEMATE_POINTS;
            second.points += STALEMATE_POINTS;
        }

        assert(htInsert(&table, first.teamName, &first) == 1);
        assert(htInsert(&table, second.teamName, &second) == 1);
    }

    /*Sort scores*/
    /*Hastable => array*/
    team *teamArr = malloc(sizeof(team) * table.count);
    assert(teamArr != NULL);
    {
        hashTableEntry *e = htEnumerate(&table);
        int i = 0;
        while (e != NULL)
        {
            memcpy(&teamArr[i++], e->value, sizeof(team));
            e = htEnumerate(NULL);
        }
    }
    htDeleteTable(table);

    qsort(teamArr, table.count, sizeof(team), compareTeams);

    /*Print result table*/
    printf("%*.*s | %-*.*s || %*.*s | %-*.*s\n", PRINT_WIDTH, PRINT_WIDTH, "Name", PRINT_WIDTH, PRINT_WIDTH, "Points", PRINT_WIDTH, PRINT_WIDTH, "Goals", PRINT_WIDTH, PRINT_WIDTH, "GoalsVs");
    printf("%*.*s=|=%*.*s====%*.*s=|=%*.*s\n", PRINT_WIDTH, PRINT_WIDTH, "==============", PRINT_WIDTH, PRINT_WIDTH, "==============", PRINT_WIDTH, PRINT_WIDTH, "==============", PRINT_WIDTH, PRINT_WIDTH, "==============");
    for (size_t i = 0; i < table.count; i++)
    {
        printTeamLine(teamArr[i]);
    }
}