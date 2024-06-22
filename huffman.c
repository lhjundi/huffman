#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

void caminho_nodo(t_nodo *nodo, char *caminho) {
    if (nodo == NULL) {
        return;
    }

    strcpy(nodo->caminho, caminho);

    char caminho_esquerda[MAX_SIZE], caminho_direita[MAX_SIZE];
    strcpy(caminho_esquerda, caminho);
    strcat(caminho_esquerda, "0");
    caminho_nodo(nodo->esquerda, caminho_esquerda);

    strcpy(caminho_direita, caminho);
    strcat(caminho_direita, "1");
    caminho_nodo(nodo->direita, caminho_direita);
}

codigo_huffman *criar_codigo(t_nodo *nodo) {
    codigo_huffman *codigo = (codigo_huffman *)malloc(sizeof(codigo_huffman));
    if (codigo == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para o código Huffman.\n");
        exit(EXIT_FAILURE);
    }

    codigo->codigo = (char *)malloc(MAX_SIZE * sizeof(char));
    if (codigo->codigo == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para o código Huffman.\n");
        free(codigo);
        exit(EXIT_FAILURE);
    }

    strcpy(codigo->codigo, nodo->caminho);
    codigo->item = nodo->item;
    codigo->frequencia = nodo->frequencia;
    return codigo;
}

void pre_ordem(t_nodo *nodo, lista_huffman *lista_codigos) {
    if (nodo == NULL) {
        return;
    }
    if (nodo->item != '-') {
        lista_codigos->itens[lista_codigos->tamanho++] = criar_codigo(nodo);
    }
    pre_ordem(nodo->esquerda, lista_codigos);
    pre_ordem(nodo->direita, lista_codigos);
}

lista_huffman *criar_lista_huffman(t_arvore *arvore) {
    lista_huffman *lista = (lista_huffman *)malloc(sizeof(lista_huffman));
    if (lista == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para a lista Huffman.\n");
        exit(EXIT_FAILURE);
    }

    lista->itens = (codigo_huffman **)malloc(arvore->numero_de_caracteres * sizeof(codigo_huffman *));
    if (lista->itens == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para os itens da lista Huffman.\n");
        free(lista);
        exit(EXIT_FAILURE);
    }

    lista->tamanho = 0;
    return lista;
}

lista_huffman *criar_lista_codigos(t_arvore *arvore) {
    lista_huffman *lista_codigos = criar_lista_huffman(arvore);

    caminho_nodo(arvore->raiz, "");
    pre_ordem(arvore->raiz, lista_codigos);

    return lista_codigos;
}

void imprimir_huffman(lista_huffman *lista_codigos) {
    if (lista_codigos == NULL || lista_codigos->tamanho == 0) {
        printf("A lista de codigos esta vazia.\n");
        return;
    }

    for (int i = 0; i < lista_codigos->tamanho; i++) {
        printf("%c com frequencia %d codificado como %s\n",
               lista_codigos->itens[i]->item,
               lista_codigos->itens[i]->frequencia,
               lista_codigos->itens[i]->codigo);
    }
}

void limpar_lista_codigos(lista_huffman *lista_codigos) {
    if (lista_codigos != NULL) {
        for (int i = 0; i < lista_codigos->tamanho; i++) {
            free(lista_codigos->itens[i]->codigo);
            free(lista_codigos->itens[i]);
        }
        free(lista_codigos->itens);
        lista_codigos->tamanho = 0;
    }
}

void destruir_lista_codigos(lista_huffman *lista_codigos) {
    if (lista_codigos != NULL) {
        limpar_lista_codigos(lista_codigos);
        free(lista_codigos);
    }
}

void decodificar(char *sequencia, lista_huffman *lista_codigos, t_arvore *arvore) {
    if (lista_codigos == NULL || lista_codigos->tamanho == 0) {
        printf("Erro: Lista de codigos nao esta calculada.\n");
        return;
    }

    t_nodo *atual = arvore->raiz;
    for (int i = 0; sequencia[i] != '\0'; i++) {
        if (sequencia[i] == '0') {
            atual = atual->esquerda;
        } else if (sequencia[i] == '1') {
            atual = atual->direita;
        }

        if (atual->esquerda == NULL && atual->direita == NULL) { 
            printf("%c", atual->item);
            atual = arvore->raiz;
        }
    }
    printf("\n");
}

void codificar(char *sequencia, lista_huffman *lista_codigos, int *tamanho_original, int *tamanho_codificado) {
    if (lista_codigos == NULL || lista_codigos->tamanho == 0) {
        printf("Erro: Lista de codigos nao esta calculada.\n");
        return;
    }

    *tamanho_original = strlen(sequencia) * 8;
    *tamanho_codificado = 0;

    for (int i = 0; sequencia[i] != '\0'; i++) {
        for (int j = 0; j < lista_codigos->tamanho; j++) {
            if (sequencia[i] == lista_codigos->itens[j]->item) {
                printf("%s", lista_codigos->itens[j]->codigo);
                *tamanho_codificado += strlen(lista_codigos->itens[j]->codigo);
                break;
            }
        }
    }
    printf("\n");
}

double calcular_taxa_compressao(int tamanho_original, int tamanho_codificado) {
    if (tamanho_original == 0) {
        return 0.0;
    }
    return (1.0 - (double)tamanho_codificado / tamanho_original) * 100.0;
}
