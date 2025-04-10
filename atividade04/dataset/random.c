#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_MIN 1024       // 2¹⁰
#define N_MAX 1073741824 // 2³⁰

int main()
{
    FILE *file;
    int n = N_MIN;
    char filename[32];
    char buffer[32];
    srand(262016);

    while (n <= N_MAX)
    {
        sprintf(filename, "%d.txt", n);
        printf("%s\n", filename);

        file = fopen(filename, "w");
        if (!file)
        {
            perror("Erro ao abrir o arquivo");
            return 1;
        }

        fprintf(file, "%d\n", n);

        // Escreve n números aleatórios
        for (int i = 0; i < n; i++)
        {
            int r = rand();
            fprintf(file, "%d\n", r);
        }

        fclose(file);

        if (n == N_MAX)
            break;

        n *= 16;
    }

    return 0;
}
