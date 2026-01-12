#include<stdio.h>
#include<stdlib.h>

typedef struct No{
    int valor;
    struct No * dir;
    struct No * esq;
}No;

No *raiz = NULL;
int tam = 0;

No * buscar(int valor, No *aux){
    if(aux == NULL){
        return NULL;
    }else if(valor == aux->valor){
        return aux;
    }else if(valor < aux->valor){
        //pode estar na esq
        if(aux->esq != NULL){
            return buscar(valor, aux->esq);
        }else{
            return aux; //pai do elemento se ele existisse
        }
    }else{
        //pode estar na dir
        if(aux->dir != NULL){
            return buscar(valor, aux->dir);
        }else{
            return aux; //pai do elemento se ele existisse
        }
    }
}


void add(int valor){
    No *novo = malloc (sizeof(No));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    No* aux = buscar(valor, raiz);
    if(aux == NULL){
        raiz = novo;
    }else if(aux->valor == valor){
        printf("Adicao impossivel, chave duplicada! :'( \n");
        free(novo);
    }else if(valor < aux->valor){
        aux->esq = novo;
    }else{
        aux->dir = novo;
    }    
}

int remover(int valor) {
    No *pai = NULL;
    No *lixo = raiz;

    // Buscando o no e o seu pai
    while (lixo != NULL && lixo->valor != valor) {
        pai = lixo;
        if (valor < lixo->valor) {
            lixo = lixo->esq;
        } else {
            lixo = lixo->dir;
        }
    }

    // no não encontrado
    if (lixo == NULL) {
        return -1;
    }

    // Caso 1: O nó é uma folha
    if (lixo->esq == NULL && lixo->dir == NULL) {
        if (pai == NULL) {
            raiz = NULL;  // se a raiz for removida e a árvore ficar vazia
        } else if (pai->esq == lixo) {
            pai->esq = NULL;  // se for o filho esquerdo
        } else {
            pai->dir = NULL;  // se for o filho direito
        }
        free(lixo);
    }
    // Caso 2: no tem apenas um filho 
    else if (lixo->esq == NULL || lixo->dir == NULL) {
        No *novoFilho = (lixo->esq != NULL) ? lixo->esq : lixo->dir;

        if (pai == NULL) {
            raiz = novoFilho;  
        } else if (pai->esq == lixo) {
            pai->esq = novoFilho;  
        } else {
            pai->dir = novoFilho;  
        }
        free(lixo);
    }
    // Caso 3: no tem dois filhos
    else {
        No *sucessor = lixo->dir;
        No *paiSucessor = lixo;
        
        // Buscando um sucessor 
        while (sucessor->esq != NULL) {
            paiSucessor = sucessor;
            sucessor = sucessor->esq;
        }

        lixo->valor = sucessor->valor;

        // remove o sucessor 
        if (paiSucessor->esq == sucessor) {
            paiSucessor->esq = sucessor->dir;  
        } else {
            paiSucessor->dir = sucessor->dir;  
        }
        free(sucessor);
    }

    tam--;  
    return valor;
}

void imprimir_in_ordem(No *aux){
    if(aux != NULL){
        imprimir_in_ordem(aux->esq);
        printf("%d\n", aux->valor);
        imprimir_in_ordem(aux->dir);
    }
}

int main(){
    add(54);
    add(60);
    add(10);
    add(69);
    add(7);
    add(7);
    add(420);
    add(37);
    add(42);
    remover(60);
    imprimir_in_ordem(raiz);
    return 0;
}
