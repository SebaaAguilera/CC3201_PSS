#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#include "impr.h"

/* indique aca los campos que necesita en una orden de trabajo */
struct orden {
  ...
};

/* defina aca las variables globales que necesite y programe las funciones
 * pedidas.
 */

void init_impr(Impr **imprs, int n_impr) {
  ... /* use pthread_create para lanzar n_impr threads consumidores */
}

void terminar_impr() {
  ... /* no olvide invocar pthread_join para enterrar los threads */
}

Orden *imprimir_asinc(Doc *doc) {
  ...
}

void confirmar(Orden *ord) {
  ...
}

/* no olvide programar ademas la funcion que ejecutara cada thread */
