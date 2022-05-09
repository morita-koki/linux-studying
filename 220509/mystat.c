#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[])
{
    struct stat buf;
    int ret = stat(argv[1], &buf);

    if (ret < 0)
    {
        printf("stat error\n");
        exit(0);
    }
    printf("Size: %ld byte\n", buf.st_size);
    printf("Access: %s", ctime(&buf.st_atime));
    printf("inode: %ld\n", buf.st_ino);

    return 0;
}