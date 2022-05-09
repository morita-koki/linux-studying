## inodeとは

inodeはファイルに関する管理情報を保持しているデータで、ファイル１つに対し、１つのinode割り当てられている。inode番号はファイルシステムごとに一意である。

<br>

* コマンドで確認する
```
$ df -i
Filesystem       Inodes   IUsed    IFree IUse% Mounted on
/dev/sda       16777216  180800 16596416    2% /
tmpfs            503103       1   503102    1% /mnt/wsl
tools               999 -999001  1000000     - /init
none             502582     138   502444    1% /dev
none             503103      12   503091    1% /run
none             503103       1   503102    1% /run/lock
none             503103       1   503102    1% /run/shm
none             503103       1   503102    1% /run/user
tmpfs            503103      15   503088    1% /sys/fs/cgroup
drivers             999 -999001  1000000     - /usr/lib/wsl/drivers
lib                 999 -999001  1000000     - /usr/lib/wsl/lib
C:\                 999 -999001  1000000     - /mnt/c
G:\                 999 -999001  1000000     - /mnt/g
$ 
```
<br>

```
$ ls -i
42847 README.md
$ 
```
<br>

* 指定したファイルのinodeを確認する
```
$ stat README.md
  File: README.md
  Size: 1113            Blocks: 8          IO Block: 4096   regular file
Device: 800h/2048d      Inode: 42847       Links: 1
Access: (0644/-rw-r--r--)  Uid: ( 1000/mochikun)   Gid: ( 1000/mochikun)
Access: 2022-05-09 22:39:27.309953100 +0900
Modify: 2022-05-09 22:39:27.219953100 +0900
Change: 2022-05-09 22:39:27.219953100 +0900
 Birth: -
$ 
```


* inodeを確認するプログラム書いてみる

```
$ ./mystat mystat.c
Size: 442 byte
Access: Mon May  9 22:59:50 2022
inode: 47767
$ 
```

<br>

```
$ ./myls .
47767 mystat.c
42847 README.md
47768 myls.c
84834 myls
42390 ..
42806 .
$ 
```