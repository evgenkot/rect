#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringproc.h"
#include "arr.h"
#include "arr2d.h"


#define clear() printf("\033[H\033[J")


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

