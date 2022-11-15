#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define clear() printf("\033[H\033[J")

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

void arr2d_free(array2d arr)
{
    for (int i = 0; i < arr.I; i++)
    {
        free(arr.A[i]);
    }
    free(arr.A);
}

void arr2d_print(array2d arr)
{
    int I = arr.I;
    int J = arr.J;
    printf("Printing a 2D Array:\n");

    printf("   ");
    for (int j = 0; j < J; j++)
        printf("%14d", j);
    printf("\n");

    for (int i = 0; i < I; i++)
    {
        printf("%3d", i);
        for (int j = 0; j < J; j++)
        {
            printf("%14.5f", arr.A[i][j]);
        }
        printf("\n");
    }
}

int element_exist(array2d arr, int i, int j)
{
    if (i >= arr.I || i < 0 || j >= arr.J || j < 0)
    {
        // doesnt exist
        return 0;
    }
    // exist
    return 1;
}

void print_cool_element(array2d arr, int i, int j)
{
    if (element_exist(arr, i, j))
    {
        printf("A[%d][%d] = %f\n", i, j, arr.A[i][j]);
    }
}

char *read_line_file(FILE *f)
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

char *read_line()
{
    int cap = 1, len = 0, ch;
    char *str = malloc(cap);
    while (1)
    {
        if (len == cap)
        {
            str = realloc(str, cap *= 2);
            if (str == NULL)
            {
                return NULL;
            }
        }
        ch = getchar();
        if (ch == '\n')
        {
            break;
        }
        str[len++] = ch;
    }
    return str;
}

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

int arr2d_readfile(char *filename, array2d *arr)
{
    // Open file
    FILE *fptr;
    if ((fptr = fopen("matrix.csv", "rb")) == NULL)
    {
        printf("Error! opening file");

        return 1;
    }

    char *s;
    // Count Cols
    s = read_line_file(fptr);
    char *char_str_ptr = s;
    char *str_ptr;
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

    int lines_allocated = 1;
    arr->A = (double **)malloc(lines_allocated * sizeof(double *));
    arr->I = 0;
    arr->J = counter;

    for (int i = 0; i < lines_allocated; i++)
    {
        arr->A[i] = (double *)malloc(arr->J * sizeof(double));
    }

    // lines to arr
    do
    {
        if (arr->I == lines_allocated)
        {
            printf("Realloc\n");
            int bgn = lines_allocated;
            lines_allocated = lines_allocated * 2;
            arr->A = realloc(arr->A, lines_allocated * sizeof(double *));

            for (int il = bgn; il < lines_allocated; il++)
            {
                arr->A[il] = (double *)malloc(arr->J * sizeof(double));
            }
        }

        linetoarr(s, arr->A[arr->I], arr->J);

        arr->I = arr->I + 1;

        free(s);
    } while (s = read_line_file(fptr));
    //free(s);
    fclose(fptr);

    for (int il = arr->I; il < lines_allocated; il++)
    {
        free(arr->A[il]);
    }

    arr->A = realloc(arr->A, arr->I * sizeof(double *));
    return 0;
}

int string_to_int(char *str ,int *target)
{
    int len = strlen(str);
    //printf("Len = %d\n", len);
    if (len == 0) //Line empty
    {
        //printf("Line empty\n");
        return 1;
    }
    int number = 0;

    int bgn = 0;
    switch (str[0]) // Sign check
    {
    case '-':
        bgn = 1;
        break;
    default:
        break;
    }

    if (bgn == 1 && len == 1)
    {
        //printf("Single char\n");
        return 4; // Single char
    }
    
    for (int i = bgn; i < len; i++)
    {
        switch (str[i])
        {
        case '0':
            number = number * 10;
            break;
        case '1':
            number = number * 10 + 1;
            break;
        case '2':
            number = number * 10 + 2;
            break;
        case '3':
            number = number * 10 + 3;
            break;
        case '4':
            number = number * 10 + 4;
            break;
        case '5':
            number = number * 10 + 5;
            break;
        case '6':
            number = number * 10 + 6;
            break;
        case '7':
            number = number * 10 + 7;
            break;
        case '8':
            number = number * 10 + 8;
            break;
        case '9':
            number = number * 10 + 9;
            break;
        default:
            //printf("Unexpected symbol %c\n", str[i]);
            return 3; //Unexpected symbol
            break;
        }
    }
    
    if (bgn == 1)
    {
        number = -number;
    }

    *target = number;
    return 0;
}

int get_int_limitations(int *target, int min, int max, char *text)
{
    *target = max + 1;
    char *str;
    // int result;
    do
    {

        printf("%s [%d:%d]\n>", text, min, max);
        str = read_line();
        string_to_int(str, target);
        //*target = strtiumax(str, NULL, 10);
        //*target = atoi(str);
        // result = scanf("%d", target);
        free(str);
    } while (*target < min || *target > max);
    //free(str);
    return 0;
}

double rectangle_formula(array2d arr, int i, int j, int x, int y)
{
    return (arr.A[i][j] * arr.A[x][y] - arr.A[i][y] * arr.A[x][j]) / arr.A[x][y];
}

void rectangle(array2d arr, int x, int y)
{
    // L square
    for (int j = 0; j < y; j++)
    {
        if (arr.A[x][j] != 0)
        {
            // U square
            for (int i = 0; i < x; i++)
            {
                arr.A[i][j] = rectangle_formula(arr, i, j, x, y);
            }
            // D square
            for (int i = x + 1; i < arr.I; i++)
            {
                arr.A[i][j] = rectangle_formula(arr, i, j, x, y);
            }
            arr.A[x][j] = arr.A[x][j] / arr.A[x][y];
        }
    }

    // R square
    for (int j = y + 1; j < arr.J; j++)
    {
        if (arr.A[x][j] != 0)
        {
            // U square
            for (int i = 0; i < x; i++)
            {
                arr.A[i][j] = rectangle_formula(arr, i, j, x, y);
            }
            // D square
            for (int i = x + 1; i < arr.I; i++)
            {
                arr.A[i][j] = rectangle_formula(arr, i, j, x, y);
            }
            arr.A[x][j] = arr.A[x][j] / arr.A[x][y];
        }
    }

    // Cross
    for (int i = 0; i < x; i++)
    {
        arr.A[i][y] = 0;
    }
    for (int i = x + 1; i < arr.I; i++)
    {
        arr.A[i][y] = 0;
    }
    arr.A[x][y] = 1;
}

int main()
{
    array2d arr;
    arr2d_readfile("matrix.csv", &arr);
    int c;

    do
    {
        clear();
        arr2d_print(arr);
        get_int_limitations(&c, 0, 1, "1-rect 0-exit\n");

        switch (c)
        {

        case 1:
        {
            // arr2d_print(arr);
            int i;
            get_int_limitations(&i, 0, arr.I - 1, "Enter i");

            int j;
            get_int_limitations(&j, 0, arr.J - 1, "Enter j");
            print_cool_element(arr, i, j);

            rectangle(arr, i, j);

            break;
        }

        case 0:
        {
            printf("Press any key...");
        }
        default:
            break;
        }

        getchar();
    } while (c);

    arr2d_free(arr);
    return 0;
}
