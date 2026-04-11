#include "../include/ArbolN.hpp"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <utility>

using namespace std;

void esOpeAlcanzable(const ArbolN<int>& arbol, int posicionV, const vector<int>& valoresEstabilidad, vector<int>& alcanzables);

int main() {
    int t;
    cin >> t;

    for (int caso = 1; caso <= t; ++caso) {
        int cantidadNodos;
        cin >> cantidadNodos;

        vector<int> valoresEstabilidad(cantidadNodos, 0);
        for (int i = 0; i < cantidadNodos; ++i) {
            cin >> valoresEstabilidad[i];
        }

        vector<pair<int, int> > aristas;
        /*
        La función reserve aumenta la capacidad del vector para que pueda contener al menos __n elementos. Si __n es mayor que la capacidad actual, la función asigna nueva memoria, reubica o copia los elementos existentes al nuevo espacio y libera el almacenamiento anterior.
        */
        aristas.reserve(cantidadNodos > 0 ? cantidadNodos - 1 : 0);
        for (int i = 0; i < cantidadNodos - 1; ++i) {
            int padre, hijo;
            cin >> padre >> hijo;
            aristas.push_back(make_pair(padre, hijo));
        }

        ArbolN<int> arbol;
        if (cantidadNodos > 0) {
            arbol.insertarNodo(0, 1);
        }

        // Insercion robusta sin exigir que las aristas lleguen ordenadas por padre.
        vector<int> insertada(aristas.size(), 0);
        int totalInsertadas = 0;
        bool huboAvance = true;

        while (huboAvance && totalInsertadas < (int)aristas.size()) {
            huboAvance = false;
            for (size_t i = 0; i < aristas.size(); ++i) {
                if (insertada[i] == 0) {
                    int padre = aristas[i].first;
                    int hijo = aristas[i].second;
                    if (arbol.buscarNodo(padre) != NULL) {
                        arbol.insertarNodo(padre, hijo);
                        insertada[i] = 1;
                        ++totalInsertadas;
                        huboAvance = true;
                    }
                }
            }
        }

        if (totalInsertadas != (int)aristas.size()) {
            throw runtime_error("No fue posible construir el arbol con las aristas dadas");
        }

        vector<int> alcanzables(cantidadNodos, 0);
        Lista<int> recorrido = arbol.preOrden();

        while (!recorrido.esVacia()) {
            int posicionV = recorrido.consultar(1);
            if (posicionV >= 1 && posicionV <= cantidadNodos && alcanzables[posicionV - 1] == 0) {
                esOpeAlcanzable(arbol, posicionV, valoresEstabilidad, alcanzables);
            }
            recorrido.eliminar(1);
        }

        int posicionesAlcanzables = 0;
        for (int i = 0; i < cantidadNodos; ++i) {
            if (alcanzables[i] == 1) {
                ++posicionesAlcanzables;
            }
        }

        if (caso > 1) {
            cout << '\n';
        }
        cout << posicionesAlcanzables;
    }

    return 0;
}

void esOpeAlcanzable(const ArbolN<int>& arbol, int posicionV, const vector<int>& valoresEstabilidad, vector<int>& alcanzables) {
    Lista<int> camino = arbol.camino(arbol.getRaiz(), posicionV);
    int estabilidadAcumulada = 0;

    while (!camino.esVacia() && estabilidadAcumulada >= 0) {
        int idNodo = camino.consultar(1);
        if (idNodo <= 0 || idNodo > (int)valoresEstabilidad.size()) {
            throw out_of_range("ID de nodo fuera de rango para valoresEstabilidad");
        }

        estabilidadAcumulada += valoresEstabilidad[idNodo - 1];
        if (estabilidadAcumulada >= 0) {
            alcanzables[idNodo - 1] = 1;
        }
        camino.eliminar(1);
    }

    while (!camino.esVacia()) {
        int idNodo = camino.consultar(1);
        if (idNodo <= 0 || idNodo > (int)valoresEstabilidad.size()) {
            throw out_of_range("ID de nodo fuera de rango para valoresEstabilidad");
        }

        alcanzables[idNodo - 1] = -1;
        camino.eliminar(1);
    }
}