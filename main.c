#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ---- swap_int ÚNICA para todos os métodos ---- */
static inline void swap_int(int *a, int *b, unsigned long long *movimentacoes) {
    int tmp = *a;
    (*movimentacoes)++;   // tmp = *a
    *a = *b;
    (*movimentacoes)++;   // *a = *b
    *b = tmp;
    (*movimentacoes)++;   // *b = tmp
}

/* inclui implementações dos métodos (DEVEM usar unsigned long long) */
#include "./metodos/bubbleSort.c"
#include "./metodos/contagemDosMenores.c"
#include "./metodos/heapSort.c"
#include "./metodos/insertionSort.c"
#include "./metodos/mergeSort.c"
#include "./metodos/quickSort.c"
#include "./metodos/radixSort.c"
#include "./metodos/selectionSort.c"
#include "./metodos/shellSort.c"

char* gerar_nome_arquivo(int caso_registros, int tamanho_vetor, char* nome_arquivo, int run);
int* ler_vetor(char* nome_arquivo, int tamanho_vetor);
void menu_algoritmos();
void menu_casos();
void printar_vetor_final(int tamanho_vetor, int *vetor);

/* Struct com unsigned long long */
typedef struct {
    int codigo;
    const char *nome;
    double tempo;
    unsigned long long comparacoes;
    unsigned long long movimentacoes;
} ResultadoAlg;

const char* nome_algoritmo_por_codigo(int codigo) {
    switch (codigo) {
        case 1: return "BubbleSort";
        case 2: return "SelectionSort";
        case 3: return "InsertionSort";
        case 4: return "ShellSort";
        case 5: return "QuickSort";
        case 6: return "HeapSort";
        case 7: return "MergeSort";
        case 8: return "ContagemDosMenores";
        case 9: return "RadixSort";
        default: return "Desconhecido";
    }
}

int main() {
    int algoritmos_escolhidos[9];
    int qtd_alg = 0;

    menu_algoritmos();

    while (1) {
        int escolha;
        printf("Digite o numero do metodo (ou 10 para finalizar a selecao): ");

        if (scanf(" %d", &escolha) != 1) {
            printf("Entrada invalida.\n");
            return 1;
        }

        if (escolha == 10) break;
        if (escolha < 1 || escolha > 9) {
            printf("Opcao invalida!\n");
            continue;
        }

        int existe = 0;
        for (int i = 0; i < qtd_alg; i++)
            if (algoritmos_escolhidos[i] == escolha)
                existe = 1;

        if (existe) {
            printf("Metodo ja selecionado.\n");
            continue;
        }

        algoritmos_escolhidos[qtd_alg++] = escolha;
        printf("Metodo %s selecionado.\n", nome_algoritmo_por_codigo(escolha));
    }

    if (qtd_alg == 0) {
        printf("Nenhum metodo selecionado. Encerrando.\n");
        return 0;
    }

    menu_casos();
    int caso;
    scanf(" %d", &caso);

    if (caso < 1 || caso > 3) {
        printf("Caso invalido!\n");
        return 0;
    }

    const char *nome_caso =
        (caso == 1 ? "ordenado" :
         caso == 2 ? "inverso" : "aleatorio");

    int tamanhos[] = {100, 1000, 10000, 100000};

    FILE *csv = fopen("resultados.csv", "w");
    fprintf(csv, "algoritmo,caso,tamanho,run,tempo_s,comparacoes,movimentacoes\n");

    char nome_arquivo[100];

    for (int t = 0; t < 4; t++) {
        int tamanho_vetor = tamanhos[t];

        printf("\n==============================\n");
        printf("===== TAMANHO DO VETOR: %d =====\n", tamanho_vetor);
        printf("==============================\n");

        ResultadoAlg resultados[9];

        for (int a = 0; a < qtd_alg; a++) {
            int codigo_alg = algoritmos_escolhidos[a];
            const char *nome_alg = nome_algoritmo_por_codigo(codigo_alg);

            double soma_tempo = 0.0;
            unsigned long long soma_comp = 0;
            unsigned long long soma_mov = 0;

            int num_runs = (caso == 3 ? 5 : 1);

            printf("\n===== Executando %s | Caso: %s | Tam: %d =====\n",
                    nome_alg, nome_caso, tamanho_vetor);

            for (int run = 1; run <= num_runs; run++) {
                gerar_nome_arquivo(caso, tamanho_vetor, nome_arquivo,
                                   (caso == 3 ? run : 0));

                int *vetor = ler_vetor(nome_arquivo, tamanho_vetor);

                unsigned long long comparacoes = 0, movimentacoes = 0;

                clock_t inicio = clock();

                switch (codigo_alg) {
                    case 1: bubbleSort(vetor, tamanho_vetor, &comparacoes, &movimentacoes); break;
                    case 2: selectionSort(vetor, tamanho_vetor, &comparacoes, &movimentacoes); break;
                    case 3: insertionSort(vetor, tamanho_vetor, &comparacoes, &movimentacoes); break;
                    case 4: shellSort(vetor, tamanho_vetor, &comparacoes, &movimentacoes); break;
                    case 5: quickSort(vetor, tamanho_vetor, &comparacoes, &movimentacoes); break;
                    case 6: heapSort(vetor, tamanho_vetor, &comparacoes, &movimentacoes); break;
                    case 7: mergeSort(vetor, tamanho_vetor, &comparacoes, &movimentacoes); break;
                    case 8: contagemDosMenores(vetor, tamanho_vetor, &comparacoes, &movimentacoes); break;
                    case 9: radixSort(vetor, tamanho_vetor, &comparacoes, &movimentacoes); break;
                }

                clock_t fim = clock();
                double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

                soma_tempo += tempo;
                soma_comp += comparacoes;
                soma_mov += movimentacoes;

                fprintf(csv, "%s,%s,%d,%d,%.8f,%llu,%llu\n",
                    nome_alg, nome_caso, tamanho_vetor,
                    run, tempo, comparacoes, movimentacoes);

                free(vetor);
            }

            resultados[a].codigo = codigo_alg;
            resultados[a].nome = nome_alg;
            resultados[a].tempo = soma_tempo / num_runs;
            resultados[a].comparacoes = soma_comp / num_runs;
            resultados[a].movimentacoes = soma_mov / num_runs;

            printf(">>> %s - tempo %.8f | comp %llu | mov %llu\n",
                   nome_alg,
                   resultados[a].tempo,
                   resultados[a].comparacoes,
                   resultados[a].movimentacoes);
        }

        /* ENCONTRAR MELHORES */
        int idx_tempo = 0, idx_comp = 0, idx_mov = 0;

        for (int i = 1; i < qtd_alg; i++) {
            if (resultados[i].tempo < resultados[idx_tempo].tempo)
                idx_tempo = i;
            if (resultados[i].comparacoes < resultados[idx_comp].comparacoes)
                idx_comp = i;
            if (resultados[i].movimentacoes < resultados[idx_mov].movimentacoes)
                idx_mov = i;
        }

        printf("\n===== MELHORES (TAM %d) =====\n", tamanho_vetor);
        printf("Menor tempo: %s (%.8f s)\n",
            resultados[idx_tempo].nome, resultados[idx_tempo].tempo);
        printf("Menor comparacoes: %s (%llu)\n",
            resultados[idx_comp].nome, resultados[idx_comp].comparacoes);
        printf("Menor movimentacoes: %s (%llu)\n",
            resultados[idx_mov].nome, resultados[idx_mov].movimentacoes);
    }

    fclose(csv);
    printf("\nArquivo 'resultados.csv' criado!\n");
    return 0;
}

