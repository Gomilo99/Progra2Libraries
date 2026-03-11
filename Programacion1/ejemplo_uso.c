#include <stdio.h>

#include "cola.h"
#include "lista.h"
#include "pila.h"

int main(void) {
    Lista productos;
    Pila historial;
    Cola turnos;
    int valor;

    lista_inicializar(&productos);
    pila_inicializar(&historial);
    cola_inicializar(&turnos);

    lista_insertar_final(&productos, 101);
    lista_insertar_final(&productos, 205);
    lista_insertar_en_posicion(&productos, 150, 1);

    pila_apilar(&historial, 10);
    pila_apilar(&historial, 20);
    pila_apilar(&historial, 30);

    cola_encolar(&turnos, 1);
    cola_encolar(&turnos, 2);
    cola_encolar(&turnos, 3);

    printf("Lista de productos cargados: ");
    lista_imprimir(&productos);

    printf("Historial de acciones: ");
    pila_imprimir(&historial);
    pila_desapilar(&historial, &valor);
    printf("Se deshizo la accion %d\n", valor);

    printf("Turnos en espera: ");
    cola_imprimir(&turnos);
    cola_desencolar(&turnos, &valor);
    printf("Se atendio el turno %d\n", valor);

    printf("Estado final de productos: ");
    lista_imprimir(&productos);
    printf("Estado final del historial: ");
    pila_imprimir(&historial);
    printf("Estado final de turnos: ");
    cola_imprimir(&turnos);

    lista_destruir(&productos);
    pila_destruir(&historial);
    cola_destruir(&turnos);
    return 0;
}