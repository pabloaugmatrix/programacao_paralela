#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

#define MAX_NIVEL 2 

void Intercala(int A[], int e, int m, int d)
{
    int *B = (int *)malloc((d - e + 1) * sizeof(int));
    if (B == NULL)
    {
        perror("Erro ao alocar vetor auxiliar B");
        exit(1);
    }

    for (int i = e; i <= m; i++)
    {
        B[i - e] = A[i];
    }

    for (int j = m + 1; j <= d; j++)
    {
        B[d + m + 1 - j - e] = A[j];
    }

    int i = 0;
    int j = d - e;
    for (int k = e; k <= d; k++)
    {
        if (B[i] <= B[j])
        {
            A[k] = B[i++];
        }
        else
        {
            A[k] = B[j--];
        }
    }

    free(B);
}

void MergeSort(int A[], int e, int d, int nivel)
{
    if (e < d)
    {
        int m = (e + d) / 2;

        if (nivel < MAX_NIVEL)
        {
#pragma omp task firstprivate(A, e, m, nivel)
            MergeSort(A, e, m, nivel + 1);

#pragma omp task firstprivate(A, m, d, nivel)
            MergeSort(A, m + 1, d, nivel + 1);

#pragma omp taskwait
        }
        else
        {
            MergeSort(A, e, m, nivel);
            MergeSort(A, m + 1, d, nivel);
        }

        Intercala(A, e, m, d);
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
    printf("MERGESORT OPENMP:\n");
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
#pragma omp parallel
    {
#pragma omp single
        MergeSort(numeros, 0, quantidade - 1, 0);
    }
    gettimeofday(&fim, NULL);

    tempo_decorrido = (fim.tv_sec - inicio.tv_sec) + (fim.tv_usec - inicio.tv_usec) / 1e6;
    printf("Tempo: %lf segundos\n", tempo_decorrido);

    free(numeros);
    return 0;
}
