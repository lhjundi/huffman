#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "heap.h"
#include "tree.h"
#include "huffman.h"

int main() {
    t_arvore *arvore = criar_arvore();
    t_heap *heap = criar_heap(MAX_SIZE);
    lista_huffman *lista_codigos = NULL;
    int frequencias[MAX_SIZE] = {0};
    char option[10];

    printf("\nBem-vindo ao Codificador Huffman!\n");

    do {
        printf("\nMenu:\n");
        printf("1. add <E> <freq>   - Adicionar Caractere\n");
        printf("2. calc             - Calcular Codigos Huffman\n");
        printf("3. print            - Imprimir Codigos Huffman\n");
        printf("4. cod <str>        - Codificar Texto\n");
        printf("5. dec <bits>       - Decodificar Bits\n");
        printf("6. clear            - Limpar Tabela de Frequencias\n");
        printf("7. exit             - Sair\n");
        printf("\n-> ");

        scanf("%s", option);

        if (strcmp(option, "add") == 0) {
            char caractere;
            int frequencia;
            scanf(" %c %d", &caractere, &frequencia);
            caractere = toupper(caractere);

            if (frequencia <= 0 || !isalpha(caractere)) {
                printf("Erro: Frequencia deve ser positiva e o caractere deve ser uma letra.\n");
            }

            frequencias[caractere] = frequencia;
            inserir_heap(heap, criar_nodo(caractere, frequencia));
            if (arvore->raiz != NULL) {
                limpar_arvore(arvore);
            }
            arvore->numero_de_caracteres++;
            printf("Caractere adicionado com sucesso!\n");
        } else if (strcmp(option, "calc") == 0) {
            if (heap->tamanho < 2) {
                printf("Erro: Informe ao menos dois caracteres com suas frequencias.\n");
            } else {
                while (heap->tamanho > 1) {
                    t_nodo *esquerda = extrair_minimo(heap);
                    t_nodo *direita = extrair_minimo(heap);
                    t_nodo *pai = criar_nodo('-', esquerda->frequencia + direita->frequencia);
                    pai->esquerda = esquerda;
                    pai->direita = direita;
                    inserir_heap(heap, pai);
                }
                arvore->raiz = extrair_minimo(heap);

                if (lista_codigos != NULL) {
                    destruir_lista_codigos(lista_codigos);
                }
                lista_codigos = criar_lista_codigos(arvore);
                printf("Codigos Huffman calculados com sucesso!\n");
            }
        } else if (strcmp(option, "print") == 0) {
            imprimir_huffman(lista_codigos);
        } else if (strcmp(option, "cod") == 0) {
            printf("Texto Codificado: ");
            char texto[MAX_SIZE];
            fgets(texto, MAX_SIZE, stdin); 
            texto[strcspn(texto, "\n")] = 0;
            int tamanho_original, tamanho_codificado;
            codificar(texto, lista_codigos, &tamanho_original, &tamanho_codificado);
            calcular_taxas_compressao(texto, tamanho_codificado, arvore->numero_de_caracteres);
        } else if (strcmp(option, "dec") == 0) {
            char bits[MAX_SIZE];
            printf("Bits Decodificados: ");
            fgets(bits, MAX_SIZE, stdin);
            bits[strcspn(bits, "\n")] = 0;
            decodificar(bits, lista_codigos, arvore);
        } else if (strcmp(option, "clear") == 0) {
            limpar_lista_codigos(lista_codigos);
            destruir_heap(heap);
            heap = criar_heap(MAX_SIZE);
            limpar_arvore(arvore);
            memset(frequencias, 0, sizeof(frequencias));
            printf("Tabela de frequencias e arvore limpas com sucesso!\n");
        } else {
            printf("Invalido!\n");
            while (getchar() != '\n');
        }
    } while (strcmp(option, "exit") != 0);
    destruir_lista_codigos(lista_codigos);
    destruir_heap(heap);
    destruir_arvore(arvore);
    printf("Obrigado por usar o Codificador Huffman! Espero que tenha sido util.\n");
    return 0;
}