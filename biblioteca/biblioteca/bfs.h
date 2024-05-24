#ifndef BFS_H
#define BFS_H

#include "grafo.h"

/**
 * @file bfs.h
 * @brief Definições e declarações para o algoritmo de pesquisa em largura (BFS).
 */

 /**
  * @struct Fila
  * @brief Estrutura de dados para uma fila utilizada na BFS.
  */
typedef struct Fila {
    int* itens; ///< Array para armazenar os itens da fila.
    int frente; ///< Índice da frente da fila.
    int tras;   ///< Índice da traseira da fila.
    int tamanho; ///< Número atual de elementos na fila.
    unsigned capacidade; ///< Capacidade máxima da fila.
} Fila;


Fila* criar_fila(unsigned capacidade);
bool fila_cheia(Fila* fila);
bool fila_vazia(Fila* fila);
bool enfileirar(Fila* fila, int item);
int desenfileirar(Fila* fila);
bool bfs_caminho_mais_curto(Grafo* grafo, int inicio, int destino);
int soma_valores_caminho(Grafo* grafo, int inicio, int destino);

#endif /* BFS_H */
