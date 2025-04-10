#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <omp.h>

void troca(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void ShakeSort(int A[], int n)
{
    int e = 0;
    int i = n - 1;

    while (e < i)
    {

#pragma omp parallel for
        for (int j = e; j < i; j++)
        {
            if (A[j] > A[j + 1])
            {
#pragma omp critical
                troca(&A[j], &A[j + 1]);
            }
        }

        i--;

#pragma omp parallel for
        for (int j = i; j > e; j--)
        {
            if (A[j - 1] > A[j])
            {
#pragma omp critical
                troca(&A[j - 1], &A[j]);
            }
        }

        e++;
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
    printf("SHAKESORT OPENMP:\n");
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
