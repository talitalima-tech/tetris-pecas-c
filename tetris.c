#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct peca {
    char tipo[5];
    char cor[20];
    char borda;
    struct peca* prox;
} Peca;

void cadastrarPeca(Peca** lista) {
    int tipo;
    Peca* nova = (Peca*)malloc(sizeof(Peca));
    
    if (nova == NULL) {
        printf("Erro de alocação de memória\n");
        exit(1);
    }

    printf("Qual é o tipo de peça?\n");
    printf("[1] - Peça T\n");
    printf("[2] - Peça S1\n");
    printf("[3] - Peça S2\n");
    printf("[4] - Peça I\n");
    printf("[5] - Peça L1\n");
    printf("[6] - Peça L2\n");
    printf("[7] - Peça Q\n");
    scanf("%d", &tipo);
    
    switch (tipo) {
        case 1: strcpy(nova->tipo, "T"); break;
        case 2: strcpy(nova->tipo, "S1"); break;
        case 3: strcpy(nova->tipo, "S2"); break;
        case 4: strcpy(nova->tipo, "I"); break;
        case 5: strcpy(nova->tipo, "L1"); break;
        case 6: strcpy(nova->tipo, "L2"); break;
        case 7: strcpy(nova->tipo, "Q"); break;
        default:
            printf("Opção inválida! Tente novamente\n");
            free(nova);  
            return;
    }
    
    printf("Qual a cor da peça?\n");
    scanf("%s", nova->cor);
    
    printf("A peça possui borda? (S para sim, N para não):\n");
    scanf(" %c", &nova->borda);  
    nova->prox = NULL;

    if (*lista == NULL) { //quando a lista esta vazia
        *lista = nova;
    } else {
        Peca* aux = *lista;
        while (aux->prox != NULL) {  // Percorre ate o ultimo elemento
            aux = aux->prox;
        }
        aux->prox = nova;  
    }
}

void listarPecas(Peca* lista) {
    Peca* aux = lista; //Ponteiro para percorrer a lista
    while (aux != NULL) {
        if (aux->borda == 'S') {
            printf("Peça: %s - Cor: %s - Com borda\n", aux->tipo, aux->cor);
        } else {
            printf("Peça: %s - Cor: %s - Sem borda\n", aux->tipo, aux->cor);
        }
        aux = aux->prox;
    }
}

void reorganizarPecas(Peca** lista) {
    if (*lista == NULL) {
        printf("Não existe peças na lista.\n");
        return;
    }

    const char* ordem[] = {"T", "S1", "S2", "I", "L1", "L2", "Q"};
    Peca* listaOrganizada = NULL;  // Lista para adicionar as peças reorganizadas
    Peca* final = NULL;  
    for (int i = 0; i < 7; i++) {
        Peca* aux = *lista;
        Peca* anterior = NULL;

        while (aux != NULL) {
            Peca* temp = aux;
            aux = aux->prox;

            if (strcmp(temp->tipo, ordem[i]) == 0) {
                if (anterior == NULL) {
                    *lista = aux; 
                } else {
                    anterior->prox = aux;
                }

                // Adiciona a peça na lista ordenada
                temp->prox = NULL;
                if (listaOrganizada == NULL) {
                    listaOrganizada = temp;
                } else {
                    final->prox = temp;
                }
                final = temp;  
            } else {
                anterior = temp;
            }
        }
    }

    *lista = listaOrganizada;
    printf("Reorganizando peças...\n");
    listarPecas(*lista);
}

void liberarMemoria(Peca* lista) {
    Peca* aux;
    while (lista != NULL) {
        aux = lista;
        lista = lista->prox;  
        free(aux);  
    }
}

int main() {
    Peca* lista = NULL; 
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1 - Cadastrar peça\n");
        printf("2 - Listar peças\n");
        printf("3 - Reorganizar peças\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarPeca(&lista);
                break;
            case 2:
                listarPecas(lista);
                break;
            case 3:
                reorganizarPecas(&lista);
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente\n");
                break;
        }
    } while (opcao != 0);
    
    liberarMemoria(lista);

    return 0;
}