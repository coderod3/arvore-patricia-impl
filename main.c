#include "arvore_patricia.h"
#include <stdio.h>

int main() {
    Node *raiz = criar_node("", 0);

    // inserindo palavras teste
    inserir_gerenciador(raiz, "casa");
    inserir_gerenciador(raiz, "casaco");
    inserir_gerenciador(raiz, "casinha");
    inserir_gerenciador(raiz, "carro");
    inserir_gerenciador(raiz, "carga");

    int opcao;
    char palavra[100];

    while (1) {
        printf("\nMenu:\n");
        printf("1 - Inserir\n");
        printf("2 - Imprimir\n");
        printf("3 - Remover\n");
        printf("4 - Carregar arquivo de palavras\n");
        printf("5 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite a palavra para inserir: ");
                scanf("%s", palavra);
                inserir_gerenciador(raiz, palavra);
                break;
            case 2:
                printf("\nÁrvore Patricia:\n");
                imprimir_arvore(raiz, "");
                break;
            case 3:
                printf("Digite a palavra para remover: ");
                scanf("%s", palavra);
                deletar_palavra(raiz, palavra);
                break;
            case 4: {
                char nomeArquivo[100];
                printf("Digite o caminho do arquivo (ex: ../palavras.txt): ");
                scanf("%s", nomeArquivo);
                carregar_palavras_de_arquivo(raiz, nomeArquivo);
                break;
            }
            case 5:
                printf("Encerrando...\n");
                return 0;
            default:
                printf("Opção inválida!\n");
        }
    }
    return 0;
}
