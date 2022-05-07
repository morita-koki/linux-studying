#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/vfs.h>

int main(int argc, char* argv[])
{
    double gb = 1024.0 * 1024.0 * 1024.0;

    sync();
    struct statfs buf;
    int ret = statfs(argv[1], &buf);
    if (ret < 0) { exit(0); }

    printf("Total Size = %.1f GB\n", buf.f_blocks * buf.f_bsize / gb);

    int ubs = buf.f_blocks - buf.f_bfree;

    printf("Used Size = %.0f GB\n", ubs * buf.f_bsize / gb);
    printf("Free Size = %.0f GB\n", buf.f_bfree * buf.f_bsize / gb);
    printf("Used Ratio = %.0f %%\n", 100.0 * ubs / buf.f_blocks);
    return 0;
}