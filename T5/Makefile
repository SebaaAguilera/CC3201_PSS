
CFLAGS= -g -Wall -pedantic -std=c99
LDFLAGS= -g -pthread

all: test-impr

test-impr.o impr.o: impr.h

test-impr: test-impr.o impr.o

clean:
	rm -f *.o
	rm -f test-impr
