#include <assert.h>
#include <stdio.h>

#include "cola.h"
#include "lista.h"
#include "pila.h"

static void probar_lista(void) {
    Lista lista;
    int valor;
    size_t posicion;

    lista_inicializar(&lista);
    assert(lista_esta_vacia(&lista));
    assert(lista_insertar_inicio(&lista, 20));
    assert(lista_insertar_inicio(&lista, 10));
    assert(lista_insertar_final(&lista, 30));
    assert(lista_insertar_en_posicion(&lista, 25, 2));
    assert(lista_tamanio(&lista) == 4);
    assert(lista_obtener(&lista, 2, &valor));
    assert(valor == 25);
    assert(lista_buscar(&lista, 30, &posicion));
    assert(posicion == 3);
    assert(lista_eliminar_en_posicion(&lista, 1, &valor));
    assert(valor == 20);
    assert(lista_tamanio(&lista) == 3);
    lista_destruir(&lista);
}

static void probar_pila(void) {
    Pila pila;
    int valor;

    pila_inicializar(&pila);
    assert(pila_esta_vacia(&pila));
    assert(pila_apilar(&pila, 5));
    assert(pila_apilar(&pila, 8));
    assert(pila_apilar(&pila, 13));
    assert(pila_tamanio(&pila) == 3);
    assert(pila_cima(&pila, &valor));
    assert(valor == 13);
    assert(pila_desapilar(&pila, &valor));
    assert(valor == 13);
    assert(pila_desapilar(&pila, &valor));
    assert(valor == 8);
    pila_destruir(&pila);
}

static void probar_cola(void) {
    Cola cola;
    int valor;

    cola_inicializar(&cola);
    assert(cola_esta_vacia(&cola));
    assert(cola_encolar(&cola, 100));
    assert(cola_encolar(&cola, 200));
    assert(cola_encolar(&cola, 300));
    assert(cola_tamanio(&cola) == 3);
    assert(cola_frente(&cola, &valor));
    assert(valor == 100);
    assert(cola_desencolar(&cola, &valor));
    assert(valor == 100);
    assert(cola_desencolar(&cola, &valor));
    assert(valor == 200);
    cola_destruir(&cola);
}

int main(void) {
    probar_lista();
    probar_pila();
    probar_cola();
    printf("Todas las pruebas pasaron correctamente.\n");
    return 0;
}