#include "arvore_patricia.h"


// recebe o ponteiro para raiz de uma arvore e uma palavra chave e performa a busca
int buscar_palavra(Node *raiz, const char *chave) {
    // verifica se a árvore está vazia
    if (!raiz) return 0;

    // inicializa ponteiros para navegação
    Node *atual = raiz;
    const char *resto = chave;     // restante da palavra chave a ser buscada

    while (atual->filhos) {
        int encontrado = 0;
        
        // percorre todos os filhos do node atual
        for (int i = 0; atual->filhos[i]; i++) {
            Node *filho = atual->filhos[i];
            
            // compara o conteúdo do filho com o resto
            if (strncmp(resto, filho->conteudo, strlen(filho->conteudo)) == 0) { // se for igual retorna 0, foi encontrado
                encontrado = 1;
                atual = filho; // anda para o filho

                // parte da palavra foi encontrada então avança o ponteiro pra parte que ainda não achou
                resto += strlen(filho->conteudo);
                break;
            }
        }
        
        // se não foi encontrado, break
        if (!encontrado) {
            break;
        }
    }

    // se em resto sobrar apenas \0 e o nó atual for um fim de palavra então encontrou e retorna 1, se não 0.
    return (*resto == '\0' && atual->fim_palavra);
}