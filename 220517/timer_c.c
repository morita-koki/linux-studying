#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>


time_t start;
void stop(int signum);

int main()
{
    time(&start);
    signal(SIGINT, stop);
    for (;;)
    {
        sleep(1);
        printf(".");
        fflush(stdout);
    }
    return 0;
}

void stop(int signum)
{
    time_t end;
    time(&end);
    printf("\nsignal number=%d, time=%ld\n", signum, end-start);
    exit(0);
}