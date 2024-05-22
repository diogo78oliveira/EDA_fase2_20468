#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

/**
 * @brief Cria um novo grafo vazio
 *
 * @return Ponteiro para a estrutura de grafo criada
 */
Grafo* criar_grafo() {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    if (grafo == NULL) {
        return NULL;
    }
    grafo->num_vertices = 0;
    grafo->lista_adj = NULL;
    return grafo;
}

/**
 * @brief Destroi um grafo, libertando toda a memoria alocada
 *
 * @param grafo Ponteiro para o grafo a ser destruido
 * @return true se o grafo foi destruido com sucesso, false caso controrio
 */
bool destruir_grafo(Grafo* grafo) {
    if (grafo == NULL) {
        return false;
    }
    for (int i = 0; i < grafo->num_vertices; ++i) {
        No* atual = grafo->lista_adj[i];
        while (atual) {
            Aresta* aresta_atual = atual->lista_arestas;
            while (aresta_atual) {
                Aresta* proxima_aresta = aresta_atual->prox;
                free(aresta_atual);
                aresta_atual = proxima_aresta;
            }
            No* proximo = atual->prox;
            free(atual);
            atual = proximo;
        }
    }
    free(grafo->lista_adj);
    free(grafo);
    return true;
}

/**
 * @brief Adiciona um novo vertice ao grafo
 *
 * @param grafo Ponteiro para o grafo
 * @param valor Valor do v�rtice a ser adicionado
 * @return true se o vertice foi adicionado com sucesso, false caso contrario
 */
bool adicionar_vertice(Grafo* grafo, int valor) {
    if (grafo == NULL) {
        return false;
    }
    No** nova_lista = realloc(grafo->lista_adj, (grafo->num_vertices + 1) * sizeof(No*));
    if (nova_lista == NULL) {
        return false;
    }
    grafo->lista_adj = nova_lista;
    grafo->lista_adj[grafo->num_vertices] = (No*)malloc(sizeof(No));
    if (grafo->lista_adj[grafo->num_vertices] == NULL) {
        return false;
    }
    grafo->lista_adj[grafo->num_vertices]->valor = valor;
    grafo->lista_adj[grafo->num_vertices]->lista_arestas = NULL;
    grafo->lista_adj[grafo->num_vertices]->prox = NULL;
    grafo->num_vertices++;
    return true;
}

/**
 * @brief Adiciona uma nova aresta ao grafo
 *
 * @param grafo Ponteiro para o grafo
 * @param origem Valor do vertice de origem da aresta
 * @param destino Valor do vertice de destino da aresta
 * @param valor Peso ou valor da aresta
 * @return true se a aresta foi adicionada com sucesso, false caso contrario
 */
bool adicionar_aresta(Grafo* grafo, int origem, int destino, int valor) {
    if (grafo == NULL || origem >= grafo->num_vertices || destino >= grafo->num_vertices) {
        return false;
    }
    Aresta* nova_aresta = (Aresta*)malloc(sizeof(Aresta));
    if (nova_aresta == NULL) {
        return false;
    }
    nova_aresta->origem = origem;
    nova_aresta->destino = destino;
    nova_aresta->valor = valor;
    nova_aresta->prox = NULL;

    No* no_origem = grafo->lista_adj[origem];
    Aresta* aresta_atual = no_origem->lista_arestas;

    if (aresta_atual == NULL) {
        no_origem->lista_arestas = nova_aresta;
    }
    else {
        while (aresta_atual->prox != NULL) {
            aresta_atual = aresta_atual->prox;
        }
        aresta_atual->prox = nova_aresta;
    }
    return true;
}

/**
 * @brief Imprime a representa��o do grafo
 *
 * @param grafo Ponteiro para o grafo a ser impresso
 */
bool imprimir_grafo(Grafo* grafo) {
    if (grafo == NULL) {
        return false;
    }
    for (int i = 0; i < grafo->num_vertices; ++i) {
        printf("Vertice %d: %d\n", i, grafo->lista_adj[i]->valor);
        Aresta* aresta_atual = grafo->lista_adj[i]->lista_arestas;
        while (aresta_atual != NULL) {
            printf("   Aresta: %d + %d = %d\n", grafo->lista_adj[aresta_atual->origem]->valor,
                grafo->lista_adj[aresta_atual->destino]->valor,
                aresta_atual->valor);
            aresta_atual = aresta_atual->prox;
        }
    }
}

/**
 * @brief Conecta os vertices na mesma linha, sem somar os valores dos vertices adjacentes
 *
 * @param grafo Ponteiro para o grafo
 * @param matriz Matriz de valores dos vertices
 * @param linha indice da linha a ser processada
 * @param coluna indice da coluna do vertice de origem
 * @return true se os vertices foram conectados com sucesso, false caso contrario
 */
