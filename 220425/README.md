### C言語復習

* 静的型付け言語
```
char s;
int t;
double d;
...
```

* ポインタ変数
```
int a = 0;
int p = &a;
*p += 5;
```
ポインタ変数はアドレスを格納する。


* 構造体
```
struct human
{
    int age;
    double height;
    double weight;
    char* firstName;
    char* lastName;
    ...
}
```
異なるデータ型の変数をひとまとまりにできる。

* 線形リスト
```
struct humanList
{
    int age;
    char* firstName;
    char* lastName;
    struct humanList* next;
}
```
構造体に次のデータのアドレスをポインタ変数として持たせる

* コマンドライン引数
```
int main(int argc, char* argv[]){
    printf("%d\n", argc);
    for (int i = 0; i < argc; ++i)
    {
        printf("%s ", argv[i]);
    }
}
```

```
$ ./a.out hoge sample ababa
4
./a.out hoge sample ababa
```
main関数の引数を指定することでコマンドライン引数を設定できる