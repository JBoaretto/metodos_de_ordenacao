#include <stdio.h>

void selectionSort(int *vetor, int tamanho_vetor, unsigned long long *comparacoes, unsigned long long *movimentacoes) {
    printf("SelectionSort selecionado!\n");

    if (comparacoes) *comparacoes = 0;
    if (movimentacoes) *movimentacoes = 0;

    for (int i = 0; i < tamanho_vetor - 1; i++) {
        int min_index = i;

        // Encontra o menor elemento no resto do vetor
        for (int j = i + 1; j < tamanho_vetor; j++) {
            (*comparacoes)++;
            if (vetor[j] < vetor[min_index]) {
                min_index = j;
            }
        }

        // Se encontrou elemento menor, troca
        if (min_index != i) {
            swap_int(&vetor[i], &vetor[min_index], movimentacoes);
        }
    }
}
