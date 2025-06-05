#include "arvore_patricia.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// auxiliar para comparação de nodes usando seu conteúdo
// essa função será chamada pelo qsort para ordenar os filhos em ordem alfabetica
static int comparar_nodes(const void *a, const void *b) {
    Node *node_a = *(Node **)a;
    Node *node_b = *(Node **)b;
    return strcmp(node_a->conteudo, node_b->conteudo);
}

// imprimir a árvore patricia em ordem alfabetica
void imprimir_arvore(Node *raiz, char *prefixo) {
    if (!raiz)
        return;

    char novo_prefixo[100];

    if (raiz->filhos) {
        // conta o número de filhos
        int count = 0;
        while (raiz->filhos[count] != NULL)
            count++;

        if (count > 0) {
            // cria uma cópia dos ponteiros para os filhos para não modificar a ordem original
            Node **filhosOrdenados = malloc(count * sizeof(Node *));
            for (int i = 0; i < count; i++) {
                filhosOrdenados[i] = raiz->filhos[i];
            }

            // ordena os filhos alfabeticamente com base no campo 'conteudo'
            // dependendo do output de comparar nodes
            qsort(filhosOrdenados, count, sizeof(Node *), comparar_nodes);

            // percorre os filhos já ordenados
            for (int i = 0; i < count; i++) {
                // concatena o prefixo atual com o conteúdo do filho para formar a palavra completa
                snprintf(novo_prefixo, sizeof(novo_prefixo), "%s%s", prefixo, filhosOrdenados[i]->conteudo);
                if (filhosOrdenados[i]->fim_palavra) {
                    printf("%s\n", novo_prefixo);
                }

                // processa recursivamente os nodes filhos
                imprimir_arvore(filhosOrdenados[i], novo_prefixo);
            }

            free(filhosOrdenados);
        }
    }
}
