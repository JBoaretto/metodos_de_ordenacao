#include <stdio.h>

void bubbleSort(int* vetor, int tamanho_vetor) {
    printf("BubbleSort selecionado!\n");

    // Implementação do Bubble Sort
    int i, j, aux, troca = 1;
    for(i=0; i < tamanho_vetor && troca; i++) {
        troca = 0;
        for(j = 0; j < tamanho_vetor - i - 1; j++) {
            if(vetor[j] > vetor[j + 1]) {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
                troca = 1;
            }
        }
    }
}