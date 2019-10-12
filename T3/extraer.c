#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char** argv) {
    char *nom_cola = argv[1];
    FILE *cola= fopen(argv[1], "r+"); 

    //si está malo lo bota
    if (cola==NULL) {
        perror("fopen");
        exit(1);
    }

    int largo_fila_uno = 4;
    int largo_filas = 16;
    
    // retorna el largo de la cola
    char fila_uno[largo_fila_uno+1];
    fread(fila_uno,largo_fila_uno+1, 1, cola);
    int cant_filas = atoi(fila_uno);
    if (cant_filas==0){
        fprintf(stderr, "error: %s esta vacia\n",nom_cola);
        exit(1);
    }
      
    char filas[largo_filas+1];
    int prioridad = INT32_MAX;
    int fila_prioridad;
    char *p;
    char elegido[10];
    //itera por las filas
    for(int i = 0; i<cant_filas; i++){
        fread(filas,largo_filas+1, 1, cola);
        p=filas+10;
        int prioridad_i = atoi(p);
        if (prioridad_i < prioridad){
            prioridad = prioridad_i;
            fila_prioridad = i;
            memcpy(elegido,filas,10);
        }
    }

    printf("%s\n", elegido); //imprimir el extraido;

    //copiar el de más abajo sobre el extraido
    fseek(cola,largo_fila_uno+1+(largo_filas+1)*fila_prioridad,SEEK_SET);
    fwrite(filas,largo_filas+1,1,cola);
    
    // reduce el número de elementos de la cola
    sprintf(fila_uno, "%-4d\n",cant_filas-1);
    fseek(cola,0,SEEK_SET);
    fwrite(fila_uno,largo_fila_uno+1,1,cola);
    fclose(cola);

    return 0;
}
