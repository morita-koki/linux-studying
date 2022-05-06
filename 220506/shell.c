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

int get_arg(char* c, char* arg[])
{
    int i = 0;
    for (arg[i] = strtok(c, " "); arg[i] != NULL; i++, arg[i] = strtok(NULL, " ")){}
    return i;
}


int main()
{
    char line[256], command[256], *dir[64], *arg[32];
    get_path(dir);

    for(;;)
    {
        printf("--> ");
        fgets(line, sizeof(line), stdin);
        sscanf(line, "%[^\n]", command);

        get_arg(command, arg);

        pid_t pid = fork();
        if (pid == 0)
        {
            int ret = execv(arg[0], arg);
            if (ret < 0) 
            {
                for (int i = 0; dir[i] != NULL; ++i)
                {
                    char ncommand[256], *narg[32];
                    sscanf(line, "%[^\n]", ncommand);
                    char nncommand[4096];
                    sprintf(nncommand, "%s/%s", dir[i], ncommand);

                    get_arg(nncommand, narg);
                    execv(narg[0], narg);
                }
                exit(0);
            }
        }
        else 
        {
            int st;
            wait(&st);
        }
    }
    return 0;
}