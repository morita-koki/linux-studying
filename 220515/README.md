## パーミッションの見方

10文字の文字列で表される  
（ファイルorディレクトリ）（所有者権限）（グループ権限）（その他）の順番で表される

先頭1文字
* d : ディレクトリ
* \- : ファイル


### ファイルの場合
* r : ファイルの意味込み許可
* w : ファイルの書き込み許可
* x : ファイルの実行許可

### ディレクトリの場合
* r : ディレクトリ内の閲覧権限
* w : ディレクトリ内でファイルを作成、削除権限
* x : ディレクトリ内に侵入する権限、path指定による読み込み権限

## 確認してみる

```
$ ./sample.c
-bash: ./sample.c: 許可がありません
$ ls -l
合計 8
-rw-r--r-- 1 mochikun mochikun 632  5月 15 23:51 README.md
-rw-r--r-- 1 mochikun mochikun  72  5月 15 23:51 sample.c
$ 
```
確かに実行権限がない。  


## 権限を変更してみる

```
$ touch hoge.txt
# ls -l
(省略省略)
-rw-r--r-- 1 mochikun mochikun   0  5月 15 23:55 hoge.txt
(省略)
$ chmod g+w hoge.txt
$ ls -l
(省略)
-rw-rw-r-- 1 mochikun mochikun   0  5月 15 23:55 hoge.txt
(省略)
$ 
```
確かにグループの書き込み権限が追加されている

* chmodコマンド  
Usage 
```
$ chmod [ugo][+/-][rwx] file_name
```

u : User  
g : Group  
o : Others

\+ : 権限の付与  
\- : 権限の削除

r : read  
w : write  
x : execute  


ex ) 
* chmod o+rwx file_name
* chmod u-wx file_name  

<br>

2進3桁(0~7)を3つ並べて権限を変更することもできる

ex ) 
* chmod 777 file_name




