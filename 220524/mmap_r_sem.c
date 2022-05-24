#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main()
{
    key_t semkey = ftok("mmap2_r_sem", 'a');
    int semid = semget(semkey, 1, IPC_CREAT | IPC_EXCL | 0666);
    if (semid < 0) {
        semid = semget(semkey, 1, IPC_CREAT | 0666);
    } else {
        semctl(semid, 0, SETVAL, 0);
    }

    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_flg = 0;

    int fd = shm_open("/shared_memory", O_RDWR, 0666);
    if (fd == -1) {
        fprintf(stderr, "shm_open failed\n");
        return 1;
    }

    char* p = mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED) {
        fprintf(stderr, "mmap\n");
        return 1;
    }

    for (;;) {
        buf.sem_op = -2;
        semop(semid, &buf, 1);
        fprintf(stderr, "-%s-\n", p);
        int ret1 = strcmp(p, "exit");
        if (ret1 == 0) break;

        int n = strlen(p);
        char count[4096];
        snprintf(count, sizeof count, "%d", n);
        fprintf(stderr, "%s\n", count);
        strncpy(p, count, 4096);

        buf.sem_op = 1;
        semop(semid, &buf, 1);
    }

    if (munmap(p, sizeof(char)) == -1) fprintf(stderr, "munmap\n");
    close(fd);
    shm_unlink("/shared_memory");
    return 0;
}