#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct EstadoDFS {
    int nodo;
    long acumuladaHastaPadre;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    for (int caso = 1; caso <= t; ++caso) {
        int cantidadNodos;
        cin >> cantidadNodos;

        vector<int> valoresEstabilidad(cantidadNodos + 1, 0);
        for (int i = 1; i <= cantidadNodos; ++i) {
            cin >> valoresEstabilidad[i];
        }

        vector<vector<int> > hijos(cantidadNodos + 1);
        for (int i = 0; i < cantidadNodos - 1; ++i) {
            int padre, hijo;
            cin >> padre >> hijo;
            hijos[padre].push_back(hijo);
        }

        int posicionesAlcanzables = 0;
        if (cantidadNodos > 0) {
            stack<EstadoDFS> pila;
            EstadoDFS raiz;
            raiz.nodo = 1;
            raiz.acumuladaHastaPadre = 0;
            pila.push(raiz);

            while (!pila.empty()) {
                EstadoDFS actual = pila.top();
                pila.pop();

                long acumuladaActual = actual.acumuladaHastaPadre + valoresEstabilidad[actual.nodo];
                if (acumuladaActual >= 0) {
                    ++posicionesAlcanzables;

                    for (size_t i = 0; i < hijos[actual.nodo].size(); ++i) {
                        EstadoDFS sig;
                        sig.nodo = hijos[actual.nodo][i];
                        sig.acumuladaHastaPadre = acumuladaActual;
                        pila.push(sig);
                    }
                }
            }
        }

        if (caso > 1) {
            cout << '\n';
        }
        cout << posicionesAlcanzables;
    }

    return 0;
}