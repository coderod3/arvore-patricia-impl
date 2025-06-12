# Projeto de implementação de uma Árvore Patricia em C, para estrutura de dados II.

O projeto tem funcionalidades básicas de manipular uma Árvore Patricia, incluindo inserção, busca, deleção, carregamento de palavras de arquivo txt, e exibição de estatísticas.

### Alunos:

- Rodrigo Araujo - 841935
- David Camara - 841925
- Aurora Coelho - 841942
- Matheus Abílio - 841929

## Estrutura de Arquivos

- arvore_patricia.h: Cabeçalho principal que define a estrutura do nó (Node) e declara as funções públicas da API da Árvore Patricia.
- inserir.c: Contém as funções responsáveis por adicionar novas palavras à árvore, incluindo lógica para dividir nós quando prefixos comuns são encontrados.
- deletar.c: Implementa a funcionalidade de remover palavras da árvore, com lógica para compactar ou remover nós vazios.
- buscar.c: Contém a função para verificar a existência de uma palavra na árvore.
- imprimir.c: Implementa a função para imprimir todas as palavras na árvore em ordem alfabética.
- carregar_palavras_de_arquivo.c: Contém a função para ler palavras de um arquivo de texto e inseri-las na árvore.
- estatisticas.c: Fornece funções para calcular e exibir estatísticas sobre a árvore, como número de nós, palavras, nível máximo e uso de memória.
- main.c: Contém a função principal que demonstra o uso das funcionalidades da árvore através de um menu interativo.

## Exemplo de Uso

Ao executar o programa, um menu interativo será exibido no console:

*Menu:*

*1 - Inserir*
*2 - Remover*
*3 - Buscar*
*4 - Carregar arquivo de palavras*
*5 - Imprimir*
*6 - Exibir dados da árvore*
*7 - Sair*

*Escolha:*

- Você pode:
- Digite 1 e em seguida a palavra desejada.
- Digite 2 e a palavra a ser deletada.
- Digite 3 e a palavra que deseja buscar.
- Digite 4 para carregar palavras de um arquivo digitando o caminho para o arquivo.
- Digite 5 e print as palavras na arvore.
- Digite 6 e é mostrado um agrupamento de dados da árvore.
- Digite 7 para terminar e sair do programa.
