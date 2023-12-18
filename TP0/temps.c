#include <stdio.h>
#include <time.h>

int main()
{
    int temps = -1;
    while (1)
    {
        if (clock()/CLOCKS_PER_SEC > temps){
            temps = clock()/1000000;
            printf("Temps: %d\n", temps);
        }
    }
    
    return 0;
}