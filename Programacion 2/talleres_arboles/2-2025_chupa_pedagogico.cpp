#include "../include/ArbolN.hpp"
#include <iostream>
#include <vector>
#include <limits>
#include <stdexcept>

using namespace std;

/*
Clase auxiliar solo para poder utilizar de plantilla para futuros ejercicios donde extender la clase sea más fácil que hacer los métodos con puros vainas de árboles, pa' ladilla.
*/
struct ConteoHojas {
    int pares;
    int impares;

    ConteoHojas() : pares(0), impares(0) {}
};

class ArbolNExtPedagogico {
private:
    static int msiDesdeNodo(const NodoN<int>* nodo, bool incluirPadre, const vector<int>& eficienciasLocales) {
        if (nodo == NULL) {
            return 0;
        }

        if (incluirPadre) {
            int suma = 0;
            const NodoN<int>* hijo = nodo->getHijoIzq();
            while (hijo != NULL) {
                suma += msiDesdeNodo(hijo, false, eficienciasLocales);
                hijo = hijo->getHnoDer();
            }
            return suma;
        }

        int idNodo = nodo->getInfo();
        if (idNodo <= 0 || idNodo > (int)eficienciasLocales.size()) {
            throw out_of_range("ID de nodo fuera de rango para eficienciasLocales");
        }

        int sumaIncluye = eficienciasLocales[idNodo - 1];
        int sumaExcluye = 0;

        const NodoN<int>* hijo = nodo->getHijoIzq();
        while (hijo != NULL) {
            sumaIncluye += msiDesdeNodo(hijo, true, eficienciasLocales);
            sumaExcluye += msiDesdeNodo(hijo, false, eficienciasLocales);
            hijo = hijo->getHnoDer();
        }

        return (sumaIncluye > sumaExcluye) ? sumaIncluye : sumaExcluye;
    }

    static void contarHojasPorNivelDesdeNodo(const NodoN<int>* nodo, int nivel, ConteoHojas& conteo) {
        if (nodo == NULL) {
            return;
        }

        if (nodo->getHijoIzq() == NULL) {
            if (nivel % 2 == 0) {
                conteo.pares += 1;
            } else {
                conteo.impares += 1;
            }
            return;
        }

        const NodoN<int>* hijo = nodo->getHijoIzq();
        while (hijo != NULL) {
            contarHojasPorNivelDesdeNodo(hijo, nivel + 1, conteo);
            hijo = hijo->getHnoDer();
        }
    }

    static void validarIdsDesdeNodo(const NodoN<int>* nodo, int cantidadNodos) {
        if (nodo == NULL) {
            return;
        }

        int id = nodo->getInfo();
        if (id <= 0 || id > cantidadNodos) {
            throw out_of_range("Hay un ID en el arbol fuera del rango 1..N");
        }

        const NodoN<int>* hijo = nodo->getHijoIzq();
        while (hijo != NULL) {
            validarIdsDesdeNodo(hijo, cantidadNodos);
            hijo = hijo->getHnoDer();
        }
    }

public:
    static void validarIds(const ArbolN<int>& arbol, int cantidadNodos) {
        if (arbol.esNulo()) {
            return;
        }

        const NodoN<int>* raiz = arbol.buscarNodo(arbol.getRaiz());
        validarIdsDesdeNodo(raiz, cantidadNodos);
    }

    static int sumaConjuntoIndependiente(const ArbolN<int>& arbol, const vector<int>& eficienciasLocales) {
        if (arbol.esNulo()) {
            return 0;
        }

        const NodoN<int>* raiz = arbol.buscarNodo(arbol.getRaiz());
        return msiDesdeNodo(raiz, false, eficienciasLocales);
    }

    static int balanceHojas(const ArbolN<int>& arbol) {
        if (arbol.esNulo()) {
            return 0;
        }

        const NodoN<int>* raiz = arbol.buscarNodo(arbol.getRaiz());
        ConteoHojas conteo;
        contarHojasPorNivelDesdeNodo(raiz, 0, conteo);

        return conteo.pares - conteo.impares;
    }
};

int main() {
    int t;
    cin >> t;

    for (int caso = 1; caso <= t; ++caso) {
        int cantidadNodos;
        cin >> cantidadNodos;

        vector<int> eficienciasLocales(cantidadNodos);
        for (int i = 0; i < cantidadNodos; ++i) {
            cin >> eficienciasLocales[i];
        }

        ArbolN<int> arbol;
        for (int i = 0; i < cantidadNodos - 1; ++i) {
            int padre, hijo;
            cin >> padre >> hijo;

            if (i == 0) {
                arbol.insertarNodo(0, padre);
                arbol.insertarNodo(padre, hijo);
            } else {
                arbol.insertarNodo(padre, hijo);
            }
        }

        ArbolNExtPedagogico::validarIds(arbol, cantidadNodos);

        int msi = ArbolNExtPedagogico::sumaConjuntoIndependiente(arbol, eficienciasLocales);
        int balance = ArbolNExtPedagogico::balanceHojas(arbol);
        int chupa = msi * balance;

        cout << chupa;
        if (caso < t) {
            cout << "\n";
        }
    }

    return 0;
}
