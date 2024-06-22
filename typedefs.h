#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#define MAX_SIZE 256

typedef struct _nodo {
    char item;      
    char *caminho;
    int frequencia;
    struct _nodo *esquerda;
    struct _nodo *direita;
} t_nodo;

typedef struct {
    t_nodo *raiz;
    int numero_de_caracteres;
} t_arvore;

typedef struct {
    char item;
    char *codigo;
    int frequencia;
} codigo_huffman;

typedef struct {
    codigo_huffman **itens; 
    int tamanho;
} lista_huffman;

typedef struct {
    t_nodo **itens;
    int tamanho;
    int capacidade;
} t_heap;

#endif