bool conectar_vertices_linha(Grafo* grafo, int matriz[5][5], int linha, int coluna) {
    if (grafo == NULL || linha >= 5 || coluna >= 5) {
        return false;
    }
    for (int k = 0; k < 5; ++k) {
        if (k != coluna) { // Verifica se k nao e o mesmo vertice de coluna
            if (!adicionar_aresta(grafo, linha * 5 + coluna, linha * 5 + k, matriz[linha][coluna] + matriz[linha][k])) {
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief Conecta os vertices na mesma coluna
 *
 * @param grafo Ponteiro para o grafo
 * @param matriz Matriz de valores dos vertices
 * @param linha indice da linha do vertice de origem
 * @param coluna indice da coluna a ser processada
 * @return true se os vertices foram conectados com sucesso, false caso contrario
 */
bool conectar_vertices_coluna(Grafo* grafo, int matriz[5][5], int linha, int coluna) {
    if (grafo == NULL || linha >= 5 || coluna >= 5) {
        return false;
    }
    for (int k = 0; k < 5; ++k) {
        if (k != linha) { // Verifica se k nao e o mesmo vertice de linha
            if (!adicionar_aresta(grafo, linha * 5 + coluna, k * 5 + coluna, matriz[linha][coluna] + matriz[k][coluna])) {
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief Remove um vertice do grafo
 *
 * @param grafo Ponteiro para o grafo
 * @param valor Valor do vertice a ser removido
 * @return true se o vertice foi removido com sucesso, false caso contrario
 */
bool remover_vertice(Grafo* grafo, int valor) {
    if (grafo == NULL) {
        return false;
    }
    // Procurar pelo vertice com o valor especificado
    for (int i = 0; i < grafo->num_vertices; ++i) {
        if (grafo->lista_adj[i]->valor == valor) {
            // Remover todas as arestas conectadas ao vertice
            No* atual = grafo->lista_adj[i];
            while (atual) {
                Aresta* aresta_atual = atual->lista_arestas;
                while (aresta_atual) {
                    Aresta* proxima_aresta = aresta_atual->prox;
                    free(aresta_atual);
                    aresta_atual = proxima_aresta;
                }
                No* proximo = atual->prox;
                free(atual);
                atual = proximo;
            }
            // Deslocar os vertices e direita do vertice removido
            for (int j = i; j < grafo->num_vertices - 1; ++j) {
                grafo->lista_adj[j] = grafo->lista_adj[j + 1];
            }
            grafo->num_vertices--;
            // Redimensionar a lista de adjacencia
            No** nova_lista = realloc(grafo->lista_adj, grafo->num_vertices * sizeof(No*));
            if (grafo->num_vertices > 0 && nova_lista == NULL) {
                return false;
            }
            grafo->lista_adj = nova_lista;
            return true;
        }
    }
    return false;
}

/**
 * @brief Remove uma aresta do grafo
 *
 * @param grafo Ponteiro para o grafo
 * @param origem Valor do vertice de origem da aresta
 * @param destino Valor do vertice de destino da aresta
 * @return true se a aresta foi removida com sucesso, false caso contrario
 */
bool remover_aresta(Grafo* grafo, int origem, int destino) {
    if (grafo == NULL || origem >= grafo->num_vertices || destino >= grafo->num_vertices) {
        return false;
    }
    No* no_origem = grafo->lista_adj[origem];
    Aresta* aresta_atual = no_origem->lista_arestas;
    Aresta* anterior = NULL;

    while (aresta_atual) {
        if (aresta_atual->destino == destino) {
            if (anterior == NULL) {
                no_origem->lista_arestas = aresta_atual->prox;
            }
            else {
                anterior->prox = aresta_atual->prox;
            }
            free(aresta_atual);
            return true;
        }
        anterior = aresta_atual;
        aresta_atual = aresta_atual->prox;
    }
    return false;
}


bool guardar_grafo_binario(Grafo* grafo, const char* nome_ficheiro) {
    FILE* arquivo = fopen(nome_ficheiro, "wb");
    if (!arquivo) {
        printf("Erro");
        return false;
    }

    // Escrever o número de vértices
    fwrite(&grafo->num_vertices, sizeof(int), 1, arquivo);

    // Escrever cada vértice e suas arestas
    for (int i = 0; i < grafo->num_vertices; ++i) {
        No* no_atual = grafo->lista_adj[i];
        fwrite(&no_atual->valor, sizeof(int), 1, arquivo);

        // Escrever as arestas do vértice
        Aresta* aresta_atual = no_atual->lista_arestas;
        while (aresta_atual) {
            fwrite(&aresta_atual->origem, sizeof(int), 1, arquivo);
            fwrite(&aresta_atual->destino, sizeof(int), 1, arquivo);
            fwrite(&aresta_atual->valor, sizeof(int), 1, arquivo);
            aresta_atual = aresta_atual->prox;
        }
        // Marcador de fim de lista de arestas para o vértice atual
        int fim_lista = -1;
        fwrite(&fim_lista, sizeof(int), 1, arquivo);
    }
    return true;
    fclose(arquivo);
    printf("Grafo guardado");

}