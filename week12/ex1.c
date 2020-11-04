#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>


int main()
{
    int randomDevice = open("/dev/random", O_RDONLY);
    if (randomDevice < 0) return 1;
    char string[20];
    int status;
    status = read(randomDevice, string, sizeof string);
    if (status < 0) return 2;
    FILE * output = fopen("ex1.txt", "w");
    fprintf(output, "%s", string);
    fclose(output);
    return 0;
}