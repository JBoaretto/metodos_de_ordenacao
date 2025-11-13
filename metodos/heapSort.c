#include <stdio.h>

static inline void swap_int(int *a, int *b, long *movimentacoes) {
    int tmp = *a;
    (*movimentacoes)++;
    *a = *b;
    (*movimentacoes)++;
    *b = tmp;
    (*movimentacoes)++;
}

static void heapify(int *vetor, int tamanho_vetor, int i, long *comparacoes, long *movimentacoes) {
    int largest = i;
    int left  = 2 * i + 1;
    int right = 2 * i + 2;

    // Compara filho esquerdo com o pai
    if (left < tamanho_vetor) {
        (*comparacoes)++;                     
        if (vetor[left] > vetor[largest]) {
            largest = left;
        }
    }

    // Compara filho direito com o "maior" atual
    if (right < tamanho_vetor) {
        (*comparacoes)++;                     
        if (vetor[right] > vetor[largest]) {
            largest = right;
        }
    }

    // Se o maior não é a raiz, troca e continua ajustando
    if (largest != i) {
        swap_int(&vetor[i], &vetor[largest], movimentacoes);
        heapify(vetor, tamanho_vetor, largest, comparacoes, movimentacoes);
    }
}

void heapSort(int *vetor, int tamanho_vetor, long *comparacoes, long *movimentacoes) {
    printf("HeapSort selecionado!\n");

    if (tamanho_vetor <= 1) return;

    if (comparacoes) *comparacoes = 0;
    if (movimentacoes) *movimentacoes = 0;

    for (int i = tamanho_vetor / 2 - 1; i >= 0; i--) {
        heapify(vetor, tamanho_vetor, i, comparacoes, movimentacoes);
    }

    for (int i = tamanho_vetor - 1; i > 0; i--) {
        // maior elemento na posição final
        swap_int(&vetor[0], &vetor[i], movimentacoes);

        // Restaura o heap
        heapify(vetor, i, 0, comparacoes, movimentacoes);
    }
}