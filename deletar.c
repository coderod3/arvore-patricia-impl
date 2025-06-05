#include "arvore_patricia.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// conta quantos filhos tem em cada nodes e retorna
int contar_filhos(Node *node) {
    int count = 0;
    if (node->filhos) {
        while (node->filhos[count] != NULL)
            count++; // conta até encontrar NULL no final
    }
    return count;
}

// remove um filho dado o node pai e o índice
void remover_filho(Node *pai, int index) {
    int count = contar_filhos(pai);
    Node *filho = pai->filhos[index]; // pega o filho a ser removido

    // move todos os filhos pra esquerda pra tampar o buraco deixado pelo removido
    for (int j = index; j < count; j++) {
        pai->filhos[j] = pai->filhos[j + 1];
    }

    // libera a memória do nodes removido
    free(filho->conteudo);
    free(filho->filhos);
    free(filho);
}


// função recursiva que percorre a árvore pra deletar uma palavra
int deletar_recursivo(Node *node, const char *chave) {
    if (*chave == '\0') {
        // chegou no fim da palavra
        if (node->fim_palavra) {
            node->fim_palavra = 0; // desmarca como fim de palavra

            // se não tiver filhos, esse nodes pode ser removido
            if (node->filhos == NULL || node->filhos[0] == NULL)
                return 1; // sinaliza que pode ser removido
            else
                return 0; // só desmarcou, mas ainda tem filhos
        } else {
            return -1; // a palavra nao existia
        }
    }

    if (node->filhos == NULL)
        return -1; // não tem filhos

    int len;
    int encontrado = 0;
    int status = -1;

    // percorre os filhos procurando um que combine com a chave
    for (int i = 0; node->filhos[i] != NULL; i++) {
        Node *filho = node->filhos[i];
        len = strlen(filho->conteudo);

        // compara o início da palavra chave com o conteúdo do filho
        if (strncmp(chave, filho->conteudo, len) == 0) {

            // chama recursivo com o resto da chave
            int substatus = deletar_recursivo(filho, chave + len);

            if (substatus == -1) {
                // palavra não achada nesse ramo
                status = -1;
            } else {
                encontrado = 1;

                if (substatus == 1) {
                    // filho ficou vazio, pode remover
                    remover_filho(node, i);
                } else if (substatus == 0) {
                    // tenta fazer merge se possível
                    int contFilhos = contar_filhos(filho);

                    if (!filho->fim_palavra && contFilhos == 1) {
                        Node *neto = filho->filhos[0];
                        int novoTamanho = strlen(filho->conteudo) + strlen(neto->conteudo);

                        // junta os conteúdos
                        char *novoConteudo = (char *)malloc(novoTamanho + 1);
                        strcpy(novoConteudo, filho->conteudo);
                        strcat(novoConteudo, neto->conteudo);

                        // atualiza o conteúdo e os filhos
                        free(filho->conteudo);
                        filho->conteudo = novoConteudo;
                        filho->fim_palavra = neto->fim_palavra;

                        free(filho->filhos);
                        filho->filhos = neto->filhos;

                        free(neto->conteudo);
                        free(neto); // libera o neto
                    }
                }

                status = 0; // deletou com sucesso
            }

            break; // achou o ramo certo, não precisa continuar
        }
    }

    if (!encontrado)
        return -1; // não achou essa palavra em nenhum dos filhos

    // se esse node não é fim de palavra e ficou sem filhos, pode ser removido também
    if (node->fim_palavra == 0 && (node->filhos == NULL || node->filhos[0] == NULL))
        return 1;

    return 0; // node continua existindo
}

// função pública pra deletar uma palavra a partir da raiz
void deletar_palavra(Node *raiz, const char *chave) {
    if (!raiz) return; // árvore nula

    int result = deletar_recursivo(raiz, chave);
    if (result == -1)
        printf("Palavra '%s' não encontrada para deleção.\n", chave);
    else
        printf("Palavra '%s' removida!\n", chave);
}
