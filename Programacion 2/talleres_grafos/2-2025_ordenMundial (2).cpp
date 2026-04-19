#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "../include/Grafos.hpp"
#include "../include/VisualizacionGrafos.hpp"

using namespace std;

// Prototipos
void construirIndiceAeropuertos(const Grafo<string>& redAerea,
                                map<string, int>& indiceDeAeropuerto,
                                vector<string>& aeropuertoPorIndice);

vector< vector<int> > construirVecinosPorIndice(const Grafo<string>& redAerea,
                                                const map<string, int>& indiceDeAeropuerto,
                                                const vector<string>& aeropuertoPorIndice);

bool esCompatibleConSeleccionActual(int aeropuerto,
                                    const vector< vector<int> >& vecinosPorIndice,
                                    const vector<bool>& seleccionadoActual);

void buscarConjuntoIndependienteMaximoRec(const vector< vector<int> >& vecinosPorIndice,
                                          int posicion,
                                          vector<bool>& seleccionadoActual,
                                          int tamanoActual,
                                          vector<bool>& mejorSeleccion,
                                          int& mejorTamano);

vector<int> calcularConjuntoIndependienteMaximo(const vector< vector<int> >& vecinosPorIndice);

void imprimirConjuntoIndependiente(const vector<int>& indices,
                                   const vector<string>& aeropuertoPorIndice,
                                   ostream& os);


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
        // Solo se procesa una linea no vacia y con formato valido (exactamente 2 tokens).
        if (!linea.empty()) {
            // stringstream permite partir la linea en tokens por espacios.
            stringstream ss(linea);
            string aeropuertoA;
            string aeropuertoB;

            // Si no se logran leer exactamente dos nombres, se descarta la linea.
            if (ss >> aeropuertoA >> aeropuertoB) {
                // Si hay basura extra en la linea (mas de dos tokens), tambien se descarta.
                string tokenExtra;
                if (!(ss >> tokenExtra)) {
                    // Paso 1: garantizar que ambos aeropuertos existan como vertices.
                    redAerea.insertarVertice(aeropuertoA);
                    redAerea.insertarVertice(aeropuertoB);

                    // Paso 2: agregar la conexion entre ambos.
                    // Como el grafo es no dirigido, internamente se agregan ambos sentidos.
                    redAerea.insertarArco(aeropuertoA, aeropuertoB);
                }
            }
        }
    }

    map<string, int> indiceDeAeropuerto;
    vector<string> aeropuertoPorIndice;
    construirIndiceAeropuertos(redAerea, indiceDeAeropuerto, aeropuertoPorIndice);

    vector< vector<int> > vecinosPorIndice = construirVecinosPorIndice(
        redAerea,
        indiceDeAeropuerto,
        aeropuertoPorIndice
    );
    vector<int> solucion = calcularConjuntoIndependienteMaximo(vecinosPorIndice);

    imprimirConjuntoIndependiente(solucion, aeropuertoPorIndice);

    // Visualizacion opcional para depuracion/local:
    // imprimirGrafoBonitoCLI(redAerea);
    // exportarGrafoASVG(redAerea, "talleres_grafos/grafos.svg", true, 1000, 700);
    
    return 0;
}


void construirIndiceAeropuertos(const Grafo<string>& redAerea,
                                map<string, int>& indiceDeAeropuerto,
                                vector<string>& aeropuertoPorIndice) {
    indiceDeAeropuerto.clear();
    aeropuertoPorIndice.clear();

    Lista<string> vertices = redAerea.getVertices();
    int indice = 0;

    while (!vertices.esVacia()) {
        string v = vertices.consultar(1);
        vertices.eliminar(1);
        indiceDeAeropuerto[v] = indice;
        aeropuertoPorIndice.push_back(v);
        ++indice;
    }
}

