#include <stdio.h>
#include <unistd.h>

int main()
{
    execl("/bin/ls", "/bin/ls", "-l", NULL);
    printf("これは表示されない");
}