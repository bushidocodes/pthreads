#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Header file for sleep(). man 3 sleep for details. 
#include <pthread.h>

// Global
long long sum = 0;

// Takes a pointer to a long long containing the number that we want to accumulate to
// Treats the global sum as a scratchpad. Not thread-safe.
void* sum_runner(void* arg) {
    printf("Thread Started\n");
    long long *limit_ptr = (long long*)arg;

    for (long long i = 0; i<= *limit_ptr; i++) {
        sum += i;
    }
    pthread_exit(0);
}

int main (int argc, char **argv){
    if (argc < 2){
        printf("Usage: %s <num>\n", argv[0]);
        exit(-1);
    }

    long long limit = atoll(argv[1]);

    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&tid, &attr, sum_runner, &limit);
    // I can do work here
    for (int i = 0; i < 10; i++){
        sleep(1);
        printf("I'm not hanging %d\n", i);
    }
    pthread_join(tid, NULL);
    printf("Sum is %lld\n", sum);
}
