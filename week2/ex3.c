#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    for (int line = 0; line < n; ++line)
    {
        // each line has (n/2) - line spaces
        for (int space = 0; space < n - line - 1; ++space)
        {
            printf(" ");
        }
        // each line has 2line + 1 asterisk chars
        for (int asterisk = 0; asterisk < (2 * line + 1); ++asterisk)
        {
            printf("*");
        }
        printf("\n");

    }
    
    return 0;
}