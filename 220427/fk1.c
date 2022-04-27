#include <stdio.h>
#include <unistd.h>

int main()
{
    const int N = 10;
    pid_t pid = fork();
    
    if (pid == 0) //子プロセス
    {
        for (int i = 0; i < N; ++i)
        {
            printf("子プロセス i=%d\n", i);
        }
    }
    else //親プロセス
    {
        for (int i = 0; i < N; ++i)
        {
            printf("親プロセス i=%d\n", i);
        }
    }
    return 0;
}