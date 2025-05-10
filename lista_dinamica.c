/*
Titulo: Lista Dinamica
Autores: João Volta, Bruno da Silveira, Guilherme Coelho, Yuri e Gabriel Ferreira
Data: 06/05/2025
Descrição: Implementação das operacoes realizadas na aplicacao.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lista_dinamica.h" // Definições de 'tarefa', 'No_lista' e 'Lista'

int count = 0; // Contador global não utilizado neste trecho

// Inicializa a lista, tornando-a vazia (ponteiro NULL)
void cria(Lista *p_l) {
    *p_l = NULL;
}

// Verifica se a lista está vazia
int vazia(Lista *p_l) {
    return (*p_l == NULL);
}

// Insere um novo elemento no final da lista
void insere_fim(Lista *p_l, tarefa e) {
    No_lista *no = (No_lista *)malloc(sizeof(No_lista)); // Cria novo nó
    No_lista *aux = *p_l; // Ponteiro auxiliar para percorrer lista

    no->info = e; // Atribui tarefa ao nó
    no->prox = NULL; // Como será o último, o próximo é NULL

    if (aux == NULL) {
        *p_l = no; // Lista estava vazia, insere no início
        return;
    }

    // Percorre até o fim da lista
    while (aux->prox != NULL)
        aux = aux->prox;

    aux->prox = no; // Insere no final
}

// Insere elemento de forma ordenada com base no ID da tarefa
void insere_ordenado(Lista *p_l, tarefa e) {
    No_lista *novo = (No_lista *)malloc(sizeof(No_lista));
    novo->info = e;
    
    // Insere no início se a lista estiver vazia ou o ID for menor que o do primeiro elemento
    if(*p_l == NULL || e.id < (*p_l)->info.id) {
        novo->prox = *p_l;
        *p_l = novo;
    } else {
        No_lista *atual = *p_l;
        // Percorre até encontrar posição correta
        while(atual->prox != NULL && atual->prox->info.id < e.id) {
            atual = atual->prox;
        }
        novo->prox = atual->prox;
        atual->prox = novo;
    }
}

// Ordena a lista em ordem crescente de prioridade (e ID como critério de desempate)
void ordena(Lista *p_l) {
    if (vazia(p_l))
        return;

    No_lista *i = *p_l, *j;
    tarefa temp;

    // Bubble sort entre os nós
    while (i != NULL) {
        j = i->prox;
        while (j != NULL) {
            if (i->info.prioridade > j->info.prioridade ||
                (i->info.prioridade == j->info.prioridade && i->info.id > j->info.id)) {
                // Troca os dados das tarefas
                temp = i->info;
                i->info = j->info;
                j->info = temp;
            }
            j = j->prox;
        }
        i = i->prox;
    }
}

// Remove um elemento específico da lista baseado no ID
int remove_valor(Lista *p_l, tarefa e) {
    if (vazia(p_l))
        return 0;

    No_lista *aux = *p_l, *ant = NULL;

    // Busca elemento com ID correspondente
    while (aux != NULL && aux->info.id != e.id) {
        ant = aux;
        aux = aux->prox;
    }

    if (aux == NULL)
        return 0; // Não encontrado

    if (ant == NULL)
        *p_l = aux->prox; // Remoção do primeiro nó
    else
        ant->prox = aux->prox;

    free(aux); // Libera memória
    return 1;
}

// Libera a memória de todos os nós da lista
void libera(Lista *p_l) {
    No_lista *no;

    while (*p_l != NULL) {
        no = *p_l;
        *p_l = no->prox;
        free(no); // Libera cada nó
    }
}

// Exibe todos os elementos da lista no terminal
void exibe(Lista *p_l) {
    No_lista *no = *p_l;

    printf("\n=== LISTA DE TAREFAS ===\n");
    while (no != NULL) {
        printf("ID: %d\nNome: %s\nDescricao: %s\nPrioridade: %d\nCategoria: %s\n\n",
               no->info.id, no->info.nome, no->info.desc,
               no->info.prioridade, no->info.categoria);
        no = no->prox;
    }
    printf("=======================\n");
}

// Retorna quantas tarefas têm uma determinada prioridade
int busca_prioridade(Lista *p_l, int prioridade) {
    int count = 0;
    No_lista *aux = *p_l;
    while (aux) {
        if (aux->info.prioridade == prioridade) count++;
        aux = aux->prox;
    }
    return count;
}

// Retorna quantas tarefas pertencem a uma categoria específica
int busca_categoria(Lista *p_l, const char *categoria) {
    int count = 0;
    No_lista *aux = *p_l;
    while (aux) {
        if (strcmp(aux->info.categoria, categoria) == 0) count++;
        aux = aux->prox;
    }
    return count;
}

// Retorna quantas tarefas contêm um determinado nome (ou parte dele)
int busca_nome(Lista *p_l, const char *nome) {
    int count = 0;
    No_lista *aux = *p_l;
    while (aux) {
        if (strstr(aux->info.nome, nome) != NULL) count++;
        aux = aux->prox;
    }
    return count;
}

// Verifica se há uma tarefa com um ID específico
int busca_id(Lista *p_l, int id) {
    No_lista *aux = *p_l;
    while (aux) {
        if (aux->info.id == id) return 1;
        aux = aux->prox;
    }
    return 0;
}

// Lê tarefas de um arquivo e insere no fim da lista
void ler_arquivo_fim(Lista *lista, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir arquivo");
        exit(EXIT_FAILURE);
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo)) {
        tarefa t;
        linha[strcspn(linha, "\n")] = 0; // Remove '\n'

        // Parseia linha formatada com ';' como delimitador
        char *token = strtok(linha, ";");
        t.id = atoi(token);

        token = strtok(NULL, ";");
        strncpy(t.nome, token, MAX_NOME-1);

        token = strtok(NULL, ";");
        strncpy(t.desc, token, MAX_DESC-1);

        token = strtok(NULL, ";");
        t.prioridade = atoi(token);

        token = strtok(NULL, ";");
        if (token) 
            strncpy(t.categoria, token, MAX_CATEGORIA-1);

        insere_fim(lista, t); // Insere no final
    }
    fclose(arquivo);
}

// Lê tarefas de um arquivo e insere de forma ordenada por ID
void ler_arquivo_ordenado(Lista *lista, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir arquivo");
        exit(EXIT_FAILURE);
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo)) {
        tarefa t;
        linha[strcspn(linha, "\n")] = 0;

        char *token = strtok(linha, ";");
        t.id = atoi(token);

        token = strtok(NULL, ";");
        strncpy(t.nome, token, MAX_NOME-1);

        token = strtok(NULL, ";");
        strncpy(t.desc, token, MAX_DESC-1);

        token = strtok(NULL, ";");
        t.prioridade = atoi(token);

        token = strtok(NULL, ";");
        if (token) 
            strncpy(t.categoria, token, MAX_CATEGORIA-1);

        insere_ordenado(lista, t); // Insere ordenado por ID
    }
    fclose(arquivo);
}

// Duplica os elementos de uma lista origem para uma nova lista destino
void duplicar_lista(Lista *origem, Lista *destino) {
    cria(destino); // Inicializa a nova lista
    No_lista *aux = *origem;
    while (aux != NULL) {
        insere_fim(destino, aux->info); // Copia tarefa
        aux = aux->prox;
    }
}