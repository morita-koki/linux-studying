#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();
    if (pid == 0)
    {
        sleep(20);
        printf("子プロセス終了\n");
        exit(0);
    }
    else
    {
        getchar();
        printf("親プロセス終了\n");
    }
    return 0;
}