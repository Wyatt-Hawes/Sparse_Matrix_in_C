CC = gcc
CFLAGS = -std=c17 -Wall -Werror -Wextra -Wpedantic -g#$(shell pkg-config --cflags)

all: MatrixTest Sparse

MatrixTest: List.o Matrix.o MatrixTest.o
	$(CC) -o $@ $^ 

Sparse: List.o Matrix.o Sparse.o
	$(CC) -o  $@ $^ 

%.o: %.c
	$(CC) $(CFLAGS) -c -Ofast $<

clean: spotless
	rm -f *.o
	
spotless: clean
	rm -f MatrixTest Sparse
