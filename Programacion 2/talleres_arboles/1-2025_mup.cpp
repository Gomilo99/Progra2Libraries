#include "../include/ArbolBin.hpp"
#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <stdexcept>
#include <sstream>
#include <cstdlib>

using namespace std;

static vector<string> tokenizar(const string& linea) {
    vector<string> tokens;
    istringstream iss(linea);
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

static void cargarRecorrido(
    const string& linea,
    Lista<string>& inOrden,
    Lista<string>& otroRecorrido,
    bool& esPreOrden,
    vector<string>& integrantes) {
    vector<string> tokens = tokenizar(linea);
    if (tokens.empty()) {
        throw invalid_argument("Linea de recorrido vacia");
    }

    const string& tipoRecorrido = tokens[0];
    if (tipoRecorrido == "INORDEN") {
        for (int i = 1; i < (int)tokens.size(); ++i) {
            inOrden.insertar(tokens[i], inOrden.getLong() + 1);
            integrantes.push_back(tokens[i]);
        }
        return;
    }

    if (tipoRecorrido == "PREORDEN" || tipoRecorrido == "POSTORDEN") {
        for (int i = 1; i < (int)tokens.size(); ++i) {
            otroRecorrido.insertar(tokens[i], otroRecorrido.getLong() + 1);
        }
        esPreOrden = (tipoRecorrido == "PREORDEN");
        return;
    }

    throw invalid_argument("Tipo de recorrido invalido");
}

static int profundidadNodo(const ArbolBin<string>& arbol, const string& nodo) {
    return arbol.profundidadLCA(nodo, nodo);
}

static int nodosIntermediosCamino(const ArbolBin<string>& arbol, const string& u, const string& v) {
    int du = profundidadNodo(arbol, u);
    int dv = profundidadNodo(arbol, v);
    int dlca = arbol.profundidadLCA(u, v);
    if (du == -1 || dv == -1 || dlca == -1) {
        return -1;
    }

    int distanciaAristas = du + dv - 2 * dlca;
    return distanciaAristas - 1;
}

static int calcularMUPGrupo(
    const ArbolBin<string>& arbol,
    const vector<string>& integrantes,
    const vector<string>& prueba) {
    int sumaGrupo = 0;

    for (int i = 0; i < (int)prueba.size(); ++i) {
        const string& sujeto = prueba[i];
        int nivelSujeto = profundidadNodo(arbol, sujeto);
        if (nivelSujeto == -1) {
            continue;
        }

        for (int j = 0; j < (int)integrantes.size(); ++j) {
            const string& alumno = integrantes[j];
            if (sujeto == alumno) {
                continue;
            }

            int nivelAlumno = profundidadNodo(arbol, alumno);
            int camino = nodosIntermediosCamino(arbol, sujeto, alumno);
            if (nivelAlumno == -1 || camino < 0) {
                continue;
            }

            int dNivel = abs(nivelAlumno - nivelSujeto);
            sumaGrupo += camino * dNivel;
        }
    }

    return sumaGrupo;
}

int main(){
    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for(int casos = 1; casos <= t; casos++){
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int mejorGrupo = 1;
        int mejorMUP = -1;

        for(int grupos = 1; grupos <= n; grupos++){
            Lista<string> inOrden, otroRecorrido;
            bool esPreOrden = true;
            vector<string> integrantes;
            string linea1, linea2, lineaPrueba;

            getline(cin, linea1);
            getline(cin, linea2);
            getline(cin, lineaPrueba);

            cargarRecorrido(linea1, inOrden, otroRecorrido, esPreOrden, integrantes);
            cargarRecorrido(linea2, inOrden, otroRecorrido, esPreOrden, integrantes);

            ArbolBin<string> arbol(inOrden, otroRecorrido, esPreOrden);
            vector<string> prueba = tokenizar(lineaPrueba);
            int mupGrupo = calcularMUPGrupo(arbol, integrantes, prueba);

            if (mupGrupo > mejorMUP) {
                mejorMUP = mupGrupo;
                mejorGrupo = grupos;
            }
        }

        cout << mejorGrupo;
        if (casos < t) {
            cout << "\n";
        }
    }
    return 0;
}