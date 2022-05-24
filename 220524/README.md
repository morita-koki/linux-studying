# 共有メモリ

複数のプロセスかｒアクセスできる共通のメモリ
グローバル変数的なイメージ？（複数の関数からアクセスできる変数のこと）

## 特徴
* 複数のプロセスで共有できるメモリを利用
* 複数のプロセスから読み書きできる
* アクセス速度が速い <- 1番のメリット
* 処理が複雑になる <- 排他制御や同期制御が必要

## 実装してみる

```
$ gcc mmap_sen.c -lrt -o mmap_sen
$ gcc mmap_rec.c -lrt -o mmap_rec
$ ls
README.md  mmap_rec  mmap_rec.c  mmap_sen  mmap_sen.c
$ 
```

```
$ ./mmap_sen
ababa
$ 
```

```
$ ./mmap_rec
ababa
$
```


## 共有メモリオブジェクトを確認する

/dev/shm(/run/shmかも。。。？)ディレクトリに作成される

```
$ ls -l /run/shm
合計 0
$ ./mmap_sen
hello
$ ls -l /run/shm
合計 4
-rw-r--r-- 1 mochikun mochikun 4096  5月 24 15:45 shared_memory
$ ./mmap_rec
hello
$ 
```


