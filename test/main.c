#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    

    char * str = "13123.124,123.123,145.5";
    
    char *char_str_ptr = str;
    char *str_ptr;
    
    int J = 0;

    while (char_str_ptr != str_ptr)
    {
        printf("a");
        strtod(char_str_ptr, &str_ptr);
        J++;
        if (*char_str_ptr == ',')
        {
            char_str_ptr = str_ptr + 1;
        }
        printf("b");
    }
    printf("%d", J);

    return 0;
}