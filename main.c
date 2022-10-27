#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int I;
    int J;
    double **A;
} array2d;

array2d arr2d_create(int I, int J)
{

    double **A = (double **)malloc(I * sizeof(double *));
    for (int i = 0; i < I; i++)
    {
        A[i] = (double *)malloc(J * sizeof(double));
    }
    array2d arr = {I, J, A};
    return arr;
}

void arr2d_print(array2d arr)
{
    int I = arr.I;
    int J = arr.J;
    printf("Printing a 2D Array:\n");
    for (int i = 0; i < I; i++)
    {
        for (int j = 0; j < J; j++)
        {
            printf("%f ", arr.A[i][j]);
        }
        printf("\n");
    }
}

char *read_line(FILE *f)
{
    int cap = 32, next = 0, c;
    char *p = malloc(cap);
    while (1)
    {
        if (next == cap)
        {
            p = realloc(p, cap *= 2);
        }
        c = fgetc(f);
        if (c == EOF || c == '\n')
        {
            p[next++] = 0;
            break;
        }
        p[next++] = c;
    }
    if (c == EOF && next == 1)
    {
        free(p);
        p = NULL;
    }

    return p;
}

array2d arr2d_readfile(char *filename)
{
    FILE *fptr;

    if ((fptr = fopen("matrix.csv", "rb")) == NULL)
    {
        printf("Error! opening file");

        exit(1);
    }

    char *s;
    // s = read_line(fptr);

    while (s = read_line(fptr))
    {
        printf("%s\n", s);
        free(s);
    }

    fclose(fptr);

    return;
}

int main()
{
    // arr2d_readfile("matrix.csv");
    //  array2d arr = arr2d_create(4, 5);

    // for (int i = 0; i < arr.I; i++)
    // {
    //     for (int j = 0; j < arr.J; j++)
    //     {
    //         arr.A[i][j] = i + j;
    //     }
    // }
    // arr2d_print(arr);

    return 0;
}
