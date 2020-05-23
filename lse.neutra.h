// tipo ponteiro para função
typedef void (*TImpressora)(void*);
typedef int (*TComparador)(void*,void*);
typedef struct lista TLista;
TLista *criarLista();
void inserirInicioLSE(TLista *lst, void *e_carganova);
void inserirFinalLSE(TLista *lst, void *e_carganova);
int compara(void* e_carganova, void* carga);
void inserirOrdenadoLSE(TLista *lst, void *e_carganova, TComparador compara);
void* removerInicioLSE(TLista *lst);
void* removerFinalLSE(TLista *lst);
void imprimirLSE(TLista *lst, TImpressora impressora);
