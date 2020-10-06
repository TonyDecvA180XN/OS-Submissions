#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// convert all to bytes
#define BYTES(x) (x * sizeof(unsigned char))
#define KILOBYTES(x) (x * BYTES(1024))
#define MEGABYTES(x) (x * KILOBYTES(1024))

void * allocate()
{
    //printf("Allocating %ld bytes.\n", MEGABYTES(10));
    void * a = malloc(MEGABYTES(10));
    memset(a, 0, MEGABYTES(10));
    sleep(1);
    return a;
}

int main()
{
    void *chunks[10];
    for (size_t i = 0; i < 10; ++i)
    {
        chunks[i] = allocate();
    }

    printf("Done.\n");

    // no memory leaks!
    for (size_t i = 0; i < 10; ++i)
    {
        free(chunks[i]);
    }
    printf("Finished.\n");
    return 0;    
}

/*

Output from terminal:

 tonydecva180xn  AsusRogStrixG  ~  week8  $  ./ex2 & vmstat -w -S m 1 && fg
[1] 6329
procs -----------------------memory---------------------- ---swap-- -----io---- -system-- --------cpu--------
 r  b         swpd         free         buff        cache   si   so    bi    bo   in   cs  us  sy  id  wa  st
 1  0            0        12128           56          820    0    0    16   200   11   33   0   0 100   0   0
 0  0            0        12126           56          820    0    0     0    64    9   86   0   0 100   0   0
 0  0            0        12116           56          820    0    0     0     0    9   73   0   0 100   0   0
 0  0            0        12106           56          820    0    0     0     0    5   64   0   0 100   0   0
 0  0            0        12095           56          820    0    0     0     0    9   74   0   0 100   0   0
 0  0            0        12085           56          820    0    0     0     0  155  769   0   0 100   0   0
 0  0            0        12074           56          820    0    0     0     0   14   94   0   0 100   0   0
 0  0            0        12064           56          820    0    0     0    12   14   91   0   0 100   0   0
 0  0            0        12053           56          820    0    0     0     0    3   60   0   0 100   0   0
 0  0            0        12043           56          820    0    0     0     0    9   70   0   0 100   0   0
 0  0            0        12032           56          820    0    0     0     0    5   67   0   0 100   0   0
Done.
Finished.
 0  0            0        12136           56          820    0    0     0     0    9   86   0   0 100   0   0
 0  0            0        12136           56          820    0    0     0     0    8   77   0   0 100   0   0
 0  0            0        12136           56          820    0    0     0     0    4   68   0   0 100   0   0
 0  0            0        12136           56          820    0    0     0     0    8   72   0   0 100   0   0
^C[1]+  Done                    ./ex2

As we can see the memory sector under "free" tab decreases in time by ~10 MB each time.

*/