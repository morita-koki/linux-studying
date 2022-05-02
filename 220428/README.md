### コピーじゃないプロセスをつくってみる

* execlやexecvを使う
```
$ ./execl
(ディレクトリの中身がいろいろ表示される)
$
```
execlによって呼び出されたプログラム（今回の場合はls）にプロセスが上書きされる。  
<br>
* 簡単なシェルを作る
```
$ ./simple_shell
> /bin/ls
(ディレクトリ内の中身が表示される)
> /bin/pwd
(今の場所が表示される)
> ^C
$ 
```
waitで子プロセスの終了を待っている。子プロセスがexit(0)で終了するとstには0がセットされる。