#include "pila.h"

#include <stdio.h>

void pila_inicializar(Pila* pila) {
    if (pila == NULL) {
        return;
    }

    lista_inicializar(&pila->lista);
}

bool pila_esta_vacia(const Pila* pila) {
    if (pila == NULL) {
        return true;
    }

    return lista_esta_vacia(&pila->lista);
}

size_t pila_tamanio(const Pila* pila) {
    if (pila == NULL) {
        return 0;
    }

    return lista_tamanio(&pila->lista);
}

bool pila_apilar(Pila* pila, int dato) {
    if (pila == NULL) {
        return false;
    }

    return lista_insertar_inicio(&pila->lista, dato);
}

bool pila_desapilar(Pila* pila, int* dato) {
    if (pila == NULL) {
        return false;
    }

    return lista_eliminar_en_posicion(&pila->lista, 0, dato);
}

bool pila_cima(const Pila* pila, int* dato) {
    if (pila == NULL) {
        return false;
    }

    return lista_obtener(&pila->lista, 0, dato);
}

void pila_imprimir(const Pila* pila) {
    if (pila == NULL) {
        printf("(pila nula)\n");
        return;
    }

    printf("Tope -> ");
    lista_imprimir(&pila->lista);
}

void pila_destruir(Pila* pila) {
    if (pila == NULL) {
        return;
    }

    lista_destruir(&pila->lista);
}