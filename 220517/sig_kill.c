#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./sig_kill PID \n");
        return 1;
    }
    pid_t pid = atoi(argv[1]);
    int ret = kill(pid, SIGKILL);
    if (ret < 0) perror("kill");

    return 0;
}