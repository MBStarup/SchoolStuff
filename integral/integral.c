/*Magnus B. Starup; Datalogi; mstaru21@student.aau.dk; Area under curve via trapeziods; 31/09/2021*/
#include <stdio.h>
#include <assert.h>

typedef double (*mathFunc)(double);
typedef double (*convertFunc)(int);

/* sum returns the sum of f( iToXi( i ) ) for all intergers i from m to n */
double sum(int m, int n, mathFunc f, convertFunc iToXi)
{
    double acc = 0;
    for (size_t i = m; i <= n; i++)
    {
        acc += f(iToXi(i));
    }
    return acc;
}

double trap(double a, double b, int n, mathFunc f)
{
    assert(n > 0);
    double h = (b - a) / n;

    double iToXi(int i) { return a + i * h; } // A function to convert our summations i value into the corresponding xᵢ value

    return (h * (f(a) + f(b) + 2 * sum(1, n - 1, f, &iToXi))) / 2;
}

// Testing code
#ifndef COMP_AS_LIB
#include <math.h>
double g(double x)
{
    return x * x * sin(x);
}

double h(double x)
{
    return sqrt(4 - (x * x));
}

int main(int argc, char const *argv[])
{
    printf("Area under g(x) = x²sinx from x = 0 to x = π\n");
    for (size_t i = 2; i <= 128; i *= 2)
    {
        printf("n= %10d | T= %10lf\n", i, trap(0.0, M_PI, i, &g));
    }

    printf("\nArea under h(x) = √(4-x²) from x = -2 to x = 2\n");
    for (size_t i = 2; i <= 128; i *= 2)
    {
        printf("n= %10d | T= %10lf\n", i, trap(-2, 2, i, &h));
    }

    return 0;
}
#endif
