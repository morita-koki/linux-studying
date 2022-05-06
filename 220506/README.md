## プロセス・PATH・コマンドの復習

* 絶対パスを指定せずに、オプション指定が可能なシェルをつくってみる

```
$ ./shell
--> ls -l 
total 28
-rw-r--r-- 1 mochikun mochikun   156 May  7 00:05 README.md
-rwxr-xr-x 1 mochikun mochikun 17184 May  7 00:03 shell
-rw-r--r-- 1 mochikun mochikun  1371 May  7 00:03 shell.c
--> pwd
/home/mochikun/C/linux/220506
--> touch hogehoge.txt
--> ls
README.md  hogehoge.txt  shell  shell.c
--> ^C
$ 
```

いけてそう。

* コマンド：ターミナルで実行するやつ
* PATH：環境変数の一つ。コマンドがあるディレクトリが複数指定されている
* プロセス：プログラムの実行単位。OSが管理している

