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

# 排他制御

ざっくりいうと、複数のプロセスで同じメモリを書き換えるといろいろ問題が起きる（上書きされるとか）ので、処理を行うときにメモリを独り占めする。この独り占めする順番を決めるのが排他制御


## セマフォ

linuxでは排他制御を行うのにセマフォと呼ばれる概念を使う。
セマフォはセマフォ値という正の整数値を持ち、
各プロセスからアクセス可能。
加算操作をV操作、減算操作をP操作という。

### セマフォの特徴

* セマフォ値を減算操作すると排他制御を開始する
* セマフォ値を加算操作すると排他制御が終了する
* セマフォ値は0未満にはなれない
* 演算操作によりセマフォ値が0未満になる場合は原案操作が保留され、そのプロセスは待ち行列に入る（セマフォ値が増えて減算操作できるようになるとプロセスは再開される）

整理券のイメージかな？
整理券ない人は入れない（アクセスできません）的な？

* 動かしてみる
  
```
$ gcc mmap_r_sem.c -lrt -o mmap_r_sem
$ gcc mmap_s_sem.c -lrt -o mmap_s_sem
$ ls 
README.md   mmap_r_sem.c  mmap_rec.c  mmap_s_sem.c  mmap_sen.c
mmap_r_sem  mmap_rec      mmap_s_sem  mmap_sen
$ 
```

※２つのターミナルを開く
```
$ ./mmap_s_sem
> apple
=apple <-> 5=
> Ball
=Ball <-> 4=
> hogehoge
=hogehoge <-> 8=
> hello world
=hello world <-> 11=
> hi
=hi <-> 2=
> exit
$ 
```

```
$ ./mmap_r_sem
-apple-
5
-Ball-
4
-hogehoge-
8
-hello world-
11
-hi-
2
-exit-
$ 
```

[参考](https://wa3.i-3-i.info/word13357.html)




