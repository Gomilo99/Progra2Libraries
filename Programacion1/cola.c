#include "cola.h"

#include <stdio.h>

void cola_inicializar(Cola* cola) {
    if (cola == NULL) {
        return;
    }

    lista_inicializar(&cola->lista);
}

bool cola_esta_vacia(const Cola* cola) {
    if (cola == NULL) {
        return true;
    }

    return lista_esta_vacia(&cola->lista);
}

size_t cola_tamanio(const Cola* cola) {
    if (cola == NULL) {
        return 0;
    }

    return lista_tamanio(&cola->lista);
}

bool cola_encolar(Cola* cola, int dato) {
    if (cola == NULL) {
        return false;
    }

    return lista_insertar_final(&cola->lista, dato);
}

bool cola_desencolar(Cola* cola, int* dato) {
    if (cola == NULL) {
        return false;
    }

    return lista_eliminar_en_posicion(&cola->lista, 0, dato);
}

bool cola_frente(const Cola* cola, int* dato) {
    if (cola == NULL) {
        return false;
    }

    return lista_obtener(&cola->lista, 0, dato);
}

void cola_imprimir(const Cola* cola) {
    if (cola == NULL) {
        printf("(cola nula)\n");
        return;
    }

    printf("Frente -> ");
    lista_imprimir(&cola->lista);
}

void cola_destruir(Cola* cola) {
    if (cola == NULL) {
        return;
    }

    lista_destruir(&cola->lista);
}