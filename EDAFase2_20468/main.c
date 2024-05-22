#include <stdio.h>
#include "grafo.h"
#include "bfs.h"

#pragma comment(lib,"biblioteca.lib")

/**
 * @file main.c
 * @brief Programa principal para demonstrar a utilização das funções de BFS.
 */

int main() {
    int valor;
    int matriz[5][5];
    // Criando um grafo vazio
    Grafo* grafo = criar_grafo();

    // Lendo a matriz de adjacência do arquivo "matriz.txt"
    FILE* arquivo = fopen("matriz.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o ficheiro\n");
        return 1;
    }

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            fscanf(arquivo, "%d;", &matriz[i][j]);
            adicionar_vertice(grafo, matriz[i][j]);
        }
    }
    fclose(arquivo);

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            conectar_vertices_linha(grafo, matriz, i, j);
            conectar_vertices_coluna(grafo, matriz, i, j);
        }
    }

    imprimir_grafo(grafo);

    printf("-----------------------------\n");
    adicionar_vertice(grafo, 100);
    adicionar_aresta(grafo, 25, 25, 200);
    imprimir_grafo(grafo);

    printf("-----------------------------\n");
    remover_vertice(grafo, 100);
    remover_aresta(grafo, 0, 25);
    imprimir_grafo(grafo);

    guardar_grafo_binario(grafo, "grafo.bin");

    printf("-----------------------------\n");
    bfs_caminho_mais_curto(grafo, 4, 21);

    printf("-----------------------------\n");
    int soma = soma_valores_caminho(grafo, 4, 21);
    if (soma != -1) {
        printf("Soma dos valores dos vertices %d\n", soma);
    }

    destruir_grafo(grafo);

    return 0;
}
