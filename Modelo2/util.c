//
// Created by pmanu on 02/12/2024.
//

#include "util.h"





// Leitura do ficheiro de input
// Recebe: nome do ficheiro, numero de vertices (ptr), numero de iteracoes (ptr)
// Devolve a matriz de adjacencias


void* init_dados(char *nome, dados *n)
{
    FILE *fp;
    fp = fopen(nome, "r");
    if(fp == NULL){
        printf("\nErro no acesso ao ficheiro");
        exit(1);
    }
    int num, vp;

    fscanf(fp, " %d %f" , &n->numMoedas , &n->valorPagar);

    n->moedas = malloc(sizeof (float ) * n->numMoedas);
    if(n->moedas == NULL){
        printf("Erro ao alocar memoria");
    }


    for(int i = 0; i < n->numMoedas; i++){
        fscanf(fp, " %f", &n->moedas[i]);
    }
    fclose(fp);
}

// Gera a solucao inicial
// Parametros: solucao, numero de vertices

// Inicializa��o do gerador de n�meros aleat�rios
void init_rand()
{
    srand((unsigned)time(NULL));
}




// Simula o lan�amento de uma moeda, retornando o valor 0 ou 1
int flip()
{
    if ((((float)rand()) / RAND_MAX) < 0.5)
        return 0;
    else
        return 1;
}

// Criacao da populacao inicial. O vector e alocado dinamicamente
// Par�metro de entrada: Estrutura com par�metros do problema
// Par�metro de sa�da: Preenche da estrutura da popula��o apenas o vector bin�rio com os elementos que est�o dentro ou fora da mochila
pchrom init_pop(struct info d, struct dados problema)
{
    int i, j;
    pchrom indiv;

    // Aloca memória para a população
    indiv = malloc(sizeof(chrom) * d.popsize);
    if (indiv == NULL)
    {
        printf("Erro na alocação de memória\n");
        exit(1);
    }

    // Inicializa cada indivíduo na população
    for (i = 0; i < d.popsize; i++)
    {
        float soma = 0.0; // Soma atual do valor das moedas escolhidas
        for (j = 0; j < d.numGenes; j++)
        {
            // Decide aleatoriamente se uma moeda é incluída, respeitando o valor máximo
            if (flip() && (soma + problema.moedas[j] <= problema.valorPagar))
            {
                indiv[i].p[j] = 1; // Moeda selecionada
                soma += problema.moedas[j];
            }
            else
            {
                indiv[i].p[j] = 0; // Moeda não selecionada
            }
        }

        // Inicializa o fitness do indivíduo com 0 (ou outro valor padrão, se necessário)
        indiv[i].fitness = 0.0;
    }

    return indiv;
}

// Actualiza a melhor solu��o encontrada
// Par�metro de entrada: populacao actual (pop), estrutura com par�metros (d) e a melhor solucao encontrada at� a gera��oo imediatamente anterior (best)
// Par�metro de sa�da: a melhor solucao encontrada at� a gera��o actual
chrom get_best(pchrom pop, struct info d, chrom best)
{
    int i;

    for (i=0; i<d.popsize; i++)
    {
        if (best.fitness < pop[i].fitness)
            best=pop[i];
    }
    return best;
}

// Devolve um valor inteiro distribuido uniformemente entre min e max
int random_l_h(int min, int max)
{
    return min + rand() % (max-min+1);
}

// Devolve um valor real distribuido uniformemente entre 0 e 1
float rand_01()
{
    return ((float)rand())/RAND_MAX;
}

// Escreve uma solu��o na consola
// Par�metro de entrada: populacao actual (pop) e estrutura com par�metros (d)
void write_best(chrom x, struct info d)
{
    int i;

    printf("\nBest individual: %4.1f\n", x.fitness);
    for (i=0; i<d.numGenes; i++)
        printf("%d", x.p[i]);
    putchar('\n');
}
