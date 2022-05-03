#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int get_path(char* dir[])
{
    char* env;
    env = getenv("PATH");

    int i = 0;
    for (dir[i] = strtok(env, ":"); dir[i] != NULL; i++, dir[i] = strtok(NULL, ":")){}
    return i;
}



int main()
{
    pid_t pid;
    int ret, st;
    char line[256], command[256], path[4096], *dir[64];
    get_path(dir);


    for(;;)
    {
        printf("--> ");
        fgets(line, sizeof(line), stdin);
        sscanf(line, "%s", command);
        pid = fork();

        if (pid == 0)
        {
            ret = execl(command, command, NULL);
            // printf("%d\n", ret);
            if (ret < 0) 
            {
                for (int i = 0; dir[i] != NULL; ++i)
                {
                    sprintf(path, "%s/%s", dir[i], command);
                    execl(path, path, NULL);
                }
                exit(0);
            }
        }
        else 
        {
            wait(&st);
        }
    }
    return 0;
}