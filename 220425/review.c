#include <stdio.h>

struct human
{
    int age;
    double height;
    char name[20];
};

int main(int argc, char* argv[])
{
    struct human Sato = { 20, 170, "Sato" };

    printf("%d, %.1lf, %s\n", Sato.age, Sato.height, Sato.name);

    struct human* cp = &Sato;
    cp->age = 30;

    printf("%d, %.1lf, %s\n", Sato.age, Sato.height, Sato.name);
}