vector< vector<int> > construirVecinosPorIndice(const Grafo<string>& redAerea,
                                                const map<string, int>& indiceDeAeropuerto,
                                                const vector<string>& aeropuertoPorIndice) {
    int n = (int)aeropuertoPorIndice.size();
    vector< vector<int> > vecinosPorIndice(n, vector<int>());

    for (int i = 0; i < n; ++i) {
        const string& aeropuerto = aeropuertoPorIndice[i];
        Lista<string> vecinos = redAerea.getVecinos(aeropuerto);

        while (!vecinos.esVacia()) {
            string vecino = vecinos.consultar(1);
            vecinos.eliminar(1);

            map<string, int>::const_iterator it = indiceDeAeropuerto.find(vecino);
            if (it != indiceDeAeropuerto.end()) {
                vecinosPorIndice[i].push_back(it->second);
            }
        }
    }

    return vecinosPorIndice;
}

bool esCompatibleConSeleccionActual(int aeropuerto,
                                    const vector< vector<int> >& vecinosPorIndice,
                                    const vector<bool>& seleccionadoActual) {
    bool compatible = true;
    int k = 0;

    while (k < (int)vecinosPorIndice[aeropuerto].size() && compatible) {
        int vecino = vecinosPorIndice[aeropuerto][k];
        if (seleccionadoActual[vecino]) {
            compatible = false;
        }
        ++k;
    }

    return compatible;
}

void buscarConjuntoIndependienteMaximoRec(const vector< vector<int> >& vecinosPorIndice,
                                          int posicion,
                                          vector<bool>& seleccionadoActual,
                                          int tamanoActual,
                                          vector<bool>& mejorSeleccion,
                                          int& mejorTamano) {
    int n = (int)vecinosPorIndice.size();

    if (posicion == n) {
        if (tamanoActual > mejorTamano) {
            mejorTamano = tamanoActual;
            mejorSeleccion = seleccionadoActual;
        }
    } else {
        int cotaSuperior = tamanoActual + (n - posicion);
        if (cotaSuperior > mejorTamano) {
            // Rama 1: no tomar el aeropuerto actual.
            buscarConjuntoIndependienteMaximoRec(
                vecinosPorIndice,
                posicion + 1,
                seleccionadoActual,
                tamanoActual,
                mejorSeleccion,
                mejorTamano
            );

            // Rama 2: tomarlo solo si no tiene conflicto con los ya tomados.
            int aeropuerto = posicion;
            bool compatible = esCompatibleConSeleccionActual(
                aeropuerto,
                vecinosPorIndice,
                seleccionadoActual
            );

            if (compatible) {
                seleccionadoActual[aeropuerto] = true;
                buscarConjuntoIndependienteMaximoRec(
                    vecinosPorIndice,
                    posicion + 1,
                    seleccionadoActual,
                    tamanoActual + 1,
                    mejorSeleccion,
                    mejorTamano
                );
                seleccionadoActual[aeropuerto] = false;
            }
        }
    }
}

vector<int> calcularConjuntoIndependienteMaximo(const vector< vector<int> >& vecinosPorIndice) {
    int n = (int)vecinosPorIndice.size();
    vector<bool> seleccionadoActual(n, false);
    vector<bool> mejorSeleccion(n, false);
    int mejorTamano = 0;

    buscarConjuntoIndependienteMaximoRec(
        vecinosPorIndice,
        0,
        seleccionadoActual,
        0,
        mejorSeleccion,
        mejorTamano
    );

    vector<int> solucion;
    for (int i = 0; i < n; ++i) {
        if (mejorSeleccion[i]) {
            solucion.push_back(i);
        }
    }

    return solucion;
}

void imprimirConjuntoIndependiente(const vector<int>& indices,
                                   const vector<string>& aeropuertoPorIndice,
                                   ostream& os = cout) {
    os << "Tamano maximo: " << (int)indices.size() << "\n";
    os << "Conjunto independiente maximo: [";

    for (int i = 0; i < (int)indices.size(); ++i) {
        os << aeropuertoPorIndice[indices[i]];
        if (i + 1 < (int)indices.size()) {
            os << ", ";
        }
    }

    os << "]\n";
}