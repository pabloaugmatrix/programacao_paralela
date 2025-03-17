// Pablo Augusto Matos da Silva
// 2022015139

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define A_REAL 2.5  // Inclinação real da reta
#define B_REAL 15.0 // Intercepto real da reta

// Produto escalar
double multXY(int n, double *x, double *y)
{
    double multXY = 0;
    for (int i = 0; i < n; i++)
    {
        multXY += x[i] * y[i];
    }
    return multXY;
}

// Soma elementos
double somX(int n, double *x)
{
    double somX = 0;
    for (int i = 0; i < n; i++)
    {
        somX += x[i];
    }
    return somX;
}

// Soma quadrados
double dobraX(int n, double *x)
{
    double dobraX = 0;
    for (int i = 0; i < n; i++)
    {
        dobraX += x[i] * x[i];
    }
    return dobraX;
}

int main()
{
    // Setup para o experimento
    srand(262016);
    clock_t inicio, fim;
    double tempo_decorrido, tempo_medio;
    int repeticoes = 100000;
    int n = 128; // Valor inicial de elementos sugerido pelo professor (2⁷)

    // Variaveis referentes ao calculo da regressão linear
    double a, b;   // Inclinação e intercepto
    double *x, *y; // vetores de pontos

    /*
    O seguinte laço garante um numero de repetições para a medição
    de tempo como forma de obter uma consideravel amostragem
    */
    while (n <= 32768)
    {

        // Alocação dinamica de memoria para os vetores
        x = (double *)malloc(n * sizeof(double));
        y = (double *)malloc(n * sizeof(double));

        // Gera números x e y com dependência linear
        for (int i = 0; i < n; i++)
        {
            x[i] = (rand() % (990 - 100 + 1) + 100) / 10.0;                  // No intervalo [10.0, 99.0]
            y[i] = A_REAL * x[i] + B_REAL + ((rand() % 201 - 100) / 1000.0); // Relação linear com ruído
        }

        // O seguinte laço garante um numero de repetições para a medição de tempo como forma de obter uma consideravel amostragem
        tempo_medio = 0;
        for (int i = 0; i < repeticoes; i++)
        {
            inicio = clock(); // Inicio do calculo

            a = (n * multXY(n, x, y) - somX(n, x) * somX(n, y)) /
                (n * dobraX(n, x) - somX(n, x) * somX(n, x));

            b = (somX(n, x) * multXY(n, x, y) - somX(n, y) *
                                                    dobraX(n, x)) /
                (somX(n, x) * somX(n, x) - n * dobraX(n,
                                                      x));

            fim = clock(); // Fim do calculo

            tempo_decorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
            tempo_medio += tempo_decorrido;
        }
        tempo_medio = tempo_medio / repeticoes; // tempo medio demandandado pelo calculo

        // Liberação da memoria alocada dinamicamente para o experimento
        free(x);
        free(y);

        // Impressão dos resultados
        printf("___________________________________________________________________\n\n");
        printf("(%d elementos)\n", n);
        printf("b: %.9lf\n", b);
        printf("a: %.9lf\n", a);
        printf("Tempo medio gasto para calcular: %.9lf segundos\n", tempo_medio);
        printf("___________________________________________________________________\n");

        n = n * 2;
    }

    return 0;
}
