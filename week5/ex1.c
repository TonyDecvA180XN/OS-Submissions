#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <pthread.h> 
  
#define N 10


void *myThreadFun(void *vargp) 
{ 
    //sleep(1);
    size_t* number = (size_t *)vargp;
    printf("Hi! I am thread which number is %li.\n", *number + 1);
    free(number); // no memory leaks!
    return NULL; 
} 
   
int main() 
{ 
    pthread_t my_threads[N]; 
    printf("Thread creation initiated.\n");

    // This is a first version of the program
    // for (size_t i = 0; i < N; i++)
    // {
    //     /*
    //         There is a problem since I have to pass my arguments by pointer.
    //         If I pass a reference to i, it might be updated before new thread will print it.
    //         Hence, I need to make a copy that will not be changed.
    //     */
    //     size_t* temp = (size_t*)malloc(i);
    //     *temp = i;
    //     pthread_create(&my_threads[i], NULL, myThreadFun, (void *)temp); 
    // }
    // // We created all the threads
    // printf("Threads initiation complete.\n"); 
    // // Now we destroy all of them
    // for (size_t i = 0; i < N; ++i)
    // {
    //     pthread_join(my_threads[i], NULL); 
    // }


    // This is a second version of a program
    for (size_t i = 0; i < N; i++)
    {
        /*
            There is a problem since I have to pass my arguments by pointer.
            If I pass a reference to i, it might be updated before new thread will print it.
            Hence, I need to make a copy that will not be changed.
        */
        size_t* temp = (size_t*)malloc(i);
        *temp = i;
        pthread_create(&my_threads[i], NULL, myThreadFun, (void *)temp);
        pthread_join(my_threads[i], NULL); 
        // Here we have to wait until the thread is done work and only then, go on.
    }
     
    printf("All threads are terminated.\n"); 
    exit(0); 
}