//Aluno: João Pedro de Araújo Lima - UFC
//Matícula: 497687
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct NO{
    int chave;
    int bal;
    struct NO *dir;
    struct NO *esq;
}No;

No*  novoNo(int x);
void caso1(No **pt, int *h);
void caso2(No **pt, int *h);
void inserirAVL(int x, No **pt, int *h);
void caso1R(No **pt, int *h);
void caso2R(No **pt, int *h);
void balancear(No **pt, int r, int *h);
void trocar(No **pt, No **paiS);
void removerAVL(int x, No **pt, int *h);
void libera_arvore(No *pt);
int  contar_nos(No *pt);
int  altura(No *pt);
int  verif_avl(No *pt);
void gerar(int *vet, int max_val, int tam);
void teste(No **pt, int *h, int indice, int inserir, int remover);

int main() {
    No **ptraiz;
    ptraiz = (No **) malloc(sizeof(No) * 1000);
    int h = 0;
 
    //teste
   for(int i = 0; i < 1000; i ++) {
       teste(&ptraiz[i], &h, i, 10000, 1000);
   }

    return 0;
}

//inserir
No* novoNo(int x) {
    No *novo = (No *) malloc(sizeof(No));

    if(novo != NULL) {
        novo->chave = x;
        novo->bal = 0;
        novo->esq = NULL;
        novo->dir = NULL;
    }else{
        printf("Erro ao criar o nó\n");
    }

    return novo;
}

void caso1(No **pt, int *h) {
    No *ptu;

    ptu = (*pt)->esq;

    if(ptu->bal == -1) {
        (*pt)->esq = ptu->dir;
        ptu->dir = (*pt);
        (*pt) = ptu;
        (*pt)->dir->bal = 0;
    }else{
        No *ptv;

        ptv = ptu->dir;
        ptu->dir = ptv->esq;
        ptv->esq = ptu;
        (*pt)->esq = ptv->dir;
        ptv->dir = (*pt);

        if(ptv->bal == 1) {
            (*pt)->bal = 0;
            ptu->bal = -1;
        }else if(ptv->bal == 0) {
            (*pt)->bal = 0;
            ptu->bal = 0;
        }else{
            (*pt)->bal = 1;
            ptu->bal = 0;
        }
        (*pt) = ptv;
    }
    (*pt)->bal = 0;
    (*h) = 0;
}

void caso2(No **pt, int *h){
    No *ptu;
    
    ptu = (*pt)->dir;

    if(ptu->bal == 1) {
        (*pt)->dir = ptu->esq;
        ptu->esq = (*pt);
        (*pt) = ptu;
        (*pt)->esq->bal = 0;
    }else{
        No *ptv;

        ptv = ptu->esq;
        ptu->esq = ptv->dir;
        ptv->dir = ptu;
        (*pt)->dir = ptv->esq;
        ptv->esq = (*pt);

        if(ptv->bal == -1) {
            (*pt)->bal = 0;
            ptu->bal = 1;
        }else if(ptv->bal == 0) {
            (*pt)->bal = 0;
            ptu->bal = 0;
        }else{
            (*pt)->bal = -1; 
            ptu->bal = 0;
        }
        (*pt) = ptv;
    }
    (*pt)->bal = 0;
    (*h) = 0;
}

void inserirAVL(int x, No **pt, int *h) {
    if((*pt) == NULL) {
        (*h) = 1;
        (*pt) = novoNo(x);
    }else{
        if((*pt)->chave == x) {
            printf("Elemento já existe na árvore\n");
        }else{
            if(x < (*pt)->chave) {
                inserirAVL(x, &(*pt)->esq, h);
                if((*h) == 1) {
                    switch ((*pt)->bal)
                    {
                    case 1:
                        (*pt)->bal = 0;
                        (*h) = 0;
                        break;

                    case 0:
                        (*pt)->bal = -1;
                        break;

                    case -1:
                        caso1(pt, h);
                        break;
                    
                    default:
                        break;
                    }
                }
            }else{
                inserirAVL(x, &(*pt)->dir, h);
                if((*h) == 1) {
                    switch ((*pt)->bal)
                    {
                    case -1:
                        (*pt)->bal = 0;
                        (*h) = 0;
                        break;

                    case 0:
                        (*pt)->bal = 1;
                        break;
                    
                    case 1:
                        caso2(pt, h);
                        break;

                    default:
                        break;
                    }
                }
            }
        }  
    }
}

