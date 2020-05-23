// fila
#include "stdlib.h"
#include "lse.neutra.h"
#include "fila.h"

struct fila{
  // int tamanhoMax;
  int tamanho;
  TLista *lista;
};

TFila *criarFila(){
  TFila *f = malloc(sizeof(TFila));
  f->tamanho = 0;
  f->lista = criarLista();

  return f;
}

void enfileirar(TFila *f, void *novoElem){

  inserirFinalLSE(f->lista, novoElem);
  f->tamanho++;

}

void *desenfileirar(TFila *f){
  void *elemento = removerInicioLSE(f->lista);
  if(elemento != NULL)
    f->tamanho--;

  return elemento;

}
