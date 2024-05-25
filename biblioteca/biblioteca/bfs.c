/*******************************************************************************************************************
* @file bfs.c
* @autor Diogo Oliveira (a20468@alunos.ipca.pt)
* @brief Implementa��o de fun��es para realizar a pesquisa em largura (BFS).
* Este ficheiro cont�m a implementa��o das fun��es necess�rias para realizar a pesquisa em largura (BFS) em um grafo.
* Inclui as seguintes funcionalidades:
* - Cria��o e manipula��o de uma fila para a BFS
* - Encontrar o caminho mais curto entre dois v�rtices em um grafo
* - Calcular a soma dos valores dos v�rtices num caminho entre dois v�rtices
* @date maio 2024
*
* @copyright Copyright (c) 2024
*
*******************************************************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "bfs.h"


#pragma region Criar Fila
/**
 * @brief Cria uma nova fila com a capacidade especificada.
 *
 * @param capacidade Capacidade m�xima da fila.
 * @return Ponteiro para a fila criada.
 * 
 * @autor Diogo Oliveira
 */
Fila* criar_fila(unsigned capacidade) {
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    fila->capacidade = capacidade;
    fila->frente = fila->tamanho = 0;
    fila->tras = capacidade - 1;
    fila->itens = (int*)malloc(fila->capacidade * sizeof(int));
    return fila;
}
#pragma endregion


#pragma region Fila Cheia
/**
 * @brief Verifica se a fila est� cheia.
 *
 * @param fila A fila a ser verificada.
 * @return Verdadeiro se a fila estiver cheia, falso caso contr�rio.
 * 
 * @autor Diogo Oliveira
 */
bool fila_cheia(Fila* fila) {
    return (fila->tamanho == fila->capacidade);
}
#pragma endregion


#pragma region Fila Vazia
/**
 * @brief Verifica se a fila est� vazia.
 *
 * @param fila A fila a ser verificada.
 * @return Verdadeiro se a fila estiver vazia, falso caso contr�rio.
 * 
 * @autor Diogo Oliveira
 */
bool fila_vazia(Fila* fila) {
    return (fila->tamanho == 0);
}
#pragma endregion


#pragma region Enfileirar
/**
 * @brief Adiciona um valor (valor do vertice) � fila.
 *
 * @param fila A fila onde o valor ser� enfileirado.
 * @param item O valor a ser enfileirado.
 * 
 * @autor Diogo Oliveira
 */
bool enfileirar(Fila* fila, int item) {
    if (fila_cheia(fila)) {
        return;
    }
    fila->tras = (fila->tras + 1) % fila->capacidade;
    fila->itens[fila->tras] = item;
    fila->tamanho = fila->tamanho + 1;
}
#pragma endregion


#pragma region Desenfileirar
/**
 * @brief Remove e retorna o valor na frente da fila.
 *
 * @param fila A fila onde o valor ser� removido.
 * @return O valor removido da fila.
 * 
 * @autor Diogo Oliveira
 */
int desenfileirar(Fila* fila) {
    if (fila_vazia(fila)) {
        return -1;
    }
    int item = fila->itens[fila->frente];
    fila->frente = (fila->frente + 1) % fila->capacidade;
    fila->tamanho = fila->tamanho - 1;
    return item;
}
#pragma endregion


#pragma region Caminho Mais Curto
/**
 * @brief Encontra o caminho mais curto entre dois v�rtices em um grafo usando BFS.
 *
 * @param grafo O grafo onde a procura ser� realizada.
 * @param inicio O v�rtice de in�cio do caminho.
 * @param destino O v�rtice de destino do caminho.
 * 
 * @autor Diogo Oliveira
 */
