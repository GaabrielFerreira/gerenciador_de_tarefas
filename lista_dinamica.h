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

typedef struct no_lista {
    tarefa info;
    struct no_lista *prox;
} No_lista;

typedef No_lista *Lista;

// Funções básicas
void cria(Lista *p_l);
int vazia(Lista *p_l);
void insere_fim(Lista *p_l, tarefa e);
void insere_ordenado(Lista *p_l, tarefa e);
void ordena(Lista *p_l);
int remove_valor(Lista *p_l, tarefa e);
void libera(Lista *p_l);
void exibe(Lista *p_l);

// Funções de busca (modificadas para testes)
int busca_prioridade(Lista *p_l, int prioridade);
int busca_categoria(Lista *p_l, const char *categoria);
int busca_nome(Lista *p_l, const char *nome);
int busca_id(Lista *p_l, int id);

// Funções para testes
void ler_arquivo_fim(Lista *lista, const char *nome_arquivo);
void ler_arquivo_ordenado(Lista *lista, const char *nome_arquivo);
void duplicar_lista(Lista *origem, Lista *destino);