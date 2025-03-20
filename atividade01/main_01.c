// Pablo Augusto Matos da Silva
// 2022015139
/*
Uso de funções com um unico laço de repetição na main: 
Implementação de um unico laço de repetição na função main 
chamando as demais funções para realização do cálculo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define A_REAL 2.5  // Inclinação real da reta
#define B_REAL 15.0 // Intercepto real da reta

// Produto escalar
double multXY(double x, double y)
{
    return x * y;
}

// Soma elementos
double somX(double x)
{
    return x;
}

// Soma quadrados
double dobraX(double x)
{
    return x * x;
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
    double a, b;       // Inclinação e intercepto
    double *x, *y;     // vetores de pontos
    double var_multXY; // Produto escalar
    double var_somX;   // Soma elementos x
    double var_somY;   // Soma elementos y
    double var_dobraX; // Soma quadrados

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
            var_multXY = 0;
            var_somX = 0;
            var_somY = 0;
            var_dobraX = 0;

            inicio = clock(); // Inicio do calculo
            for (int j = 0; j < n; j++)
            {
                var_multXY += multXY(x[j], y[j]);
                var_somX += somX(x[j]);
                var_somY += somX(y[j]);
                var_dobraX += dobraX(x[j]);
            }
            a = ((n * var_multXY) - ((var_somX) * (var_somY))) /
                ((n * var_dobraX) - (var_somX * var_somX));
            b = ((var_somX * var_multXY) - (var_somY * var_dobraX)) /
                ((var_somX * var_somX) - (n * var_dobraX));

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
