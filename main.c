#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"
#include "algoritmo.h"



int main() {
    char fname[40];
    dados grafico;
    int *best, *sol;
    int runs = 10, best_custo , i , custo;
    float   mbf = 0.0;

    printf("\nNome Ficheiro: ");
    scanf("%s" , &fname);

    init_dados(fname, &grafico);
    sol = malloc(sizeof(int) * grafico.numMoedas);
    best = malloc(sizeof(int) * grafico.numMoedas);

    if(sol == NULL || best == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }

    for (i = 0; i < runs; ++i) {
        // Gerar solucao inicial
        gera_sol_inicial(sol, grafico.numMoedas);
        //escreve_sol(sol, vert);
        // Trepa colinas
        custo = trepa_colinas(sol, grafico.moedas, grafico.numMoedas, runs , grafico.valorPagar);
        // Escreve resultados da repeticao k
        printf("\nRepeticao %d:", i);
        escreve_sol(sol, grafico.numMoedas);
        printf("Custo final: %2d\n", custo);
        mbf += custo;
        if(i==0 || best_custo > custo)
        {
            best_custo = custo;
            substitui(best, sol, grafico.numMoedas);
        }
    }
    printf("\n\nMBF: %f\n", mbf/i);
    printf("\nMelhor solucao encontrada");
    escreve_sol(best, grafico.numMoedas);
    printf("Custo final: %2d\n", best_custo);

    return 0;
}
