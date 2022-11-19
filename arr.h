#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void linetoarr(char *s, double *arr, int J)
{
    char *char_str_ptr = s;
    char *str_ptr;
    double num;

    for (int j = 0; j < J; j++)
    {
        num = strtod(char_str_ptr, &str_ptr);
        char_str_ptr = str_ptr + 1;
        arr[j] = num;
    }
}

