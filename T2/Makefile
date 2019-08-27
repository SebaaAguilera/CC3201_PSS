# Instrucciones
# =============
#
# Cree el archivo t2.c y programe ahi las 3 funciones pedidas.
# No modifique los demas archivos.
#
# Su tarea ya esta compilada con la opcion -g, que es necesaria para
# que use gdb o ddd para depurar los errores de programacion.
#
# Para compilar ingrese el comando:
#
# $ make
#
# Resuelva todos los errores y warnings de la compilacion.
# Cuando la compilacion sea exitosa, ejecute el programa de prueba con:
#
# $ ./test-t2
#
# El programa de prueba le indicara cual test falla o lo felicitara si
# paso todos los tests.
#
# Para borrar todos los archivos generados (incluyendo binarios):
# $ make clean

CFLAGS= -g -Wall -pedantic -std=c99
LDFLAGS= -g

all: test-t2

test-t2: test-t2.o t2.o

test-t2.o t2.o: t2.h

clean:
	rm -f *.o
	rm -f test-t2
