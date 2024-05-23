#ifndef GRAFO_H
#define GRAFO_H

#include <stdbool.h> 



#pragma warning (disable: 4996)

/**
 * @brief Estrutura para representar uma aresta na lista de adjacencia
 */
typedef struct Aresta {
    int origem;          /**< Valor do vertice de origem da aresta */
    int destino;         /**< Valor do vertice de destino da aresta */
    int valor;           /**< Peso ou valor associado a aresta */
    struct Aresta* prox; /**< Ponteiro para a proxima aresta na lista de adjacencia */
} Aresta;

/**
 * @brief Estrutura para representar um no (vertice) na lista de adjac�ncia
 */
typedef struct No {
    int valor;            /**< Valor do vertice */
    Aresta* lista_arestas; /**< Ponteiro para a lista de arestas ligadas a este vertice */
    struct No* prox;      /**< Ponteiro para o proximo n� na lista de vertices */
} No;

/**
 * @brief Estrutura para representar um grafo com listas de adjacencia
 */
typedef struct Grafo {
    int num_vertices; /**< Numero de vertices no grafo */
    No** lista_adj;   /**< Ponteiro para um array de ponteiros para nos (lista de adjacencia) */
} Grafo;


Grafo* criar_grafo();
bool destruir_grafo(Grafo* grafo);
bool adicionar_vertice(Grafo* grafo, int valor);
bool adicionar_aresta(Grafo* grafo, int origem, int destino, int valor);
bool imprimir_grafo(Grafo* grafo);
bool guardar_grafo_binario(Grafo* grafo, const char* nome_ficheiro);
#endif /* GRAFO_H */
