#ifndef TREE_H
#define TREE_H

#include "typedefs.h"

t_arvore *criar_arvore();
void imprimir_arvore(t_nodo *nodo, int qtd);
void liberar_nodo(t_nodo *nodo);
void limpar_arvore(t_arvore *arvore);
void destruir_arvore(t_arvore *arvore);

#endif
