#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char command[256] = "";
    do
    {
        if (fork())
            scanf("%s", command);
        else
        {
            system(command);
            return 0;
        }
    } while (strcmp(command, "exit"));
    return 0;
}