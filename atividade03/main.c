#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct
{
    double x;
    double precisao;
    double resultado;
} ThreadArgs;

double exponencial(double valor, int n)
{
    double resultado = 1.0;
    for (int i = 0; i < n; i++)
    {
        resultado *= valor;
    }
    return resultado;
}

double fat(int valor)
{
    if (valor == 0 || valor == 1)
        return 1.0;
    return valor * fat(valor - 1);
}

double seno(double x, double precisao)
{
    double termo, seno = 0.0;
    int i = 0;

    do
    {
        termo = ((i % 2 == 0) ? 1 : -1) * (exponencial(x, (2 * i) + 1) / fat((2 * i) + 1));
        seno += termo;
        i++;
    } while (termo > precisao || termo < -precisao);

    return seno;
}

double cosseno(double x, double precisao)
{
    double termo, cosseno = 0.0;
    int i = 0;

    do
    {
        termo = ((i % 2 == 0) ? 1 : -1) * (exponencial(x, 2 * i) / fat(2 * i));
        cosseno += termo;
        i++;
    } while (termo > precisao || termo < -precisao);

    return cosseno;
}

double tangente(double x, double precisao)
{
    return seno(x, precisao) / cosseno(x, precisao);
}

double tangente_fork(double x, double precisao)
{
    int fd[2];
    pid_t pid;
    double sen, cos;

    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(1);
    }

    if ((pid = fork()) < 0)
    {
        perror("fork");
        exit(1);
    }

    if (pid == 0)
    {
        close(fd[0]);
        sen = seno(x, precisao);
        write(fd[1], &sen, sizeof(double));
        close(fd[1]);
        exit(0);
    }
    else
    {
        close(fd[1]);
        cos = cosseno(x, precisao);
        read(fd[0], &sen, sizeof(double));
        close(fd[0]);
        wait(NULL); // Aguarda o filho terminar
    }

    return (sen / cos);
}

void *calcular_seno(void *arg)
{
    ThreadArgs *args = (ThreadArgs *)arg;
    args->resultado = seno(args->x, args->precisao);
    return NULL;
}

void *calcular_cosseno(void *arg)
{
    ThreadArgs *args = (ThreadArgs *)arg;
    args->resultado = cosseno(args->x, args->precisao);
    return NULL;
}

double tangente_thread(double x, double precisao)
{
    pthread_t thread_seno, thread_cosseno;
    ThreadArgs args_seno = {x, precisao, 0};
    ThreadArgs args_cosseno = {x, precisao, 0};

    pthread_create(&thread_seno, NULL, calcular_seno, &args_seno);
    pthread_create(&thread_cosseno, NULL, calcular_cosseno, &args_cosseno);

    pthread_join(thread_seno, NULL);
    pthread_join(thread_cosseno, NULL);

    return args_seno.resultado / args_cosseno.resultado;
}

int main()
{
    srand(262016);
    double resultado, x = (rand() % 100) / 10.0;

    struct timeval inicio, fim;
    double tempo_decorrido;

    printf("UM SO PROCESSO:\n\n");

    for (double precisao = 1e-5; precisao >= 1e-15; precisao /= 1e5)
    {
        gettimeofday(&inicio, NULL);
        resultado = tangente(x, precisao);
        gettimeofday(&fim, NULL);

        tempo_decorrido = (fim.tv_sec - inicio.tv_sec) + (fim.tv_usec - inicio.tv_usec) / 1e6;

        printf("Precisao(%e)\n", precisao);
        printf("tangente(%lf) ≈ %lf\n", x, resultado);
        printf("Tempo: %lf segundos\n\n", tempo_decorrido);
    }

    printf("____________________________________________________\n\n");
    printf("DOIS PROCESSOS:\n\n");

    for (double precisao = 1e-5; precisao >= 1e-15; precisao /= 1e5)
    {
        gettimeofday(&inicio, NULL);
        resultado = tangente_fork(x, precisao);
        gettimeofday(&fim, NULL);

        tempo_decorrido = (fim.tv_sec - inicio.tv_sec) + (fim.tv_usec - inicio.tv_usec) / 1e6;

        printf("Precisao(%e)\n", precisao);
        printf("tangente(%lf) ≈ %lf\n", x, resultado);
        printf("Tempo: %lf segundos\n\n", tempo_decorrido);
    }

    printf("____________________________________________________\n\n");
    printf("DUAS THREADS:\n\n");

    for (double precisao = 1e-5; precisao >= 1e-15; precisao /= 1e5)
    {
        gettimeofday(&inicio, NULL);
        resultado = tangente_thread(x, precisao);
        gettimeofday(&fim, NULL);

        tempo_decorrido = (fim.tv_sec - inicio.tv_sec) + (fim.tv_usec - inicio.tv_usec) / 1e6;

        printf("Precisao(%e)\n", precisao);
        printf("tangente(%lf) ≈ %lf\n", x, resultado);
        printf("Tempo: %lf segundos\n\n", tempo_decorrido);
    }

    return 0;
}
