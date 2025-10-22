#include <stdio.h>

void contagemDosMenores(int *vetor, int tamanho_vetor){
    printf("Contagem Dos Menores selecionado!\n");

    int arranjo_aux[tamanho_vetor];
    int array_final[tamanho_vetor];
    int i, j;

    for(i = 0; i < tamanho_vetor; i++){
        arranjo_aux[i] = 0;
    }

    for(i = 1; i < tamanho_vetor; i++){
        for(j = i - 1; j >= 0; j--){
            if(vetor[i] < vetor[j]){
                arranjo_aux[j]++;
            }else{
                arranjo_aux[i]++;
            }
        }
    }

    for(i = 0; i < tamanho_vetor; i++){
        array_final[arranjo_aux[i]] = vetor[i];
    }

    for(i = 0; i < tamanho_vetor; i++){
        vetor[i] = array_final[i];
    }
}