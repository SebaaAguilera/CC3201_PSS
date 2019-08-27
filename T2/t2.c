#include "t2.h"
#include <stdio.h>

int calzar(Nodo *a, Nodo **ppat){
    Nodo *b = *ppat;

    if (b==NULL) { 
        *ppat=a;
        return 1;
    } else if (a==NULL || a->x != b->x){
        return 0;
    }
    
    int i = calzar(a->izq,&b->izq) && calzar(a->der,&b->der);
    //printf("%i\n",i);
    return i;

}