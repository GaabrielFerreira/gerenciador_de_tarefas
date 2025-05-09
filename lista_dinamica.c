#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lista_dinamica.h"

int count = 0;

// Inicializa a lista, tornando-a vazia
void cria(Lista *p_l) {
    *p_l = NULL;
}

// Verifica se a lista está vazia
int vazia(Lista *p_l) {
    return (*p_l == NULL);
}

// Insere um elemento no final da lista
void insere_fim(Lista *p_l, tarefa e) {
    No_lista *no = (No_lista *)malloc(sizeof(No_lista));
    No_lista *aux = *p_l;

    no->info = e;
    no->prox = NULL;

    if (aux == NULL) {
        *p_l = no;
        return;
    }

    while (aux->prox != NULL)
        aux = aux->prox;

    aux->prox = no;
}

// Insere um elemento ordenado
void insere_ordenado(Lista *p_l, tarefa e) {
    No_lista *novo = (No_lista *)malloc(sizeof(No_lista));
    novo->info = e;
    
    if(*p_l == NULL || e.id < (*p_l)->info.id) {
        novo->prox = *p_l;
        *p_l = novo;
    } else {
        No_lista *atual = *p_l;
        while(atual->prox != NULL && atual->prox->info.id < e.id) {
            atual = atual->prox;
        }
        novo->prox = atual->prox;
        atual->prox = novo;
    }
}

// Ordena a lista de forma crescente
void ordena(Lista *p_l) {
    if (vazia(p_l))
        return;

    No_lista *i = *p_l, *j;
    tarefa temp;

    while (i != NULL) {
        j = i->prox;
        while (j != NULL) {
            if (i->info.prioridade > j->info.prioridade ||
                (i->info.prioridade == j->info.prioridade && i->info.id > j->info.id)) {
                temp = i->info;
                i->info = j->info;
                j->info = temp;
            }
            j = j->prox;
        }
        i = i->prox;
    }
}

// Remove um elemento específico da lista
int remove_valor(Lista *p_l, tarefa e) {
    if (vazia(p_l))
        return 0;

    No_lista *aux = *p_l, *ant = NULL;

    while (aux != NULL && aux->info.id != e.id) {
        ant = aux;
        aux = aux->prox;
    }

    if (aux == NULL)
        return 0;

    if (ant == NULL)
        *p_l = aux->prox;
    else
        ant->prox = aux->prox;

    free(aux);
    return 1;
}

// Libera toda a memória da lista
void libera(Lista *p_l) {
    No_lista *no;

    while (*p_l != NULL) {
        no = *p_l;
        *p_l = no->prox;
        free(no);
    }
}

// Exibe todos os elementos da lista
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

// Busca tarefas por prioridade
int busca_prioridade(Lista *p_l, int prioridade) {
    int count = 0;
    No_lista *aux = *p_l;
    while (aux) {
        if (aux->info.prioridade == prioridade) count++;
        aux = aux->prox;
    }
    return count;
}

// Busca tarefas por categoria
int busca_categoria(Lista *p_l, const char *categoria) {
    int count = 0;
    No_lista *aux = *p_l;
    while (aux) {
        if (strcmp(aux->info.categoria, categoria) == 0) count++;
        aux = aux->prox;
    }
    return count;
}

// Busca tarefa por nome
int busca_nome(Lista *p_l, const char *nome) {
    int count = 0;
    No_lista *aux = *p_l;
    while (aux) {
        if (strstr(aux->info.nome, nome) != NULL) count++;
        aux = aux->prox;
    }
    return count;
}

// Busca tarefa por id
int busca_id(Lista *p_l, int id) {
    No_lista *aux = *p_l;
    while (aux) {
        if (aux->info.id == id) return 1;
        aux = aux->prox;
    }
    return 0;
}

// Funções para testes
void ler_arquivo_fim(Lista *lista, const char *nome_arquivo) {
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

        insere_fim(lista, t);
    }
    fclose(arquivo);
}

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

        insere_ordenado(lista, t);
    }
    fclose(arquivo);
}

//Função para duplicar lista
void duplicar_lista(Lista *origem, Lista *destino) {
    cria(destino);
    No_lista *aux = *origem;
    while (aux != NULL) {
        insere_fim(destino, aux->info);
        aux = aux->prox;
    }
}