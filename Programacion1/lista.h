#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stddef.h>

#include "nodo.h"

typedef struct {
	Nodo* cabeza;
	size_t tamanio;
} Lista;

void lista_inicializar(Lista* lista);
bool lista_esta_vacia(const Lista* lista);
size_t lista_tamanio(const Lista* lista);
bool lista_insertar_inicio(Lista* lista, int dato);
bool lista_insertar_final(Lista* lista, int dato);
bool lista_insertar_en_posicion(Lista* lista, int dato, size_t posicion);
bool lista_obtener(const Lista* lista, size_t posicion, int* dato);
bool lista_eliminar_en_posicion(Lista* lista, size_t posicion, int* dato);
bool lista_buscar(const Lista* lista, int dato, size_t* posicion);
void lista_imprimir(const Lista* lista);
void lista_destruir(Lista* lista);

#endif
