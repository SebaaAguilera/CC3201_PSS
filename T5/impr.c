#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#include "impr.h"

#define FALSE 0
#define TRUE 1

/* indique aca los campos que necesita en una orden de trabajo */
struct orden {
  Doc *doc;
  int listo;
};

/* defina aca las variables globales que necesite y programe las funciones
 * pedidas.
 */
ColaFifo *cola;
int n_impr_aux = 0;
pthread_t *t; 
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

void * imprimir_thread(void * ptr){
  for(;;){
    pthread_mutex_lock(&m);
    while(vacia(cola))
      pthread_cond_wait(&c,&m);
    Impr * impr = ptr;
    Orden *ord = extraer(cola);
    pthread_mutex_unlock(&m);
    imprimir(ord->doc,impr);
    pthread_mutex_lock(&m);
    ord->listo=TRUE;
    pthread_cond_broadcast(&c);
    pthread_mutex_unlock(&m);
  }  
  return NULL;
}

void init_impr(Impr **imprs, int n_impr){
  n_impr_aux=n_impr;
  t = malloc(sizeof(pthread_t)*n_impr);
  cola = nuevaColaFifo();
  for (int i=0; i<n_impr;i++){
      pthread_create(&t[i],NULL,imprimir_thread,imprs[i]);
  }
}

void terminar_impr() {
  for(int i = 0; i < n_impr_aux; i++){
    pthread_join(t[i],NULL);
  }
}

Orden *imprimir_asinc(Doc *doc) {
  Orden *ord = malloc(sizeof(Orden));
  ord->doc=doc;
  ord->listo=FALSE;
  agregar(cola,ord);
  pthread_cond_broadcast(&c);
  return ord;
}

void confirmar(Orden *ord) {
  pthread_mutex_lock(&m);
  while (!ord->listo)
    pthread_cond_wait(&c,&m);
  pthread_cond_broadcast(&c);
  pthread_mutex_unlock(&m);
  free(ord);
}

