//
// Created by pmanu on 02/12/2024.
//

#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Leitura do ficheiro de input
// Recebe: nome do ficheiro, numero de vertices (ptr), numero de iteracoes (ptr)
// Devolve a matriz de adjacencias


void* init_dados(char *nome, dados *n)
{
    FILE *fp;
    fp = fopen(nome, "r");
    if(fp == NULL){
        printf("\nErro no acesso ao ficheiro");
        exit(1);
    }
    int num, vp;

    fscanf(fp, " %d %f" , &n->numMoedas , &n->valorPagar);

    n->moedas = malloc(sizeof (float ) * n->numMoedas);
    if(n->moedas == NULL){
        printf("Erro ao alocar memoria");
    }


    for(int i = 0; i < n->numMoedas; i++){
        fscanf(fp, " %f", &n->moedas[i]);
    }
    fclose(fp);
}

// Gera a solucao inicial
// Parametros: solucao, numero de vertices
void gera_sol_inicial(int *sol, int v)
{
    int i, x;

    for(i=0; i<v; i++)
        sol[i]=0;
    for(i=0; i<v/2; i++)
    {
        do
            x = random_l_h(0, v-1);
        while(sol[x] != 0);
        sol[x]=1;
    }
}

// Escreve solucao
// Parametros: solucao e numero de vertices
void escreve_sol(int *sol, int vert)
{
    int i;

    printf("\nConjunto A: ");
    for(i=0; i<vert; i++)
        if(sol[i]==0)
            printf("%2d  ", i);
    printf("\nConjunto B: ");
    for(i=0; i<vert; i++)
        if(sol[i]==1)
            printf("%2d  ", i);
    printf("\n");
}

// copia vector b para a (tamanho n)
void substitui(int a[], int b[], int n)
{
    int i;
    for(i=0; i<n; i++)
        a[i]=b[i];
}

// Inicializa o gerador de numeros aleatorios
void init_rand()
{
    srand((unsigned)time(NULL));
}

// Devolve valor inteiro aleatorio entre min e max
int random_l_h(int min, int max)
{
    return min + rand() % (max-min+1);
}

// Devolve um valor real aleatorio do intervalo [0, 1]
float rand_01()
{
    return ((float)rand())/RAND_MAX;
}
