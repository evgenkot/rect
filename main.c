#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void linetoarr(char *s, double *arr, int J)
{
    char *char_str_ptr = s;
    char *str_ptr;
    double num;

    for (int j = 0; j < J; j++)
    {
        num = strtod(char_str_ptr, &str_ptr);
        //printf("%f", num);
        char_str_ptr = str_ptr + 1;
        arr[j] = num;
    }
}

int arr2d_readfile(char *filename, array2d *arr)
{
    int lines_allocated = 1;
    arr->A = (double **)malloc(lines_allocated * sizeof(double *));
    arr->I = lines_allocated;

    FILE *fptr;
    if ((fptr = fopen("matrix.csv", "rb")) == NULL)
    {
        printf("Error! opening file");

        return 1;
    }

    char *s;
    s = read_line(fptr);

    char *char_str_ptr = s;
    char *str_ptr;
    // Cols counter

    int counter = 0;

    while (1)
    {
        counter++;
        strtod(char_str_ptr, &str_ptr);
        arr->J = arr->J + 1;
        if (*str_ptr == ',')
        {
            char_str_ptr = str_ptr + 1;
        }
        else
        {
            break;
        }
    }
    arr->J = counter;

    int i = 0;

    // linetoarr(s, arr->A[i], arr->J);
    arr->A[0] = (double *)malloc(arr->J * sizeof(double));

    do
    {
        if (i == lines_allocated)
        {
            int bgn = lines_allocated - 1;
            lines_allocated = lines_allocated * 2;
            arr->A = realloc(arr->A, lines_allocated * sizeof(double *));
            // for (int il = 0; il < bgn; il++)
            // {
            //     arr->A[il] = realloc(arr->A[il],arr->J * sizeof(double));
            // }
            for (int il = bgn; il < lines_allocated; il++)
            {
                arr->A[il] = (double *)malloc(arr->J * sizeof(double));
            }
        }

        linetoarr(s, arr->A[i], arr->J);
        i++;

        arr->I = i;
        //printf("%s\n", s);
        free(s);
    } while (s = read_line(fptr));
    fclose(fptr);

    return 0;
}

int main()
{

    array2d arr;
    arr2d_readfile("matrix.csv", &arr);
    //  array2d arr = arr2d_create(4, 5);

    // for (int i = 0; i < arr.I; i++)
    // {
    //     for (int j = 0; j < arr.J; j++)
    //     {
    //         arr.A[i][j] = i + j;
    //     }
    // }
    arr2d_print(arr);

    return 0;
}
