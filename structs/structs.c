#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct
{
    unsigned int numerator;
    unsigned int denominator;
} Fraction;

unsigned int gcd(unsigned int large, unsigned int small);
Fraction shortenFraction(Fraction fraction);
void printFraction(Fraction f);
Fraction multiplyFractionWithNumber(Fraction f, unsigned int scalar);
Fraction multiplyFractionWithFraction(Fraction a, Fraction b);
Fraction addFractionWithFraction(Fraction a, Fraction b);

int main()
{
    Fraction f, f_in;
    int in;

    printf("Enter fraction: ");
    scanf(" %u/%u", &f.numerator, &f.denominator);
    printFraction(f);
    f = shortenFraction(f);
    printFraction(f);

    printf("Multiply with (number): ");
    scanf(" %u", &in);
    f = multiplyFractionWithNumber(f, in);
    printFraction(f);

    printf("Multiply with (fraction): ");
    scanf(" %u/%u", &f_in.numerator, &f_in.denominator);
    f = multiplyFractionWithFraction(f, f_in);
    printFraction(f);

    printf("Add with (fraction): ");
    scanf(" %u/%u", &f_in.numerator, &f_in.denominator);
    f = addFractionWithFraction(f, f_in);
    printFraction(f);

    return EXIT_SUCCESS;
}

Fraction shortenFraction(Fraction fraction)
{
    unsigned int small,
        large,
        a;

    large = fraction.numerator > fraction.denominator ? fraction.numerator : fraction.denominator;
    small = fraction.numerator > fraction.denominator ? fraction.denominator : fraction.numerator;

    a = gcd(large, small);
    fraction.numerator = fraction.numerator / a;
    fraction.denominator = fraction.denominator / a;

    return fraction;
}

unsigned int gcd(unsigned int large, unsigned int small)
{
    unsigned int remainder;
    while (small > 0)
    {
        remainder = large % small;
        large = small;
        small = remainder;
    }
    return large;
}

void printFraction(Fraction f)
{
    printf("Fraction: %u / %u\n", (f.numerator), (f.denominator));
}

Fraction multiplyFractionWithNumber(Fraction f, unsigned int scalar)
{
    f.numerator *= scalar;
    return shortenFraction(f);
}

Fraction multiplyFractionWithFraction(Fraction a, Fraction b)
{
    int temp = a.denominator;

    a.numerator *= b.numerator;
    a.denominator *= b.denominator;
    return shortenFraction(a);
}

Fraction addFractionWithFraction(Fraction a, Fraction b)
{
    int temp = a.denominator;

    a.numerator *= b.denominator;
    a.denominator *= b.denominator;

    b.numerator *= temp;

    a.numerator += b.numerator;
    return shortenFraction(a);
}