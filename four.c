#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>

// Global
// long long sum = 0;
struct sum_runner_struct
{
    long long limit;
    long long answer;
};

// Takes a pointer to a long long containing the number that we want to accumulate to
// Treats the global sum as a scratchpad. Not thread-safe.
void *sum_runner(void *arg)
{
    printf("Thread Started\n");
    struct sum_runner_struct *arg_ptr = (struct sum_runner_struct *)arg;
    long long sum = 0;
    for (long long i = 0; i <= arg_ptr->limit; i++)
    {
        sum += i;
    }
    arg_ptr->answer = sum;
    pthread_exit(0);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Usage: %s <num>\n", argv[0]);
        exit(-1);
    }

    int num_args = argc - 1;

    pthread_t tid[num_args];
    struct sum_runner_struct limits[num_args];
    for (int i = 0; i < num_args; i++)
    {
        limits[i].limit = atoll(argv[i + 1]);
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tid[i], &attr, sum_runner, &limits[i]);
    }
    // I can do work here
    // for (int i = 0; i < 10; i++)
    // {
    //     sleep(1);
    //     printf("I'm not hanging %d\n", i);
    // }
    for (int i = 0; i < num_args; i++)
    {
        pthread_join(tid[i], NULL);
        printf("Sum %d is %lld\n", i, limits[i].answer);
    }
}
