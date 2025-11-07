#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "./metodos/bubbleSort.c" // feito, testado e com contagem de comparações e movimentações
#include "./metodos/contagemDosMenores.c" // feito, testado e com contagem de comparações e movimentações
#include "./metodos/heapSort.c" // jao
#include "./metodos/insertionSort.c" // já tem
#include "./metodos/mergeSort.c" // já tem
#include "./metodos/quickSort.c" // já tem
#include "./metodos/radixSort.c" // feito, testado e com contagem de comparações e movimentações
#include "./metodos/selectionSort.c" // jao
#include "./metodos/shellSort.c" // já tem
/*
    TO DO:
    - Implementar demais métodos de ordenação
    - Ajustar os métodos que já tem
    - Testar fluxo do programa (menus, chamadas de funções, etc)
    - Adicionar a contagem de comparações e movimentações em todos os métodos
*/

char* gerar_nome_arquivo(int caso_registros, int tamanho_vetor, char* nome_arquivo);
int* ler_vetor(char* nome_arquivo, int tamanho_vetor);
void menu_algoritmos();
void menu_casos();
void menu_tamanhos();

void printar_vetor_final(int tamanho_vetor, int *vetor);

int main(){

    long comparacoes = 0;
    long movimentacoes = 0;

    menu_algoritmos();
    int menu;    scanf(" %d", &menu);

    menu_casos();
    int caso;    scanf(" %d", &caso);

    menu_tamanhos();
    int tamanho;    scanf(" %d", &tamanho);
 
    char nome_arquivo[100] = "./casos_de_teste/";
    gerar_nome_arquivo(caso, tamanho, nome_arquivo);

    if(tamanho == 1){
        tamanho = 100;
    } else if(tamanho == 2){
        tamanho = 1000;
    } else if(tamanho == 3){
        tamanho = 10000;
    } else if(tamanho == 4){
        tamanho = 100000;
    }

    int* vetor = ler_vetor(nome_arquivo, tamanho);
    int tamanho_vetor = tamanho;

    clock_t inicio, fim;
    inicio = clock();

    switch (menu) {
    case 1: 
        bubbleSort(vetor, tamanho_vetor, &comparacoes, &movimentacoes);
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
    case 8: contagemDosMenores(vetor, tamanho_vetor, &comparacoes, &movimentacoes);   
        break;
    case 9: radixSort(vetor, tamanho_vetor, &comparacoes, &movimentacoes);   
        break;
    case 0:
        bubbleSort(vetor, tamanho_vetor, &comparacoes, &movimentacoes);
        selectionSort();
        insertionSort();
        shellSort();
        quickSort();
        heapSort();
        mergeSort();
        contagemDosMenores(vetor, tamanho_vetor, &comparacoes, &movimentacoes);
        radixSort(vetor, tamanho_vetor, &comparacoes, &movimentacoes);
        break;    
    default: printf("Opcao invalida!\n");
        break;
    }
    
    fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de execucao: %.4f\n", tempo);
    printf("Numero de comparacoes: %ld\n", comparacoes);
    printf("Numero de movimentacoes: %ld\n\n", movimentacoes);

    if(menu != 0){
        printf("Voce deseja apresentar o vetor ordenado? [Y/N]\n");
        char printar; scanf(" %c", &printar);

        if(printar == 'Y' || printar == 'y'){
            printar_vetor_final(tamanho_vetor, vetor);
        }
    }

    printf("\n\nPrograma concluido!\n\n");
    return 0;
}

char* gerar_nome_arquivo(int caso_registros, int tamanho_vetor, char* nome_arquivo){
    if(caso_registros == 1){
        strcat(nome_arquivo, "ordenado_");
    }else if(caso_registros == 2){
        strcat(nome_arquivo, "inverso_");
    }else if(caso_registros == 3){
        strcat(nome_arquivo, "aleatorio_");
    }

    if(tamanho_vetor == 1){
        strcat(nome_arquivo, "100");
    } else if(tamanho_vetor == 2){
        strcat(nome_arquivo, "1000");
    } else if(tamanho_vetor == 3){
        strcat(nome_arquivo, "10000");
    } else if(tamanho_vetor == 4){
        strcat(nome_arquivo, "100000");
    }

    if(caso_registros == 3){
        printf("Escolha o caso de teste de 1 a 5 para o vetor aleatorio: ");
        int aleatorio; scanf("%d", &aleatorio);
        strcat(nome_arquivo, "_run");

        char sufixo[2];
        sprintf(sufixo, "%d", aleatorio);

        strcat(nome_arquivo, sufixo);
    }
    
    strcat(nome_arquivo, ".in");

    return nome_arquivo;
}

/*
    Para ter o nome do arquivo, já preciso saber o tamanho do vetor, 
    ou seja, não preciso usar como um ponteiro para poder retornar e 
    usar o tamanho posteriormente para loops e como parâmetro para os 
    métodos de ordenação (já que o tamanho já foi escolhido)
*/
int* ler_vetor(char* nome_arquivo, int tamanho_vetor){
    // ./casos_teste/+ordenado_100_run1+.in
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
        fscanf(arquivo, " %d", &vetor[i]);
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

void printar_vetor_final(int tamanho_vetor, int *vetor){
    printf("\nVetor Ordenado = [");
    for(int k = 0; k < tamanho_vetor; k++){
        if(k - tamanho_vetor == -1){
            printf("%d", vetor[k]);
        }else{
            printf("%d, ", vetor[k]);
        }
    }
    printf("]");
}