#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "typedefs.h"

void caminho_nodo(t_nodo *nodo, char *caminho);
codigo_huffman *criar_codigo(t_nodo *nodo);
void pre_ordem(t_nodo *nodo, lista_huffman *lista_codigos);
lista_huffman *criar_lista_huffman(t_arvore *arvore);
lista_huffman *criar_lista_codigos(t_arvore *arvore);
void imprimir_huffman(lista_huffman *lista_codigos);
void limpar_lista_codigos(lista_huffman *lista_codigos);
void destruir_lista_codigos(lista_huffman *lista_codigos);
void decodificar(char *sequencia, lista_huffman *lista_codigos, t_arvore *arvore);
void codificar(char *sequencia, lista_huffman *lista_codigos, int *tamanho_original, int *tamanho_codificado);
void calcular_taxas_compressao(char *texto, int tamanho_codificado, int num_caracteres_distintos);

#endif
