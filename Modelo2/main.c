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
    int runs = 10, i ;
    float   mbf = 0.0,best_custo,custo ;
    struct info EA_param;
    pchrom      pop = NULL, parents = NULL;
    chrom       best_run, best_ever;
    int         gen_actual, r, inv;


/*
 *
 *     fscanf(f, " pop: %d", &x.popsize);
    fscanf(f, " pm: %f", &x.pm);
    fscanf(f, " pr: %f", &x.pr);
    fscanf(f, " tsize: %d", &x.tsize);
    fscanf(f, " max_gen: %d", &x.numGenerations);
    fscanf(f, " obj: %d", &x.numGenes);
    fscanf(f, " cap: %d", &x.capacity);
    */



    printf("\nNome Ficheiro: ");
    scanf("%s" , &fname);

    init_rand();
    // Preenche a matriz com dados dos objectos (peso e valor) e a estrutura EA_param que foram definidos no ficheiro de input
    init_data(fname, &grafico);

    EA_param.popsize = 100;
    EA_param.pm = 0.1;
    EA_param.pr = 0.7;
    EA_param.tsize = 2;
    EA_param.numGenerations = 1000;
    EA_param.numGenes = grafico.numMoedas;
    EA_param.capacity = grafico.valorPagar;




    // Faz um ciclo com o n�mero de execu��es definidas
    for (r=0; r<runs; r++)
    {
        printf("Repeticao %d\n",r+1);
        // Gera��o da popula��o inicial
        pop = init_pop(EA_param);
        // Avalia a popula��o inicial
        evaluate(pop, EA_param, mat);
        gen_actual = 1;
        // Como ainda n�o existe, escolhe-se como melhor solu��o a primeira da popula��o (poderia ser outra qualquer)
        best_run = pop[0];
        // Encontra-se a melhor solu��o dentro de toda a popula��o
        best_run = get_best(pop, EA_param, best_run);
        // Reserva espa�o para os pais da popula��o seguinte
        parents = malloc(sizeof(chrom)*EA_param.popsize);
        // Caso n�o consiga fazer a aloca��o, envia aviso e termina o programa
        if (parents==NULL)
        {
            printf("Erro na alocacao de memoria\n");
            exit(1);
        }
        // Ciclo de optimiza��o
        while (gen_actual <= EA_param.numGenerations)
        {
            // Torneio bin�rio para encontrar os progenitores (ficam armazenados no vector parents)
            tournament(pop, EA_param, parents);
            // Aplica os operadores gen�ticos aos pais (os descendentes ficam armazenados na estrutura pop)
            genetic_operators(parents, EA_param, pop);
            // Avalia a nova popula��o (a dos filhos)
            evaluate(pop, EA_param, mat);
            // Actualiza a melhor solu��o encontrada
            best_run = get_best(pop, EA_param, best_run);
            gen_actual++;
        }
        // Contagem das solu��es inv�lidas
        for (inv=0, i=0; i<EA_param.popsize; i++)
            if (pop[i].valido == 0)
                inv++;
        // Escreve resultados da repeti��o que terminou
        printf("\nRepeticao %d:", r);
        write_best(best_run, EA_param);
        printf("\nPercentagem Invalidos: %f\n", 100*(float)inv/EA_param.popsize);
        mbf += best_run.fitness;
        if (r==0 || best_run.fitness > best_ever.fitness)
            best_ever = best_run;
        // Liberta a mem�ria usada
        free(parents);
        free(pop);
    }
    // Escreve resultados globais
    printf("\n\nMBF: %f\n", mbf/r);
    printf("\nMelhor solucao encontrada");
    write_best(best_ever, EA_param);
    return 0;
}
