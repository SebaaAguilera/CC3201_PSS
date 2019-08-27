#include "t1.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//typedef unsigned int uint;

uint comprimir(uint *a, int nbits){
    //uint size = 4
    int a_length = 0;
    for (int i = nbits ; i<(sizeof(uint)<<3); i+= nbits){
        a_length++;
    }
    
    uint c = 0; 
    uint mask = ~(-1 << nbits);

    for(int i = 0; i<a_length; i++){
        a[i] &= mask; 
        //a[i] <<= nbits * (a_length - (i + 1));
        for(int j = 0; j<(a_length - (i + 1)); j++){
            a[i] <<= nbits;
        }
        c |= a[i];
    }
    return c;
}

char *insercion(char *d, char *s){        
    char *newStr = malloc(sizeof(char)*(strlen(s)+strlen(d)+1));
    
    strcpy(newStr,s);
    strcat(newStr,d);
    
    return newStr;
}

void insertar(char *d, char *s){

    char *auxs = s;
    char *auxd = d;
    char *auxd2 = d;
    
    for(int i = 0; i<strlen(s)-1;i++){
        auxs++;
    }
        
    for (int l = 0; l<strlen(s);l++){
        for (int j = 0; j<strlen(d);j++){;
            auxd++;
            auxd2++;
        }auxd2--;

        for(int k = 0; k<strlen(d)-1;k++){
            *auxd=*auxd2;
            auxd--;
            auxd2--;
        }*auxd=*auxs;
        auxd2++;        
        auxs--;
    }
}