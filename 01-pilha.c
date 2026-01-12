// questão 1 pilha 

#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *prox;
} No;

No *topo = NULL;
int tam = 0;

void add(int valor) {
    No *novo = malloc(sizeof(No));
    novo->valor = valor;
    novo->prox = topo;
    topo = novo;
    tam++;
}

int remover() {
    int valor;
    if (tam > 0) {
        No *lixo = topo;
        topo = topo->prox;
        valor = lixo->valor;
        free(lixo);
        tam--;
        return valor;
    } else {
        printf("Pilha está vazia!\n");
        return -1; // Indica que a pilha estava vazia
    }
}

int main() {
    
    char expressao[] = {'1', '2', '-', '4', '5', '+', '*'};  
    
    
    for (int i = 0; expressao[i] != '\0'; i++) {
        char entrada = expressao[i];

        // Ignorar espaços 
        if (entrada == ' ') {
            continue;
        }

        // Verificar se é um número entre '0' e '9'
        if (entrada >= '0' && entrada <= '9') {
            int numero = entrada - '0';  // Converte para inteiro
            add(numero);
        } else {  // Se for um operador
            // verificar se tem pelo menos dois elementos na pilha para operar
            if (tam < 2) {
                printf("Pilha com poucos elementos para operação!\n");
                return 1; // Finaliza em caso de erro
            }

            int valor2 = remover();
            int valor1 = remover();
            int total;

            switch (entrada) {
                case '+':
                    total = valor1 + valor2;
                    break;
                case '-':
                    total = valor1 - valor2;
                    break;
                case '*':
                    total = valor1 * valor2;
                    break;
                case '/':
                    total = valor1 / valor2;
                    break;
                default:
                    printf("Operador inválido: %c\n", entrada);
                    return 1; // Finaliza em caso de operador inválido
            }
            add(total);  // Adiciona o resultado à pilha
        }
    }

    if (topo != NULL) {
        printf("Resultado final: %d\n", topo->valor);
    } else {
        printf("Pilha vazia após calcular a expressão.\n");
    }

    return 0;
}
