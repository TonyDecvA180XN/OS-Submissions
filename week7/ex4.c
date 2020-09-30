#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void* my_realloc(void* a, size_t old_size, size_t new_size) // in bytes
{
    if (a == NULL)
        return malloc(new_size);
    if (new_size == 0)
    {
        free(a);
        return NULL;
    }

    void* new = malloc(new_size);
    if (new_size > old_size)
    {
        memcpy(new, a, old_size);
    }
    else
    {
        memcpy(new, a, new_size);
    }
    free(a);
    return new;
}

int main()
{
    // test program from ex3 is used.
    printf("Enter original array size: ");
    int n1 = 0;
    scanf("%d", &n1);

    //Create a new array of n1 ints
    int* a1 = (int*)malloc(n1 * sizeof(int));
    int i;
    for (i = 0; i < n1; i++)
    {
        //Set each value in a1 to 100
        a1[i] = 100;

        //Print each element out (to make sure things look right)
        printf("%i ", a1[i]);
    }

    //User specifies the new array size, stored in variable n2.
    printf("\nEnter new array size: ");
    int n2 = 0;
    scanf("%d", &n2);

    //Dynamically change the array to size n2

    a1 = my_realloc(a1, n1 * sizeof(int), n2 * sizeof(int));

    for (i = 0; i < n2; i++)
    {
        //Print each element out (to make sure things look right)
        printf("%i ", a1[i]);
    }
    printf("\n");

    //Done with array now, done with program :D
    free(a1);
    return 0;
}