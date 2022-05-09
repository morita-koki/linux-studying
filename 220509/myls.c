#include <stdio.h>
#include <dirent.h>

int main(int argc, char* argv[])
{
    DIR* dir = opendir(argv[1]);

    struct dirent* d;
    while ((d = readdir(dir)) != NULL)
    {
        printf("%lu %s\n", d->d_ino, d->d_name);
    }

    closedir(dir);
    return 0;
}