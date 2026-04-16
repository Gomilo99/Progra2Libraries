#include <iostream>
#include <string>
#include <sstream>
#include "../include/Grafos.hpp"

using namespace std;

/*
Plantilla inicial del taller 2-2025 (Orden Mundial).

Objetivo actual:
1) Leer conexiones de aeropuertos desde stdin.
2) Construir el grafo no dirigido.
3) Imprimir la lista de adyacencia para validar que la carga fue correcta.

Nota: aqui aun NO se resuelve el conjunto independiente maximo;
solo se deja la base lista para la siguiente fase del taller.
*/
int main() {
    // Se crea un grafo NO dirigido porque un vuelo directo A-B
    // representa conectividad mutua para este modelo base.
    Grafo<string> redAerea(false);

    // Cada linea deberia venir como: "AeropuertoA AeropuertoB"
    // y la lectura se mantiene hasta EOF.
    string linea;
    while (getline(cin, linea)) {
        // Si la linea viene vacia, se ignora y se pasa a la siguiente.
        if (linea.empty()) {
            continue;
        }

        // stringstream permite partir la linea en tokens por espacios.
        stringstream ss(linea);
        string aeropuertoA;
        string aeropuertoB;

        // Si no se logran leer exactamente dos nombres, se descarta la linea.
        if (!(ss >> aeropuertoA >> aeropuertoB)) {
            continue;
        }

        // Si hay basura extra en la linea (mas de dos tokens), tambien se descarta.
        string tokenExtra;
        if (ss >> tokenExtra) {
            continue;
        }

        // Paso 1: garantizar que ambos aeropuertos existan como vertices.
        redAerea.insertarVertice(aeropuertoA);
        redAerea.insertarVertice(aeropuertoB);

        // Paso 2: agregar la conexion entre ambos.
        // Como el grafo es no dirigido, internamente se agregan ambos sentidos.
        redAerea.insertarArco(aeropuertoA, aeropuertoB);
    }

    // Salida de depuracion: muestra como quedo construida la red.
    // En la fase de resolucion del problema, aqui se reemplazara por
    // la impresion del conjunto independiente maximo.
    redAerea.imprimirAdyacencia();

    return 0;
}
