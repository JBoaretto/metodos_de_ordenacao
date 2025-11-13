#include <stdio.h>

int obter_maior_valor(int* vetor, int tamanho_vetor, long* comparacoes, long* movimentacoes){
    int max = vetor[0];
    for(int i = 1; i < tamanho_vetor; i++){
        (*comparacoes)++;
        if(vetor[i] > max){
            max = vetor[i];
            (*movimentacoes)++;
        }
    }
    return max;
}

void Contagem_de_Tipos(int *vetor, int tamanho_vetor, int exp, long* comparacoes, long* movimentacoes){
    int array_final[tamanho_vetor];
    int i, count[10] = {0};

    // Contagem de tipos
    for(i = 0; i < tamanho_vetor; i++){
        count[(vetor[i] / exp) % 10]++;
        (*movimentacoes)++;
    }

    // Contagem dos menores
    for(i = 1; i < 10; i++){
        count[i] += count[i - 1];
        (*movimentacoes)++;
    }

    // Montando array final
    for(i = tamanho_vetor - 1; i >= 0; i--){
        array_final[count[(vetor[i] / exp) % 10] - 1] = vetor[i];
        count[(vetor[i] / exp) % 10]--;
        (*movimentacoes) += 2;
    }

    // Copia o array de volta pro vetor original
    for(i = 0; i < tamanho_vetor; i++){
        vetor[i] = array_final[i];
        (*movimentacoes)++;
    }
}

void radixSort(int* vetor, int tamanho_vetor, long* comparacoes, long* movimentacoes){
    printf("RadixSort selecionado!\n");

    // Implementação do Radix Sort
    int max = obter_maior_valor(vetor, tamanho_vetor, comparacoes, movimentacoes);
    
    for (int exp = 1; max / exp > 0; exp *= 10){
        Contagem_de_Tipos(vetor, tamanho_vetor, exp, comparacoes, movimentacoes);   
        (*comparacoes++);
    }
}