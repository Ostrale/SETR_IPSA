#include <stdio.h>

int main(int argc, char *argv[])
{
    int a_list[] = {25, 50, 75, 100, 125, 150, 175, 200, 225};

    int chiffre_a_trouver;
    printf("Entrez un chiffre: ");
    scanf("%d", &chiffre_a_trouver);

    int find = 0;
    int min = 0;
    int max = 8;
    int mid = (min + max) / 2;
    while (min <= max)
    {
        if (a_list[mid] < chiffre_a_trouver)
        {
            min = mid + 1;
        }
        else if (a_list[mid] == chiffre_a_trouver)
        {
            printf("Trouvé, il est à l'index %d\n", mid);
            find = 1;
            break;
        }
        else
        {
            max = mid - 1;
        }
        mid = (min + max) / 2;
    }
    if (find == 0)
    {
        printf("Pas trouvé\n");
    }
    return 0;
}