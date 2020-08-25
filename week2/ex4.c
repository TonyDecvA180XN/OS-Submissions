#include <stdio.h>
#include <string.h>

void swap(int * x, int * y)
{
    *x = *x ^ *y;
    *y = *x ^ *y;
    *x = *x ^ *y;
}

int main()
{
    int a, b;
    scanf("%i %i", &a, &b);
    swap(&a, &b);
    printf("%i %i\n", a, b);


    return 0;
}