#define _DEFAULT_SOURCE 1  /* para poder usar usleep */
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "impr.h"

/* las estructuras doc e impr se definen aca para esconderlas de la
 * implementacion del sistema de impresion en impr.c.  Considere que
 * en impr.c Ud. no conoce los campos incluidos en struct doc y struc impr.
 */
struct doc {
  char *nombre; /* nombre de la obra */
  int duracion; /* tiempo que toma imprimir esta obra */
  int impreso;  /* 1 si fue impreso en alguna de las impresoras */
};

struct impr {
  int id; /* identificacion de la impresora: 0, 1, 2 */
  Doc *doc; /* nombre del documento que se impreme ahora, NULL si esta ociosa */
  int apagado; /* 1 cuando se apago la impresora al final */
};

#define N_IMPR 3
#define N_DOC 10

static Doc docs[N_DOC]= {
  {"la caperucita", 5000, 0},
  {"el quijote", 12000, 0},
  {"la iliada", 8000, 0},
  {"la odisea", 9000, 0},
  {"el padrino", 10000, 0},
  {"hansel y gretel", 4000, 0},
  {"el principito", 6000, 0},
  {"papelucho", 7000, 0},
  {"blancanieves", 3000, 0},
  {"alicia en el pais de las maravillas", 11000, 0}
};

/* detiene la ejecucion con un mensaje cuando se detecta un error */
void error(char *fmt, ...) {
  va_list args;

  va_start(args, fmt);
  fprintf(stderr, "Error: ");
  vfprintf(stderr, fmt, args);
  fprintf(stderr, "\n");
  va_end(args);

  exit(1);
}

/* entrega el tiempo transcurrido desde 1/1/1970 en milisegundos */
long long get_time() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec*1000+tv.tv_usec/1000;
}

/* crea una impresora */
Impr *nuevaImpr(int id) {
  Impr *impr= malloc(sizeof(Impr));
  impr->id= id;
  impr->doc= NULL;
  impr->apagado= 0;
  return impr;
}

/* realiza el trabajo de impresion efectivo en la impresora impr */
void imprimir(Doc *doc, Impr *impr) {
  if (impr->doc!=NULL)
    error("No se puede imprimir %s en impresora %d.  Esta imprimiendo %s\n",
          doc->nombre, impr->id, impr->doc->nombre);
  printf("Comienza impresion de %s en impresora %d\n", doc->nombre, impr->id);
  impr->doc= doc;
  /* Ja ja: no se imprime nada.  Solo perdemos el tiempo.  :-)  */
  usleep(doc->duracion*1000);
  printf("Termina impresion de %s en impresora %d\n", doc->nombre, impr->id);
  impr->doc->impreso= 1;
  impr->doc= NULL;
}

int main() {
  Impr *imprs[N_IMPR]= { nuevaImpr(0), nuevaImpr(1), nuevaImpr(2) };
  init_impr(imprs, N_IMPR);
  Orden *ordenes[N_DOC];
  long long init_time= get_time();

  for (int i= 0; i<N_DOC; i++) {
    printf("ordenando impresion: %s\n", docs[i].nombre);
    ordenes[i]= imprimir_asinc(&docs[i]);
    usleep(1500000);
  }

  for (int i= 0; i<N_DOC; i++) {
    printf("confirmando impresion: %s (%d de %d)\n",
           docs[i].nombre, i+1, N_DOC);
    confirmar(ordenes[i]);
    if (!docs[i].impreso)
      error("mentira, el documento %s no se ha impreso aun\n", docs[i].nombre);
  }

  printf("Apagando impresoras\n");
  terminar_impr();

  long long final_time= get_time();
  long long total_time= final_time-init_time;
  printf("Tiempo total de impresion: %lld milisegundos\n", total_time);
  if (total_time>40000)
    error("se excedio el tiempo requerido de %d milisegundo\n", 40000);
  if (total_time>=33000)
    printf("Al profesor le dio 31011 milisegundos.  Raro.\n");
  printf("Felicitaciones su tarea funciona correctamente\n");
  return 0;
}

/* La Cola Fifo */

#define MAXTAM 100

struct colafifo {
  int prim, ult, tam;
  void *arr[MAXTAM];
};

ColaFifo *nuevaColaFifo() {
  ColaFifo *cola= malloc(sizeof(ColaFifo));
  cola->prim= cola->ult= cola->tam= 0;
  return cola;
}

void destruirColaFifo(ColaFifo *cola) {
  free(cola);
}

int vacia(ColaFifo *cola) {
  return cola->tam==0;
}

void agregar(ColaFifo *cola, void *ptr) {
  if (cola->tam>=MAXTAM) {
    fprintf(stderr, "Error: tamanno de cola excedido\n");
    exit(1);
  }
  cola->arr[cola->ult]= ptr;
  cola->ult = (cola->ult+1)%MAXTAM;
  cola->tam++;
}

void *extraer(ColaFifo *cola) {
  if (cola->tam<=0) {
    return NULL;
  }
  void *ptr= cola->arr[cola->prim];
  cola->prim= (cola->prim+1)%MAXTAM;
  cola->tam--;
  return ptr;
}
