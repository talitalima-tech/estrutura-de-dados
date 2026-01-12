#include<stdio.h>
#include<stdlib.h>

typedef struct No{ // Representa um nó (joia) na pilha
    int valor;
    struct No * prox;
}No;

typedef struct Pilha{ // Representa a pilha
    No* topo;
    int tam;
}Pilha;

void add(Pilha* pilha, int valor) {
    No* novo = malloc(sizeof(No));
    novo->valor = valor;
    novo->prox = pilha->topo;
    pilha->topo = novo;
    pilha->tam++;
}

int remover(Pilha* pilha) {
    int valor;
    if (pilha->tam > 0) {
        No* lixo = pilha->topo;
        pilha->topo = pilha->topo->prox;
        valor = lixo->valor;
        free(lixo);
        pilha->tam--;
        return valor;
    } else {
        printf("Pilha está vazia!\n");
        return -1;
    }
}

void imprimir(Pilha* pilha) {
    No* aux = pilha->topo;
    while (aux != NULL) {
        printf("Valor: %d\n", aux->valor);
        aux = aux->prox;
    }
}

// Função de ordenação simples (Bubble Sort)
void ordenarVetor(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                int temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

void mover_joias(int quantidade, Pilha* origem, Pilha* auxiliar, Pilha* destino) {
    if (quantidade == 1) {
        // Caso base: mover uma única joia 
        add(destino, remover(origem));
        return;
    }

    // mover as n-1 joias menores para o portal auxiliar
    mover_joias(quantidade - 1, origem, destino, auxiliar);

    //mover a maior joia para o portal de destino
    add(destino, remover(origem));

    //mover as n-1 joias menores do portal auxiliar para o portal de destino
    mover_joias(quantidade - 1, auxiliar, origem, destino);
}

int main() {
    Pilha origem = {NULL, 0};   
    Pilha auxiliar = {NULL, 0}; 
    Pilha destino = {NULL, 0};  

    int quantidade;
    printf("Digite quantas joias você quer adicionar:\n");
    scanf("%d", &quantidade);

    int vetor[quantidade];

    // Receber os valores do usuário
    for (int i = 0; i < quantidade; i++) {
        printf("Digite o valor da joia %d:\n", i + 1);
        scanf("%d", &vetor[i]);
    }

    ordenarVetor(vetor, quantidade);

    // adicionar as joias já ordenados na pilha de origem
    for (int i = quantidade - 1; i >= 0; i--) {
        add(&origem, vetor[i]);
    }

    printf("\nPilha de origem:\n");
    imprimir(&origem);  

    // Mover as joias para a pilha de destino
    mover_joias(quantidade, &origem, &auxiliar, &destino);

    printf("\nPilha de destino:\n");
    imprimir(&destino);  

    return 0;
}


