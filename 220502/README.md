## 「PATHを通す」とは

* *環境変数*：利用している端末の情報が格納されている
* *端末*：シェル（ターミナル）のこと。

一つのPCに複数端末つないで使うことも。授業で大学のサーバ-にログインしている状態。それぞれの端末で環境変数が異なる。

* envコマンド：環境変数一覧が見れる
```
$ env 
SHELL=/bin/bash
WSL_DISTRO_NAME=Ubuntu-20.04
PWD=/home/mochikun/C/linux/220502
:
USER=mochikun
:
$ 
```

* echoコマンド：指定した環境変数が見れる
```
$ echo %USER
mochikun
$ 
``` 
先頭に*$*を付けることで般教変数を示す。

早速PATHを見る
```
$ echo $PATH
/home/mochikun/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Program Files (x86)/Common Files/Apple/Apple Application Support:/mnt/c/WINDOWS/system32:/mnt/c/WINDOWS:/mnt/c/WINDOWS/System32/Wbem:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/:/mnt/c/WINDOWS/System32/OpenSSH/.....
.....
$
```
*:* で区切られている。
/usr/local/sbinや/usr/local/binがある。
コマンドを実行するとき、このPATHの中にあるディレクトリ内にあるコマンドを実行する。

どんなコマンドがあるか/usr/binの中を見てみる
```
$ ls /usr/bin
:
apt-get
:
base32
base64
basename
bash
:
:
cat
:
emacs
:
env
:
:

$
```

*./* を付けなくても実行できるコマンドはすべてPATHに指定されているディレクトリの中にある。


試しにPATHをカレントディレクトリのみに変更してみる
```
$ echo $PATH
(PATH一覧が表示される)
$ PATH=.
$ ls
Command 'ls' is available in the following places
 * /bin/ls
 * /usr/bin/ls
The command could not be located because '/bin:/usr/bin' is not included in the PATH environment variable.
ls: command not found
$
```

メッセージは多少異なるかもしれないが、コマンドが見つからない旨が表示されているはず。
安心してください、一度ログアウトすれば元に戻ります。

おまけ：
ホームディレクトリ以下の.bashrcファイルに
```
export PATH=$PATH:(追加したいPATH)
```
とすればPATHを追加することができる
*※PATHにカレントディレクトリを追加するのは良くない。例えば外部からインストールしたファイルの中にlsという名前の悪意ある実行ファイルがあったとき、それが実行されてしまう*  
  
