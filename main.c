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

char* gerar_nome_arquivo(int caso_registros, int tamanho_vetor, char* nome_arquivo, int run);
int* ler_vetor(char* nome_arquivo, int tamanho_vetor);
void menu_algoritmos();
void menu_casos();
void menu_tamanhos();
void printar_vetor_final(int tamanho_vetor, int *vetor);

int main(){
    long comparacoes = 0, movimentacoes = 0;
    double tempo = 0.0;

    menu_algoritmos();
    int menu;    scanf(" %d", &menu);

    if(menu < 1 || menu > 9){
        printf("Opcao Invalida!\n");
        return 0;
    }

    menu_casos();
    int caso;    scanf(" %d", &caso);

    menu_tamanhos();
    int tamanho_vetor;    scanf(" %d", &tamanho_vetor);

    if(tamanho_vetor == 1) tamanho_vetor = 100;
    else if(tamanho_vetor == 2) tamanho_vetor = 1000;
    else if(tamanho_vetor == 3) tamanho_vetor = 10000;
    else if(tamanho_vetor == 4) tamanho_vetor = 100000;
    else {
        printf("Tamanho invalido!\n");
        return 0;
    }

    char nome_arquivo[100];

    if(caso == 3){ // Vetor Aleatório: Executar 5 vezes e tirar média
        double soma_tempo = 0;
        long soma_comparacoes = 0, soma_movimentacoes = 0;

        for (int run = 1; run <= 5; run++) {
            gerar_nome_arquivo(caso, tamanho_vetor, nome_arquivo, run);

            int* vetor = ler_vetor(nome_arquivo, tamanho_vetor);
            if (!vetor) {
                printf("Erro ao carregar vetor %d!\n", run);
                continue;
            }

            comparacoes = movimentacoes = 0;
            clock_t inicio = clock();

            switch (menu) { // Menu de escolha do método de ordenação
                case 1: bubbleSort(vetor, tamanho_vetor, &comparacoes, &movimentacoes); break;
                case 2: selectionSort(vetor, tamanho_vetor, &comparacoes, &movimentacoes); break;
                case 3: insertionSort(vetor, tamanho_vetor, &comparacoes, &movimentacoes); break;
                case 4: shellSort(vetor, tamanho_vetor, &comparacoes, &movimentacoes); break;
                case 5: quickSort(vetor, tamanho_vetor, &comparacoes, &movimentacoes); break;
                case 6: heapSort(vetor, tamanho_vetor, &comparacoes, &movimentacoes); break;
                case 7: mergeSort(vetor, tamanho_vetor, &comparacoes, &movimentacoes); break;
                case 8: contagemDosMenores(vetor, tamanho_vetor, &comparacoes, &movimentacoes); break;
                case 9: radixSort(vetor, tamanho_vetor, &comparacoes, &movimentacoes); break;  
                default: printf("Opcao invalida!\n"); break;
            }

            clock_t fim = clock();
            tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

            soma_tempo += tempo;
            soma_comparacoes += comparacoes;
            soma_movimentacoes += movimentacoes;

            free(vetor);
        }

        // Retornando resultados para o usuário
        printf("\n===== RESULTADOS MEDIOS (5 execucoes) =====\n");
        printf("Tempo medio: %.4f s\n", soma_tempo / 5);
        printf("Comparacoes medias: %ld\n", soma_comparacoes / 5);
        printf("Movimentacoes medias: %ld\n", soma_movimentacoes / 5);

    }else{
        gerar_nome_arquivo(caso, tamanho_vetor, nome_arquivo, 0);

        int* vetor = ler_vetor(nome_arquivo, tamanho_vetor);
        if(!vetor){
            printf("Erro ao carregar o vetor!\n");
            return 0;
        }

        clock_t inicio, fim;
        inicio = clock();

        switch (menu) { // Menu de escolha do método de ordenação
            case 1: bubbleSort(vetor, tamanho_vetor, &comparacoes, &movimentacoes); break;
            case 2: selectionSort(vetor, tamanho_vetor, &comparacoes, &movimentacoes); break;
            case 3: insertionSort(vetor, tamanho_vetor, &comparacoes, &movimentacoes); break;
            case 4: shellSort(vetor, tamanho_vetor, &comparacoes, &movimentacoes); break;
            case 5: quickSort(vetor, tamanho_vetor, &comparacoes, &movimentacoes); break;
            case 6: heapSort(vetor, tamanho_vetor, &comparacoes, &movimentacoes); break;
            case 7: mergeSort(vetor, tamanho_vetor, &comparacoes, &movimentacoes); break;
            case 8: contagemDosMenores(vetor, tamanho_vetor, &comparacoes, &movimentacoes); break;
            case 9: radixSort(vetor, tamanho_vetor, &comparacoes, &movimentacoes); break;  
            default: printf("Opcao invalida!\n"); break;
        }
        
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

        // Retornando resultados para o usuário
        
        printf("\n===== RESULTADOS =====\n");
        printf("Tempo de execucao: %.4f\n", tempo);
        printf("Numero de comparacoes: %ld\n", comparacoes);
        printf("Numero de movimentacoes: %ld\n\n", movimentacoes);

        printf("Voce deseja apresentar o vetor ordenado? [Y/N]\n");
        char printar; scanf(" %c", &printar);

        if(printar == 'Y' || printar == 'y'){
            printar_vetor_final(tamanho_vetor, vetor);
        }
        free(vetor);
    }

    printf("\n\nPrograma concluido!\n\n");
    return 0;
}


char* gerar_nome_arquivo(int caso_registros, int tamanho_vetor, char* nome_arquivo, int run){
    strcpy(nome_arquivo, "./casos_de_teste/");

    if(caso_registros == 1){
        strcat(nome_arquivo, "ordenado_");
    }else if(caso_registros == 2){
        strcat(nome_arquivo, "inverso_");
    }else if(caso_registros == 3){
        strcat(nome_arquivo, "aleatorio_");
    }

    char tamanho_str[10];
    sprintf(tamanho_str, "%d", tamanho_vetor);
    strcat(nome_arquivo, tamanho_str);

    // Só adiciona o numero do arquivo run se for vetor aleatório
    if (caso_registros == 3 && run > 0) {
        char sufixo[10];
        sprintf(sufixo, "_run%d", run);
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