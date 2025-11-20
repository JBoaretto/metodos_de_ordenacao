#include <stdio.h>

void insertionSort(int *vetor, int tamanho_vetor, unsigned long long *comparacoes, unsigned long long *movimentacoes) {
    printf("InsertionSort selecionado!\n");

    if (comparacoes) *comparacoes = 0;
    if (movimentacoes) *movimentacoes = 0;

    for (int i = 1; i < tamanho_vetor; i++) {
        int key = vetor[i];
        (*movimentacoes)++;

        int j = i - 1;

        // Comparação de chaves feita dentro do while
        while (j >= 0) {
            (*comparacoes)++;

            if (key >= vetor[j])
                break;

            // Desloca elemento para a direita
            vetor[j + 1] = vetor[j];
            (*movimentacoes)++;

            j--;
        }

        // Coloca na posição correta
        vetor[j + 1] = key;
        (*movimentacoes)++;
    }
}