#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>

// convert all to bytes
#define BYTES(x) (x * sizeof(unsigned char))
#define KILOBYTES(x) (x * BYTES(1024))
#define MEGABYTES(x) (x * KILOBYTES(1024))

/*
struct rusage {
               struct timeval ru_utime;
               struct timeval ru_stime;
               long   ru_maxrss;       
               long   ru_ixrss;        
               long   ru_idrss;        
               long   ru_isrss;        
               long   ru_minflt;       
               long   ru_majflt;       
               long   ru_nswap;        
               long   ru_inblock;      
               long   ru_oublock;      
               long   ru_msgsnd;       
               long   ru_msgrcv;       
               long   ru_nsignals;     
               long   ru_nvcsw;        
               long   ru_nivcsw;       
           };
*/

void * allocate()
{
    void * a = malloc(MEGABYTES(10));
    memset(a, 0, MEGABYTES(10));
    struct rusage my_rusage;
    getrusage(RUSAGE_SELF, &my_rusage);
    printf("Memory usage: ru_maxrss = %ld; ru_ixrss = %ld; ru_idrss = %ld; ru_isrss = %ld.\n", my_rusage.ru_maxrss, my_rusage.ru_ixrss, my_rusage.ru_idrss, my_rusage.ru_isrss);
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

the out of the program is:

 tonydecva180xn  AsusRogStrixG  ~  week8  $  ./ex4
Memory usage: ru_maxrss = 11272; ru_ixrss = 0; ru_idrss = 0; ru_isrss = 0.
Memory usage: ru_maxrss = 22040; ru_ixrss = 0; ru_idrss = 0; ru_isrss = 0.
Memory usage: ru_maxrss = 32064; ru_ixrss = 0; ru_idrss = 0; ru_isrss = 0.
Memory usage: ru_maxrss = 42352; ru_ixrss = 0; ru_idrss = 0; ru_isrss = 0.
Memory usage: ru_maxrss = 52640; ru_ixrss = 0; ru_idrss = 0; ru_isrss = 0.
Memory usage: ru_maxrss = 62928; ru_ixrss = 0; ru_idrss = 0; ru_isrss = 0.
Memory usage: ru_maxrss = 73216; ru_ixrss = 0; ru_idrss = 0; ru_isrss = 0.
Memory usage: ru_maxrss = 83504; ru_ixrss = 0; ru_idrss = 0; ru_isrss = 0.
Memory usage: ru_maxrss = 93528; ru_ixrss = 0; ru_idrss = 0; ru_isrss = 0.
Memory usage: ru_maxrss = 103816; ru_ixrss = 0; ru_idrss = 0; ru_isrss = 0.
Done.
Finished.

*/