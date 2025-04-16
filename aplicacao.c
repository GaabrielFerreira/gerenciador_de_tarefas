#include <stdio.h>
#include <stdlib.h>
#include "lista_dinamica.h"

int opcao2;

void escolhaInsere();
void escolhaRemove();
void escolhaBusca();

int main () {
    Lista *p_l;
    int opcao;

    do{
        printf("\n****** MENU ******\n1 - Insere\n2 - Remove\n3 - Ordena\n 4 - Busca\n5 - Altera\n6 - Limpa TUDO\n 7 - Mostra tarefas\n8 - SAIR\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao){
            case 1:
                escolhaInsere();
                break;
            case 2:
                escolhaRemove();
                break;
            case 3:
                /*PRIORIDADE
                    CATEGORIA
                        NOME*/
                break;
            case 4:
                escolhaBusca();
                break;
            case 5:
                /*ALTERA PELO ID
                    O QUE DESEJA ALTERAR DESSA TAREFA? {
                    1 - PRIORIDADE
                    2 - CATEGORIA
                    3 - NOME
                    4 - DESCRICAO
                    }
                    
                    SE ESTAVA ORDENADA (ORDENA)
                    SE NAO ESTAVA APENAS ALTERA
                    */
                break;
            case 6:
                libera(&p_l);
                break;
            case 7:
                /*ORDENA
                  EXIBE LISTA DE TAREFAS*/
                break;
            case 8:
                printf("\n\nENCERRANDO PROGRAMA...");
                break;
            default:
                printf("\n\nOpcao invalida!\n");
                break;
        }
    }while(opcao != 8);
}

void escolhaInsere() {
    printf("\n***** INSERE *****\n1 - Inicio\n2 - Fim\n3 - Ordenado\nEscolha uma opcao: ");
    scanf("%d", &opcao2);
                
    switch (opcao2) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            break;
    }
}

void escolhaRemove() {
    printf("\n***** REMOVE *****\n1 - Inicio\n2 - Fim\n3 - Tarefa\nEscolha uma opcao: ");
    scanf("%d", &opcao2);
                
    switch (opcao2) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            break;
    }
}

void escolhaBusca() {
    printf("\n***** BUSCA TAREFAS *****\n1 - Prioridade\n2 - Categoria\n3 - Nome\nEscolha uma opcao: ");
    scanf("%d", &opcao2);
                
    switch (opcao2) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            break;
    }
}