#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// add a boiler plate template that demonstrates the use of signals

// to handle the SIGINT signal (Ctrl+C) and SIGTERM signal (kill command)
void sigint_handler(int sig)
{
    fprintf(stdout, "Caught SIGINT Signal (%d)\n", sig);
}

int main()
{
    if (signal(SIGINT, sigint_handler) == SIG_ERR)
    {

        printf("Error setting up signal handler for SIGINT\n");
        return 1;
    }

    printf("Press Ctrl+C to send a SIGINT signal\n");

    while (1)
    {
        sleep(1);
    }
    return 0;
}