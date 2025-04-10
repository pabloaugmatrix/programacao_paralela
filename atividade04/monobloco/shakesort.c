#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

void troca(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void ShakeSort(int A[], int n)
{
    int e = 1;
    int i, j;

    while (e < n)
    {
        for (i = n - 1; i >= e; i--)
        {
            for (j = e; j <= i; j++)
            {
                if (A[j] > A[j + 1])
                {
                    troca(&A[j], &A[j + 1]);
                }
            }
            for (j = i; j >= e + 1; j--)
            {
                if (A[j - 1] > A[j])
                {
                    troca(&A[j - 1], &A[j]);
                }
            }
        }
        e = e + 1;
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Uso correto: %s <qnt_elementos> <nomearquivo>.txt\n", argv[0]);
        exit(1);
    }

    struct timeval inicio, fim;
    double tempo_decorrido;
    int quantidade = atoi(argv[1]);
    int *numeros = (int *)malloc(quantidade * sizeof(int));
    if (numeros == NULL)
    {
        perror("Erro ao alocar memória.");
        exit(1);
    }

    char filename[100];
    snprintf(filename, sizeof(filename), "%s", argv[2]);
    printf("_________________________________________________________\n");
    printf("SHAKESORT MONOBLOCO:\n");
    printf("Arquivo: %s\nQnt elementos: %d\n", filename, quantidade);

    FILE *arquivo = fopen(filename, "r");
    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo");
        free(numeros);
        exit(1);
    }

    for (int i = 0; i < quantidade; i++)
    {
        if (fscanf(arquivo, "%d", &numeros[i]) != 1)
        {
            fprintf(stderr, "Erro ao ler número %d do arquivo.\n", i);
            free(numeros);
            fclose(arquivo);
            exit(1);
        }
    }

    fclose(arquivo);

    gettimeofday(&inicio, NULL);
    ShakeSort(numeros, quantidade - 1);
    gettimeofday(&fim, NULL);
    tempo_decorrido = (fim.tv_sec - inicio.tv_sec) + (fim.tv_usec - inicio.tv_usec) / 1e6;
    printf("Tempo: %lf segundos\n", tempo_decorrido);

    free(numeros);
    return 0;
}
