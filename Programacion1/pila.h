#ifndef PILA_H
#define PILA_H

#include <stdbool.h>
#include <stddef.h>

#include "lista.h"

typedef struct {
	Lista lista;
} Pila;

void pila_inicializar(Pila* pila);
bool pila_esta_vacia(const Pila* pila);
size_t pila_tamanio(const Pila* pila);
bool pila_apilar(Pila* pila, int dato);
bool pila_desapilar(Pila* pila, int* dato);
bool pila_cima(const Pila* pila, int* dato);
void pila_imprimir(const Pila* pila);
void pila_destruir(Pila* pila);

#endif
