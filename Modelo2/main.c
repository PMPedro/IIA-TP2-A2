#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"
#include "algoritmo.h"
#include "funcao.h"

int main() {
    char fname[40];
    dados grafico;
    int *best, *sol;
    int runs = 10, i;
    float mbf = 0.0, best_custo, custo;
    struct info EA_param;
    pchrom pop = NULL, parents = NULL;
    chrom best_run, best_ever;
    int gen_actual, r, inv;

    printf("\nNome Ficheiro: ");
    scanf("%s", fname);

    init_rand();
    init_dados(fname, &grafico);

    EA_param.popsize = 100;
    EA_param.pm = 0.1;
    EA_param.pr = 0.7;
    EA_param.tsize = 2;
    EA_param.numGenerations = 1000;
    EA_param.numGenes = grafico.numMoedas;
    EA_param.capacity = grafico.valorPagar;

    // Inicializa a melhor solução
    best_ever.fitness = -INFINITY;

    // Faz um ciclo com o número de execuções definidas
    for (r = 0; r < runs; r++) {
        printf("Repeticao %d\n", r + 1);
        pop = init_pop(EA_param, grafico);
        evaluate(pop, EA_param, grafico.moedas, grafico.valorPagar);

        gen_actual = 1;
        best_run = pop[0];
        best_run = get_best(pop, EA_param, best_run);

        // Reserva espaço para os pais da população seguinte
        parents = malloc(sizeof(chrom) * EA_param.popsize);
        if (parents == NULL) {
            printf("Erro na alocacao de memoria\n");
            exit(1);
        }

        while (gen_actual <= EA_param.numGenerations) {
            tournament(pop, EA_param, parents);
            genetic_operators(parents, EA_param, pop, grafico);
            evaluate(pop, EA_param, grafico.moedas, grafico.valorPagar);

            best_run = get_best(pop, EA_param, best_run);
            gen_actual++;
        }

        // Contagem das soluções inválidas
        for (inv = 0, i = 0; i < EA_param.popsize; i++)
            if (pop[i].valido == 0)
                inv++;

        printf("\nRepeticao %d:", r + 1);
        write_best(best_run, EA_param, grafico);
        printf("\nPercentagem Invalidos: %f\n", 100 * (float)inv / EA_param.popsize);
        mbf += best_run.fitness;

        if (r == 0 || best_run.fitness > best_ever.fitness)
            best_ever = best_run;

        free(parents);
        free(pop);
    }

    // Escreve resultados globais
    printf("\n\nMBF: %f\n", mbf / runs);
    printf("\nMelhor solucao encontrada");
    write_best(best_ever, EA_param, grafico);

    return 0;
}
