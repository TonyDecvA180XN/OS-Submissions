#include <stdio.h>
#include <stdlib.h>

void draw_pyramid_up_symmetric(int n)
{
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
}

void draw_pyramid_up_left(int n)
{
    for (int line = 0; line < n; ++line)
    {
        // each line has 2line + 1 asterisk chars
        for (int asterisk = 0; asterisk < (2 * line + 1); ++asterisk)
        {
            printf("*");
        }
        printf("\n");
    }
}

void draw_pyramid_right_symmetric(int n)
{
    for (int line = 0; line < (n + 1) / 2; ++line)
    {
        for (int asterisk = 0; asterisk < line + 1; ++asterisk)
        {
            printf("*");
        }
        printf("\n");
    }
    for (int line = n / 2; line >= 0; --line)
    {
        for (int asterisk = 0; asterisk < line + 1; ++asterisk)
        {
            printf("*");
        }
        printf("\n");
    }
}

void draw_square(int n)
{
    for (int line = 0; line < n; ++line)
    {
        // each line has 2line + 1 asterisk chars
        for (int asterisk = 0; asterisk < n; ++asterisk)
        {
            printf("*");
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    int type = atoi(argv[2]);
    switch (type)
    {
    case 1:
        draw_pyramid_up_symmetric(n);
        break;
    case 2:
        draw_pyramid_up_left(n);
        break;
    case 3:
        draw_pyramid_right_symmetric(n);
        break;
    case 4:
        draw_square(n);
        break;
    default:
        break;
    }
    
    return 0;
}