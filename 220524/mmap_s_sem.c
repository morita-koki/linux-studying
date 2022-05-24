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
    key_t semkey = ftok("mmap2_r_sem", 'a'); // keyの作成
    int semid = semget(semkey, 1, IPC_CREAT|IPC_EXCL|0666); // 既存セマフォの有無
    if (semid < 0) { //既存のセマフォが存在
        semid = semget(semkey, 1, IPC_CREAT|0666); //同一キーで作成
    } else {
        semctl(semid, 0, SETVAL, 1); //作成したセマフォを初期化する
    }

    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_flg = 0;

    int fd = shm_open("/shared_memory", O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        fprintf(stderr, "shm_open failed\n");
        return 1;
    }

    char line[4096], command[4096];
    int ret1 = ftruncate(fd, sizeof line);
    char* p = mmap(0, sizeof line, PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED) {
        fprintf(stderr, "mmap\n");
        return 1;
    }

    for (;;) {
        buf.sem_op = -1;
        semop(semid, &buf, 1);
        fprintf(stderr, "> ");
        fgets(line, sizeof line, stdin);
        int ret2 = sscanf(line, "%[^\n]", command);
        if (ret2 < 0) break;
        int ret3 = strcmp(command, "exit");
        strncpy(p, command, sizeof command);
        buf.sem_op = 2;
        semop(semid, &buf, 1);
        if (ret3 == 0) break;
        buf.sem_op = -1;
        semop(semid, &buf, 1);
        fprintf(stderr, "=%s <-> %s=\n", command, p);
        buf.sem_op = 1;
        semop(semid, &buf, 1);
    }

    if (munmap(p, sizeof line) == -1) { fprintf(stderr, "munmap"); }
    if (semctl(semid, 0, IPC_RMID) != 0) { fprintf(stderr, "semctl"); }
    close(fd);
    return 0;
}