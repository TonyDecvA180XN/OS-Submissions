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
    int source_file = open("./ex1.txt", O_RDONLY);
    if (source_file < 0) return 1;
    int dest_file = open("./ex1.memcpy.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (dest_file < 0) return 2;

    // get file info
    int status;
    struct stat file_stat = {};
    status = fstat(source_file, &file_stat);
    if (status) return 3;

    // get file size
    int file_size = file_stat.st_size;

    // set destination file size same as source
    status = ftruncate(dest_file, file_size);
    if (status) return 4;

    // map space from the source file
    void * source_space = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, source_file, 0);
    if (source_space == MAP_FAILED) return 5;

    // map space to the destination file
    void * write_space = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, dest_file, 0);
    if (write_space == MAP_FAILED) return 6;

    // copy string into the file
    memcpy(write_space, source_space, file_size);

    // flush the buffer
    status = msync(write_space, file_size, MS_SYNC);
    if (status) return 7;

    return 0;
}