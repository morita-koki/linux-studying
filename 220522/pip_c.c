#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int rfd = atoi(argv[1]);
    int wfd = atoi(argv[2]);

    char word[256];
    read(rfd, word, sizeof word); //バッファからデータを読み込む

    int n = strlen(word);
    sleep(10);
    write(wfd, &n, sizeof n); // バッファに書き込む

    close(rfd);
    close(wfd);
    return 0;
}