#include "arvore_patricia.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// struct auxiliar pra guardar os dados da árvore
typedef struct {
    int totalNos;
    int somaNiveis;
    int nivelMax;
    int totalPalavras;
    size_t memoriaTotal;
} Estatisticas;


// calcula o tamanho em memória de um node
static size_t calcular_tamanho_node(Node *node) {
    size_t tam = sizeof(Node); // tamanho do struct

    if (node->conteudo)
        tam += strlen(node->conteudo) + 1; // soma o tamanho da string com o \0

    int nFilhos = 0;

    if (node->filhos) {
        // conta quantos filhos tem
        while (node->filhos[nFilhos] != NULL)
            nFilhos++;
        // soma espaço pro vetor de ponteiros
        tam += (nFilhos + 1) * sizeof(Node *);
    }

    return tam; // retorna o tamanho estimado
}

// registra as infos de um node nas estatísticas
static void registrar_node(Node *node, int nivel, Estatisticas *est) {
    est->totalNos++;
    est->somaNiveis += nivel;

    if (nivel > est->nivelMax)
        est->nivelMax = nivel; // atualiza se esse for o maior nível

    est->memoriaTotal += calcular_tamanho_node(node); // adiciona o uso de memória


    if (node->fim_palavra)
        est->totalPalavras++;
}

// percorre a árvore recursivamente pra atualizar os dados
static void percorrer_arvore(Node *node, int nivel, Estatisticas *est) {
    if (!node)
        return; // se chegou num nulo, para aqui

    registrar_node(node, nivel, est); // registra o nde atual

    if (node->filhos) {
        // percorre todos os filhos
        for (int i = 0; node->filhos[i] != NULL; i++) {
            percorrer_arvore(node->filhos[i], nivel + 1, est);
        }
    }
}

// mostra na tela as estatísticas da árvore
void exibir_estatisticas(Node *raiz) {
    Estatisticas est = {0, 0, 0, 0, 0}; // inicializa os dados

    percorrer_arvore(raiz, 0, &est); // começa a percorrer a partir do nível 0

    // calcula a média dos níveis
    double nivelMedio = (est.totalNos > 0) ? ((double) est.somaNiveis / est.totalNos) : 0;

    // mostra os dados pro usuário
    printf("Estatísticas da Árvore Patricia:\n");
    printf("Número total de nós: %d\n", est.totalNos);
    printf("Número total de palavras: %d\n", est.totalPalavras);
    printf("Nível máximo: %d\n", est.nivelMax);
    printf("Nível médio: %.2f\n", nivelMedio);
    printf("Uso de memória aproximado: %zu bytes\n", est.memoriaTotal);
}
