# パイプ

* 名前なしパイプ
* 名前付きパイプ

## 名前なしパイプ
バッファを介して親子関係にあるプロセス間の通信を行う

* 親子関係にあるプロセス間通信
* 非同期で単方向のみ
* バッファを介する
* 読み込みは一つのプロセスからだけ

```
$ ps -lax | grep bash
4  1000    11    10  20   0  11200  5544 do_wai Ss   pts/0      0:00 -bash
0  1000   298    11  20   0   7484   716 -      R+   pts/0      0:00 grep --color=auto bas
$ 
```

### 復習
* 一つ目のコマンド（プロセス）の標準出力を次のコマンドに標準入力として渡す：パイプ

```
$ cat upper.c | ./upper
#INCLUDE <STDIO.H>
#INCLUDE <CTYPE.H>

INT MAIN()
{
    FOR(;;)
    {
        INT C = GETCHAR();
        IF (C == EOF) BREAK;
        PRINTF("%C", (CHAR)TOUPPER(C));
    }
    RETURN 0;
}
$ 
```

* 標準入力・標準出力を選ぶリダイレクト（リダイレクション）というものもある

```
$ ./upper < upper.c
#INCLUDE <STDIO.H>
#INCLUDE <CTYPE.H>

INT MAIN()
{
    FOR(;;)
    {
        INT C = GETCHAR();
        IF (C == EOF) BREAK;
        PRINTF("%C", (CHAR)TOUPPER(C));
    }
    RETURN 0;
}
$ 
```

```
$ echo hello 
hello
$ echo hello > hello.txt
$ cat hello.txt
hello
$ 
```

## パイプを用いたプロセス間通信

```
$ gcc pip_p.c -o pip_p
$ gcc pip_c.c -o pip_c
$ ./pip_p
apple
apple <-> 5
$ 
```

* 用語  
バッファ：貯水槽的なイメージでデータを貯めたり出したりする  
パイプ：バッファとプロセスをつないで、データをやり取りする道（書き込み用と読み込み用で別の道を使う）







