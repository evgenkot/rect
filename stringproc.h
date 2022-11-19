#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    str[len] = '\0';
    return str;
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