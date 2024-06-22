#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

t_heap *criar_heap(int capacidade) {
    t_heap *heap = (t_heap *)malloc(sizeof(t_heap));
    if (heap == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para o heap.\n");
        exit(EXIT_FAILURE);
    }

    heap->itens = (t_nodo **)malloc(capacidade * sizeof(t_nodo *));
    if (heap->itens == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para os itens do heap.\n");
        free(heap);
        exit(EXIT_FAILURE);
    }

    heap->tamanho = 0;
    heap->capacidade = capacidade;
    return heap;
}

void inserir_heap(t_heap *heap, t_nodo *nodo) {
    if (heap->tamanho == heap->capacidade) {
        heap->capacidade *= 2;
        heap->itens = (t_nodo **)realloc(heap->itens, heap->capacidade * sizeof(t_nodo *));
        if (heap->itens == NULL) {
            fprintf(stderr, "Erro ao realocar memoria para os itens do heap.\n");
            exit(EXIT_FAILURE);
        }
    }

    int i = heap->tamanho;
    heap->itens[i] = nodo;
    heap->tamanho++;

    while (i != 0 && (heap->itens[(i - 1) / 2]->frequencia > heap->itens[i]->frequencia ||
                    (heap->itens[(i - 1) / 2]->frequencia == heap->itens[i]->frequencia &&
                    heap->itens[(i - 1) / 2]->item > heap->itens[i]->item))) {
        t_nodo *temp = heap->itens[(i - 1) / 2];
        heap->itens[(i - 1) / 2] = heap->itens[i];
        heap->itens[i] = temp;
        i = (i - 1) / 2;
    }
}

t_nodo *extrair_minimo(t_heap *heap) {
    if (heap->tamanho == 0) {
        return NULL;
    }

    t_nodo *minimo = heap->itens[0];
    heap->tamanho--;
    heap->itens[0] = heap->itens[heap->tamanho];

    int i = 0;
    while (1) {
        int esquerda = 2 * i + 1;
        int direita = 2 * i + 2;
        int menor = i;

        if (esquerda < heap->tamanho && heap->itens[esquerda]->frequencia < heap->itens[menor]->frequencia) {
            menor = esquerda;
        }
        if (direita < heap->tamanho && heap->itens[direita]->frequencia < heap->itens[menor]->frequencia) {
            menor = direita;
        }
        if (menor == i) {
            break;
        }

        t_nodo *temp = heap->itens[i];
        heap->itens[i] = heap->itens[menor];
        heap->itens[menor] = temp;
        i = menor;
    }

    return minimo;
}

void destruir_heap(t_heap *heap) {
    for (int i = 0; i < heap->tamanho; i++) {
        free(heap->itens[i]);
    }
    free(heap->itens);
    free(heap);
}

t_nodo *criar_nodo(char item, int frequencia) {
    t_nodo *nodo = (t_nodo *)malloc(sizeof(t_nodo));
    if (nodo == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para o nodo.\n");
        exit(EXIT_FAILURE);
    }
    nodo->item = item;
    nodo->frequencia = frequencia;
    nodo->esquerda = NULL;
    nodo->direita = NULL;
    nodo->caminho = (char *)malloc(MAX_SIZE * sizeof(char));
    if (nodo->caminho == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para o caminho do nodo.\n");
        free(nodo); 
        exit(EXIT_FAILURE);
    }
    nodo->caminho[0] = '\0';
    return nodo;
}
