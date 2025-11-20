#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ---- swap_int ÚNICA para todos os métodos ----
static inline void swap_int(int *a, int *b, long *movimentacoes) {
    int tmp = *a;
    (*movimentacoes)++;   // tmp = *a
    *a = *b;
    (*movimentacoes)++;   // *a = *b
    *b = tmp;
    (*movimentacoes)++;   // *b = tmp
}

// inclui implementações dos métodos (usam swap_int)
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
void menu_tamanhos();
void printar_vetor_final(int tamanho_vetor, int *vetor);

typedef struct {
    int codigo;             // 1..9
    const char *nome;       // "BubbleSort", etc
    double tempo;           // tempo médio (ou único) em segundos
    long comparacoes;       // médio ou único
    long movimentacoes;     // médio ou único
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
    // === Seleção de algoritmos ===
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

        if (escolha == 10) {
            break;
        }

        if (escolha < 1 || escolha > 9) {
            printf("Opcao invalida! Tente novamente.\n");
            continue;
        }

        // evitar duplicados
        int ja_existe = 0;
        for (int i = 0; i < qtd_alg; i++) {
            if (algoritmos_escolhidos[i] == escolha) {
                ja_existe = 1;
                break;
            }
        }
        if (ja_existe) {
            printf("Metodo ja selecionado, escolha outro ou digite 10 para finalizar.\n");
            continue;
        }

        algoritmos_escolhidos[qtd_alg++] = escolha;
        printf("Metodo %s selecionado.\n", nome_algoritmo_por_codigo(escolha));
    }

    if (qtd_alg == 0) {
        printf("Nenhum metodo selecionado. Encerrando.\n");
        return 0;
    }

    // === Seleção do caso ===
    menu_casos();
    int caso;
    scanf(" %d", &caso);

    if (caso < 1 || caso > 3) {
        printf("Caso invalido!\n");
        return 0;
    }

    const char *nome_caso = "";
    switch (caso) {
        case 1: nome_caso = "ordenado"; break;
        case 2: nome_caso = "inverso"; break;
        case 3: nome_caso = "aleatorio"; break;
    }

    // === Seleção do tamanho ===
    menu_tamanhos();
    int tamanho_vetor_op;
    scanf(" %d", &tamanho_vetor_op);

    int tamanho_vetor;
    if (tamanho_vetor_op == 1) tamanho_vetor = 100;
    else if (tamanho_vetor_op == 2) tamanho_vetor = 1000;
    else if (tamanho_vetor_op == 3) tamanho_vetor = 10000;
    else if (tamanho_vetor_op == 4) tamanho_vetor = 100000;
    else {
        printf("Tamanho invalido!\n");
        return 0;
    }

    // === Criar CSV do zero nesta execução ===
    const char *csv_filename = "resultados.csv";
    FILE *csv = fopen(csv_filename, "w");
    if (csv == NULL) {
        printf("Erro ao criar arquivo CSV.\n");
        return 1;
    }
    // cabeçalho
    fprintf(csv, "algoritmo,caso,tamanho,run,tempo_s,comparacoes,movimentacoes\n");

    // Vetor de resultados finais (médias ou únicos) para comparar eficiência
    ResultadoAlg resultados[9];

    char nome_arquivo[100];

    // === Rodar cada algoritmo selecionado ===
    for (int idx = 0; idx < qtd_alg; idx++) {
        int codigo_alg = algoritmos_escolhidos[idx];
        const char *nome_alg = nome_algoritmo_por_codigo(codigo_alg);

        double soma_tempo = 0.0;
        long soma_comp = 0;
        long soma_mov = 0;
        int num_runs = (caso == 3) ? 5 : 1;

        printf("\n===== Executando %s | Caso: %s | Tamanho: %d =====\n",
               nome_alg, nome_caso, tamanho_vetor);

        for (int run = 1; run <= num_runs; run++) {
            int run_id = (caso == 3) ? run : 1;

            gerar_nome_arquivo(caso, tamanho_vetor, nome_arquivo,
                               (caso == 3 ? run : 0));

            int *vetor = ler_vetor(nome_arquivo, tamanho_vetor);
            if (!vetor) {
                printf("Erro ao carregar vetor (run %d) para %s.\n", run_id, nome_alg);
                continue;
            }

            long comparacoes = 0, movimentacoes = 0;
            clock_t inicio = clock();

            // chama o algoritmo correto
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
                default: printf("Codigo de metodo invalido.\n"); break;
            }

            clock_t fim = clock();
            double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

            int tempo_muito_pequeno = (tempo < 0.0000001);

            soma_tempo += tempo;
            soma_comp += comparacoes;
            soma_mov += movimentacoes;

            // ==== Impressão humana ====
            if (num_runs > 1) {
                printf("Run %d:\n", run_id);
            } 

            if (tempo_muito_pequeno) {
                printf("  Tempo: extremamente pequeno (abaixo da precisao do clock)\n");
            } else {
                printf("  Tempo: %.8f s\n", tempo);
            }

            printf("  Comparacoes: %ld\n", comparacoes);
            printf("  Movimentacoes: %ld\n", movimentacoes);

            // registra no CSV (uma linha por execução)
            fprintf(csv, "%s,%s,%d,%d,%.8f,%ld,%ld\n",
                    nome_alg,
                    nome_caso,
                    tamanho_vetor,
                    run_id,
                    tempo,
                    comparacoes,
                    movimentacoes);

            free(vetor);
        }

        // médias (ou valor único, se num_runs == 1)
        double tempo_medio = soma_tempo / num_runs;
        long comp_medias = soma_comp / num_runs;
        long mov_medias = soma_mov / num_runs;

        resultados[idx].codigo = codigo_alg;
        resultados[idx].nome = nome_alg;
        resultados[idx].tempo = tempo_medio;
        resultados[idx].comparacoes = comp_medias;
        resultados[idx].movimentacoes = mov_medias;

        if (num_runs > 1) {
            printf(">>> %s - Medias (%d execucoes): tempo = %.6f s, comparacoes = %ld, movimentacoes = %ld\n",
                   nome_alg, num_runs, tempo_medio, comp_medias, mov_medias);
        }
    }

    fclose(csv);

    // === Comparar qual metodo foi melhor em cada categoria ===
