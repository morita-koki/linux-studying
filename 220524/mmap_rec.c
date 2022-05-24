#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main(int argc, char* argv[])
{
    int fd = shm_open("/shared_memory", O_RDONLY, 0666); // 共有メモリオブジェクトを読み取り専用でオープン
    if (fd == -1) {
        fprintf(stderr, "shm_open failed\n");
        return 1;
    }

    char* p = mmap(NULL, 4096, PROT_READ, MAP_SHARED, fd, 0); // 読み取り専用でマップする
    if (p == MAP_FAILED) {
        fprintf(stderr, "mmap");
        return 1;
    }

    fprintf(stderr, "%s\n", p);

    if (munmap(p, sizeof(char)) == -1) {
        fprintf(stderr, "munmap");
        return 1;
    }

    shm_unlink("/shared_memory");
    close(fd);
    return 0;
}