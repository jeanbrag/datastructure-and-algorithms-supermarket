#include "stdlib.h"
#include "stdio.h"
#include "lse.neutra.h"

typedef struct elemento{
  void *carga; // carga util
  struct elemento *prox; // ponteiro proximo
} TElemento;

struct lista{
  int nroElementos;
  TElemento *inicio;
  TElemento *final;
};

TLista *criarLista(){
  TLista *e_lista = malloc(sizeof(TLista));

  e_lista->nroElementos = 0;
  e_lista->inicio=NULL;
  e_lista->final = NULL;

  return e_lista;
}

void inserirInicioLSE(TLista *lst, void *e_carganova){
  // lista vazia
  if (lst->inicio == NULL){
    TElemento *elem = malloc(sizeof(TElemento));
    elem->carga = e_carganova;
    elem->prox = NULL;

    lst->inicio = elem;
    lst->final = elem;
    lst->nroElementos = 1;
  }else{
    // trocar o inicio da Lista
    TElemento *elem = malloc(sizeof(TElemento));
    elem->prox = lst->inicio;
    elem->carga = e_carganova;
    lst->inicio = elem;
    lst->nroElementos++;
  }
}
//inserir no final
void inserirFinalLSE(TLista *lst, void *e_carganova){
  // lista vazia
  if (lst->inicio == NULL){
    TElemento *elem = malloc(sizeof(TElemento));
    elem->carga = e_carganova;
    elem->prox = NULL;

    lst->inicio = elem;
    lst->final = elem;
    lst->nroElementos = 1;
  }else{
    // trocar o final da Lista
    TElemento *elem = malloc(sizeof(TElemento));

    lst->final->prox = elem;
    elem->carga = e_carganova;
    elem->prox = NULL;

    lst->final = elem;
    lst->nroElementos++;
  }
}

int compara(void* e_carganova, void* carga){
    if(carga==e_carganova)
        return 0;
    else if(carga>e_carganova)
        return -1;
    else return 1;
}

void inserirOrdenadoLSE(TLista *lst, void *e_carganova, TComparador compara){
// -1 se e_carganova < carga
// 0 se e_carganova == carga
// 1 se e_carganova > carga
    TElemento *anterior = NULL;
    TElemento *caminhador = lst->inicio;

    while ((caminhador!=NULL) && (compara(e_carganova, caminhador->carga) >= 0)){
        anterior = caminhador;
        caminhador = caminhador->prox;
    }

    if (anterior==NULL){
        inserirInicio(lst, e_carganova);
    }else if(caminhador == NULL){
        inserir(lst,e_carganova);
    } else{
        TElemento *elem = malloc(sizeof(TElemento));
        elem->carga = e_carganova;
        elem->prox = caminhador;
        anterior->prox = elem;

    lst->nroElementos++;
    }
}


// remover no inicio
void* removerInicioLSE(TLista *lst){
  void *carga=NULL;
  if (lst->inicio != NULL){
    TElemento *prim = lst->inicio;
    TElemento *e_novoInicio = prim->prox;
    carga = prim->carga;

    free(prim);
    lst->inicio = e_novoInicio;
    lst->nroElementos--;
    if (lst->inicio == NULL)
      lst->final = NULL;
  }else{
    //printf("Lista Vazia\n");
  }
  return carga;
}

// remover no final
void* removerFinalLSE(TLista *lst){
  void *carga=NULL;
  if(lst->inicio != NULL){
    TElemento *anterior=NULL;
    TElemento *caminhador = lst->inicio;
    while(caminhador->prox!=NULL){
      anterior = caminhador;
      caminhador = caminhador->prox;
    }
    carga = lst->final->carga;

    free(lst->final);
    lst->final = anterior;
    if (lst->final == NULL){
      lst->inicio=NULL;
    }else{
      lst->final->prox = NULL;
    }
    lst->nroElementos--;
  }else{
    //printf("Lista Vazia\n");
  }
  return carga;
}

void imprimirLSE(TLista *lst, TImpressora impressora){
  if (lst->inicio == NULL){
      printf("Lista Vazia\n");
  }else{
    TElemento *caminhador=lst->inicio;
    while(caminhador != NULL){
      impressora(caminhador->carga);
      caminhador = caminhador->prox;
    }
 }

}
