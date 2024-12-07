#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "algoritmo.h"
#include "funcao.h"

void tournament(pchrom pop, struct info d, pchrom parents) {
    for (int i = 0; i < d.popsize; i++) {
        int x1 = random_l_h(0, d.popsize - 1);
        int x2;
        do {
            x2 = random_l_h(0, d.popsize - 1);
        } while (x1 == x2);

        struct individual *winner = (pop[x1].fitness < pop[x2].fitness) ? &pop[x1] : &pop[x2];
        deep_copy_individual(&parents[i], winner, d.numGenes);
    }
}

void genetic_operators(pchrom parents, struct info d, pchrom offspring, struct dados moedas) {
    for (int i = 0; i < d.popsize; i++) {
        offspring[i].p = malloc(sizeof(int) * d.numGenes);
        if (offspring[i].p == NULL) {
            fprintf(stderr, "Erro ao alocar memória para offspring[%d].p\n", i);
            exit(1);
        }
    }

    crossover(parents, d, offspring, moedas);
    mutation(offspring, d, moedas);
}

void crossover(pchrom parents, struct info d, pchrom offspring, struct dados moedas) {
    for (int i = 0; i < d.popsize; i += 2) {
        if (rand_01() < d.pr) {
            int point = random_l_h(0, d.numGenes - 1);
            for (int j = 0; j < d.numGenes; j++) {
                if (j < point) {
                    offspring[i].p[j] = parents[i].p[j];
                    offspring[i + 1].p[j] = parents[i + 1].p[j];
                } else {
                    offspring[i].p[j] = parents[i + 1].p[j];
                    offspring[i + 1].p[j] = parents[i].p[j];
                }
            }
        } else {
            for (int j = 0; j < d.numGenes; j++) {
                offspring[i].p[j] = parents[i].p[j];
                offspring[i + 1].p[j] = parents[i + 1].p[j];
            }
        }

        repair_solution(offspring[i].p, moedas, d.numGenes);
        repair_solution(offspring[i + 1].p, moedas, d.numGenes);
    }
}

void mutation(pchrom offspring, struct info d, struct dados moedas) {
    for (int i = 0; i < d.popsize; i++) {
        for (int j = 0; j < d.numGenes; j++) {
            if (rand_01() < d.pm) {
                offspring[i].p[j] = !(offspring[i].p[j]);
            }
        }
        repair_solution(offspring[i].p, moedas, d.numGenes);
    }
}

void repair_solution(int *genes, dados problema, int numGenes) {
    float soma = 0.0;
    for (int i = 0; i < numGenes; i++) {
        soma += genes[i] * problema.moedas[i];
    }

    // Mostrar a soma antes da reparação para depuração
   // printf("Soma inicial antes de reparacao: %.6f\n", soma);

    // Reparar só se a diferença for significativa
    if (fabs(soma - problema.valorPagar) > 0.05) {
        int ajustes = 0;
        while (ajustes < 1000 && fabs(soma - problema.valorPagar) > 0.01) {
            if (soma > problema.valorPagar) {
                for (int i = numGenes - 1; i >= 0; i--) {
                    if (genes[i] > 0) {
                        genes[i]--;
                        soma -= problema.moedas[i];
                        ajustes++;
                        break;
                    }
                }
            } else {
                for (int i = 0; i < numGenes; i++) {
                    if (soma + problema.moedas[i] <= problema.valorPagar + 0.01) {
                        genes[i]++;
                        soma += problema.moedas[i];
                        ajustes++;
                        break;
                    }
                }
            }
        }
    }
}


void free_population(pchrom pop, int popsize) {
    for (int i = 0; i < popsize; i++) {
        if (pop[i].p != NULL) {
            free(pop[i].p);
            pop[i].p = NULL;
        }
    }
}
