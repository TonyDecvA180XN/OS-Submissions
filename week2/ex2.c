#include <stdio.h>
#include <string.h>

#define MAX_STR_LENGTH 256

int main()
{
    char string[MAX_STR_LENGTH];
    scanf("%s", string);
    for (int i = strlen(string) - 1; i >= 0; --i)
    {
        printf("%c", string[i]);
    }
    printf("\n");
    
    return 0;
}