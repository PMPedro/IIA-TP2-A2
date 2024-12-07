//
// Created by pmanu on 02/12/2024.
//

#include "funcao.h"


// Calcula a qualidade de uma solu��o
//recebe as vals -> moedas existentes , vert -> nr de moedas que existem valor
float eval_individual(int sol[], struct info d, float moedas[], float valorPagar, int *valido) {
    float soma_valores = 0.0;
    int num_moedas = 0;

    for (int i = 0; i < d.numGenes; i++) {
        soma_valores += sol[i] * moedas[i];

        if (sol[i] < 0) {
            printf("Erro: Gene negativo detectado! sol[%d] = %d\n", i, sol[i]);
            exit(1);
        }

        num_moedas += sol[i];
    }

    if (fabs(soma_valores - valorPagar) <= 1e-2) {
        *valido = 1;
        return num_moedas; // Minimiza o número de moedas
    } else {
        *valido = 0;
        return fabs(soma_valores - valorPagar) * 10 + num_moedas;
    }
}

void evaluate(pchrom pop, struct info d, float *moedas, float valorPagar) {
    int i;

    for (i = 0; i < d.popsize; i++) {
        int valido;
        pop[i].fitness = eval_individual(pop[i].p, d, moedas, valorPagar, &valido);
        pop[i].valido = valido;
    }
}
