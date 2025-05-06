#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lista_dinamica.h"

void testar_operacoes(const char *arquivo) {
    Lista original, copia;
    clock_t inicio, fim, a, b;
    int data_size = atoi(strrchr(arquivo, '_') + 1);
    double total_tempo = 0.;
    
    a = clock();
    // Teste 1: Inserção
    cria(&original);
    inicio = clock();
    ler_arquivo(&original, arquivo);
    fim = clock();
    double tempo_insercao = (double)(fim - inicio)/CLOCKS_PER_SEC;
    total_tempo += tempo_insercao;

    // Teste 2: Ordenação
    duplicar_lista(&original, &copia);
    inicio = clock();
    ordena(&copia);
    fim = clock();
    double tempo_ordenacao = (double)(fim - inicio)/CLOCKS_PER_SEC;
    libera(&copia);
    total_tempo += tempo_ordenacao;

    // Teste 3: Verificação de ordenação
    duplicar_lista(&original, &copia);
    ordena(&copia);
    inicio = clock();
    int ordenada_res = ordenada(&copia);
    fim = clock();
    double tempo_verificacao = (double)(fim - inicio)/CLOCKS_PER_SEC;
    libera(&copia);
    total_tempo += tempo_verificacao;

    // Teste 4: Buscas
    inicio = clock();
    int b_pri = busca_prioridade(&original, 2);
    int b_cat = busca_categoria(&original, "Trabalho");
    int b_nome = busca_nome(&original, "Importante");
    int b_id = busca_id(&original, data_size/2);
    fim = clock();
    double tempo_buscas = (double)(fim - inicio)/CLOCKS_PER_SEC;
    total_tempo += tempo_buscas;

    // Teste 5: Remoções
    // Remoção no início
    duplicar_lista(&original, &copia);
    inicio = clock();
    for(int i = 0; i < data_size/10; i++) {
        tarefa temp;
        remove_inicio(&copia, &temp);
    }
    fim = clock();
    double tempo_rem_inicio = (double)(fim - inicio)/CLOCKS_PER_SEC;
    libera(&copia);
    total_tempo += tempo_rem_inicio;

    // Remoção no fim
    duplicar_lista(&original, &copia);
    inicio = clock();
    for(int i = 0; i < data_size/10; i++) {
        tarefa temp;
        remove_fim(&copia, &temp);
    }
    fim = clock();
    double tempo_rem_fim = (double)(fim - inicio)/CLOCKS_PER_SEC;
    libera(&copia);
    total_tempo += tempo_rem_fim;

    // Remoção por valor
    duplicar_lista(&original, &copia);
    inicio = clock();
    for(int i = 1; i <= data_size/10; i++) {
        tarefa alvo = {.id = i*10};
        remove_valor(&copia, alvo);
    }
    fim = clock();
    double tempo_rem_valor = (double)(fim - inicio)/CLOCKS_PER_SEC;
    libera(&copia);
    total_tempo += tempo_rem_valor;

    // Liberar memória
    libera(&original);

    // Saída formatada para análise
    printf("%d\t%.6fs\t%.6fs\t%.6fs\t%.6fs\t%.6fs\t%.6fs\t%.6fs\t%.6fs\n",
           data_size,
           tempo_insercao,
           tempo_ordenacao,
           tempo_verificacao,
           tempo_buscas,
           tempo_rem_inicio,
           tempo_rem_fim,
           tempo_rem_valor,
           total_tempo);

    b = clock();
    double tempo_total = (double)(b - a)/CLOCKS_PER_SEC;
    printf("TEMPO TOTAL: %.6fs\n\n", tempo_total);
}

int main() {
    printf("Tamanho\tInsercao\tOrdenacao\tVerificacao\tBuscas\t\tRemocao_Inicio\tRemocao_Fim\tRemocao_Valor\tTOTAL\n");
    
    testar_operacoes("tarefas_100.txt");
    testar_operacoes("tarefas_1000.txt");
    testar_operacoes("tarefas_10000.txt");
    testar_operacoes("tarefas_20000.txt");
    testar_operacoes("tarefas_30000.txt");
    testar_operacoes("tarefas_40000.txt");
    testar_operacoes("tarefas_50000.txt");
    
    return 0;
}