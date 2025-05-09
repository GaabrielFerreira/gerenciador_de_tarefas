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

// Funções básicas
void cria_avl(AVL *p_avl);
int vazia_avl(AVL *p_avl);
void insere_avl(AVL *p_avl, tarefa e);
int remove_avl(AVL *p_avl, int id);
void libera_avl(AVL *p_avl);

// Funções de busca
int busca_prioridade_avl(AVL *p_avl, int prioridade);
int busca_categoria_avl(AVL *p_avl, const char *categoria);
int busca_nome_avl(AVL *p_avl, const char *nome);
int busca_id_avl(AVL *p_avl, int id);

// Funções para testes
void ler_arquivo_avl(AVL *avl, const char *nome_arquivo);
void medir_tempo_insercao_avl(AVL *avl, const char *arquivo);
void medir_tempo_busca_avl(AVL *avl);
void exibe_avl(AVL *p_avl);