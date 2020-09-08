#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int n = fork();
    
    if (n)
        printf("Hello from parent [PID - %d]\n", n);
    else
        printf("Hello from child [PID - %d]\n", n);

    return 0;
}