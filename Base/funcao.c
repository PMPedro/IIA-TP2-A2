//
// Created by pmanu on 02/12/2024.
//

#include "funcao.h"


// Calcula a qualidade de uma solu��o
//recebe as vals -> moedas existentes , vert -> nr de moedas que existem valor
int calcula_fit(int a[], float *vals, int vert , float valor)
{
    float soma = 0.0;
    int total_moedas = 0;
    int i;

    // Calcular a soma dos valores e o total de moedas
    for (i = 0; i < vert; i++) {
        soma += a[i] * vals[i];
        total_moedas += a[i];
    }

    // Verifica se a soma é diferente do valor desejado
    if (fabs(soma - valor) > TOLERANCIA) {
        // Retorna um valor de custo alto (1000 + a diferença) se a soma for diferente do valor desejado
        return 1000 + abs(soma - valor) * 100;
    }


    return total_moedas;
}

