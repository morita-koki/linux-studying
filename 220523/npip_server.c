#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

int main()
{
    char* myfifo = "./named_pipe";
    mkfifo(myfifo, 0666);

    for(;;)
    {
        int fd = open(myfifo,O_RDONLY);
        char word[256];
        read(fd, word, sizeof word);
        printf("client: %s \n", word);
        close(fd);

        fd = open(myfifo, O_WRONLY);
        int n = strlen(word);
        write(fd, &n, sizeof n);
        close(fd);
    }
    return 0;
}