#include <stdio.h>

void bubbleSort(int* vetor, int tamanho_vetor, unsigned long long* comparacoes, unsigned long long* movimentacoes) {
    printf("BubbleSort selecionado!\n");

    if (comparacoes) *comparacoes = 0;
    if (movimentacoes) *movimentacoes = 0;

    // Implementação do Bubble Sort
    int i, j, aux, troca = 1;
    for(i=0; i < tamanho_vetor && troca; i++) {
        troca = 0;
        for(j = 0; j < tamanho_vetor - i - 1; j++) {
            
            (*comparacoes)++; // Contabiliza a comparação

            if(vetor[j] > vetor[j + 1]) {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;

                (*movimentacoes) += 3; // Contabiliza as movimentações
                troca = 1;
            }
        }
    }
}