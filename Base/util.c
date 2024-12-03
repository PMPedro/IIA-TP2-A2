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
void gera_sol_inicial(int *sol, int v, float *moedas, float valorPagar)
{
    int i, x;
    float soma = 0.0;

    // Inicializa a solução com 0 (nenhuma moeda selecionada inicialmente)
    for (i = 0; i < v; i++) {
        sol[i] = 0;
    }

    // Encontra a menor moeda disponível
    float menor_moeda = moedas[0];
    for (i = 1; i < v; i++) {
        if (moedas[i] < menor_moeda) {
            menor_moeda = moedas[i];
        }
    }

    // Adiciona moedas enquanto o valor total não ultrapassar valorPagar
    while (soma < valorPagar) {
        // Seleciona uma posição aleatória
        x = random_l_h(0, v - 1);

        // Calcula o número máximo de moedas que pode ser adicionado na posição x
        int max_adicionar = (valorPagar - soma) / moedas[x];
        if (max_adicionar > 0) {
            // Gera aleatoriamente quantas moedas adicionar (pelo menos 1)
            int adicionar = random_l_h(1, max_adicionar);
            sol[x] += adicionar;
            soma += adicionar * moedas[x];
        }

        // Verifica se o valor restante é muito pequeno para ser preenchido
        float valor_restante = valorPagar - soma;
        if (valor_restante < menor_moeda - 0.001) { // Tolerância para erros de arredondamento
            break;
        }

        // Verifica se é possível adicionar mais moedas
        int adicionou_moeda = 0;
        for (int j = 0; j < v; j++) {
            if ((valorPagar - soma) >= moedas[j]) {
                adicionou_moeda = 1;
                break;
            }
        }

        if (!adicionou_moeda) {
            break;
        }
    }

    // Ajusta para não ultrapassar o valor exato (opcional, dependendo da lógica geral)
    if (fabs(soma - valorPagar) > 0.001) {
        printf("Aviso: Não foi possível gerar uma solução inicial exata para %.2f\n", valorPagar);
    }
}

// Escreve solucao
// Parametros: solucao e numero de vertices
void escreve_sol(int *sol, int vert, float *valores)
{
    int i;

    printf("\nMoedas escolhidas: ");
    for(i = 0; i < vert; i++) {
        if (sol[i] > 0) {  // Se a moeda foi escolhida
            printf("%.2f x %d ", valores[i], sol[i]);  // Exibe o valor da moeda e a quantidade escolhida
        }
    }

    printf("\nMoedas nao escolhidas: ");
    for(i = 0; i < vert; i++) {
        if (sol[i] == 0) {  // Se a moeda não foi escolhida
            printf("%.2f ", valores[i]);  // Exibe o valor da moeda
        }
    }
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
