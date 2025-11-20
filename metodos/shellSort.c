#include <stdio.h>

void shellSort(int* vetor, int tamanho_vetor, unsigned long long* comparacoes, unsigned long long* movimentacoes) {
    printf("ShellSort selecionado!\n");

    if (tamanho_vetor < 2) {
        return;
    }

    // Zerar contadores
    if (comparacoes) *comparacoes = 0;
    if (movimentacoes) *movimentacoes = 0;

    // Gap usando a sequência de Knuth
    int gap = 1;
    while (gap < tamanho_vetor / 3) {
        gap = 3 * gap + 1;
    }

    for (gap; gap > 0; gap = (gap - 1) / 3) {
        for (int i = gap; i < tamanho_vetor; ++i) {
            int temp = vetor[i];
            (*movimentacoes)++;

            int j = i;

             while (1) {
                if (j < gap) break;

                (*comparacoes)++;
                if (!(vetor[j - gap] > temp)) break;

                vetor[j] = vetor[j - gap]; // move elemento
                (*movimentacoes)++;

                j -= gap;
            }

            vetor[j] = temp;
            (*movimentacoes)++;
        }
    }
}