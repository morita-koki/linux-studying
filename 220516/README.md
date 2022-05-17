# プロセス間通信

### 復習
* プロセス：プログラムの実行単位
* psコマンドで確認できる

### 本題

* プロセスは独立しているため、プロセスから異なるプロセスの情報にはアクセスできない

* 同じPCのプロセス同士の通信と異なるPCのプロセス同士の通信の2種類ある。後者はClientとServerの通信が代表的

### キーワード
* シグナル
* パイプ（名前なし）
* パイプ（名前付き）
* 共有メモリ
* ソケット

<br>

## シグナル
* 非同期に単方向へ送信
* シグナルの種類に応じてシグナルハンドラを設定できる

## パイプ（名前なし）
* 親子関係のプロセスにおいて非同期に単方向へ送信
* バッファを介す
* 読み込みはひとつのプロセスからだけ

## パイプ（名前付き）
* 親子関係にないプロセスでも非同期に単方向へ送信
* FIFOという特殊ファイルを介す
* 使わなくなったら削除が必要
* 読み込みはひとつのプロセスからだけ

## 共有メモリ
* j複数のプロセス間で共有するメモリを作成し、各プロエスがアクセスする
* 処理が複雑になりやすい
* 使わなくなったら削除が必要
* 処理速度が速いが安定性に注意が必要

## ソケット
* 異なるPC間のプロセスの双方向通信が可能