char* gerar_nome_arquivo(int caso_registros, int tamanho_vetor, char* nome_arquivo, int run) {
    strcpy(nome_arquivo, "./casos_de_teste/");

    if (caso_registros == 1) {
        strcat(nome_arquivo, "ordenado_");
    } else if (caso_registros == 2) {
        strcat(nome_arquivo, "inverso_");
    } else if (caso_registros == 3) {
        strcat(nome_arquivo, "aleatorio_");
    }

    char tamanho_str[16];
    sprintf(tamanho_str, "%d", tamanho_vetor);
    strcat(nome_arquivo, tamanho_str);

    if (caso_registros == 3 && run > 0) {
        char sufixo[16];
        sprintf(sufixo, "_run%d", run);
        strcat(nome_arquivo, sufixo);
    }

    strcat(nome_arquivo, ".in");
    return nome_arquivo;
}

int* ler_vetor(char* nome_arquivo, int tamanho_vetor) {
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
        if (fscanf(arquivo, " %d", &vetor[i]) != 1) {
            printf("Erro ao ler elemento %d do arquivo %s\n", i, nome_arquivo);
            free(vetor);
            fclose(arquivo);
            return NULL;
        }
    }

    fclose(arquivo);
    return vetor;
}

void menu_algoritmos() {
    printf("\nVamos testar metodos de ordenacao!\n");
    printf("Selecione UM OU MAIS metodos.\n");
    printf("Digite o numero do metodo e, quando terminar, digite [10] para finalizar a selecao.\n\n");

    printf("[1] BubbleSort\n");
    printf("[2] SelectionSort\n");
    printf("[3] InsertionSort\n");
    printf("[4] ShellSort\n");
    printf("[5] QuickSort\n");
    printf("[6] HeapSort\n");
    printf("[7] MergeSort\n");
    printf("[8] Contagem dos Menores\n");
    printf("[9] RadixSort\n");
    printf("[10] Finalizar selecao de metodos\n\n");
}

void menu_casos() {
    printf("\nAgora, escolha qual caso de teste voce quer usar:\n\n");
    printf("[1] Vetor Ordenado (Crescente)\n");
    printf("[2] Vetor Inversamente Ordenado (Decrescente)\n");
    printf("[3] Vetor Aleatorio (5 vetores diferentes, medias)\n\n");
}

void printar_vetor_final(int tamanho_vetor, int *vetor) {
    printf("\nVetor Ordenado = [");
    for (int k = 0; k < tamanho_vetor; k++) {
        if (k == tamanho_vetor - 1)
            printf("%d", vetor[k]);
        else
            printf("%d, ", vetor[k]);
    }
    printf("]\n");
}
