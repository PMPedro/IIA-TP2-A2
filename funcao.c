//
// Created by pmanu on 02/12/2024.
//

#include "funcao.h"


// Calcula a qualidade de uma solu��o
//recebe as vals -> moedas existentes , vert -> nr de moedas que existem valor
int calcula_fit(int a[], int *vals, int vert , float valor)
{
    float soma = 0.0;
    int total=0;
    int moedas = 0;
    int i, j;

    for(i=0; i<vert; i++){
        if(a[i]==1)
        {
            soma += vals[i];
            moedas++;
        }
    }

    if( soma =! valor ){
        return 1000 + abs(soma - valor) * 100;
    }

    return total;
}

