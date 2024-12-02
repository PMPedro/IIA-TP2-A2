//
// Created by pmanu on 02/12/2024.
//

#ifndef TP_UTIL_H
#define TP_UTIL_H

typedef struct dados{
    float valorPagar;
    int numMoedas;
    float *moedas;
}dados;

void* init_dados(char *nome, dados *n);
void gera_sol_inicial(int *sol, int v);
void escreve_sol(int *sol, int vert);
void substitui(int a[], int b[], int n);
void init_rand();
int random_l_h(int min, int max);
float rand_01();

#endif //TP_UTIL_H

