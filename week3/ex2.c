#include <stdio.h>

// this is my swapping function from week 2 ex. 4
void swap(int * x, int * y)
{
    *x = *x ^ *y;
    *y = *x ^ *y;
    *x = *x ^ *y;
}

void bubble_sort(int array[], int n)
{
    do
    {
        int newn = 0;
        for (int i = 1; i < n; ++i)
        {
            if (array[i - 1] > array[i])
            {
                swap(&array[i - 1], &array[i]);
                newn = i;
            }
        }
        n = newn;
    }
    while (n > 1);
    return;
}

int main()
{
    int storage[] = {1, 31415, 2, 666, 4, 69, 42};
    bubble_sort(storage, sizeof(storage) / sizeof(storage[0]));
    for (int i = 0; i < sizeof(storage) / sizeof(storage[0]); ++i)
    {
        printf("%d ", storage[i]);
    }
    printf("\n");
    return 0;
}