#include <stdio.h>
#include <ctype.h>

int main()
{
    for(;;)
    {
        int c = getchar();
        if (c == EOF) break;
        printf("%c", (char)toupper(c));
    }
    return 0;
}
