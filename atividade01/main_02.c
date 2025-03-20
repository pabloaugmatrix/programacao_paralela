// Pablo Augusto Matos da Silva
// 2022015139
/*
Sem uso de funções e com um unico laço de repetição na main: 
Execução dos cálculos diretamente dentro da função main 
em um unico laço e sem modularização.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define A_REAL 2.5  // Inclinação real da reta
#define B_REAL 15.0 // Intercepto real da reta

int main()
{
    // Setup para o experimento
    srand(262016);
    clock_t inicio, fim;
    double tempo_decorrido, tempo_medio;
    int repeticoes = 100000;
    int n = 128; // Valor inicial de elementos sugerido pelo professor (2⁷)

    // Variaveis referentes ao calculo da regressão linear
    double multXY; // Produto escalar
    double somX;   // Soma elementos x
    double somY;   // Soma elementos y
    double dobraX; // Soma quadrados
    double *x, *y; // vetores de pontos
    double a, b;   // Inclinação e intercepto

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

        tempo_medio = 0;
        for (int i = 0; i < repeticoes; i++)
        {
            multXY = 0;
            somX = 0;
            somY = 0;
            dobraX = 0;

            inicio = clock(); // Inicio do calculo
            for (int j = 0; j < n; j++)
            {
                multXY += x[j] * y[j];
                somX += x[j];
                somY += y[j];
                dobraX += x[j] * x[j];
            }
            a = ((n * multXY) - ((somX) * (somY))) / ((n * dobraX) - (somX * somX));
            b = ((somX * multXY) - (somY * dobraX)) / ((somX * somX) - (n * dobraX));
            fim = clock(); // Fim do calculo

            tempo_decorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
            tempo_medio += tempo_decorrido;
        }
        tempo_medio = tempo_medio / repeticoes;

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

        n = n * 2; // Dobra o numero de elementos
    }

    return 0;
}
