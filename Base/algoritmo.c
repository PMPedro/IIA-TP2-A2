#include <stdio.h>
#include <stdlib.h>
#include "algoritmo.h"
#include "funcao.h"
#include "util.h"

// Gera um vizinho
// Parametros: solucao actual, vizinho, numero de vertices
//swap two vertices



void gera_vizinho(int a[], int b[], int n, float *moedas, float valorPagar, int tipo)
{
    int i, p1, p2, quantidade;

    // Copia a solução atual para o vizinho
    for (i = 0; i < n; i++) {
        b[i] = a[i];
    }

    if (tipo == 1) {
        // Tipo 1: Mover apenas uma moeda de p2 para p1
        do {
            p1 = random_l_h(0, n - 1); // Escolhe aleatoriamente a posição de p1
        } while (b[p1] > a[p1]); // Garante que podemos adicionar mais moedas em p1

        do {
            p2 = random_l_h(0, n - 1); // Escolhe aleatoriamente a posição de p2
        } while (b[p2] <= 0); // Garante que podemos remover uma moeda de p2


        int max_transferivel = (a[p1] - b[p1]) < b[p2] ? (a[p1] - b[p1]) : b[p2];
        max_transferivel = max_transferivel > 0 ? max_transferivel : 1; // Evita transferências negativas
        quantidade = random_l_h(1, max_transferivel);
        b[p1] += quantidade;  // Adiciona as moedas em p1
        b[p2] -= quantidade;  // Remove as moedas de p2
    }
    else if (tipo == 2) {
        // Tipo 2: Tentar mover várias moedas de p2 para p1
        do {
            p1 = random_l_h(0, n - 1); // Escolhe aleatoriamente a posição de p1
        } while (b[p1] > a[p1]); // Garante que podemos adicionar mais moedas em p1

        do {
            p2 = random_l_h(0, n - 1); // Escolhe aleatoriamente a posição de p2
        } while (b[p2] <= 0); // Garante que podemos remover uma moeda de p2

        // Calcula quantas moedas podemos mover de p2 para p1
        int max_transferivel = (a[p1] - b[p1]) < b[p2] ? (a[p1] - b[p1]) : b[p2];
        max_transferivel = max_transferivel > 0 ? max_transferivel : 1; // Se max_transferivel for 0 ou negativo, usar 1

        // Gera um número aleatório de moedas a mover, entre 1 e max_transferivel
        quantidade = random_l_h(1, max_transferivel);

        // Realiza a transferência de moedas
        b[p1] += quantidade;  // Adiciona as moedas em p1
        b[p2] -= quantidade;  // Remove as moedas de p2
    }

    // Valida se o valor total ainda é válido
    float valorAtual = 0;
    for (i = 0; i < n; i++) {
        valorAtual += b[i] * moedas[i];  // Soma o valor das moedas
    }

    // Se o valor total exceder o valor a pagar, desfaz a alteração
    if (valorAtual > valorPagar) {
        b[p1] -= quantidade;  // Desfaz a adição de p1
        b[p2] += quantidade;  // Desfaz a remoção de p2
    }
}

// Trepa colinas first-choice
// Parametros: solucao, matriz de adjacencias, numero de vertices e numero de iteracoes
// Devolve o custo da melhor solucao encontrada
int trepa_colinas(int sol[], float *mat, int vert, int num_iter , float valor)
{
    int *nova_sol , *nova_sol2, custo, custo_viz, custo_viz2, i;

    nova_sol = malloc(sizeof(int)*vert);
    nova_sol2 = malloc(sizeof(int)*vert);

    if(nova_sol == NULL || nova_sol2 == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }

    // Avalia solucao inicial
    custo = calcula_fit(sol, mat, vert, valor);
    for(i=0; i<num_iter; i++)
    {

        // Gera vizinho
        gera_vizinho(sol, nova_sol, vert, mat, valor, 1);
        gera_vizinho(sol, nova_sol2, vert, mat, valor , 2);

        // Avalia vizinho
        custo_viz = calcula_fit(nova_sol, mat, vert , valor);
        custo_viz2 = calcula_fit(nova_sol2, mat, vert , valor);

        // Aceita vizinho se o custo diminuir (problema de minimizacao)
        if (custo_viz < custo_viz2 && custo_viz < custo) {
            substitui(sol, nova_sol, vert); // Atualiza para a melhor solução
            custo = custo_viz;
        } else if (custo_viz2 < custo) {
            substitui(sol, nova_sol2, vert); // Atualiza para a melhor solução
            custo = custo_viz2;
        }
    printf("\nCUSTO %d", custo);

    }
    free(nova_sol);
    return custo;
}
