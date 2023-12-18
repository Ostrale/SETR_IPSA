#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int a, b, result;
    if (argc != 3)
    {
        printf("Usage: %s <a> <b>\n", argv[0]);
        return 1;
    }
    a = atoi(argv[1]);
    b = atoi(argv[2]);
    if (a > b){
        printf("%d > %d\n", a, b);
    } else if (a < b){
        printf("%d < %d\n", a, b);
    } else {
        printf("%d = %d\n", a, b);
    }
}