bool bfs_caminho_mais_curto(Grafo* grafo, int inicio, int destino) {
    if (grafo == NULL || inicio >= grafo->num_vertices || destino >= grafo->num_vertices) {
        return false;
    }

    bool* visitado = (bool*)malloc(grafo->num_vertices * sizeof(bool));
    int* predecessores = (int*)malloc(grafo->num_vertices * sizeof(int));
    for (int i = 0; i < grafo->num_vertices; ++i) {
        visitado[i] = false;
        predecessores[i] = -1;
    }

    Fila* fila = criar_fila(grafo->num_vertices);
    enfileirar(fila, inicio);
    visitado[inicio] = true;

    while (!fila_vazia(fila)) {
        int vertice_atual = desenfileirar(fila);

        if (vertice_atual == destino) {
            break;
        }

        No* no_atual = grafo->lista_adj[vertice_atual];
        Aresta* aresta_atual = no_atual->lista_arestas;

        while (aresta_atual) {
            int vertice_vizinho = aresta_atual->destino;
            if (!visitado[vertice_vizinho]) {
                enfileirar(fila, vertice_vizinho);
                visitado[vertice_vizinho] = true;
                predecessores[vertice_vizinho] = vertice_atual;
            }
            aresta_atual = aresta_atual->prox;
        }
    }

    if (!visitado[destino]) {
        printf("N�o existe caminho entre %d e %d\n", inicio, destino);
    }
    else {
        int atual = destino;
        int tamanho_caminho = 0;

        while (atual != -1) {
            tamanho_caminho++;
            atual = predecessores[atual];
        }

        int* caminho = (int*)malloc(tamanho_caminho * sizeof(int));
        atual = destino;
        int index = tamanho_caminho - 1;
        while (atual != -1) {
            caminho[index--] = atual;
            atual = predecessores[atual];
        }

        printf("Caminho mais curto entre %d e %d: ", inicio, destino);
        for (int i = 0; i < tamanho_caminho; ++i) {
            printf("%d ", caminho[i]);
        }
        printf("\n");


        free(caminho);
    }

    free(visitado);
    free(predecessores);
    free(fila->itens);
    free(fila);
}
#pragma endregion


#pragma region Soma Caminho
/**
 * @brief Calcula a soma dos valores dos v�rtices num dado caminho.
 *
 * @param grafo O grafo onde a pesquisa ser� realizada.
 * @param inicio O v�rtice de in�cio do caminho.
 * @param destino O v�rtice de destino do caminho.
 * @return A soma dos valores dos v�rtices no caminho, ou -1 se n�o existir caminho.
 * 
 * @autor Diogo Oliveira
 */
int soma_valores_caminho(Grafo* grafo, int inicio, int destino) {
    if (grafo == NULL || inicio >= grafo->num_vertices || destino >= grafo->num_vertices) {
        return -1;
    }

    bool* visitado = (bool*)malloc(grafo->num_vertices * sizeof(bool));
    int* predecessores = (int*)malloc(grafo->num_vertices * sizeof(int));
    for (int i = 0; i < grafo->num_vertices; ++i) {
        visitado[i] = false;
        predecessores[i] = -1;
    }

    Fila* fila = criar_fila(grafo->num_vertices);
    enfileirar(fila, inicio);
    visitado[inicio] = true;

    while (!fila_vazia(fila)) {
        int vertice_atual = desenfileirar(fila);

        if (vertice_atual == destino) {
            break;
        }

        No* no_atual = grafo->lista_adj[vertice_atual];
        Aresta* aresta_atual = no_atual->lista_arestas;

        while (aresta_atual) {
            int vertice_vizinho = aresta_atual->destino;
            if (!visitado[vertice_vizinho]) {
                enfileirar(fila, vertice_vizinho);
                visitado[vertice_vizinho] = true;
                predecessores[vertice_vizinho] = vertice_atual;
            }
            aresta_atual = aresta_atual->prox;
        }
    }

    int soma = 0;
    if (!visitado[destino]) {
        printf("N�o existe caminho entre %d e %d\n", inicio, destino);
        soma = -1;
    }
    else {
        int atual = destino;
        while (atual != -1) {
            soma += grafo->lista_adj[atual]->valor;
            atual = predecessores[atual];
        }
    }

    free(visitado);
    free(predecessores);
    free(fila->itens);
    free(fila);

    return soma;
}

#pragma endregion
