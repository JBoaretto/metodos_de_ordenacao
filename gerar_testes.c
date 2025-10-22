#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifdef _WIN32
    #include <direct.h> // Para mkdir no Windows
#else
    #include <sys/stat.h> // Para mkdir no POSIX (Linux/macOS)
    #include <sys/types.h> // Para mkdir no POSIX
#endif

void criar_diretorio(const char* nome_dir) {
    #ifdef _WIN32
        _mkdir(nome_dir);
    #else
        // 0777 dá permissão total (leitura/escrita/execução)
        mkdir(nome_dir, 0777); 
    #endif
}

/**
 * @brief Escreve um vetor de inteiros em um arquivo.
 *
 * @param nome_arquivo O caminho completo do arquivo (ex: "casos_de_teste/ordenado_100.in").
 * @param n O tamanho do vetor.
 * @param vetor O ponteiro para os dados a serem escritos.
 */
void escrever_arquivo(const char* nome_arquivo, int n, int* vetor) {
    FILE *f = fopen(nome_arquivo, "w");
    if (f == NULL) {
        fprintf(stderr, "Erro: Nao foi possivel criar o arquivo %s\n", nome_arquivo);
        return;
    }

    // 1. Escreve o tamanho N na primeira linha
    fprintf(f, "%d\n", n);

    // 2. Escreve os N elementos, um por linha
    for (int i = 0; i < n; i++) {
        fprintf(f, "%d\n", vetor[i]);
    }

    fclose(f);
}

int main() {
    // ---- Configuração ----
    int tamanhos[] = {100, 1000, 10000, 100000};
    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);
    const int RUNS_ALEATORIAS = 5;
    
    // ---- Nome do Diretório de Saída ----
    const char* NOME_DIRETORIO = "casos_de_teste";

    // 1. (NOVO) Cria o diretório de saída antes de começar
    criar_diretorio(NOME_DIRETORIO);

    // Garantir aleatoriedade (UMA ÚNICA VEZ)
    srand(time(NULL));

    printf("Iniciando a geração de casos de teste na pasta '%s/'...\n", NOME_DIRETORIO);

    // ---- Loop Principal (por tamanho) ----
    for (int i = 0; i < num_tamanhos; i++) {
        int n = tamanhos[i];
        printf("Gerando arquivos para N = %d...\n", n);

        // Aloca memória dinamicamente
        int* vetor = (int*)malloc(n * sizeof(int));
        if (vetor == NULL) {
            fprintf(stderr, "Erro: Falha ao alocar memória para N = %d\n", n);
            continue; 
        }

        char nome_arquivo[128]; 

        // ---- 1. Vetor Ordenado (Crescente) ----
        for (int j = 0; j < n; j++) {
            vetor[j] = j + 1; // 1, 2, 3, ... N
        }
        sprintf(nome_arquivo, "%s/ordenado_%d.in", NOME_DIRETORIO, n);
        escrever_arquivo(nome_arquivo, n, vetor);
        printf("  -> %s gerado.\n", nome_arquivo);

        // ---- 2. Vetor Inversamente Ordenado (Decrescente) ----
        for (int j = 0; j < n; j++) {
            vetor[j] = n - j; // N, N-1, ... 1
        }
        sprintf(nome_arquivo, "%s/inverso_%d.in", NOME_DIRETORIO, n);
        escrever_arquivo(nome_arquivo, n, vetor);
        printf("  -> %s gerado.\n", nome_arquivo);

        // ---- 3. Vetores Aleatórios (5 runs) ----
        printf("  -> Gerando %d arquivos aleatórios...\n", RUNS_ALEATORIAS);
        for (int run = 0; run < RUNS_ALEATORIAS; run++) {
            for (int j = 0; j < n; j++) {
                vetor[j] = rand() % (n * 2);
            }
            sprintf(nome_arquivo, "%s/aleatorio_%d_run%d.in", NOME_DIRETORIO, n, run + 1);
            escrever_arquivo(nome_arquivo, n, vetor);
        }
        printf("  -> Arquivos aleatórios para N=%d gerados.\n", n);


        // Libera a memória alocada para este N
        free(vetor);
    }

    printf("\nProcesso concluido! Todos os arquivos .in foram gerados em '%s/'.\n", NOME_DIRETORIO);
    return 0;
}