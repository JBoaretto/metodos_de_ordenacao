#include <stdio.h>
#include <stdlib.h>

void merge(int *vetor, int l, int m, int r, int *aux, long *comparacoes, long *movimentacoes) {
    int i = l, j = m + 1, k = l;

    // Intercala as duas metades [l..m] e [m+1..r] em aux
    while (i <= m && j <= r) {
        (*comparacoes)++; // compara vetor[i] e vetor[j]
        if (vetor[i] <= vetor[j]) {
            aux[k++] = vetor[i++];
            (*movimentacoes)++; // copia para aux
        } else {
            aux[k++] = vetor[j++];
            (*movimentacoes)++;
        }
    }

    // Copia o resto da metade esquerda, se sobrar
    while (i <= m) {
        aux[k++] = vetor[i++];
        (*movimentacoes)++;
    }

    // Copia o resto da metade direita, se sobrar
    while (j <= r) {
        aux[k++] = vetor[j++];
        (*movimentacoes)++;
    }

    // Copia de volta de aux para o vetor original
    for (int t = l; t <= r; t++) {
        vetor[t] = aux[t];
        (*movimentacoes)++;
    }
}

void mergeSort_rec(int *vetor, int l, int r, int *aux, long *comparacoes, long *movimentacoes) {
    if (l >= r) return;

    int m = l + (r - l) / 2;

    mergeSort_rec(vetor, l, m, aux, comparacoes, movimentacoes);       // esquerda
    mergeSort_rec(vetor, m + 1, r, aux, comparacoes, movimentacoes);   // direita

    // Otimização: se já estiver em ordem, evita o merge
    (*comparacoes)++; // compara vetor[m] e vetor[m+1]
    if (vetor[m] <= vetor[m + 1]) return;

    merge(vetor, l, m, r, aux, comparacoes, movimentacoes);
}

void mergeSort(int *vetor, int tamanho_vetor, long *comparacoes, long *movimentacoes) {
    printf("MergeSort selecionado!\n");

    if (tamanho_vetor <= 1) return;

    if (comparacoes) *comparacoes = 0;
    if (movimentacoes) *movimentacoes = 0;

    int *aux = (int*) malloc(tamanho_vetor * sizeof(int));
    if (aux == NULL) {
        printf("Erro de alocação de memória\n");
        return;
    }

    mergeSort_rec(vetor, 0, tamanho_vetor - 1, aux, comparacoes, movimentacoes);

    free(aux);
}
