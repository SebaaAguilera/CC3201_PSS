#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "t1.h"

int main(int argc, char **argv) {
  // Parte a
  // int a[]= { 0b100 110 101 011 000, 0b101 101 011, 0b001 010 000 };
  uint a[]= { 046530, 0553, 0120 };
  uint r= comprimir(a, 9);
  if (r!=0530553120) {
    fprintf(stderr, "resultado incorrecto %o\n", r);
    exit(1);
  }
  // Parte b
  char *s1= insercion("perro", "gato");
  if (strcmp(s1, "gatoperro")!=0) {
    fprintf(stderr, "resultado incorrecto %s\n", s1);
    exit(1);
  }
  char *s2= insercion("", "gato");
  if (strcmp(s2, "gato")!=0) {
    fprintf(stderr, "resultado incorrecto %s\n", s2);
    exit(1);
  }
  char *s3= insercion("perro", "");
  if (strcmp(s3, "perro")!=0) {
    fprintf(stderr, "resultado incorrecto %s\n", s3);
    exit(1);
  }
  // Parte c
  char d[80]= "*perro"; // d es un arreglo de 80 bytes con el string "perro"
  d[strlen("*gatoperro")+1]='/';
  insertar(d+1, "gato"); // d es el string "gatoperro"
  if (strcmp(d+1, "gatoperro")!=0) {
    fprintf(stderr, "resultado incorrecto %s\n", d);
    exit(1);
  }
  if (d[0]!='*' || d[strlen("*gatoperro")+1]!='/') {
    fprintf(stderr, "escribio fuera del string de destino\n");
    exit(1);
  }
  printf("Bien, felicitaciones\n");
  return 0;
}
