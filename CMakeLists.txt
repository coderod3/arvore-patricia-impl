cmake_minimum_required(VERSION 3.31)
project(arvore_patricia C)

set(CMAKE_C_STANDARD 11)

add_executable(arvore_patricia
        arvore_patricia.h
        inserir.c
        imprimir.c
        main.c
        deletar.c
        buscar.c
        estatisticas.c
        carregar_palavras_de_arquivo.c
)
