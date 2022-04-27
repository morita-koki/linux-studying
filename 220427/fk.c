#include <stdio.h>
#include <unistd.h>

int main()
{
    fork();
    pid_t pid = getpid();
    for (int i = 0; i < 10; ++i)
    {
        printf("PID=%d i=%d\n", pid, i);
        usleep(1);
    }
    return 0;
}