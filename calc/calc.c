/*Magnus B. Starup; Datalogi; mstaru21@student.aau.dk; Calculator; 25/09/2021*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// please imagine everything between "BEGIN INCLUDE calc.c" and "END INCLUDE calc.c" was included from another file
/*BEGIN INCLUDE calc.c*/
#define CALC_QUIT_OPERAND 'q'
#define CALC_HELP_OPERAND 'h'
#define CALC_MAX_OPERANDS 100 // completely arbitrary amount, don't know what to base it on

#ifdef CALC_DEBUG
#define PRINT_DEBUG(...) \
    printf("    ");      \
    printf(__VA_ARGS__)
#endif
#ifndef CALC_DEBUG
#define PRINT_DEBUG(...)
#endif

// Operation struct definition
typedef struct operation
{
    int operands_n;
    char operator;
    double (*operation)(double *);
    char *descrition;
} operation;

// Calculator function declarations
const operation *scan_data(const operation *operations, int operation_n);
const operation *getOperation(char operator, const operation * operations, int operation_n);
void help(const operation *operations, int operation_n);
void clearInputBuffer();
double runCalculator(const operation *operations, int operation_n);

const operation *getOperation(char operator, const operation * operations, int operation_n)
{
    for (size_t i = 0; i < operation_n; i++)
    {
        if ((*(operations + i)).operator== operator)
            return operations + i;
    }
    return NULL;
}

void help(const operation *operations, int operation_n)
{
    printf("Use any of the followng characters, and press enter\n");
    printf("    %c | %s\n", CALC_QUIT_OPERAND, "Quit the calculator");
    printf("    %c | %s\n", CALC_HELP_OPERAND, "Display this help page");
    for (size_t i = 0; i < operation_n; i++)
    {
        printf("    %c | %s\n", operations[i].operator, operations[i].descrition);
    }
}

// Will "break" (pause and wait for enter) if run with an empty stdin, so don't run twice in a row
// TODO: figure out good way to fix this
void clearInputBuffer()
{
    PRINT_DEBUG("Running %s...\n", __func__);
    char c;
    do
    {
        c = getchar();
        PRINT_DEBUG((c == '\n' ? ("Cleared: NewLine\n") : ("Cleared: %c\n")), c);
    } while (c != '\n');
    return;
}

double runCalculator(const operation *operations, int operation_n)
{
    // TODO: Add history
    // TODO: Assert that noone uses the CALC_QUIT_OPERATOR or CALC_HELP_OPERATOR, as that would make the operation unreachable
    double acc = 0;
    char in_operator;
    double in_operands[CALC_MAX_OPERANDS];

    help(operations, operation_n);
    printf("\nStarting result: %f\n", acc);
    while (1)
    {
        in_operator = ' ';
        PRINT_DEBUG("Getting input\n");
        scanf(" %c", &in_operator);
        if (in_operator == CALC_QUIT_OPERAND) // special handling cuz we have to exit
        {
            return acc;
        }
        else if (in_operator == CALC_HELP_OPERAND)
        { // special handling cuz it needs the operation list
            help(operations, operation_n);
        }
        else
        {

            const operation *op_ptr = getOperation(in_operator, operations, operation_n);

            if (op_ptr != NULL)
            {
                PRINT_DEBUG("Operation found\n");
                operation op = *op_ptr;
                in_operands[0] = acc;
                int i = 1;
                // TODO: Assert that the operands_n isn't larger than max operands (maybe do this earliere when loading the operations?)
                while (i < op.operands_n && i < CALC_MAX_OPERANDS)
                {
                    PRINT_DEBUG("Looking for %d operand(s)\n", op.operands_n - i);
                    if (scanf(" %lf", &in_operands[i]) != 0)
                    {
                        PRINT_DEBUG("Operand found\n");
                        ++i;
                    }
                    else
                    {
                        clearInputBuffer();
                    }
                }

                PRINT_DEBUG("Operator: %c \n", in_operator);
                PRINT_DEBUG("Values:");
#ifdef CALC_DEBUG
                for (size_t i = 0; i < op.operands_n; i++)
                {
                    printf(" %f,", in_operands[i]);
                }
#endif
                PRINT_DEBUG("\b\n");

                PRINT_DEBUG("Calling operation\n");
                acc = (op.operation)(in_operands);
                PRINT_DEBUG("Returned form operation, acc is %f\n", acc);
                printf("\nResult: %f\n", acc);
            }
        }
        clearInputBuffer();
    }
}
/*END INCLUDE calc.c*/

// Operation declarations
double add(double *a);
double subtract(double *a);
double multiply(double *a);
double divide(double *a);
double power(double *a);
double squareRoot(double *a);
double negate(double *a);
double reciprocate(double *a);
double test(double *a);

// Program
int main()
{
    operation operations[] = {
        {.operands_n = 2, .operator= '+', .operation = &add, .descrition = "Add a number to your current result"},
        {.operands_n = 2, .operator= '-', .operation = &subtract, .descrition = "Subtract a number from your current result"},
        {.operands_n = 2, .operator= '*', .operation = &multiply, .descrition = "Multiply your current result by a number"},
        {.operands_n = 2, .operator= '/', .operation = &divide, .descrition = "Divide your current result by a number"},
        {.operands_n = 2, .operator= '^', .operation = &power, .descrition = "Raise your current result a power"},
        {.operands_n = 1, .operator= '#', .operation = &squareRoot, .descrition = "Take the square root of your current result"},
        {.operands_n = 1, .operator= '!', .operation = &negate, .descrition = "Negate your current result"},
        {.operands_n = 1, .operator= '%', .operation = &reciprocate, .descrition = "Take the reciprocate of your current result"},
        {.operands_n = 4, .operator= 't', .operation = &test, .descrition = "Print your current result and 3 numbers (don't use)"},
    };

    printf("Final result: %f\n", runCalculator(operations, (sizeof(operations) / sizeof(operation))));
}

// Operation definitions
double add(double *a)
{
    PRINT_DEBUG("Running %s...\n", __func__);
    return *a + *(a + 1);
}

double subtract(double *a)
{
    PRINT_DEBUG("Running %s...\n", __func__);
    return *a - *(a + 1);
}

double multiply(double *a)
{
    PRINT_DEBUG("Running %s...\n", __func__);
    return *a * *(a + 1);
}

double divide(double *a)
{
    PRINT_DEBUG("Running %s...\n", __func__);
    if (*(a + 1) == 0)
        return *a;
    else
        return *a / *(a + 1);
}

double power(double *a)
{
    PRINT_DEBUG("Running %s...\n", __func__);
    return pow(*a, *(a + 1));
}

double squareRoot(double *a)
{
    PRINT_DEBUG("Running %s...\n", __func__);
    if (*a < 0)
    {
        return *a;
    }
    else
    {
        return sqrt(*a);
    }
}

double negate(double *a)
{
    PRINT_DEBUG("Running %s...\n", __func__);
    return *a * -1;
}

double reciprocate(double *a)
{
    PRINT_DEBUG("Running %s...\n", __func__);
    if (*a == 0)
        return *a;
    else
        return 1 / *a;
}

double test(double *a)
{
    PRINT_DEBUG("Running %s...\n", __func__);
    printf("test: %f, %f, %f, %f\n", *a, *(a + 1), *(a + 2), *(a + 3));
    return *a;
}
