## 絶対パスしていしなくて良いシェルをつくってみる

* getenv(const char* name)：指定した環境変数を得る
* strtok(char* s, const char* t)：文字列sを 文字tで区切る

```
$ ./shell
--> ls
README.md  shell  shell.c
--> pwd
/home/mochikun/C/linux/220503
--> ^C
$ 
```


特に説明することはないが、カンマ演算子について

カンマ演算子は前から順番に式を評価し、一番最後の式の値を返す。

```
$ ./comma
x[5]
i[9]
y[5]
```

あまり使いどころがなさそうだけど
```
while((printf("x = "), scanf("%d", &x)) == 1)
{
    // xがうまく入力できた時の処理
}
```
みたいに書くと意外と使えなくもなさそう
