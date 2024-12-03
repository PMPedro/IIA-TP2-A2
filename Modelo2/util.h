//
// Created by pmanu on 02/12/2024.
//

#ifndef TP_UTIL_H
#define TP_UTIL_H
#include "algoritmo.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct dados{
    float  valorPagar;
    int numMoedas;
    float *moedas;
}dados;

struct info init_data(char *s, int mat[][2]);

pchrom init_pop(struct info d, struct dados problema);

void print_pop(pchrom pop, struct info d);

chrom get_best(pchrom pop, struct info d, chrom best);

void write_best(chrom x, struct info d);

void init_rand();

int random_l_h(int min, int max);

float rand_01();

int flip();

#endif //TP_UTIL_H

