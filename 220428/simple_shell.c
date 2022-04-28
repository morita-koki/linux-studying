#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid;
    int st, ret;
    char line[256], command[256];
    
    for (;;)
    {
        printf("> ");
        fgets(line, sizeof(line), stdin);
        sscanf(line, "%s", command);

        pid = fork();
        if (pid == 0)
        {
            ret = execl(command, command, NULL);
            if (ret < 0) exit(0);
        }
        else 
        {
            wait(&st);
        }
    }
    return 0;
}