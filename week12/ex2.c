#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char *argv[]) 
{
    if (argc <= 1) return 1;
    printf("Args number\n");
    int append = 0;

    int optional = -1;
    while ((optional = getopt(argc, argv, "a:")) != -1)
    {
        if (optional == 'a')
        {
            append = 1;
            break;
        }
    }

    int status;

    int inputFile, outputFile;

    char* fileName = NULL;
    if (append) fileName = argv[1];

    outputFile = open(fileName, O_WRONLY | O_CREAT | (append ? O_APPEND: O_TRUNC));
    if (outputFile < 0) return 2;
    printf("Ooutput file\n");


    inputFile = 0;
    ssize_t bytesRead;
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));
    while ((bytesRead = read(inputFile, buffer, 256)) > 0) 
    {
        status = write(outputFile, buffer, (size_t) bytesRead);
        if (status) return 3;

        fprintf(stdout, "%s", buffer);
        memset(buffer, 0, sizeof(buffer));
    }

    if (bytesRead) return 4;

    close(outputFile);
    return 0;
}