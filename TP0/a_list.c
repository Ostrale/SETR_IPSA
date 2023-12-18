#include <stdio.h>

int main(int argc, char *argv[])
{
    int a_list[] = {25, 50, 75, 100, 125, 150, 175, 200};

    int chiffre_a_trouver;
    printf("Entrez un chiffre: ");
    scanf("%d", &chiffre_a_trouver);

    int find = 0;
    for (int i = 0; i < 8; i++)
    {
        if (a_list[i] == chiffre_a_trouver)
        {
            printf("Trouvé, il est à l'index %d\n", i);
            find = 1;
        }
    }
    if (find == 0)
    {
        printf("Pas trouvé\n");
    }
    return 0;
}