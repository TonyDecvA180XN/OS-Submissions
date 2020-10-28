#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>


int main()
{
    // open file
    int file = open("./ex1.txt", O_RDWR);
    if (file < 0) return 1;

    // get file info
    int status;
    struct stat file_stat = {};
    status = fstat(file, &file_stat);
    if (status) return 2;

    // get file size
    int file_size = file_stat.st_size;

    // map space to the file space
    void * adress_space = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, file, 0);
    if (adress_space == MAP_FAILED) return 3;

    // copy string into the file
    strcpy(adress_space, "This is a nice day\n");

    return 0;
}