//remover
void caso1R(No **pt, int *h) {
    No *ptu;

    ptu = (*pt)->esq;

    if(ptu->bal <= 0) {
        (*pt)->esq = ptu->dir;
        ptu->dir = (*pt);
        (*pt) = ptu;
        if(ptu->bal == -1) {
            ptu->bal = 0;
            (*pt)->dir->bal = 0;
            (*h) = 1;
        }else{
            ptu->bal = 1;
            (*pt)->dir->bal = -1;
            (*h) = 0;
        }
    }else{
        No *ptv;

        ptv = ptu->dir;
        ptu->dir = ptv->esq;
        ptv->esq = ptu;
        (*pt)->esq = ptv->dir;
        ptv->dir = (*pt);
        (*pt) = ptv;

        if(ptv->bal == 1) {
            (*pt)->dir->bal = 0;
            ptu->bal = -1;
        }else if(ptv->bal == 0) {
            (*pt)->dir->bal = 0;
            ptu->bal = 0;
        }else if(ptv->bal == -1){
            (*pt)->dir->bal = 1;
            ptu->bal = 0;
        }
        (*pt)->bal = 0;
        (*h) = 1;
    }       
}

void caso2R(No **pt, int *h) {
    No *ptu;

    ptu = (*pt)->dir;

    if(ptu->bal >= 0) {
        (*pt)->dir = ptu->esq;
        ptu->esq = (*pt);
        (*pt) = ptu;
        if(ptu->bal == 1) {
            ptu->bal = 0;
            (*pt)->esq->bal = 0;
            (*h) = 1;
        }else{
            ptu->bal = -1;
            (*pt)->esq->bal = 1;
            (*h) = 0;
        } 
    }else{
        No *ptv;

        ptv = ptu->esq;
        ptu->esq = ptv->dir;
        ptv->dir = ptu;
        (*pt)->dir = ptv->esq;
        ptv->esq = (*pt);
        (*pt) = ptv;

        if(ptv->bal == 1) {
            (*pt)->esq->bal = -1;
            ptu->bal = 0;
        }else if(ptv->bal == 0) {
            (*pt)->esq->bal = 0;
            ptu->bal = 0;
        }else if(ptv->bal == -1){
            (*pt)->esq->bal = 0;
            ptu->bal = 1;
        }
        (*pt)->bal = 0;
        (*h) = 1;
    }     
}

void balancear(No **pt, int r, int *h) {
    if((*h) == 1) {
        if(r == 1) {
            switch ((*pt)->bal)
            {
            case 1:
                (*pt)->bal = 0;
                break;
            
            case 0 :
                (*pt)->bal = -1;
                (*h) = 0;
                break;

            case -1:
                caso1R(pt, h);
                break;

            default:
                break;
            }
        }else{
            switch ((*pt)->bal)
            {
            case 1:
                caso2R(pt, h);
                break;

            case 0:
                (*pt)->bal = 1;
                (*h) = 0;
                break;

            case -1:
                (*pt)->bal = 0;
                break;
            
            default:
                break;
            }
        }
    }
}

void trocar(No **pt, No **paiS) {
    int aux;
    No *auxNo;

    aux = (*pt)->chave;
    (*pt)->chave = (*paiS)->chave;
    (*paiS)->chave = aux;
}

void removerAVL(int x, No **pt, int *h) {
    if((*pt) == NULL) {
        printf("Elemento não existe!\n");
        (*h) = 0;
    }else{
        if(x < (*pt)->chave) {
            removerAVL(x, &(*pt)->esq, h);
            balancear(pt, 0, h);
        }else{
            if(x > (*pt)->chave) {
                removerAVL(x, &(*pt)->dir, h);
                balancear(pt, 1, h);
            }else{
                No *aux;
                aux = (*pt);

                if((*pt)->esq == NULL) {
                    (*pt) = (*pt)->dir;
                    (*h) = 1;
                }else{
                    if((*pt)->dir == NULL) {
                        (*pt) = (*pt)->esq;
                        (*h) = 1;
                    }else{
                        No *s;
                        s = (*pt)->dir;

                        if(s->esq == NULL) {
                            s->esq = (*pt)->esq;
                            s->bal = (*pt)->bal;
                            (*pt) = s;
                            (*h) = 1;
                        }else{
                            No *paiS;

                            while(s->esq != NULL){
                                paiS = s;
                                s = s->esq;
                            }
                            trocar(pt, &paiS->esq);
                            removerAVL(x, &(*pt)->dir, h);
                        }
                        balancear(pt, 1, h);
                    }
                }if(aux->chave == x) {
                    free(aux);
                }
            }
        }
    }
}

