/*Magnus B. Starup; Datalogi; mstaru21@student.aau.dk; palindrome*; 09/11/2021*/
#include <stdio.h>

int stringLength(const char *str)
{
    int l = 0;

    while (str[l++] != '\0')
    {
    }

    return l;
}

int is_palindrome_iter(const char *str)
{
    int l = stringLength(str);

    for (size_t i = 0; i < (l / 2); i++)
    {
        if (str[i] != str[(l - 2) - i])
        {
            return 0;
        }
    }

    return 1;
}

int _is_palindrome_rec(const char *str, int size)
{
    if (size < 2)
    {
        return 1;
    }

    if (str[0] != str[size - 2])
    {
        return 0;
    }

    return _is_palindrome_rec(str + 1, size - 2);
}

int is_palindrome_rec(const char *str)
{
    int l = stringLength(str);

    return _is_palindrome_rec(str, l);
}

int main()
{
    char *string[] = {
        "test",
        "paap",
        "pap",
        "regninger",
        "",
    };

    for (size_t i = 0; i < (sizeof(string) / sizeof(string[0])); i++)
    {
        printf("\nis \"%s\" a palindrome?\n", string[i]);
        printf("iter: %s | rec: %s\n\n", is_palindrome_iter(string[i]) == 0 ? "no" : "yes", is_palindrome_rec(string[i]) == 0 ? "no" : "yes");
    }
}