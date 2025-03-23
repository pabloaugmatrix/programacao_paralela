/// TODO: criar struct para retornar maximo e limites para adaptar retorno das funções
/// TODO: implementar main e calcular o desempenho de cada uma das funções

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE (1024 * 8)

/// @brief Encontra o valor máximo da soma de uma subsequência contígua no vetor
/// utilizando uma abordagem de força bruta com complexidade T(n) = O(n²).
///
/// A solução testa cada elemento como ponto de partida e acumula a soma ao longo dos subsequentes,
/// armazenando a maior soma encontrada.
///
/// @param A Vetor de inteiros
/// @param n Numero de elementos
/// @return Valor maximo da soma de uma subsequencia contida no vetor
int Somax2(int A[], int n)
{
    int max = 0;
    int aux;
    for (int i = 0; i < n; i++)
    {
        aux = 0;
        for (int j = i; j < n; j++)
        {
            aux += A[j];
            if (aux > max)
            {
                max = aux;
            }
        }
    }
    return max;
}

/// @brief compara 3 numeros inteiros para definir qual o maior
/// @param valor1 numero inteiro
/// @param valor2 numero inteiro
/// @param valor3 numero inteiro
/// @return O maior valor dentre 3 numeros inteiros
int Maximo(int valor1, int valor2, int valor3)
{
    if (valor1 > valor2 && valor1 > valor3)
    {
        return valor1;
    }
    if (valor2 > valor1 && valor2 > valor3)
    {
        return valor2;
    }
    if (valor3 > valor1 && valor3 > valor2)
    {
        return valor3;
    }
}

/// @brief Calcula o valor máximo da soma de uma subsequência contida no vetor usando abordagem de Divisão e Conquista, com complexidade T(n) = O(n log n).
///
/// A função divide o vetor em duas partes e calcula a soma máxima de três formas possíveis:
/// 1. A subsequência de soma máxima está totalmente à esquerda.
/// 2. A subsequência de soma máxima está totalmente à direita.
/// 3. A subsequência de soma máxima atravessa o meio do vetor.
///
/// @param A Vetor de inteiros
/// @param e Índice inicial da subparte do vetor considerada
/// @param d Índice final da subparte do vetor considerada
/// @return Valor máximo da soma de uma subsequência contida no vetor
int Somax3(int A[], int e, int d)
{
    int E_Lim = 0, D_Lim = 0, aux_E = 0, aux_D = 0;
    int Lim = ((e + d) / 2);
    int Esq, Dir;
    if (e == d)
    {
        if (A[e] > 0)
        {
            return A[e];
        }
        return 0;
    }
    Esq = Somax3(A, e, Lim);
    Dir = Somax3(A, Lim + 1, d);
    for (int i = Lim; i >= e; i--) // pode ser que essa linha de problema na condição de parada
    {
        aux_E += A[i];
        if (aux_E > E_Lim)
        {
            E_Lim = aux_E;
        }
    }
    for (int i = Lim + 1; i <= d; i++) // mesmo problema do laço anterior
    {
        aux_D += A[i];
        if (aux_D > D_Lim)
        {
            D_Lim = aux_D;
        }
    }
    return Maximo(Esq, Dir, (E_Lim + D_Lim));
}

/// @brief Calcula o valor máximo da soma de uma subsequência contígua dentro do vetor,
/// utilizando o Algoritmo de Kadane, com complexidade O(n).
///
/// O algoritmo percorre o vetor uma única vez, mantendo um acumulador da soma parcial.
/// Se a soma parcial for negativa, é descartada e reiniciada a partir do próximo elemento.
///
/// @param A Vetor de inteiros
/// @param n Numero de elementos
/// @return Valor máximo da soma de uma subsequência contígua dentro do vetor
int Somax4(int A[], int n)
{
    int max = 0, aux = 0, j = 0, k = 0;
    int ini = 1, fim = 1;
    for (int i = 0; i < n; i++)
    {
        aux += A[i];
        k += 1;
        if (n == 0)
        {
            max = aux;
            fim = k;
        }
        else if (aux < 0)
        {
            aux = 0;
            j = i + 1;
            k = i + 1;
            ini = j;
        }
    }
    return max;
}

/// @brief Função para ler os números do arquivo e armazená-los no vetor
/// @param sequencia Vetor de inteiros onde os números serão armazenados
/// @param n Número máximo de elementos a serem lidos
/// @param nome_arquivo Nome do arquivo a ser lido
/// @param arquivo Ponteiro para o arquivo a ser lido
void ler_arquivo(int *sequencia, int n, char nome_arquivo[], FILE *arquivo) {
    size_t i = 0;
    while (i < n && fscanf(arquivo, "%d", &sequencia[i]) == 1) {
        i++;
    }
    /*
    printf("Arquivo: %s | Lidos %zu números:\n", nome_arquivo, i);
    for (size_t j = 0; j < i; j++) {
        printf("%d ", sequencia[j]);
    }
    printf("\n");
    */
}

int main() {
    int *sequencia;
    int n = 1024;
    int numero_arquivo = 1;
    char nome_arquivo[20];
    FILE *arquivo;

    while (n <= MAX_SIZE) {
        if (numero_arquivo == 2) {
            numero_arquivo *= 2;
            n *= 2;
            continue;
        }

        sprintf(nome_arquivo, "%dM.dat", numero_arquivo);

        arquivo = fopen(nome_arquivo, "r");  // MODO TEXTO
        if (!arquivo) {
            perror("Erro ao abrir o arquivo");
            return 1;
        }

        sequencia = (int *)malloc(n * sizeof(int));
        if (sequencia == NULL) {
            perror("Erro ao alocar memória");
            fclose(arquivo);
            return 1;
        }

        // Chamada da função para ler o arquivo corretamente
        ler_arquivo(sequencia, n, nome_arquivo, arquivo);

        free(sequencia);
        fclose(arquivo);

        n *= 2;
        numero_arquivo *= 2;
    }

    return 0;
}
