#include <stdio.h>

static void quicksort_rec(int* vetor, int low, int high, long* comparacoes, long* movimentacoes) {

    if (low >= high) return;

    int size = high - low + 1;

    // Caso base para subvetor com 2 elementos
    if (size == 2) {
        (*comparacoes)++;
        if (vetor[low] > vetor[high]) {
            swap_int(&vetor[low], &vetor[high], movimentacoes);
        }
        return;
    }

    // size >= 3
    int mid = low + (high - low) / 2;

    // Mediana de 3 (contando comparações entre elementos)
    (*comparacoes)++;
    if (vetor[mid] < vetor[low])
        swap_int(&vetor[mid], &vetor[low], movimentacoes);

    (*comparacoes)++;
    if (vetor[high] < vetor[low])
        swap_int(&vetor[high], &vetor[low], movimentacoes);

    (*comparacoes)++;
    if (vetor[high] < vetor[mid])
        swap_int(&vetor[high], &vetor[mid], movimentacoes);

    // Coloca o pivô em high-1
    swap_int(&vetor[mid], &vetor[high - 1], movimentacoes);
    int pivot = vetor[high - 1];
    (*movimentacoes)++;

    int i = low;
    int j = high - 1;

    while(1) {
        // Avança i até achar elemento >= pivot
        do {
            i++;
            (*comparacoes)++;
        } while (vetor[i] < pivot);

        // Recua j até achar elemento <= pivot
        do {
            j--;
            (*comparacoes)++;
        } while (vetor[j] > pivot);

        if (i >= j)
            break;

        swap_int(&vetor[i], &vetor[j], movimentacoes);
    }

    // Coloca pivô em sua posição final
    swap_int(&vetor[i], &vetor[high - 1], movimentacoes);

    // Recursão nos subvetores
    quicksort_rec(vetor, low, i - 1, comparacoes, movimentacoes);
    quicksort_rec(vetor, i + 1, high, comparacoes, movimentacoes);

}

void quickSort(int* vetor, int tamanho_vetor, long* comparacoes, long* movimentacoes) {
    printf("QuickSort selecionado!\n");

    if (tamanho_vetor < 2) return;

    if (comparacoes) *comparacoes = 0;
    if (movimentacoes) *movimentacoes = 0;

    quicksort_rec(vetor, 0, tamanho_vetor - 1, comparacoes, movimentacoes);
}