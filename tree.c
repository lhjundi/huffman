#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

// Implementação das funções declaradas em tree.h

t_arvore *criar_arvore() {
    t_arvore *arvore = (t_arvore *)malloc(sizeof(t_arvore));
    if (arvore == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para a árvore.\n");
        exit(EXIT_FAILURE);
    }
    arvore->raiz = NULL;
    arvore->numero_de_caracteres = 0;
    return arvore;
}

void imprimir_arvore(t_nodo *nodo, int qtd) {
    if (nodo == NULL) {
        return;
    }
    imprimir_arvore(nodo->direita, qtd + 1); // Percorre a subárvore direita
    for (int i = 0; i < qtd; i++) {
        printf("\t"); // Imprime tabulações para indicar o nível
    }
    if (nodo->item == '-') {
        printf("-\n"); // Imprime o caractere '-' para nodos internos
    } else {
        printf("%c (%d)\n", nodo->item, nodo->frequencia); // Imprime o caractere e sua frequência para folhas
    }
    imprimir_arvore(nodo->esquerda, qtd + 1); // Percorre a subárvore esquerda
}

void liberar_nodo(t_nodo *nodo) {
    if (nodo == NULL) {
        return;
    }
    liberar_nodo(nodo->esquerda);  // Libera a subárvore esquerda recursivamente
    liberar_nodo(nodo->direita);   // Libera a subárvore direita recursivamente
    free(nodo->caminho);           // Libera a memória do caminho
    free(nodo);                    // Libera a memória do nodo
}

void limpar_arvore(t_arvore *arvore) {
    if (arvore == NULL) {
        return;
    }
    liberar_nodo(arvore->raiz); // Libera todos os nodos da árvore
    arvore->raiz = NULL;
    arvore->numero_de_caracteres = 0;
}

void destruir_arvore(t_arvore *arvore) {
    if (arvore == NULL) {
        return;
    }
    limpar_arvore(arvore); // Limpa a árvore antes de liberar sua memória
    free(arvore);
}
