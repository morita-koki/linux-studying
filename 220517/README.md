# シグナル

非同期イベントをプロセスへ通知するための仕組み

* 非同期に単方向へ送信とは  
例えば、誤って無限ループに入ってしまったとき、Ctrl+Cを押してプログラムを終了する。このとき、無限ループを行っているプロセスはシグナル（SIGINT）を受け取ってプロセスを終了する

* シグナルの動作
1. プロセス開始
2. 非同期シグナル発生&プロセスに通知
3. 処理を中断
4. プロセスは受け取ったシグナルに対応するシグナルハンドラを実行する 
5. 処理を再開

```
$ ./time_c
..........^C
signal number=2, time=10
$ 
```
確かにCtrl+Cの後にstop関数が呼ばれている

kill -l コマンドで使えるシグナルが確認できる
```
$ kill -l 
 1) SIGHUP       2) SIGINT       3) SIGQUIT      4) SIGILL       5) SIGTRAP
 6) SIGABRT      7) SIGBUS       8) SIGFPE       9) SIGKILL     10) SIGUSR1
11) SIGSEGV     12) SIGUSR2     13) SIGPIPE     14) SIGALRM     15) SIGTERM
16) SIGSTKFLT   17) SIGCHLD     18) SIGCONT     19) SIGSTOP     20) SIGTSTP
21) SIGTTIN     22) SIGTTOU     23) SIGURG      24) SIGXCPU     25) SIGXFSZ
26) SIGVTALRM   27) SIGPROF     28) SIGWINCH    29) SIGIO       30) SIGPWR
31) SIGSYS      34) SIGRTMIN    35) SIGRTMIN+1  36) SIGRTMIN+2  37) SIGRTMIN+3
38) SIGRTMIN+4  39) SIGRTMIN+5  40) SIGRTMIN+6  41) SIGRTMIN+7  42) SIGRTMIN+8
43) SIGRTMIN+9  44) SIGRTMIN+10 45) SIGRTMIN+11 46) SIGRTMIN+12 47) SIGRTMIN+13
48) SIGRTMIN+14 49) SIGRTMIN+15 50) SIGRTMAX-14 51) SIGRTMAX-13 52) SIGRTMAX-12
53) SIGRTMAX-11 54) SIGRTMAX-10 55) SIGRTMAX-9  56) SIGRTMAX-8  57) SIGRTMAX-7
58) SIGRTMAX-6  59) SIGRTMAX-5  60) SIGRTMAX-4  61) SIGRTMAX-3  62) SIGRTMAX-2
63) SIGRTMAX-1  64) SIGRTMAX
$ 
```
※使えるシグナルはLinuxによって異なる。
※いろんなシグナルがあるが、中にはシグナルハンドラの変更や無視ができないものもある。
（あらゆるシグナルを無視するプロセスができかねない）

* kill コマンドで本当にシグナルを送れるか試す
```
$ sleep 60 &
[1] 3959
$ ps
  PID TTY          TIME CMD
 1666 pts/1    00:00:00 bash
 3959 pts/1    00:00:00 sleep
 3963 pts/1    00:00:00 ps
$ kill -9 3959
$ ps
  PID TTY          TIME CMD
 1666 pts/1    00:00:00 bash
 3982 pts/1    00:00:00 ps
[1]+  強制終了            sleep 60
$ 
```

kill -(送りつけるシグナル) (送信先のプロセスID)


* プログラムからシグナルを送る
```
$ sleep 60 &
[1] 4769
$ ./sig_kill 4769
[1]+  強制終了            sleep 60
$ 
```

* SIGALRMシグナルで自分自身にシグナルを投げる
```
$ ./stop_watch 10
Count 10 Seconds
Ready... Go!
1 2 3..
Press Enter to Stop.

your count is 13.899
$ 
```









