// Write, compile and execute a code to assign a value to a variable and print its value and its memory address

#include <stdio.h>

int main()
{
    int a; 
    printf("Enter a number (int): ");
    scanf("%d", &a);
    printf("a = %d\n", a);
    printf("a address = %p\n", &a);
    return 0;
}