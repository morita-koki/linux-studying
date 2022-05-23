## 名前付きパイプ

* FIFO: First In First Outのデータ構造

FIFOファイル、、、通常のファイルと同様にファイルシステムで管理されている  
-> 書き込みでオープンされているとき、別のプロセスから書き込みでオープンすることはできない。

### 特徴
* FIFOという特殊なファイルを介する
* どんなプロセス間でも通信可能
* 非同期で単方向のみ
* 書き込みや読み込みは一つのプロセスからだけ


```
$ gcc npip_client.c -o npip_client
$ gcc npip_server.c -o npip_server
$ ls
README.md  npip_client  npip_client.c  npip_server  npip_server.c
$
```

```
$ ./npip_server
client: Apple
client: banana
client: so hot today
^C
$
```

```
$ ./npip_client
Apple
Apple <-> 5
banana
banana <-> 6
so hot today
so hot today <-> 12
^C
$
```
