#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef int (*TComparador)(void*,void*);
typedef void (*TImpressora)(void*);

typedef struct elemento{
  void *carga; // carga util
  struct elemento *prox; // ponteiro proximo
} TElemento;

typedef struct lista{
  int nroElementos;
  TElemento *inicio;
  TElemento *final;
} TLista;

TLista *criarLista(){
  TLista *e_lista = malloc(sizeof(TLista));

  e_lista->nroElementos = 0;
  e_lista->inicio=NULL;
  e_lista->final = NULL;

  return e_lista;
}
void inserir(TLista *lst, void *e_carganova){
  // lista vazia
  if (lst->inicio == NULL){
    TElemento *elem = malloc(sizeof(TElemento));
    elem->carga = e_carganova;
    elem->prox = NULL;
    lst->inicio = elem;
    lst->final = elem;
    lst->nroElementos = 1;
  }else{
    // em busca do ultimo elemento
    TElemento *caminhador=lst->inicio;
    while(caminhador-> prox != NULL){
      caminhador = caminhador->prox;
    }
   TElemento *elem=malloc(sizeof(TElemento));
   elem->carga=e_carganova;
   caminhador->prox = elem;
    elem->prox = NULL;
    lst->nroElementos++;
  }
}
void inserirInicio(TLista *lst, void *e_carganova){
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
void* removerInicio(TLista *lst){
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
  }
  return carga;
}

int vaziaLSE(TLista *a){
    if(a->nroElementos==0)
    return 1;
    else
      return 0;
}

