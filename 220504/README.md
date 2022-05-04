## プロセスについてもうちょっと探る

* psコマンド：-laxオプションを付けることですべてのプロセスを表示する
* PID：プロセスID
* PPID：親プロセスのID
```
$ ps -lax
F   UID   PID  PPID PRI  NI    VSZ   RSS WCHAN  STAT TTY        TIME COMMAND
4     0     1     0  20   0   1168   780 -      Sl   ?          0:00 /init
5     0     9     1  20   0   1252   360 -      Ss   ?          0:00 /init
1     0    10     9  20   0   1260   360 -      R    ?          0:00 /init
4  1000    11    10  20   0  10292  5252 do_wai Ss   pts/0      0:00 -bash
5     0  1249     1  20   0   1256   364 -      Ss   ?          0:00 /init
1     0  1250  1249  20   0   1256   364 -      S    ?          0:00 /init
4  1000  1251  1250  20   0   2612   536 do_wai Ss+  pts/1      0:00 sh -c "$VSCODE_WSL_EXT_LOCATION/scripts/wslServer.sh" dfd34e
0  1000  1252  1251  20   0   2612   536 do_wai S+   pts/1      0:00 sh /mnt/c/Users/morit/.vscode/extensions/ms-vscode-remote.re
0  1000  1257  1252  20   0   2612   600 do_wai S+   pts/1      0:00 sh /home/mochikun/.vscode-server/bin/dfd34e8260c270da74b5c2d
0  1000  1261  1257  20   0 931808 68540 -      Sl+  pts/1      0:03 /home/mochikun/.vscode-server/bin/dfd34e8260c270da74b5c2d86d
0  1000  1272  1261  20   0 620388 43476 -      Sl+  pts/1      0:00 /home/mochikun/.vscode-server/bin/dfd34e8260c270da74b5c2d86d
5     0  1307     1  20   0   1264   364 -      Ss   ?          0:00 /init
1     0  1308  1307  20   0   1264   372 -      S    ?          0:00 /init
4  1000  1309  1308  20   0 519720 38536 do_epo Ssl+ pts/2      0:00 /home/mochikun/.vscode-server/bin/dfd34e8260c270da74b5c2d86d
5     0  1317     1  20   0   1264   364 -      Ss   ?          0:00 /init
1     0  1318  1317  20   0   1264   372 -      S    ?          0:00 /init
4  1000  1319  1318  20   0 582192 37460 do_epo Ssl+ pts/3      0:01 /home/mochikun/.vscode-server/bin/dfd34e8260c270da74b5c2d86d
0  1000  1326  1261  20   0 834272 44372 -      Sl+  pts/1      0:00 /home/mochikun/.vscode-server/bin/dfd34e8260c270da74b5c2d86d
0  1000  1379  1261  20   0 836024 98564 -      Sl+  pts/1      0:05 /home/mochikun/.vscode-server/bin/dfd34e8260c270da74b5c2d86d
0  1000  1442    11  20   0  10540  3004 -      R+   pts/0      0:00 ps -lax
$ 
```

たくさんプロセスが表示されたが、基本的に一つのCPUは一つのプロセスしか実行できない。
なので、複数プロセスを実行する場合、実行するプロセスを時間割で切り替えて管理している。  
プロセスの状態は大きく4つ。
* 実行中
* 実行可能
* スリープ
* ゾンビ