if (qtd_alg > 0) {
    int idx_melhor_tempo = 0;
    int idx_melhor_comp = 0;
    int idx_melhor_mov = 0;

    for (int i = 1; i < qtd_alg; i++) {
        if (resultados[i].tempo < resultados[idx_melhor_tempo].tempo) {
            idx_melhor_tempo = i;
        }
        if (resultados[i].comparacoes < resultados[idx_melhor_comp].comparacoes) {
            idx_melhor_comp = i;
        }
        if (resultados[i].movimentacoes < resultados[idx_melhor_mov].movimentacoes) {
            idx_melhor_mov = i;
        }
    }

    const double TIME_EPS = 0.0000001;
    double menor_tempo = resultados[idx_melhor_tempo].tempo;

    // Conta quantos tempos são “quase zero”
    int qtd_tempos_muito_pequenos = 0;
    for (int i = 0; i < qtd_alg; i++) {
        if (resultados[i].tempo < TIME_EPS) {
            qtd_tempos_muito_pequenos++;
        }
    }

    printf("\n===== MELHORES METODOS NESTA EXECUCAO =====\n");

    // Caso 1: vários métodos tiveram tempo “zero”
    if (qtd_tempos_muito_pequenos >= 2) {
        printf("Menor tempo: Nao e possivel determinar com confianca\n");
        printf("             (tempos extremamente pequenos, abaixo da precisao do clock)\n");
        printf("Tempos medidos:\n");
        for (int i = 0; i < qtd_alg; i++) {
            printf("  - %s: %.8f s\n", resultados[i].nome, resultados[i].tempo);
        }
    }
    // Caso 2: só um método teve tempo extremamente pequeno
    else if (menor_tempo < TIME_EPS) {
        printf("Menor tempo: %s (%.8f s — abaixo da precisao do clock, interpretar com cautela)\n",
               resultados[idx_melhor_tempo].nome,
               menor_tempo);
    }
    // Caso 3: tempos normais, escolha clara
    else {
        printf("Menor tempo: %s (%.8f s)\n",
               resultados[idx_melhor_tempo].nome,
               menor_tempo);
    }

    // Comparações e movimentações continuam normais
    printf("Menor numero de comparacoes: %s (%ld comparacoes)\n",
           resultados[idx_melhor_comp].nome,
           resultados[idx_melhor_comp].comparacoes);

    printf("Menor numero de movimentacoes: %s (%ld movimentacoes)\n",
           resultados[idx_melhor_mov].nome,
           resultados[idx_melhor_mov].movimentacoes);
}


    printf("\nPrograma concluido! Arquivo '%s' criado com os resultados desta execucao.\n\n",
           csv_filename);

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

void menu_tamanhos() {
    printf("Por fim, escolha o tamanho do vetor:\n\n");
    printf("[1] 100 elementos\n");
    printf("[2] 1.000 elementos\n");
    printf("[3] 10.000 elementos\n");
    printf("[4] 100.000 elementos\n\n");
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
