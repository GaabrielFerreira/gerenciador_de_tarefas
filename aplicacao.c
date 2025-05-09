#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lista_dinamica.h"
#include "arvore_avl.h"

void testar_operacoes(const char *arquivo) {
    Lista lista, copia;
    AVL avl;
    clock_t inicio, fim, a, b;
    int data_size = atoi(strrchr(arquivo, '_') + 1);
    double total_tempo_lista = 0.;
    double total_tempo_avl = 0.;
    
    // Cabeçalho para o arquivo atual
    printf("\n\n***** TESTE COM %d ELEMENTOS *****\n", data_size);
    printf("\nTipo\tInsercao\tOrdenacao\tInsere Ordenado\tBuscas\t\tRemocao_Valor\tTOTAL\n");
    
    //INICIA CONTAGEM DE TEMPO DE EXECUCAO PARA LISTA
    a = clock();

    //TESTES LISTA...
    cria(&lista);

    //TESTE 1: INSERCAO FIM
    inicio = clock();
    ler_arquivo_fim(&lista, arquivo);
    fim = clock();
    double tempo_insercao_fim_lista = (double)(fim - inicio)/CLOCKS_PER_SEC;
    total_tempo_lista += tempo_insercao_fim_lista;
    
    //TESTE 2: ORDENA
    duplicar_lista(&lista, &copia);
    inicio = clock();
    ordena(&copia);
    fim = clock();
    double tempo_ordenacao_lista = (double)(fim - inicio)/CLOCKS_PER_SEC;
    libera(&copia);
    total_tempo_lista += tempo_ordenacao_lista;
    
    //TESTE 3: INSERE ORDENADO
    inicio = clock();
    ler_arquivo_ordenado(&lista, arquivo);
    fim = clock();
    double tempo_insercao_ordenado_lista = (double)(fim - inicio)/CLOCKS_PER_SEC;
    total_tempo_lista += tempo_insercao_ordenado_lista;
    
    //TESTE 4: BUSCAS
    inicio = clock();
    int b_pri = busca_prioridade(&lista, 2);
    int b_cat = busca_categoria(&lista, "Trabalho");
    int b_nome = busca_nome(&lista, "Importante");
    int b_id = busca_id(&lista, data_size/2);
    fim = clock();
    double tempo_buscas_lista = (double)(fim - inicio)/CLOCKS_PER_SEC;
    total_tempo_lista += tempo_buscas_lista;
    
    //TESTE 5: REMOVE VALOR
    duplicar_lista(&lista, &copia);
    inicio = clock();
    for(int i = 1; i <= data_size/10; i++) {
        tarefa alvo = {.id = i*10};
        remove_valor(&copia, alvo);
    }
    fim = clock();
    double tempo_rem_valor_lista = (double)(fim - inicio)/CLOCKS_PER_SEC;
    libera(&copia);
    total_tempo_lista += tempo_rem_valor_lista;
    
    // OUTPUT DA LISTA
    printf("LISTA\t%.6fs\t%.6fs\t%.6fs\t%.6fs\t%.6fs\t%.6fs\n",
           tempo_insercao_fim_lista,
           tempo_ordenacao_lista,
           tempo_insercao_ordenado_lista,
           tempo_buscas_lista,
           tempo_rem_valor_lista,
           total_tempo_lista);
    
    libera(&lista);

    
    //TESTES AVL...
    cria_avl(&avl);

    //TESTE 1: INSERCAO
    inicio = clock();
    ler_arquivo_avl(&avl, arquivo);
    fim = clock();
    double tempo_insercao_avl = (double)(fim - inicio)/CLOCKS_PER_SEC;
    total_tempo_avl += tempo_insercao_avl;
    
    //TESTE 2: BUSCAS (a AVL já mantém ordenado, não precisa de ordenação separada)
    inicio = clock();
    int b_pri_avl = busca_prioridade_avl(&avl, 2);
    int b_cat_avl = busca_categoria_avl(&avl, "Trabalho");
    int b_nome_avl = busca_nome_avl(&avl, "Importante");
    int b_id_avl = busca_id_avl(&avl, data_size/2);
    fim = clock();
    double tempo_buscas_avl = (double)(fim - inicio)/CLOCKS_PER_SEC;
    total_tempo_avl += tempo_buscas_avl;
    
    //TESTE 3: REMOCAO
    inicio = clock();
    for(int i = 1; i <= data_size/10; i++) {
        remove_avl(&avl, i*10);
    }
    fim = clock();
    double tempo_remocao_avl = (double)(fim - inicio)/CLOCKS_PER_SEC;
    total_tempo_avl += tempo_remocao_avl;
    
    // OUTPUT DA ARVORE AVL
    printf("AVL\t%.6fs\t---------\t---------\t%.6fs\t%.6fs\t%.6fs\n",
           tempo_insercao_avl,
           tempo_buscas_avl,
           tempo_remocao_avl,
           total_tempo_avl);
    
    libera_avl(&avl);
    
    b = clock();
    double tempo_total = (double)(b - a)/CLOCKS_PER_SEC;
    printf("\nTEMPO TOTAL: %.6fs\n", tempo_total);
    printf("\n------------------------------------------------------------");
}

int main() {
    printf("******** COMPARADOR DE DESEMPENHO: LISTA ENCADEADA vs ARVORE AVL ********");
    
    testar_operacoes("tarefas_crescente_100.txt");
    testar_operacoes("tarefas_crescente_1000.txt");
    testar_operacoes("tarefas_crescente_10000.txt");
    testar_operacoes("tarefas_crescente_20000.txt");
    testar_operacoes("tarefas_crescente_30000.txt");
    testar_operacoes("tarefas_crescente_40000.txt");
    testar_operacoes("tarefas_crescente_50000.txt");
    
    return 0;
}