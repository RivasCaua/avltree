#include <stdlib.h>
#include <stdio.h>

typedef struct no{
    int valor;
    int altura;
    struct no *direita, *esquerda;
} No;

int altura(No *no){
    if (no == NULL)
        return -1; 

    else 
        return no->altura;
}

int maior(int vesq, int vdir){
    if (vesq >= vdir)
        return vesq;
    else
        return vdir; 
}

int fatorbalanc(No *no){
    if (no)
        return (altura(no->esquerda) - altura(no->direita));
    else
        return 0;
}

No* rotaesq(No *raiz){
    No *filho, *neto;

    filho = raiz->direita;
    neto = filho->esquerda;

    filho->esquerda = raiz;
    raiz->direita = neto;

    raiz->altura = maior(altura(raiz->esquerda), altura(raiz->direita)) + 1;
    filho->altura = maior(altura(filho->esquerda), altura(filho->direita)) + 1;

    return filho;
}

No *rotadir(No *raiz){
    No *filho, *neto;

    filho = raiz->esquerda;
    neto = filho->direita;

    filho->direita = raiz;
    raiz->esquerda = neto;

    raiz->altura = maior(altura(raiz->esquerda), altura(raiz->direita)) + 1;
    filho->altura = maior(altura(filho->esquerda), altura(filho->direita)) + 1;

    return filho;
}

No *rotadiresq(No *raiz){
    raiz->esquerda = rotadir(raiz->esquerda);
    return rotaesq(raiz);
}

No *rotaesqdir(No *raiz){
    raiz->esquerda = rotadir(raiz->direita);
    return rotadir(raiz);
}

No *balancear(No *raiz){
    int fb = fatorbalanc(raiz);\

    if (fb > 1){
        if (fatorbalanc(raiz->esquerda) >= 0)
            raiz = rotadir(raiz);
        else
            raiz = rotaesqdir(raiz);
    }

    else if (fb < -1){
        if (fatorbalanc(raiz->direita) <= 0)
            raiz = rotaesq(raiz);
        else
            raiz = rotadiresq(raiz);
            
    }

    return raiz;
}

No *novono(int valor){
    No *novo = malloc(sizeof(No));

    if (novo){
        novo->valor = valor;
        novo->direita = NULL;
        novo->esquerda = NULL;
        novo->altura = 0;
    }

    return novo;
}

No *inserir(No *raiz, int valor){
    if (raiz == NULL)
        return novono(valor);

    else if (raiz->valor > valor)
        raiz->esquerda = inserir(raiz->esquerda, valor);

    else if (raiz->valor < valor)
        raiz->direita = inserir(raiz->direita, valor);

    raiz->altura = maior(altura(raiz->esquerda), altura(raiz->esquerda)) + 1;

    raiz = balancear(raiz);

    return raiz;
}

No *remover(No *raiz, int valor){
    if (raiz == NULL){
        return NULL;
    }
    else{
        if (raiz->valor == valor){
            
            if (raiz->direita == NULL && raiz->esquerda == NULL){
            free(raiz);
            return NULL;
            }
            else if (raiz->direita != NULL && raiz->esquerda != NULL){
                No *pai = raiz;
                No *aux = raiz->direita;

                while (aux->esquerda != NULL){
                    pai = aux;
                    aux = aux->esquerda;
                }

                pai->esquerda = aux->direita;
                aux->esquerda = raiz->esquerda;
                aux->direita = raiz->direita;
                
                aux->altura = maior(altura(aux->esquerda), altura(aux->esquerda)) + 1;
                balancear(aux);

                free(raiz);
                return aux;
            }
            else{
                No *aux;

                if (raiz->direita != NULL)
                    aux = raiz->direita;

                else 
                    aux = raiz->esquerda;

                free(raiz);
                aux->altura = maior(altura(aux->esquerda), altura(aux->esquerda)) + 1;
                return balancear(aux);
            }        
        }
        else{
            if (valor > raiz->valor)
                raiz->direita = remover(raiz->direita, valor);

            else if (valor < raiz->valor)
                raiz->esquerda = remover(raiz->esquerda, valor);

            raiz->altura = maior(altura(raiz->esquerda), altura(raiz->esquerda)) + 1;
            return balancear(raiz);
        }
    }
}

void imprimir(No *raiz, int nivel){
    int i;
    if(raiz) {
        imprimir(raiz->direita, nivel + 1);
        printf("\n\n");

        for (i=0; i < nivel; i++)  
            printf("\t");

        printf("%d", raiz->valor);
        imprimir(raiz->esquerda, nivel + 1);
    }
}

int main(){
    No *arv = NULL;
    
    arv = inserir(arv, 20);

    arv = inserir(arv, 30);

    arv = inserir(arv, 10);

    arv = inserir(arv, 25);

    arv = inserir(arv, 40);

    arv = inserir(arv,15);

    //imprimir(arv, 0);
    arv = remover(arv, 20);
    imprimir(arv, 0);
}