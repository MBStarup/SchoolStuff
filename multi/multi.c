#include <stdio.h>
#include <stdlib.h>

double multi_apply(double (*f)(double), int n, double s);
double f(double in);

int main(void)
{
    printf("%f\n", multi_apply(&f, 7, 16.0));

    return 0;
}

double f(double in)
{
    return in / 2;
}

double multi_apply(double (*f)(double), int n, double s)
{
    double temp = s;
    for (size_t i = 0; i < n; i++)
    {
        temp = (*f)(temp);
    }
    return temp;
}