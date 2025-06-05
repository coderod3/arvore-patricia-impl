#include "arvore_patricia.h"
#include <stdio.h>
#include <string.h>

// recebe um caminho de arquivo (ex: ../palavras.txt) e carrega as palavras de cada linha na árvore
void carregar_palavras_de_arquivo(Node *raiz, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");

    if (!arquivo) {
        printf("Erro: não foi possível abrir o arquivo '%s'.\n", nome_arquivo);
        return;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo)) {
        // limpa os caracteres especiais de nova linha
        linha[strcspn(linha, "\r\n")] = '\0';

        // se a linha não estiver vazia, insere a palavra na arvore
        if (strlen(linha) > 0) {
            inserir_gerenciador(raiz, linha);
        }
    }
    fclose(arquivo);

    printf("Arquivo '%s' carregado com sucesso.\n", nome_arquivo);
}
