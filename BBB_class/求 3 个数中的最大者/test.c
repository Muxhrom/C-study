#include <stdio.h>

int a, b, c, max;

int max_f()
{
    scanf_s("%d,%d,%d",&a,&b,&c);
    if (a>b) max = a;
    else max = b;
    if (max<c) max = c;
    printf("%d",max);
    return 0;
}

int main()
{
    max_f();
    return 0;
}
