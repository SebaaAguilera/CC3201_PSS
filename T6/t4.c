#include <stdio.h>
#include <pthread.h>

#include "integral.h"

typedef struct {
  Funcion f; void *ptr;
  double xi, xf, resp;
  int n;
} Args;

void* integral_mt(void *pt){
  Args *arg = pt;
  arg->resp=integral(arg->f,arg->ptr,arg->xi,arg->xf,arg->n);
  return NULL;
}

double integral_par(Funcion f, void *ptr, double xi, double xf, int n, int p) {
  pthread_t t[p]; Args array[p];
  double trap = n/p;
  double final=0;
  for (int i=0; i<p; i++){
    Args *arg = &array[i];
    arg->f=f; arg->ptr=ptr; arg->xi=xi+i*trap; arg->xf=xi+(i+1)*trap; arg->n=trap;
    pthread_create(&t[i],NULL,integral_mt,arg);
  } 
  for (int i=0; i<p; i++){
    Args *arg = &array[i];
    final+= arg->resp;
    pthread_join(t[i],NULL);
  }
  return final; 
}
