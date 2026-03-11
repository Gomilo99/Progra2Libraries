#include "lista.h"

#include <stdio.h>
#include <stdlib.h>

static Nodo* crear_nodo(int dato) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevo == NULL) {
        return NULL;
    }

    nuevo->dato = dato;
    nuevo->siguiente = NULL;
    return nuevo;
}

void lista_inicializar(Lista* lista) {
    if (lista == NULL) {
        return;
    }

    lista->cabeza = NULL;
    lista->tamanio = 0;
}

bool lista_esta_vacia(const Lista* lista) {
    return lista == NULL || lista->cabeza == NULL;
}

size_t lista_tamanio(const Lista* lista) {
    if (lista == NULL) {
        return 0;
    }

    return lista->tamanio;
}

bool lista_insertar_inicio(Lista* lista, int dato) {
    Nodo* nuevo;

    if (lista == NULL) {
        return false;
    }

    nuevo = crear_nodo(dato);
    if (nuevo == NULL) {
        return false;
    }

    nuevo->siguiente = lista->cabeza;
    lista->cabeza = nuevo;
    lista->tamanio++;
    return true;
}

bool lista_insertar_final(Lista* lista, int dato) {
    Nodo* actual;
    Nodo* nuevo;

    if (lista == NULL) {
        return false;
    }

    if (lista_esta_vacia(lista)) {
        return lista_insertar_inicio(lista, dato);
    }

    nuevo = crear_nodo(dato);
    if (nuevo == NULL) {
        return false;
    }

    actual = lista->cabeza;
    while (actual->siguiente != NULL) {
        actual = actual->siguiente;
    }

    actual->siguiente = nuevo;
    lista->tamanio++;
    return true;
}

bool lista_insertar_en_posicion(Lista* lista, int dato, size_t posicion) {
    Nodo* actual;
    Nodo* nuevo;
    size_t indice;

    if (lista == NULL || posicion > lista->tamanio) {
        return false;
    }

    if (posicion == 0) {
        return lista_insertar_inicio(lista, dato);
    }

    nuevo = crear_nodo(dato);
    if (nuevo == NULL) {
        return false;
    }

    actual = lista->cabeza;
    for (indice = 0; indice + 1 < posicion; indice++) {
        actual = actual->siguiente;
    }

    nuevo->siguiente = actual->siguiente;
    actual->siguiente = nuevo;
    lista->tamanio++;
    return true;
}

bool lista_obtener(const Lista* lista, size_t posicion, int* dato) {
    Nodo* actual;
    size_t indice;

    if (lista == NULL || dato == NULL || posicion >= lista->tamanio) {
        return false;
    }

    actual = lista->cabeza;
    for (indice = 0; indice < posicion; indice++) {
        actual = actual->siguiente;
    }

    *dato = actual->dato;
    return true;
}

bool lista_eliminar_en_posicion(Lista* lista, size_t posicion, int* dato) {
    Nodo* eliminado;
    Nodo* actual;
    size_t indice;

    if (lista == NULL || posicion >= lista->tamanio) {
        return false;
    }

    if (posicion == 0) {
        eliminado = lista->cabeza;
        lista->cabeza = eliminado->siguiente;
    } else {
        actual = lista->cabeza;
        for (indice = 0; indice + 1 < posicion; indice++) {
            actual = actual->siguiente;
        }

        eliminado = actual->siguiente;
        actual->siguiente = eliminado->siguiente;
    }

    if (dato != NULL) {
        *dato = eliminado->dato;
    }

    free(eliminado);
    lista->tamanio--;
    return true;
}

bool lista_buscar(const Lista* lista, int dato, size_t* posicion) {
    Nodo* actual;
    size_t indice;

    if (lista == NULL) {
        return false;
    }

    actual = lista->cabeza;
    indice = 0;
    while (actual != NULL) {
        if (actual->dato == dato) {
            if (posicion != NULL) {
                *posicion = indice;
            }
            return true;
        }

        actual = actual->siguiente;
        indice++;
    }

    return false;
}

void lista_imprimir(const Lista* lista) {
    Nodo* actual;

    if (lista == NULL) {
        printf("(lista nula)\n");
        return;
    }

    printf("[");
    actual = lista->cabeza;
    while (actual != NULL) {
        printf("%d", actual->dato);
        if (actual->siguiente != NULL) {
            printf(", ");
        }
        actual = actual->siguiente;
    }
    printf("]\n");
}

void lista_destruir(Lista* lista) {
    if (lista == NULL) {
        return;
    }

    while (!lista_esta_vacia(lista)) {
        lista_eliminar_en_posicion(lista, 0, NULL);
    }
}