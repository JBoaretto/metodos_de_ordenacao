#include <stdio.h>
#include <stdlib.h>
#include "./metodos/bubbleSort.c" // feito
#include "./metodos/contagemDosMenores.c" // sofia
#include "./metodos/heapSort.c" // jao
#include "./metodos/insertionSort.c" // já tem
#include "./metodos/mergeSort.c" // já tem
#include "./metodos/quickSort.c" // já tem
#include "./metodos/radixSort.c" // sofia
#include "./metodos/selectionSort.c" // jao
#include "./metodos/shellSort.c" // já tem
/*
    TO DO:
    - Verificar a entrada de dados (da leitura do arquivo)
    - Implementar demais métodos de ordenação
    - Ajustar os métodos que já tem
    - Testar fluxo do programa (menus, chamadas de funções, etc)
*/


int* ler_vetor(char* nome_arquivo, int tamanho_vetor);
void menu_algoritmos();
void menu_casos();
void menu_tamanhos();

int main(){
    
    menu_algoritmos();
    int menu;    scanf("%d", &menu);

    menu_casos();
    int caso;    scanf("%d", &caso);

    menu_tamanhos();
    int tamanho;    scanf("%d", &tamanho);


    switch (menu) {
    case 1: 
        // bubbleSort();
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
        // bubbleSort();
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

/*
    Para ter o nome do arquivo, já preciso saber o tamanho do vetor, 
    ou seja, não preciso usar como um ponteiro para poder retornar e 
    usar o tamanho posteriormente para loops e como parâmetro para os 
    métodos de ordenação (já que o tamanho já foi escolhido)
*/
int* ler_vetor(char* nome_arquivo, int tamanho_vetor){
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        return NULL;
    }

    int* vetor = (int*)malloc((tamanho_vetor) * sizeof(int));
    if (vetor == NULL) {
        printf("Erro ao alocar memoria para o vetor\n");
        fclose(arquivo);
        return NULL;
    }

    for (int i = 0; i < tamanho_vetor; i++) {
        fscanf(arquivo, "%d", &vetor[i]);
    }

    fclose(arquivo);
    return vetor;
}

void menu_algoritmos(){
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
}

void menu_casos(){
    printf("Agora, escolha qual caso de teste voce quer usar:\n\n");

    printf("[1] Vetor Ordenado (Crescente)\n");
    printf("[2] Vetor Inversamente Ordenado (Decrescente)\n");
    printf("[3] Vetor Aleatorio\n\n");
}

void menu_tamanhos(){
    printf("Por fim, escolha o tamanho do vetor:\n\n");

    printf("[1] 100 elementos\n");
    printf("[2] 1.000 elementos\n");
    printf("[3] 10.000 elementos\n");
    printf("[4] 100.000 elementos\n\n");
}