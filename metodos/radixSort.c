#include <stdio.h>

int obter_maior_valor(int *vetor, int tamanho_vetor){
    int max = vetor[0];
    for(int i = 1; i < tamanho_vetor; i++){
        if(vetor[i] > max){
            max = vetor[i];
        }
    }
}

void CountingSort(int *vetor, int tamanho_vetor, int exp){
    int output[tamanho_vetor];
    int i, count[10] = {0};

    // Contagem das ocorrências
    for(i = 0; i < tamanho_vetor; i++){
        count[(vetor[i] / exp) % 10]++;
    }

    // Atualização do array de contagem
    for(i = 1; i < 10; i++){
        count[i] += count[i - 1];
    }

    // Construção do array de saída
    for(i = tamanho_vetor - 1; i >= 0; i--){
        output[count[(vetor[i] / exp) % 10] - 1] = vetor[i];
        count[(vetor[i] / exp) % 10]--;
    }

    // Copia o array de saída de volta para o vetor original
    for(i = 0; i < tamanho_vetor; i++){
        vetor[i] = output[i];
    }
}

void radixSort(vetor, tamanho_vetor){
    printf("radixSort selecionado!\n");

    // Implementação do Radix Sort
    int max = obter_maior_valor(vetor, tamanho_vetor);
    
    for (int exp = 1; max / exp > 0; exp *= 10){
        countingSort(vetor, tamanho_vetor, exp);   
    }
}