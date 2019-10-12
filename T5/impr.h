/* Tipos que Ud. debe definir en impr.c */
typedef struct orden Orden;

/* Tipos dados */
typedef struct impr Impr;
typedef struct doc Doc;
typedef struct colafifo ColaFifo;

/* Funciones que Ud. debe programar en impr.c */

void init_impr(Impr **imprs, int n_impr);
void terminar_impr();
Orden *imprimir_asinc(Doc *doc);
void confirmar(Orden *ord);

/* Funciones dadas */

void imprimir(Doc *doc, Impr *impr);
ColaFifo *nuevaColaFifo();
void destruirColaFifo(ColaFifo *cola);
int vacia(ColaFifo *cola);
void agregar(ColaFifo *cola, void *ptr);
void *extraer(ColaFifo *cola);