void imprimir(TLista *lst, TImpressora impressora){
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

typedef struct eventoAgenda{
    double marcatempo; //horaminseg
    char tipo;
    void *e_carga;
}TEvento;

TEvento *criarEvento(double marcaTempo, char tipo, void *e_carga){
    TEvento *e = malloc(sizeof(TEvento));
    e->marcatempo=marcaTempo;
    e->tipo= tipo;
    e->e_carga=e_carga;

    return e;
}

/*void imprimirEvento (void *e,TImpressora imp){
    TEvento *ee = e;
    printf("%d %d ",ee->marcatempo,ee->tipo);
    if(imp!=NULL)
    imp(ee->e_carga);
}*/

typedef struct Agenda{
    int dia,mes,ano;
    TLista *eventos;
}TAgenda;

TAgenda *criarAgenda(int dia, int mes, int ano){
    TAgenda *a=malloc(sizeof(TAgenda));
    a->dia = dia;
    a->mes = mes;
    a->ano = ano;
    a->eventos = criarLista();

    return a;
}

int comparaEvento(void *e1,void *e){
    TEvento *ee1 = e1;
    TEvento *ee2 = e;

    if(ee1->marcatempo == ee2->marcatempo)
        return 0;
    else if(ee1->marcatempo<ee2->marcatempo)
        return -1;
    else return 1;
}

void agendamento (TAgenda *a, TEvento *e ){
    inserirOrdenadoLSE(a->eventos,e,comparaEvento);
}

TEvento* proximoEvento(TAgenda *a){
    TEvento *e = removerInicio(a->eventos);
    return e;
}

/*void imprimirAgenda(TAgenda *a){
    imprimir(a->eventos,imprimirEvento);
}*/

int temEventoAgenda(TAgenda *a){
    return !vaziaLSE(a->eventos);
}










//*********INÍCIO************//


/*

Aluno: JEAN CLEISON BRAGA GUIMARÃES - 21601227

PROJETO FINAL - O mercado quer se tornar SUPERmercado

*/


//ESTRUTURA PONTO DE VENDAS (CAIXAS)

typedef struct pdv{
  int n;                //numero do caixa
  int agil;             //agilidade do caixa
  int estado;           //estado - 1 livre 0 ocupado
  int n_clientes;       //numero de clientes atendidos
  double tempoatual;    //tempo de chegada do cliente ou tempo de inicio de descanso
  double tempofinal;    //tempo final de atendimento ou tempo final de descanso
  double tempomedio;    //tempo medio de atendimento
  double tempomaximo;   //tempo maximo de atendimento
}TPdv;

//ESTRUTURA CLIENTE

typedef struct cliente{
  int itens;            //itens comprados
  int tipo_cliente;     //tipo de cliente
  int pay_time;         //tempo de pagamento
}TCliente;

//ESTRUTURA DESCANSO DO CAIXA

typedef struct saidaCaixa{
  int cx;               //numero do caixa
  int minutos;          //minutos de descanso
}TSaida;

//FUNÇÃO QUE VERIFICA O ESTADO DO CAIXA

int estadoguiche(TPdv a){
  return a.estado;
}

int main(){
  int i;
  int n_caixasVelhos,n_caixasNovos;              //Número de caixas antigos e número de novos que serão implementados

  //*****leitura caixas antigos em vetor de struct*****//
  scanf("%d",&n_caixasVelhos);
  TPdv caixasVelhos[n_caixasVelhos];

  for(i=0;i<n_caixasVelhos;i++){
    caixasVelhos[i].n=i+1;
    caixasVelhos[i].estado=1;
    caixasVelhos[i].n_clientes=0;
    caixasVelhos[i].tempoatual=0;
    caixasVelhos[i].tempofinal=0;
    caixasVelhos[i].tempomedio=0;
    caixasVelhos[i].tempomaximo=0;
    scanf("%d",&caixasVelhos[i].agil);
  }

  //*****leitura caixas novos********//
  scanf("%d",&n_caixasNovos);
  TPdv caixasNovos[n_caixasNovos];

  for(i=0;i<n_caixasNovos;i++){
    caixasNovos[i].n=n_caixasVelhos+(i+1);
    caixasNovos[i].estado=1;
    caixasNovos[i].n_clientes=0;
    caixasNovos[i].tempoatual=0;
    caixasNovos[i].tempofinal=0;
    caixasNovos[i].tempomedio=0;
    caixasNovos[i].tempomaximo=0;
    scanf("%d",&caixasNovos[i].agil);
  }

  //****agrupamento de caixas antigos e novos em apenas um vetor******//
  TPdv caixas[n_caixasNovos+n_caixasVelhos];

  for(i=0;i<(n_caixasVelhos);i++){
    caixas[i].n=caixasVelhos[i].n;
    caixas[i].estado=caixasVelhos[i].estado;
    caixas[i].agil=caixasVelhos[i].agil;
    caixas[i].n_clientes=caixasVelhos[i].n_clientes;
    caixas[i].tempoatual=caixasVelhos[i].tempoatual;
    caixas[i].tempofinal=caixasVelhos[i].tempofinal;
    caixas[i].tempomedio=caixasVelhos[i].tempomedio;
    caixas[i].tempomaximo=caixasVelhos[i].tempomaximo;
  }
   int j=0;
  for(i=n_caixasVelhos;i<(n_caixasNovos+n_caixasVelhos);i++){
    caixas[i].n=caixasNovos[j].n;
    caixas[i].estado=caixasNovos[j].estado;
    caixas[i].agil=caixasNovos[j].agil;
    caixas[i].n_clientes=caixasNovos[j].n_clientes;
    caixas[i].tempoatual=caixasNovos[j].tempoatual;
    caixas[i].tempofinal=caixasNovos[j].tempofinal;
    caixas[i].tempomedio=caixasNovos[j].tempomedio;
    caixas[i].tempomaximo=caixasNovos[j].tempomaximo;
    j++;
  }//****fim do agrupamento******//



  double Ms;          //tempo em milissegundos para leitura do produto
  scanf("%lf",&Ms);
  Ms=(Ms/1000);       //tempo em segundos para leitura do produto

  int x,y,z;          //variáveis para o tempo de espera maximo
  scanf("%d %d %d",&x,&y,&z);


  int mnt,cxd;
  int tipocliente,n_itens,tempodepagamento; //variáveis auxiliares
  double tempo;
  char tipoevento;


  TAgenda *atendimento = criarAgenda(03,12,2018);  //AGENDA DE ATENDIMENTO


  //**********leitura do primeiro evento**********//
  scanf(" %c",&tipoevento);
    if(tipoevento!='F'){
        scanf("%lf",&tempo);
        if(tipoevento=='C'){
          TCliente *a = malloc(sizeof(TCliente));
          scanf("%d %d %d",&n_itens,&tipocliente,&tempodepagamento);
          a->itens = n_itens;
          a->tipo_cliente = tipocliente;
          a->pay_time = tempodepagamento;
          TEvento *e = criarEvento(tempo,tipoevento,a);
          agendamento(atendimento,e);
          scanf(" %c",&tipoevento);
        }
      }


    //********variaveis auxiliares************//
    double tempoatendimento;
    int ultimoCaixa=0;
    int itensnaovendidos2=0,itensnaovendidos3=0;
    int desistentes2=0,desistentes3=0;
    double relogio = tempo;
    double tempodeespera = 0,tempomediodeespera = 0, tempomaximoespera = 0;
    int aux=0;

  //********leitura dos eventos*********//
  while((temEventoAgenda(atendimento))||(tipoevento!='F')){

    //*****muda o estado dos caixas caso o tempo final esteja de acordo com o relogio*****//
    for(i=0;i<(n_caixasVelhos+n_caixasNovos);i++){
      if(relogio>=caixas[i].tempofinal)
        caixas[i].estado=1;
    }


    if(ultimoCaixa==(n_caixasVelhos+n_caixasNovos))
      ultimoCaixa=0;
    j=ultimoCaixa;


    //*******LÓGICA DE ATENDIMENTO*******//
    for(i=j;i<(n_caixasVelhos+n_caixasNovos);i++){        //utilizei um *for* para o ROUND ROBIN

      if(estadoguiche(caixas[i])==1){ //se o caixa estiver livre realiza o atendimento
        TEvento *prox = proximoEvento(atendimento);
        caixas[i].estado=0;          //muda o estado para ocupado
        TCliente *c = prox->e_carga;
        if(caixas[i].n_clientes==0){
          caixas[i].tempoatual= prox->marcatempo;
          }
        else{
            if(relogio<(prox->marcatempo)){
                relogio=prox->marcatempo;
                caixas[i].tempoatual = prox->marcatempo;
            }
              else{
                caixas[i].tempoatual= caixas[i].tempofinal;
                relogio=caixas[i].tempofinal;
              }
        }

        tempoatendimento=((c->itens)*(caixas[i].agil*Ms)+(c->pay_time));  //duraçao do atendimento do cliente

        caixas[i].tempofinal = caixas[i].tempoatual + tempoatendimento;   //tempo final de atendimento

        //cliente tipo3
        if(c->tipo_cliente==3){
          tempodeespera= prox->marcatempo + (y*60);  //tempo que o cliente esta esperando
          if(caixas[i].tempoatual>tempodeespera){    //se o tempo de inicio for maior q o tempo de espera, o cliente ja abandonou
            itensnaovendidos3=itensnaovendidos3+(c->itens);
            desistentes3++;
            caixas[i].tempofinal = caixas[i].tempoatual;
            break;
          }
          tempodeespera=z*60;                     //tempo maximo de atendimento que o cliente pode esperar
          if(tempoatendimento>tempodeespera){     //se o tempo de atendimento for maior que o de espera, o cliente abandona
            itensnaovendidos3=itensnaovendidos3+(c->itens);
            desistentes3++;
            break;
          }
        }

        //cliente tipo3
        else if(c->tipo_cliente==2){
          tempodeespera = prox->marcatempo + (x*60);
          if(caixas[i].tempofinal>tempodeespera){     //se o tempo final for maior que o tempo de espera o cliente abandona
            itensnaovendidos2=itensnaovendidos2+(c->itens);
            desistentes2++;
            break;
          }

        }
       tempodeespera = caixas[i].tempofinal - prox->marcatempo;    //tempo de espera até ser atendido
       tempomediodeespera = tempomediodeespera + tempodeespera;    //tempo medio de espera total na área dos PDVs

       if(tempodeespera>tempomaximoespera)
        tempomaximoespera=tempodeespera;                    //tempo maximo de espera na área dos PDVs
        caixas[i].n_clientes++;
        caixas[i].tempomedio = caixas[i].tempomedio + tempoatendimento;   //tempo medio de atendimento do caixa atual
        if(tempoatendimento>caixas[i].tempomaximo)
            caixas[i].tempomaximo = tempoatendimento;                     //tempo maximo de atendimento do caixa atual
        ultimoCaixa++;
        break;
        }
    }

    if(ultimoCaixa==j){
    	for(i=0;i<j;i++){        //utilizei um *for* para o ROUND ROBIN

      if(estadoguiche(caixas[i])==1){ //se o caixa estiver livre realiza o atendimento
        TEvento *prox = proximoEvento(atendimento);
        caixas[i].estado=0;          //muda o estado para ocupado
        TCliente *c = prox->e_carga;
        if(caixas[i].n_clientes==0){
          caixas[i].tempoatual= prox->marcatempo;
          }
        else{
          if(relogio<prox->marcatempo){
                relogio=prox->marcatempo;
                caixas[i].tempoatual = prox->marcatempo;
            }
              else{
                caixas[i].tempoatual= caixas[i].tempofinal;
                relogio=caixas[i].tempofinal;
              }
        }

        tempoatendimento=((c->itens)*(caixas[i].agil*Ms)+(c->pay_time));  //duraçao do atendimento do cliente

        caixas[i].tempofinal = caixas[i].tempoatual + tempoatendimento;   //tempo final de atendimento
        if(caixas[i].n_clientes==0)
          relogio= caixas[i].tempofinal;
        //cliente tipo3
        if(c->tipo_cliente==3){
          tempodeespera= prox->marcatempo + (y*60);  //tempo que o cliente esta esperando
          if(caixas[i].tempoatual>tempodeespera){    //se o tempo de inicio for maior q o tempo de espera, o cliente ja abandonou
            itensnaovendidos3=itensnaovendidos3+(c->itens);
            desistentes3++;
            caixas[i].tempofinal = caixas[i].tempoatual;
            break;
          }
          tempodeespera=z*60;                     //tempo maximo de atendimento que o cliente pode esperar
          if(tempoatendimento>tempodeespera){     //se o tempo de atendimento for maior que o de espera, o cliente abandona
            itensnaovendidos3=itensnaovendidos3+(c->itens);
            desistentes3++;
            break;
          }
        }

        //cliente tipo3
        else if(c->tipo_cliente==2){
          tempodeespera = prox->marcatempo + (x*60);
          if(caixas[i].tempofinal>tempodeespera){     //se o tempo final for maior que o tempo de espera o cliente abandona
            itensnaovendidos2=itensnaovendidos2+(c->itens);
            desistentes2++;
            break;
          }

        }
       tempodeespera = caixas[i].tempofinal - prox->marcatempo;    //tempo de espera até ser atendido
       tempomediodeespera = tempomediodeespera + tempodeespera;    //tempo medio de espera total na área dos PDVs

       if(tempodeespera>tempomaximoespera)
        tempomaximoespera=tempodeespera;                    //tempo maximo de espera na área dos PDVs
        caixas[i].n_clientes++;
        caixas[i].tempomedio = caixas[i].tempomedio + tempoatendimento;   //tempo medio de atendimento do caixa atual
        if(tempoatendimento>caixas[i].tempomaximo)
            caixas[i].tempomaximo = tempoatendimento;                     //tempo maximo de atendimento do caixa atual
        ultimoCaixa++;
        break;
        }
    }
    }

    //**** leitura do proximo evento ****//
    if(tipoevento!='F'){
        scanf("%lf",&tempo);
        if(tipoevento=='C'){
          TCliente *a = malloc(sizeof(TCliente));
          scanf("%d %d %d",&n_itens,&tipocliente,&tempodepagamento);
          a->itens = n_itens;
          a->tipo_cliente = tipocliente;
          a->pay_time = tempodepagamento;
          TEvento *e = criarEvento(tempo,tipoevento,a);
          agendamento(atendimento,e);
        }

        //***saída do caixa para descanso***//
        else if(tipoevento=='S'){
          TSaida *s = malloc(sizeof(TSaida));
          scanf("%d %d",&cxd,&mnt);
          s->cx = cxd;
          s->minutos = mnt;
          if(estadoguiche(caixas[s->cx-1])==1){

          caixas[s->cx-1].estado=0;
          caixas[s->cx-1].tempoatual = tempo;
          caixas[s->cx-1].tempofinal = tempo + (s->minutos*60);
          if(caixas[s->cx-1].tempofinal<relogio)
            caixas[s->cx-1].tempofinal= relogio;

          }
          else{
            double aposdescanso = tempo + (s->minutos*60);
            if(aposdescanso > caixas[s->cx-1].tempofinal){
              caixas[s->cx-1].tempofinal = aposdescanso;
              if(caixas[s->cx-1].tempofinal<relogio)
                caixas[s->cx-1].tempofinal=relogio;
            }
          }
        }
        scanf(" %c",&tipoevento);
      }

      relogio=relogio+0.1; //RELÓGIO
  }


  //*******LEITURA DOS DADOS ANTES DA IMPLEMENTAÇÃO DOS NOVOS CAIXAS**********//
  for(i=0;i<n_caixasVelhos;i++){
    scanf("%d",&caixasVelhos[i].n_clientes);
    scanf("%lf",&caixasVelhos[i].tempomedio);
    scanf("%lf",&caixasVelhos[i].tempomaximo);
  }
  double total_clientesPDVantes;
  double total_tempmedioPDVantes,total_tempmaximoPDVantes;
  double desistentes2antes,desistentes3antes;
  double itensnaovendidos2antes,itensnaovendidos3antes;
  scanf("%lf",&total_clientesPDVantes);
  scanf("%lf",&total_tempmedioPDVantes);
  scanf("%lf",&total_tempmaximoPDVantes);
  scanf("%lf",&desistentes2antes);
  scanf("%lf",&itensnaovendidos2antes);
  scanf("%lf",&desistentes3antes);
  scanf("%lf",&itensnaovendidos3antes);
  //FIM DA LEITURA DOS DADOS ANTERIORES


  int totalClientes = 0;   //Total de clientes área PDVs

  for(i=0;i<(n_caixasNovos+n_caixasVelhos);i++){
    caixas[i].tempomedio = caixas[i].tempomedio/(double)caixas[i].n_clientes;
    totalClientes = totalClientes + caixas[i].n_clientes;
    printf("PDV - %d\nClientes Atendidos: %d\nTempo Medio de Atendimento: %.2lf\nTempo Maximo de Atendimento: %.2lf\n\n",caixas[i].n,caixas[i].n_clientes,caixas[i].tempomedio,caixas[i].tempomaximo);
  }

    tempomediodeespera = tempomediodeespera/(double)totalClientes; //tempo medio de espera area PDVs
    printf("\n---------------------------------\n\n");

    printf("Dados atuais da Area de Atendimento\n\n");

    printf("Total de clientes atendidos: %d\n",totalClientes);
    printf("Tempo medio de espera: %.2lf\n",tempomediodeespera);
    printf("Tempo maximo de espera: %.2lf\n",tempomaximoespera);
    printf("Clientes Desistentes Tipo 2: %d\n",desistentes2);
    printf("Itens nao vendidos: %d\n",itensnaovendidos2);
    printf("Clientes Desistentes Tipo 3: %d\n",desistentes3);
    printf("Itens nao vendidos: %d\n",itensnaovendidos3);


  //******COMPARAÇÃO COM OS DADOS ANTERIORES*********//

  double melhoraClientes = (((double)totalClientes - total_clientesPDVantes)/total_clientesPDVantes)*100;
  double melhoraTempoMedio = ((tempomediodeespera - total_tempmedioPDVantes)/total_tempmedioPDVantes)*100;
  double melhoraTempoMax = ((tempomaximoespera - total_tempmaximoPDVantes)/total_tempmaximoPDVantes)*100;
  double melhoraDesistentesT2 = (((double)desistentes2 - desistentes2antes)/desistentes2antes)*100;
  double melhoraItensT2 = (((double)itensnaovendidos2 - itensnaovendidos2antes)/itensnaovendidos2antes)*100;
  double melhoraDesistentesT3 = (((double)desistentes3 - desistentes3antes)/desistentes3antes)*100;
  double melhoraItensT3 = (((double)itensnaovendidos3 - itensnaovendidos3antes)/itensnaovendidos3antes)*100;

  printf("\n---------------------------------\n\n");

  printf("Apresentação dos índices de melhora\n\n");

  printf("AUMENTO DE CLIENTES ATENDIDOS: %.2lf%%\n",melhoraClientes);
  printf("REDUÇÃO NO TEMPO MEDIO DE ATENDIMENTO: %.2lf%%\n",melhoraTempoMedio );
  printf("REDUÇÃO NO TEMPO MAXIMO DE ESPERA: %.2lf%%\n",melhoraTempoMax);
  printf("REDUÇÃO DE DESISTENTES TIPO 2: %.2lf%%\n",melhoraDesistentesT2);
  printf("REDUÇÃO DE ITENS NAO VENDIDOS TIPO 2: %.2lf%%\n",melhoraItensT2);
  printf("REDUÇÃO DE DESISTENTES TIPO 3: %.2lf%%\n",melhoraDesistentesT3);
  printf("REDUÇÃO DE ITENS NAO VENDIDOS TIPO 3: %.2lf%%\n",melhoraItensT3);
  return 0;
}
