#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

struct File
{
    int m_inode;
    const char *name;
};

#define INITIAL_CAPACITY 5

void pushFile(struct File *arr, int index, struct File value, int *size, int *capacity)
{
    if (*size > *capacity)
    {
        realloc(arr, sizeof(arr) * 2);
        *capacity = sizeof(arr) * 2;
    }
    arr[index] = value;
    *size = *size + 1;
}

void pushNumber(int *arr, int index, int value, int *size, int *capacity)
{
    if (*size > *capacity)
    {
        realloc(arr, sizeof(arr) * 2);
        *capacity = sizeof(arr) * 2;
    }
    arr[index] = value;
    *size = *size + 1;
}

int main()
{
    int filesSize = 0;
    int filesCapacity = INITIAL_CAPACITY;
    struct File *files = malloc(INITIAL_CAPACITY * sizeof(struct File));

    int numbersSize = 0;
    int numbersCapacity = INITIAL_CAPACITY;
    int *numbers = malloc(INITIAL_CAPACITY * sizeof(int));

    DIR *pDir = opendir(".");
    if (pDir == NULL)
    {
        return 69;
    }
    struct dirent *dp;
    while ((dp = readdir(pDir)) != NULL)
    {
        const char * filename = dp->d_name;
        //printf("Scanning \'%s\'.\n", filename);
        struct stat buf;
        if (stat(filename, &buf))
        {
            return 420;
        }
        if ( !S_ISDIR(buf.st_mode) && buf.st_nlink >= 2)
        {
            struct File file;
            file.m_inode = buf.st_ino;
            file.name = filename;
            //printf("Pushing.\n");
            pushFile(files, filesSize, file, &filesSize, &filesCapacity);
            int exist = 0;
            for (int i = 0; i < numbersSize; ++i)
            {
                if (numbers[i] == file.m_inode)
                {
                    exist = 1;
                    break;
                }
            }
            if (!exist)
            {
                pushNumber(numbers, numbersSize, file.m_inode, &numbersSize, &numbersCapacity);
            }
        }
    }
    closedir(pDir);
    //printf("Found %d files and %d unique numbers.\n", filesSize, numbersSize);

    for (int i = 0; i < numbersSize; ++i)
    {
        int currentNumber = numbers[i];
        printf("For inodenumber %d:\n", currentNumber);
        for (int j = 0; j < filesSize; ++j)
        {
            struct File currentFile = files[j];
            if (currentFile.m_inode == currentNumber)
            {
                printf("\t%s\n", currentFile.name);
            }
        }
        printf("\n");
        
    }

    free(files);
    free(numbers);
    return 0;
}