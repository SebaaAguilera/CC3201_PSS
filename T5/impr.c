#include <pthread.h>
#include "impr.h"
#include <stdio.h>
#include <stdlib.h>

#define FALSE 0;
#define TRUE 1;

struct orden{
    Doc *doc;
    int listo;
}; /* Un recibo */

pthread_mutex_t mutex= PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond= PTHREAD_COND_INITIALIZER;

ColaFifo *colita;
pthread_t *arregloThread;
//indica si las impresoras están activas
int activas = FALSE
//numero de impresoras
int n_imp;


void* fThread(void* args){
    Impr *impresora= args;
    for(;;){
        pthread_mutex_lock(&mutex);
        while (vacia(colita)){
            pthread_cond_wait(&cond,&mutex);
            if (!activas){
                pthread_mutex_unlock(&mutex);          
                return NULL;
            }

        }
        Orden *orden=(Orden*)extraer(colita);
    
        pthread_mutex_unlock(&mutex);
        imprimir(orden->doc, impresora);
        pthread_mutex_lock(&mutex);
        orden->listo = TRUE;
        /*Despierta stuff en espera */
        pthread_cond_broadcast(&cond); 
        pthread_mutex_unlock(&mutex);
    }
}

void init_impr(Impr **imprs, int n_impr){
    n_imp=n_impr;
    arregloThread=(pthread_t *)malloc((n_impr+1)*sizeof(pthread_t));
    colita=nuevaColaFifo();
    for(int i=0;i<n_impr;i++){
        pthread_create(&arregloThread[i], NULL, fThread, imprs[i]);
        }
    //están todas las impresoras activas
    activas=TRUE;
}

Orden *imprimir_asinc(Doc *doc) {
    Orden *prec=malloc(sizeof(Orden));
    prec->doc= doc;
    prec->listo= FALSE;
    pthread_mutex_lock(&mutex);
    agregar(colita, prec);
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);
    return prec;
}


void confirmar(Orden *ord) {
    pthread_mutex_lock(&mutex);
    while (!ord->listo){
        pthread_cond_wait(&cond,&mutex);
    }
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);
    free(ord);
    
}

void terminar_impr(){
    int indice=0;
    activas=FALSE;
    
    pthread_cond_broadcast(&cond); 
    while (indice<n_imp){
        pthread_join(arregloThread[indice],NULL);
        indice++;
    }
    destruirColaFifo(colita);
}