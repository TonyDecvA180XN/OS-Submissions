#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%i", &n);

    int * array = (int *) malloc(n * sizeof(int));
    for (size_t i = 0; i < (size_t) n; ++i)
    {
        array[i] = (int)i;
    }
    for (size_t i = 0; i < (size_t) n; ++i)
    {
        printf("%i ", array[i]);
    }

    free(array);
    return 0;
}