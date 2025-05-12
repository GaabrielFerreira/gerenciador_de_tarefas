/*
Titulo: Arvore AVL.h
Autores: Bruno da Silveira, Gabriel Ferreira, Guilherme Coelho, João Volta e Yuri
Data: 06/05/2025
Descrição: Definicoes da estrutura AVL e operacoes basicas para gerenciamento de tarefas
*/

#ifndef TAREFA_DEFINIDA
#define TAREFA_DEFINIDA

#define MAX_NOME 50
#define MAX_DESC 100
#define MAX_CATEGORIA 20

typedef struct {
    int id;
    char nome[MAX_NOME];
    char desc[MAX_DESC];
    int prioridade;
    char categoria[MAX_CATEGORIA];
} tarefa;

#endif

typedef struct no_avl {
    tarefa info;
    int altura;
    struct no_avl *esq;
    struct no_avl *dir;
} No_avl;

typedef No_avl *AVL;

// Funções auxiliares para AVL
int altura(No_avl *no);
int max(int a, int b);
int fator_balanceamento(No_avl *no);
No_avl* rotacao_direita(No_avl *y);
No_avl* rotacao_esquerda(No_avl *x);
No_avl* criar_no(tarefa e);

// Funções básicas
void cria_avl(AVL *p_avl);
int vazia_avl(AVL *p_avl);
void insere_avl(AVL *p_avl, tarefa e);
No_avl* menor_no(No_avl *no);
int remove_avl(AVL *p_avl, int id);

// Funções de busca
int busca_prioridade_avl(AVL *p_avl, int prioridade);
int busca_categoria_avl(AVL *p_avl, const char *categoria);
int busca_nome_avl(AVL *p_avl, const char *nome);
int busca_id_avl(AVL *p_avl, int id);

// Funções para testes
void ler_arquivo_avl(AVL *avl, const char *nome_arquivo);
void libera_avl(AVL *p_avl);
void exibe_avl(AVL *p_avl);
void exibe_em_ordem(AVL p_avl);