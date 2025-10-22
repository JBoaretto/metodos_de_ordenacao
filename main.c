#include <stdio.h>
#include "./metodos/bubbleSort.c"
#include "./metodos/contagemDosMenores.c"
#include "./metodos/heapSort.c"
#include "./metodos/insertionSort.c"
#include "./metodos/mergeSort.c"
#include "./metodos/quickSort.c"
#include "./metodos/radixSort.c"
#include "./metodos/selectionSort.c"
#include "./metodos/shellShort.c"

int* ler_vetor(char* nome_arquivo, int* tamanho_vetor);

int main(){
    printf("Vamos testar métodos de ordenação!\n");
    printf("Por favor, escolha qual método você quer testar\n");
}

int* ler_vetor(char* nome_arquivo, int* tamanho_vetor){
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        return NULL;
    }

    fscanf(arquivo, "%d", tamanho_vetor);
    int* vetor = (int*)malloc((*tamanho_vetor) * sizeof(int));
    if (vetor == NULL) {
        printf("Erro ao alocar memoria para o vetor\n");
        fclose(arquivo);
        return NULL;
    }

    for (int i = 0; i < *tamanho_vetor; i++) {
        fscanf(arquivo, "%d", &vetor[i]);
    }

    fclose(arquivo);
    return vetor;
}