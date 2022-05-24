#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>


/*****************************************************\
int shm_open(const char* path, int oflags, mode_t mode)
    共有メモリオブジェクトをオープンする
    引数
        path ：共有メモリオブジェクトの名前（/から始まること）
        oflag：ビットマスク
        mode ：共有メモリオブジェクトのパーミッションん
    返り値
        成功時：ファイルディスクリプタ番号
        失敗時：-1


int ftruncate(int fd, off_t length)
    共有メモリオブジェクトのファイルサイズを指定する
    引数
        fd    ：ファイルディスクリプタ番号
        length：指定するファイルサイズ
    返り値
        成功時：0
        失敗時：-1

void* mmap(void* addr, size_t length, int prot, int flags, int fd, off_t offset)
    共有メモリオブジェクトをメモリ上にマップする
    引数
        addr  ：マッピング開始アドレス。（NULLにするとOSが自動で選んでくれる）
        length：マップするサイズ
        prot  ：読み書きモードの指定
        flags ：マッピングの更新を他のプロセスに公開するか
        fd    ：ファイルディスクリプタ番号
        offset：マッピングを開始するオフセット
    返り値
        成功時：マップされた領域のアドレス
        失敗時：MAP_FAILED

int manmap(void* addr, size_t length)
    指定したアドレス範囲のマップを削除する
    引数
        addr  ：マップされた領域のアドレス
        length：マップされたサイズ
    返り値
        成功時：0
        失敗時：-1

int shm_unlink(const char* name)
    全てのプロセスがマップを削除後、共有メモリを削除する
    引数
        name：共有メモリオブジェクトの名前
    返り値
        成功時：0
        失敗時：-1
\*****************************************************/

int main()
{
    int fd = shm_open("/shared_memory", O_CREAT | O_RDWR, 0666); // 共有メモリオブジェクトをオープン
    if (fd == -1) {
        fprintf(stderr,"shm_open failed\n");
        return 1;
    }
    char line[4096]; 
    if (ftruncate(fd, sizeof(line)) < 0) { // 共有メモリオブジェクトのファイルサイズを指定
        fprintf(stderr, "ftruncate");
        return 1;
    }

    char* p = mmap(NULL, sizeof line, PROT_WRITE, MAP_SHARED, fd, 0); // 共有メモリオブジェクトをメモリ上にマップ
    if (p == MAP_FAILED) {
        fprintf(stderr, "mmap");
        return 1;
    }

    fgets(line, sizeof(line), stdin);
    char command[4096];
    if (sscanf(line, "%[^\n]", command) > 0) {
        strncpy(p, command, sizeof(command)); // 文字列を共有メモリにコピーする
    }

    if (munmap(p, sizeof(line)) == -1) {
        fprintf(stderr, "munmap");
        return 1;
    }

    close(fd);
    return 0;
}