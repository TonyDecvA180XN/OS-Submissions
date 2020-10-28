#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int status;
    status = setvbuf(stdout, NULL, _IOLBF, 0);

    const char * string = "Hello";
    for (int i = 0; i < strlen(string); ++i)
    {
        printf("%c", string[i]);
        sleep(1);
    }
    printf("\n");
    return 0;
}