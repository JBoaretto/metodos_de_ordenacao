#include <stdio.h>

void contagemDosMenores(int *vetor, int tamanho_vetor, long* comparacoes, long* movimentacoes){
    printf("Contagem Dos Menores selecionado!\n");

    int arranjo_aux[tamanho_vetor];
    int array_final[tamanho_vetor];
    int i, j;

    *comparacoes = 0;
    *movimentacoes = 0;

    for(i = 0; i < tamanho_vetor; i++){
        arranjo_aux[i] = 0;
        (*movimentacoes)++; // movimentação: escrita no arranjo auxiliar
    }

    for(i = 1; i < tamanho_vetor; i++){
        for(j = i - 1; j >= 0; j--){
            (*comparacoes)++; // comparação entre vetor[i] e vetor[j]

            if(vetor[i] < vetor[j]){
                arranjo_aux[j]++;
                (*movimentacoes)++; // movimentação: incremento no arranjo auxiliar
            }else{
                arranjo_aux[i]++;
                (*movimentacoes)++; // movimentação: incremento no arranjo auxiliar
            }
        }
    }

    for(i = 0; i < tamanho_vetor; i++){
        array_final[arranjo_aux[i]] = vetor[i];
        (*movimentacoes)++; // movimentação: escrita no array final
    }

    for(i = 0; i < tamanho_vetor; i++){
        vetor[i] = array_final[i];
        (*movimentacoes)++; // movimentação: escrita de volta no vetor original
    }
}