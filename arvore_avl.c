/*
Titulo: Arvore AVL.c
Autores: Bruno da Silveira, Gabriel Ferreira, Guilherme Coelho, João Volta e Yuri
Data: 06/05/2025
Descrição: Implementacao das operacoes de insercao, remocao, busca e balanceamento AVL
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arvore_avl.h"

// Retorna a altura de um nó (ou -1 se for NULL)
int altura(No_avl *no) {
    if (no == NULL) return -1;
    return no->altura;
}

// Retorna o maior entre dois valores
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Calcula o fator de balanceamento de um nó
int fator_balanceamento(No_avl *no) {
    if (no == NULL) return 0;
    return altura(no->esq) - altura(no->dir);
}

// Rotação simples à direita
No_avl* rotacao_direita(No_avl *y) {
    No_avl *x = y->esq;
    No_avl *T2 = x->dir;

    // Realiza a rotação
    x->dir = y;
    y->esq = T2;

    // Atualiza alturas
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;

    return x; // Novo nó raiz
}

// Rotação simples à esquerda
No_avl* rotacao_esquerda(No_avl *x) {
    No_avl *y = x->dir;
    No_avl *T2 = y->esq;

    // Realiza a rotação
    y->esq = x;
    x->dir = T2;

    // Atualiza alturas
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;

    return y; // Novo nó raiz
}

// Cria um novo nó AVL com os dados da tarefa
No_avl* criar_no(tarefa e) {
    No_avl *no = (No_avl*)malloc(sizeof(No_avl));
    no->info = e;
    no->altura = 0;
    no->esq = NULL;
    no->dir = NULL;
    return no;
}

// Inicializa a árvore como vazia
void cria_avl(AVL *p_avl) {
    *p_avl = NULL;
}

// Verifica se a árvore está vazia
int vazia_avl(AVL *p_avl) {
    return (*p_avl == NULL);
}

// Insere uma nova tarefa na árvore AVL
void insere_avl(AVL *p_avl, tarefa e) {
    if (*p_avl == NULL) {
        *p_avl = criar_no(e);
        return;
    }

    // Inserção recursiva com base no ID
    if (e.id < (*p_avl)->info.id) {
        insere_avl(&((*p_avl)->esq), e);
    } else if (e.id > (*p_avl)->info.id) {
        insere_avl(&((*p_avl)->dir), e);
    } else {
        return; // ID duplicado não é permitido
    }

    // Atualiza altura do nó atual
    (*p_avl)->altura = 1 + max(altura((*p_avl)->esq), altura((*p_avl)->dir));

    // Verifica balanceamento e realiza rotações se necessário
    int balance = fator_balanceamento(*p_avl);

    // Casos de desbalanceamento
    if (balance > 1 && e.id < (*p_avl)->esq->info.id) {
        *p_avl = rotacao_direita(*p_avl);
        return;
    }

    if (balance < -1 && e.id > (*p_avl)->dir->info.id) {
        *p_avl = rotacao_esquerda(*p_avl);
        return;
    }

    if (balance > 1 && e.id > (*p_avl)->esq->info.id) {
        (*p_avl)->esq = rotacao_esquerda((*p_avl)->esq);
        *p_avl = rotacao_direita(*p_avl);
        return;
    }

    if (balance < -1 && e.id < (*p_avl)->dir->info.id) {
        (*p_avl)->dir = rotacao_direita((*p_avl)->dir);
        *p_avl = rotacao_esquerda(*p_avl);
        return;
    }
}

// Retorna o nó com menor ID (mais à esquerda)
No_avl* menor_no(No_avl *no) {
    No_avl *atual = no;
    while (atual->esq != NULL)
        atual = atual->esq;
    return atual;
}

// Remove uma tarefa pelo ID e rebalanceia a árvore
int remove_avl(AVL *p_avl, int id) {
    if (*p_avl == NULL) return 0;

    if (id < (*p_avl)->info.id) {
        if (!remove_avl(&((*p_avl)->esq), id)) return 0;
    } else if (id > (*p_avl)->info.id) {
        if (!remove_avl(&((*p_avl)->dir), id)) return 0;
    } else {
        // Nó com um ou nenhum filho
        if (((*p_avl)->esq == NULL) || ((*p_avl)->dir == NULL)) {
            No_avl *temp = (*p_avl)->esq ? (*p_avl)->esq : (*p_avl)->dir;

            if (temp == NULL) {
                temp = *p_avl;
                *p_avl = NULL;
            } else {
                **p_avl = *temp;
            }
            free(temp);
        } else {
            // Nó com dois filhos: substitui pelo menor da subárvore direita
            No_avl *temp = menor_no((*p_avl)->dir);
            (*p_avl)->info = temp->info;
            remove_avl(&((*p_avl)->dir), temp->info.id);
        }
    }

    if (*p_avl == NULL) return 1;

    // Atualiza altura e rebalanceia
    (*p_avl)->altura = 1 + max(altura((*p_avl)->esq), altura((*p_avl)->dir));
    int balance = fator_balanceamento(*p_avl);

    // Casos de desbalanceamento após remoção
    if (balance > 1 && fator_balanceamento((*p_avl)->esq) >= 0) {
        *p_avl = rotacao_direita(*p_avl);
        return 1;
    }

    if (balance > 1 && fator_balanceamento((*p_avl)->esq) < 0) {
        (*p_avl)->esq = rotacao_esquerda((*p_avl)->esq);
        *p_avl = rotacao_direita(*p_avl);
        return 1;
    }

    if (balance < -1 && fator_balanceamento((*p_avl)->dir) <= 0) {
        *p_avl = rotacao_esquerda(*p_avl);
        return 1;
    }

    if (balance < -1 && fator_balanceamento((*p_avl)->dir) > 0) {
        (*p_avl)->dir = rotacao_direita((*p_avl)->dir);
        *p_avl = rotacao_esquerda(*p_avl);
        return 1;
    }

    return 1;
}

// Busca a quantidade de tarefas com determinada prioridade
void busca_prioridade_rec(AVL p_avl, int prioridade, int *count) {
    if (p_avl == NULL) return;
    
    if (p_avl->info.prioridade == prioridade) (*count)++;
    
    busca_prioridade_rec(p_avl->esq, prioridade, count);
    busca_prioridade_rec(p_avl->dir, prioridade, count);
}

int busca_prioridade_avl(AVL *p_avl, int prioridade) {
    int count = 0;
    busca_prioridade_rec(*p_avl, prioridade, &count);
    return count;
}

// Busca a quantidade de tarefas de uma determinada categoria
void busca_categoria_rec(AVL p_avl, const char *categoria, int *count) {
    if (p_avl == NULL) return;
    
    if (strcmp(p_avl->info.categoria, categoria) == 0) (*count)++;
    
    busca_categoria_rec(p_avl->esq, categoria, count);
    busca_categoria_rec(p_avl->dir, categoria, count);
}

int busca_categoria_avl(AVL *p_avl, const char *categoria) {
    int count = 0;
    busca_categoria_rec(*p_avl, categoria, &count);
    return count;
}

// Busca por tarefas que contenham o nome fornecido
void busca_nome_rec(AVL p_avl, const char *nome, int *count) {
    if (p_avl == NULL) return;
    
    if (strstr(p_avl->info.nome, nome) != NULL) (*count)++;
    
    busca_nome_rec(p_avl->esq, nome, count);
    busca_nome_rec(p_avl->dir, nome, count);
}

int busca_nome_avl(AVL *p_avl, const char *nome) {
    int count = 0;
    busca_nome_rec(*p_avl, nome, &count);
    return count;
}

// Verifica se existe uma tarefa com determinado ID
int busca_id_avl(AVL *p_avl, int id) {
    AVL atual = *p_avl;
    
    while (atual != NULL) {
        if (id < atual->info.id) {
            atual = atual->esq;
        } else if (id > atual->info.id) {
            atual = atual->dir;
        } else {
            return 1; // Encontrou
        }
    }
    
    return 0; // Não encontrado
}

// Lê tarefas de um arquivo e insere na árvore
void ler_arquivo_avl(AVL *avl, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir arquivo");
        exit(EXIT_FAILURE);
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo)) {
        tarefa t;
        linha[strcspn(linha, "\n")] = 0; // Remove quebra de linha

        // Lê e separa os campos da linha
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

        insere_avl(avl, t);
    }
    fclose(arquivo);
}

// Libera memória de todos os nós da árvore
void libera_avl(AVL *p_avl) {
    if (*p_avl != NULL) {
        libera_avl(&((*p_avl)->esq));
        libera_avl(&((*p_avl)->dir));
        free(*p_avl);
        *p_avl = NULL;
    }
}

// Exibe tarefas em ordem crescente de ID (em-ordem)
void exibe_em_ordem(AVL p_avl) {
    if (p_avl != NULL) {
        exibe_em_ordem(p_avl->esq);
        printf("ID: %d\nNome: %s\nDescricao: %s\nPrioridade: %d\nCategoria: %s\n\n",
               p_avl->info.id, p_avl->info.nome, p_avl->info.desc,
               p_avl->info.prioridade, p_avl->info.categoria);
        exibe_em_ordem(p_avl->dir);
    }
}

// Imprime a árvore completa formatada
void exibe_avl(AVL *p_avl) {
    printf("\n=== ARVORE AVL DE TAREFAS ===\n");
    exibe_em_ordem(*p_avl);
    printf("=============================\n");
}
