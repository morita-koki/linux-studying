#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

int main()
{
	char* myfifo = "./named_pipe"; //名前付きパイプのファイル名
	mkfifo(myfifo, 0666); //名前付きファイルを作成

	for(;;) //繰り返し
	{
		char line[256], word[256];
		fgets(line, sizeof line, stdin); //標準入力から文字列を受け取る
		int ret = sscanf(line, "%[^\n]", word); //改行を抜いて別の変数に保存

		if (ret > 0) {
			int fd = open(myfifo, O_WRONLY); //ファイルを開く
			write(fd, word, sizeof word); //ファイルに書き込む
			close(fd); //閉じる

			fd = open(myfifo, O_RDONLY);
			int n;
			read(fd, &n, sizeof n);
			printf("%s <-> %d\n", word, n);
			close(fd);
		}
	}
	return 0;
}