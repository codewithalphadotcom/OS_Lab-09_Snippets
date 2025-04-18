#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

#define NUM_THREADS 4
pthread_t threads[NUM_THREADS];

void sigusr1_handler(int signum)
{
    int i = getgid(), j = getppid(), k = getpid();
    fprintf(stdout, "Thread %lu received SIGUSR1 signal (parent=%u) [pid=%u] {tid=%u} \n", pthread_self(), j, k, i);
}

void *thread_function(void *arg)
{
    while (1)
        sleep(1);
    return NULL;
    signal(SIGUSR1, sigusr1_handler);
}

int main()
{
    // signal(SIGUSR1, sigusr1_handler);
    for (int i = 0; i < NUM_THREADS; i++)
    {
        if (pthread_create(&threads[i], NULL, thread_function, NULL) != 0)
        {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    int i = getgid(), j = getpid(), k = getppid();
    fprintf(stdout, "Parent Process ID: %u, Process ID:%u, main() thread ID: %u\n", k, j, i);
    fprintf(stdout, "Thread IDs: 0=%lu, 1=%lu, 2=%lu and 3=%lu\n", threads[0], threads[1], threads[2], threads[3]);

    kill(j, SIGUSR1);
    pthread_kill(threads[2], SIGUSR1);

    for (int i = 0; i < NUM_THREADS; i++)
    {
        if (pthread_join(threads[i], NULL) != 0)
        {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}
