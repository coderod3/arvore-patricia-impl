
#ifndef PATRICIA_H
#define PATRICIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *conteudo;
    int fim_palavra;
    struct Node **filhos;
} Node;

// Funções principais
Node *criar_node(const char *conteudo, int fim_palavra);
void inserir_gerenciador(Node *raiz, const char *chave);
void deletar_palavra(Node *raiz, const char *chave);
int buscar_palavra(Node *raiz, const char *chave);
void imprimir_arvore(Node *raiz, char *prefixo);
void carregar_palavras_de_arquivo(Node *raiz, const char *nome_arquivo);
void exibir_estatisticas(Node *raiz);

#endif