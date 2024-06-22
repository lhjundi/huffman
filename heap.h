#ifndef HEAP_H
#define HEAP_H

#include "typedefs.h"

t_nodo *criar_nodo(char item, int frequencia);
t_heap *criar_heap(int capacidade);
void inserir_heap(t_heap *heap, t_nodo *nodo);
t_nodo *extrair_minimo(t_heap *heap);
void destruir_heap(t_heap *heap);

#endif