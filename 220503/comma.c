#include <stdio.h>

int main()
{
    int x = (1, 2, 3, 4, 5);
    printf("x[%d]\n",x);

    int i = 0;
    int y = (i++, i+=2, i*=3, 5);
    printf("i[%d]\n",i);
    printf("y[%d]\n",y);
}