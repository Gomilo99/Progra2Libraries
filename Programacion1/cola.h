#ifndef COLA_H
#define COLA_H

#include <stdbool.h>
#include <stddef.h>

#include "lista.h"

typedef struct {
	Lista lista;
} Cola;

void cola_inicializar(Cola* cola);
bool cola_esta_vacia(const Cola* cola);
size_t cola_tamanio(const Cola* cola);
bool cola_encolar(Cola* cola, int dato);
bool cola_desencolar(Cola* cola, int* dato);
bool cola_frente(const Cola* cola, int* dato);
void cola_imprimir(const Cola* cola);
void cola_destruir(Cola* cola);

#endif
