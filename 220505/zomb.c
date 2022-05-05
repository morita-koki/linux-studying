#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    int st;
    pid_t pid = fork();
    if (pid == 0)
    {
        exit(0);
    }
    else 
    {
        sleep(20);
        wait(&st);
        printf("正常終了\n");
    }
    return 0;
}