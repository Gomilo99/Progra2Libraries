CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
OBJETOS = lista.o pila.o cola.o

ifeq ($(OS),Windows_NT)
EXE = .exe
else
EXE =
endif

all: ejemplo_uso$(EXE) prueba_estructuras$(EXE)

ejemplo_uso$(EXE): ejemplo_uso.o $(OBJETOS)
	$(CC) $(CFLAGS) -o $@ $^

prueba_estructuras$(EXE): prueba_estructuras.o $(OBJETOS)
	$(CC) $(CFLAGS) -o $@ $^

lista.o: lista.c lista.h nodo.h
	$(CC) $(CFLAGS) -c lista.c

pila.o: pila.c pila.h lista.h nodo.h
	$(CC) $(CFLAGS) -c pila.c

cola.o: cola.c cola.h lista.h nodo.h
	$(CC) $(CFLAGS) -c cola.c

ejemplo_uso.o: ejemplo_uso.c lista.h pila.h cola.h
	$(CC) $(CFLAGS) -c ejemplo_uso.c

prueba_estructuras.o: prueba_estructuras.c lista.h pila.h cola.h
	$(CC) $(CFLAGS) -c prueba_estructuras.c

run-ejemplo: ejemplo_uso$(EXE)
	./ejemplo_uso$(EXE)

run-pruebas: prueba_estructuras$(EXE)
	./prueba_estructuras$(EXE)

clean:
	powershell -NoProfile -Command "Remove-Item -Force -ErrorAction SilentlyContinue *.o, *.exe"

.PHONY: all clean run-ejemplo run-pruebas