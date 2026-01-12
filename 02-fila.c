// questão 2 fila 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct No{ 
    float valor;
    char *sabor;           
    char *nome_cliente;    
    char tamanho;
    struct No *prox;
} No;

No *inicio = NULL;
No *fim = NULL;
int tam = 0;

void add(float valor, char *sabor, char *nome_cliente, char tamanho) {
    No *novo = malloc(sizeof(No));
    novo->valor = valor;
    novo->sabor = malloc(strlen(sabor) + 1);  // aloca memória para sabor
    novo->nome_cliente = malloc(strlen(nome_cliente) + 1);  // aloca memória para nome_cliente

    if (novo->sabor == NULL || novo->nome_cliente == NULL) {
        printf("Erro na alocação de memória para sabor ou nome_cliente!\n");
        exit(1);
    }

    strcpy(novo->sabor, sabor);  // copia a string sabor para a memória alocada
    strcpy(novo->nome_cliente, nome_cliente);  // copia a string nome_cliente para a memória alocada
    novo->tamanho = tamanho;
    novo->prox = NULL;

    if (inicio == NULL) {
        inicio = novo;
        fim = novo;
    } else {
        fim->prox = novo;
        fim = novo;
    }
    tam++;
}

char* remover() {
    char *nome_cliente = NULL;
    if (tam == 0) {
        printf("Fila vazia!\n");
    } else {
        No *lixo = inicio;
        inicio = inicio->prox;
        if (tam == 1) {
            fim = NULL;
        }
        nome_cliente = lixo->nome_cliente;  // salva o nome do cliente que será removido
        free(lixo->sabor);  // libera a memória alocada para sabor
        free(lixo->nome_cliente);  // libera a memória alocada para nome_cliente
        free(lixo);  // libera a memória do nó
        tam--;
    }
    return nome_cliente;  
}

void imprimir() {
    No *aux = inicio;
    while (aux != NULL) {
        printf("Cliente: %s\n", aux->nome_cliente);    
        printf("Sabor: %s\n", aux->sabor);             
        printf("Valor: %.2f\n", aux->valor);
        printf("Tamanho: %c\n", aux->tamanho);         
        aux = aux->prox;
    }
}

int main() {
    float valor;
    char sabor[50], nome_cliente[50], tamanho;
    
    for (int i = 0; i < 5; i++) {
        printf("Digite o sabor da pizza (Marguerita, Calabresa, Frango ou 4 Queijos):\n");
        scanf(" %49[^\n]", sabor);  
        printf("Digite o tamanho da pizza (P/M/G):\n");
        scanf(" %c", &tamanho);  
        printf("Digite o seu nome:\n");
        scanf(" %49[^\n]", nome_cliente);  
        printf("Digite o valor:\n");
        scanf("%f", &valor); 
        add(valor, sabor, nome_cliente, tamanho);
    }

    remover();  
    imprimir(); 

    return 0;
}
