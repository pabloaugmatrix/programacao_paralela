#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(argc < 3){
        fprintf(stderr,"Uso correto: %s <qnt_elementos> <nomearquivo>.txt\n", argv[0]);
        exit(1);
    }
    int quantidade = atoi(argv[1]);
    int *numeros = (int*)malloc(quantidade*sizeof(int));
    if(numeros == NULL){
        perror("Erro ao alocar memoria.");
        exit(1);
    }
    char filename [15];
    snprintf(filename, sizeof(filename), "%s", argv[2]);
    printf("Arquivo: %s\nQnt elementos: %d\n", filename, quantidade);
    free(numeros);
    return 0;
}