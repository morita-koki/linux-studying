## プロセスの状態は大きく4つ
* 実行中
* 実行可能
* スリープ
* ゾンビ

ps -laxを実行した時のSTATでプロセスの状態を確認できる

R：実行中・実行可能  
S：スリープ（割り込み可能）  
D：スリープ（割り込み不可能）  
Z：ゾンビ  

```
$ ./zomb &
[1] 479
$ ps -lax
F   UID   PID  PPID PRI  NI    VSZ   RSS WCHAN  STAT TTY        TIME COMMAND
:
0  1000   479    11  20   0   2360   580 hrtime S    pts/0      0:00 ./zomb
1  1000   480   479  20   0      0     0 -      Z    pts/0      0:00 [zomb] <defunct>
0  1000   481    11  20   0  10540  3064 -      R+   pts/0      0:00 ps -lax
$ 
```

確かにゾンビ状態のプロセスがある

## 親プロセスが子プロセスより先に終了した場合

親プロセスが子プロセスより先に終了した場合、その子プロセスはゾンビ状態をならず、
その子プロセスの親プロセスがsystemdプロセスに変更され、子プロセスの終了を確認する。


```
$ ./ppid &
[1] 742
$ ps -lax
F   UID   PID  PPID PRI  NI    VSZ   RSS WCHAN  STAT TTY        TIME COMMAND
4     0     1     0  20   0   1168   788 -      Sl   ?          0:00 /init
:
0  1000   742    11  20   0   2492   516 do_sig T    pts/0      0:00 ./ppid
1  1000   743   742  20   0   2360    80 do_sig T    pts/0      0:00 ./ppid
0  1000   744    11  20   0  10540  3104 -      R+   pts/0      0:00 ps -lax
$ fg
./ppid
(Enterを押す)
親プロセス終了
$ ps -lax
F   UID   PID  PPID PRI  NI    VSZ   RSS WCHAN  STAT TTY        TIME COMMAND
:
1     0    10     9  20   0   1260   356 -      R    ?          0:00 /init
:
1  1000   743    10  20   0   2360    80 hrtime S    pts/0      0:00 ./ppid
0  1000   745    11  20   0  10540  3072 -      R+   pts/0      0:00 ps -lax
$ 子プロセス終了（20秒後）
$
```

確かに./ppidの子プロセスのPPIDが10（/init）になっている。


