#include "arvore_patricia.h"

// cria um novo node para a arvore
Node *criar_node(const char *conteudo, int fim_palavra) {
    Node *novo_node = (Node *)malloc(sizeof(Node));

    novo_node->conteudo = strdup(conteudo); // faz uma cópia da string passada
    novo_node->fim_palavra = fim_palavra;
    novo_node->filhos = (Node **)calloc(1, sizeof(Node *)); // inicializa o vetor de filhos com NULL

    return novo_node;
}


// retorna o prefixo que as duas strings tem em comum
char *prefixo_comum(const char *s1, const char *s2) {
    int i = 0;

    while (s1[i] && s2[i] && s1[i] == s2[i]) {  // compara os dois caracteres até onde forem iguais
        i++;
    }

    char *prefixo = (char *)malloc(i + 1);
    strncpy(prefixo, s1, i);
    prefixo[i] = '\0'; // finaliza a string
    return prefixo;
}

// procura entre os filhos um que tenha prefixo em comum com a palavra chave
Node *encontrar_filho_prefixo(Node *raiz, const char *chave, char **prefixo) {
    if (!raiz->filhos) return NULL;

    for (int i = 0; raiz->filhos[i]; i++) {
        char *comum = prefixo_comum(chave, raiz->filhos[i]->conteudo);  // pega o prefixo comum entre chave e conteúdo do filho

        if (strlen(comum) > 0) {
            *prefixo = comum;
            return raiz->filhos[i];
        }

        free(comum);
    }

    *prefixo = NULL;  // nenhum filho tinha prefixo em comum
    return NULL;
}

// divide o filho em dois quando só uma parte do conteudo bate com a palavra
void dividir_node(Node *pai, Node *filho, const char *chave, char *prefixo) {
    Node *intermediario = criar_node(prefixo, 0);  // cria node intermediário com o prefixo

    // atualiza o filho removendo a parte do prefixo
    char *novo_conteudo = strdup(filho->conteudo + strlen(prefixo));
    free(filho->conteudo);
    filho->conteudo = novo_conteudo;

    // cria um vetor com os dois filhos e null
    intermediario->filhos = (Node **)calloc(3, sizeof(Node *));
    intermediario->filhos[0] = filho;
    intermediario->filhos[1] = criar_node(chave + strlen(prefixo), 1);
    intermediario->filhos[2] = NULL;

    // troca o filho antigo pelo novo intermediário na lista de filhos do pai
    for (int i = 0; pai->filhos[i]; i++) {
        if (pai->filhos[i] == filho) {
            pai->filhos[i] = intermediario;
            break;
        }
    }
}

// adiciona um novo node com a chave como filho do pai
void criar_folha(Node *pai, const char *chave) {
    Node *novo_node = criar_node(chave, 1);  // cria novo node folha com a chave

    int num_filhos = 0;
    while (pai->filhos && pai->filhos[num_filhos]) {  // conta quantos filhos já existem
        num_filhos++;
    }

    // realoca espaço para mais um filho
    Node **nova_lista = (Node **)realloc(pai->filhos, (num_filhos + 2) * sizeof(Node *));

    pai->filhos = nova_lista;
    pai->filhos[num_filhos] = novo_node; // adiciona novo filho
    pai->filhos[num_filhos + 1] = NULL;// finaliza vetor com null
}


// administra e insere uma chave na arvore patricia de forma recursiva
void inserir_gerenciador(Node *raiz, const char *chave) {
    if (!raiz)
        return;

    char *prefixo = NULL;
    Node *filho = encontrar_filho_prefixo(raiz, chave, &prefixo);  // tenta achar filho com prefixo em comum

    if (filho) {
        if (strcmp(prefixo, filho->conteudo) == 0) {
            // o conteúdo do filho é igual ao prefixo, continua recursivamente
            inserir_gerenciador(filho, chave + strlen(prefixo));
        } else {
            // os conteúdos divergem, precisa dividir o node
            dividir_node(raiz, filho, chave, prefixo);
        }
        free(prefixo);  // libera memória do prefixo usado
    } else {
        // nenhum filho bate com prefixo, insere como um novo node separado
        criar_folha(raiz, chave);
    }
}
