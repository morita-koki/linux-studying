#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
/*-----------------------------------------------*\

int pipe(int fd[2]);
    fd[0]に読み取り用のファイルディスクリプタの番号が、
    fd[1]に書き込み用のファイルディスクリプタの番号が入る
    返り値：成功時0、失敗時-1

ssize_t write(int fd, const void* buf, size_t count);
    fd：書き込み先のバッファのファイルディスクリプタ番号
    buf：書き込むデータのアドレス
    count：書き込むデータサイズ
    返り値：成功時（書き込んだデータサイズ）、失敗時（-1）

ssize_t read(int fd, void* buf, size_t count);
    fd：読み取り先のバッファのファイルディスクリプタ番号
    buf：読み取るデータの格納先アドレス
    count：読み取るデータの最大サイズ

\*-----------------------------------------------*/
int main()
{
    // ファイルディスクリプタを取得（パイプを開く。ファイルディスクリプタを開く。とも）
    int fd[2];
    int ret = pipe(fd);
    if (ret < -1) {
        puts("pipe error");
        return 1;
    }

    // int型のファイルディスクリプタをchar型に変換
    char wfd[5], rfd[5];
    snprintf(rfd, sizeof rfd, "%d", fd[0]);
    snprintf(wfd, sizeof wfd, "%d", fd[1]);


    char line[256];
    fgets(line, sizeof line, stdin);
    char word[256];
    int ret1 = sscanf(line, "%s", word);
    if (ret1 > 0) {
        pid_t pid = fork(); //子プロセスの作成
        if (pid == 0) {
            int ret2 = execl("pip_c", "pip_c", rfd, wfd, NULL); //ファイルディスクリプタの番号を引数としてpip_cを呼び出す
            if (ret2 < 0) return 1;
        }
        write(fd[1], word, sizeof word);
        int st;
        wait(&st); // 子プロセス終了まで待機

        int n;
        read(fd[0], &n, sizeof n);
        printf("%s <-> %d\n", word, n);
        // ファイルディスクリプタを閉じる
        close(fd[0]);
        close(fd[1]);
    }
    return 0;
}
