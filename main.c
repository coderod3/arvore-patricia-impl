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
    inserir_gerenciador(raiz, "casal");

    int opcao = 0;
    char palavra[100];

    while (1) {
        printf("\nMenu:\n");
        printf("1 - Inserir\n");
        printf("2 - Remover\n");
        printf("3 - Buscar\n");
        printf("4 - Carregar arquivo de palavras\n");
        printf("5 - Imprimir\n");
        printf("6 - Exibir dados da árvore\n");
        printf("7 - Sair\n");
        printf("Escolha: ");

        if (scanf("%d", &opcao) != 1) {
            opcao = 0;
            while (getchar() != '\n');
        } else {
            getchar();
        }

        switch (opcao) {
            case 1:
                printf("Digite a palavra para inserir: ");
                scanf("%s", palavra);
                inserir_gerenciador(raiz, palavra);
                break;
            case 2:
                printf("Digite a palavra para remover: ");
                scanf("%s", palavra);
                deletar_palavra(raiz, palavra);
                break;

            case 3:
                printf("Digite a palavra para buscar: ");
                scanf("%s", palavra);
                if (buscar_palavra(raiz, palavra)) {
                    printf("A palavra %s está na árvore.", palavra);
                }else {
                    printf("Essa palavra não foi encontrada na árvore.");
                }
                break;

            case 4: {
                char nomeArquivo[100];
                printf("Digite o caminho do arquivo (ex: ../palavras.txt): ");
                scanf("%s", nomeArquivo);
                carregar_palavras_de_arquivo(raiz, nomeArquivo);
                break;
            }
            case 5:
                printf("\nÁrvore Patricia:\n");
                imprimir_arvore(raiz, "");
                break;

            case 6:
                printf("Dados da árvore: ");
                exibir_estatisticas(raiz);
                break;

            case 7:
                printf("Encerrando...\n");
                return 0;

            default:
                printf("Opção inválida!\n");
        }
    }
    return 0;
}
