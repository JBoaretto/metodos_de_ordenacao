#include <stdio.h>
#include <stdlib.h>
#include "./metodos/bubbleSort.c"
#include "./metodos/contagemDosMenores.c"
#include "./metodos/heapSort.c"
#include "./metodos/insertionSort.c"
#include "./metodos/mergeSort.c"
#include "./metodos/quickSort.c"
#include "./metodos/radixSort.c"
#include "./metodos/selectionSort.c"
#include "./metodos/shellSort.c"

int* ler_vetor(char* nome_arquivo, int* tamanho_vetor);

int main(){
    printf("\nVamos testar metodos de ordenacao!\n");
    printf("Por favor, escolha qual metodo voce quer testar\n\n");

    printf("[1] BubbleSort\n");
    printf("[2] SelectionSort\n");
    printf("[3] InsertionSort\n");
    printf("[4] ShellShort\n");
    printf("[5] QuickSort\n");
    printf("[6] HeapSort\n");
    printf("[7] MergeSort\n");
    printf("[8] Contagem dos Menores\n");
    printf("[9] RadixSort\n");
    printf("[0] Quero testar todos\n\n");

    int menu;    scanf("%d", &menu);

    switch (menu) {
    case 1: bubbleSort(vetor, tamanho_vetor);
        break;
    case 2: selectionSort();   
        break;
    case 3: insertionSort();
        break;
    case 4: shellSort();   
        break;
    case 5: quickSort();   
        break;
    case 6: heapSort();
        break;
    case 7: mergeSort();   
        break;
    case 8: contagemDosMenores();   
        break;
    case 9: radixSort();   
        break;
    case 0:
        bubbleSort(vetor, tamanho_vetor);
        selectionSort();
        insertionSort();
        shellSort();
        quickSort();
        heapSort();
        mergeSort();
        contagemDosMenores();
        radixSort();
        break;    
    default: printf("Opcao invalida!\n");
        break;
    }
    
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