void libera_arvore(No *pt) {
    if(pt != NULL) {
        libera_arvore(pt->esq);
        libera_arvore(pt->dir);
        free(pt);
        pt = NULL;
    }else{
        return;
    }
}

//contador de nós
int contar_nos(No *pt) {
    if(pt != NULL) {
        return 1 + contar_nos(pt->esq) + contar_nos(pt->dir);
    }else{
        return 0;
    }
}

//verificando AVL
int altura(No *pt) {
    int altura_esq = 0, altura_dir = 0;

    if(pt != NULL) {
        if(pt->esq != NULL) {
            altura_esq = altura(pt->esq);
        }if(pt->dir != NULL) {
            altura_dir = altura(pt->dir);
        }

        if(altura_esq > altura_dir) {
            return altura_esq + 1;
        }else{
            return altura_dir + 1;
        }
    }

    return -1; //significa que a árvore está vazia.
}

int verif_avl(No *pt) {
    int altura_esq = 0, altura_dir = 0, bal = 0;

    if(pt != NULL) {
        if(pt->esq != NULL) {
            altura_esq = altura(pt->esq);
        }if(pt->dir != NULL) {
            altura_dir = altura(pt->dir);
        }

        bal = altura_esq - altura_dir;

        if(bal <= 1 && bal >= -1) {
            if(pt->esq != NULL) {
                if(verif_avl(pt->esq) == 0) 
                    return 0;
            }if(pt->dir != NULL) {
                if(verif_avl(pt->dir) == 0) 
                    return 0;
            }
        }else{
            return 0;
        }
        return 1;
    }
}

//gerando vetores de chaves que não se repetem
void gerar(int *vet, int max_val, int tam) {
    int repeat = 1;
    srand(time(NULL));

    for(int i = 0; i < tam; i++) {
        vet[i] = rand() % max_val;
        do{
            repeat = 0;
            for(int j = 0; j < i; j++) {
                if(vet[j] == vet[i]) {
                    vet[i] = rand() % max_val;
                    repeat = 1;
                }
            }
        }while(repeat == 1);
    }
}

//função de teste
void teste(No **pt, int *h, int indice, int inserir, int remover) {
    int *chaves;
    int *chaves_remover;
    chaves = (int *)malloc(sizeof(int) * inserir);
    chaves_remover = (int *)malloc(sizeof(int) * remover);

    gerar(chaves, 100000, inserir);

    for(int i = 0; i < inserir; i++) {
        inserirAVL(chaves[i], &pt[indice], h);
    }

    //verificando quantidade de nós
    printf("Quantidade de nós da árvore %d = %d\n", indice + 1, contar_nos(pt[indice])); 

    //verificando se a árvore é uma avl
    if(verif_avl(pt[indice]) == 1) {
        printf("A árvore %d é uma AVL\n", indice + 1);
    }else{
        printf("A árvore %d não é uma AVL\n", indice + 1);
    }

    gerar(chaves_remover, inserir, remover);

    for(int i = 0; i < remover; i++) {
        removerAVL(chaves[chaves_remover[i]], &pt[indice], h);
    }

    //verificando quantidade de nós após a remoção
    printf("Quantidade de nós da árvore %d aṕos a remoção = %d\n", indice + 1, contar_nos(pt[indice]));

    //verificando se a árvore é uma avl após a remoção
    if(verif_avl(pt[indice]) == 1) {
        printf("A árvore %d é uma AVL\n", indice + 1);
    }else{
        printf("A árvore %d não é uma AVL\n", indice + 1);
    }

    //liberando memória
    free(chaves);
    free(chaves_remover);
    libera_arvore(pt[indice]);
}
