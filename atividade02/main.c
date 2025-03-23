// Pablo Augusto Matos da Silva
// Matricula : 2022015139
// Benchmark dos Algoritmos de Soma Máxima de Subsequência

/// TODO: comentar codigo para melhor legibilidade

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE (1024 * 8)

// Variável global para contar operações
long long operacoes = 0;

// Algoritmos de soma máxima com contagem de operações
int Somax2(int A[], int n)
{
    int max = 0, aux;
    operacoes = 0;

    for (int i = 0; i < n; i++)
    {
        aux = 0;
        for (int j = i; j < n; j++)
        {
            aux += A[j];
            operacoes++; // Conta a soma
            if (aux > max)
            {
                max = aux;
                operacoes++; // Conta a comparação
            }
        }
    }
    return max;
}

int Somax3(int A[], int e, int d)
{
    if (e == d)
    {
        operacoes++;
        return A[e] > 0 ? A[e] : 0;
    }

    int Lim = (e + d) / 2;
    int Esq = Somax3(A, e, Lim);
    int Dir = Somax3(A, Lim + 1, d);
    int E_Lim = 0, D_Lim = 0, aux_E = 0, aux_D = 0;

    for (int i = Lim; i >= e; i--)
    {
        aux_E += A[i];
        operacoes++; // Conta a soma
        if (aux_E > E_Lim)
        {
            E_Lim = aux_E;
            operacoes++; // Conta a comparação
        }
    }

    for (int i = Lim + 1; i <= d; i++)
    {
        aux_D += A[i];
        operacoes++; // Conta a soma
        if (aux_D > D_Lim)
        {
            D_Lim = aux_D;
            operacoes++; // Conta a comparação
        }
    }

    operacoes++;
    return (Esq > Dir) ? (Esq > (E_Lim + D_Lim) ? Esq : (E_Lim + D_Lim))
                       : (Dir > (E_Lim + D_Lim) ? Dir : (E_Lim + D_Lim));
}

int wrapper_Somax3(int *A, int n)
{
    operacoes = 0;
    return Somax3(A, 0, n - 1);
}

int Somax4(int A[], int n)
{
    int max = 0, aux = 0;
    operacoes = 0;

    for (int i = 0; i < n; i++)
    {
        aux += A[i];
        operacoes++; // Conta a soma

        if (aux > max)
        {
            max = aux;
            operacoes++; // Conta a comparação
        }
        else if (aux < 0)
        {
            aux = 0;
            operacoes++; // Conta a atribuição
        }
    }
    return max;
}

void testar_algoritmo(int (*algoritmo)(int *, int), char *nome, int *sequencia, int n)
{
    clock_t inicio, fim;
    double tempo_gasto;

    operacoes = 0; // Zerar contador
    inicio = clock();
    int resultado = algoritmo(sequencia, n);
    fim = clock();
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("%s -> Resultado: %d | Tempo: %.6f s | Operações: %lld\n",
           nome, resultado, tempo_gasto, operacoes);
}

int main()
{
    int *sequencia;
    int n = 1024;
    int numero_arquivo = 1;
    char nome_arquivo[20];
    FILE *arquivo;

    while (n <= MAX_SIZE)
    {

        if (numero_arquivo == 2)
        {
            numero_arquivo *= 2;
            n *= 2;
            continue;
        }

        sprintf(nome_arquivo, "%dM.dat", numero_arquivo);

        arquivo = fopen(nome_arquivo, "r");
        if (!arquivo)
        {
            perror("Erro ao abrir o arquivo");
            return 1;
        }

        sequencia = (int *)malloc(n * sizeof(int));
        if (sequencia == NULL)
        {
            perror("Erro ao alocar memória");
            fclose(arquivo);
            return 1;
        }

        size_t i = 0;
        while (i < n && fscanf(arquivo, "%d", &sequencia[i]) == 1)
        {
            i++;
        }
        fclose(arquivo);

        printf("Arquivo: %s | Tamanho: %d\n", nome_arquivo, n);

        testar_algoritmo(Somax2, "Força Bruta O(n²)", sequencia, n);
        testar_algoritmo(wrapper_Somax3, "Divisão e Conquista O(n log n)", sequencia, n);
        testar_algoritmo(Somax4, "Kadane O(n)", sequencia, n);

        printf("\n");

        free(sequencia);

        n *= 2;
        numero_arquivo *= 2;
    }

    return 0;
}
