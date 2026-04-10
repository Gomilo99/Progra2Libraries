#include "../include/ArbolBin.hpp"
#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <stdexcept>
#include <sstream>
#include <cstdlib>

using namespace std;

static vector<string> tokenizar(const string &linea);
static void cargarRecorrido(const string &linea, Lista<string> &inOrden, Lista<string> &otroRecorrido, bool &esPreOrden, vector<string> &integrantes);
static int profundidadNodo(const ArbolBin<string> &arbol, const string &nodo);
static int nodosIntermediosCamino(const ArbolBin<string>& arbol, const string& u, const string& v);
static int calcularMUPGrupo(const ArbolBin<string>& arbol, const vector<string>& integrantes, const vector<string>& prueba);

int main(){
    // t = cantidad de casos de prueba.
    int t;
    // Lee la cantidad de casos.
    cin >> t;
    // Limpia el salto pendiente para poder usar getline luego.
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Recorre todos los casos.
    for(int casos = 1; casos <= t; casos++){
        // n = cantidad de grupos (arboles) del caso actual.
        int n;
        cin >> n;
        // Limpia salto de linea despues de leer n.
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Guarda el indice del grupo con mayor MUP.
        int mejorGrupo = 1;
        // Guarda el valor maximo del MUP encontrado.
        int mejorMUP = -1;

        // Procesa cada grupo del caso.
        for(int grupos = 1; grupos <= n; grupos++){
            // inOrden: recorrido inorden del grupo.
            // otroRecorrido: preorden o postorden.
            Lista<string> inOrden, otroRecorrido;
            // Indica si otroRecorrido es preorden (true) o postorden (false).
            bool esPreOrden = true;
            // Guarda todos los integrantes del grupo (tomados del inorden).
            vector<string> integrantes;
            // Cada grupo trae 3 lineas: recorrido 1, recorrido 2, prueba.
            string linea1, linea2, lineaPrueba;

            // Lectura de las tres lineas del grupo.
            getline(cin, linea1);
            getline(cin, linea2);
            getline(cin, lineaPrueba);

            // Interpreta cada linea de recorrido y llena estructuras.
            cargarRecorrido(linea1, inOrden, otroRecorrido, esPreOrden, integrantes);
            cargarRecorrido(linea2, inOrden, otroRecorrido, esPreOrden, integrantes);

            // Reconstruye arbol desde inorden + (preorden o postorden).
            ArbolBin<string> arbol(inOrden, otroRecorrido, esPreOrden);
            // Tokeniza la linea de sujetos de prueba.
            vector<string> prueba = tokenizar(lineaPrueba);
            // Calcula la metrica para este grupo.
            int mupGrupo = calcularMUPGrupo(arbol, integrantes, prueba);

            // Actualiza mejor grupo si este supera el maximo anterior.
            if (mupGrupo > mejorMUP) {
                mejorMUP = mupGrupo;
                mejorGrupo = grupos;
            }
        }

        // Imprime el indice del grupo ganador del caso.
        cout << mejorGrupo;
        // Evita salto extra al final del archivo de salida.
        if (casos < t) {
            cout << "\n";
        }
    }
    // Finaliza programa.
    return 0;
}

static vector<string> tokenizar(const string &linea) {
    // Vector resultado con palabras separadas por espacios.
    vector<string> tokens;
    // Flujo para extraer token por token.
    istringstream iss(linea);
    string token;
    // Extrae palabras hasta agotar la linea.
    while (iss >> token) {
        tokens.push_back(token);
    }
    // Retorna lista de tokens.
    return tokens;
}

static void cargarRecorrido(const string &linea, Lista<string> &inOrden, Lista<string> &otroRecorrido, bool &esPreOrden, vector<string> &integrantes) {
    // Convierte la linea en tokens: [TIPO, nodo1, nodo2, ...].
    vector<string> tokens = tokenizar(linea);
    // Si no hay datos, la linea es invalida.
    if (tokens.empty()) {
        throw invalid_argument("Linea de recorrido vacia");
    }

    // El primer token define el tipo de recorrido.
    const string& tipoRecorrido = tokens[0];
    if (tipoRecorrido == "INORDEN") {
        // Desde posicion 1 vienen los nodos del inorden.
        for (int i = 1; i < (int)tokens.size(); ++i) {
            // Carga nodo en la lista inorden.
            inOrden.insertar(tokens[i], inOrden.getLong() + 1);
            // Tambien guarda integrantes para el calculo posterior.
            integrantes.push_back(tokens[i]);
        }
        return;
    }

    if (tipoRecorrido == "PREORDEN" || tipoRecorrido == "POSTORDEN") {
        // Desde posicion 1 vienen los nodos del otro recorrido.
        for (int i = 1; i < (int)tokens.size(); ++i) {
            otroRecorrido.insertar(tokens[i], otroRecorrido.getLong() + 1);
        }
        // Marca que tipo de recorrido secundario se recibio.
        esPreOrden = (tipoRecorrido == "PREORDEN");
        return;
    }

    // Si no es INORDEN/PREORDEN/POSTORDEN, la entrada no cumple formato.
    throw invalid_argument("Tipo de recorrido invalido");
}

static int profundidadNodo(const ArbolBin<string> &arbol, const string &nodo) {
    // Truco: profundidadLCA(x, x) devuelve la profundidad de x.
    return arbol.profundidadLCA(nodo, nodo);
}

static int nodosIntermediosCamino(const ArbolBin<string> &arbol, const string &u, const string &v) {
    // Profundidades de ambos nodos.
    int du = profundidadNodo(arbol, u);
    int dv = profundidadNodo(arbol, v);
    // Profundidad del ancestro comun mas cercano.
    int dlca = arbol.profundidadLCA(u, v);
    // Si no existe alguno, no hay camino valido.
    if (du == -1 || dv == -1 || dlca == -1) {
        return -1;
    }

    // Distancia en aristas entre u y v: du + dv - 2*dlca.
    int distanciaAristas = du + dv - 2 * dlca;
    // Nodos intermedios = aristas - 1 (sin contar extremos).
    return distanciaAristas - 1;
}

static int calcularMUPGrupo(const ArbolBin<string> &arbol, const vector<string> &integrantes, const vector<string> &prueba) {
    // Acumulador del MUP total del grupo.
    int sumaGrupo = 0;

    // Recorre cada sujeto de prueba.
    for (int i = 0; i < (int)prueba.size(); ++i) {
        const string& sujeto = prueba[i];
        // Nivel del sujeto dentro del arbol del grupo.
        int nivelSujeto = profundidadNodo(arbol, sujeto);
        // Si no pertenece al arbol, se ignora.
        if (nivelSujeto == -1) {
            continue;
        }

        // Compara sujeto contra todos los integrantes del grupo.
        for (int j = 0; j < (int)integrantes.size(); ++j) {
            const string& alumno = integrantes[j];
            // No se compara un nodo consigo mismo.
            if (sujeto == alumno) {
                continue;
            }

            // Nivel del alumno y nodos intermedios del camino sujeto-alumno.
            int nivelAlumno = profundidadNodo(arbol, alumno);
            int camino = nodosIntermediosCamino(arbol, sujeto, alumno);
            // Si no hay datos validos, se omite este par.
            if (nivelAlumno == -1 || camino < 0) {
                continue;
            }

            // Diferencia de niveles en valor absoluto.
            int dNivel = abs(nivelAlumno - nivelSujeto);
            // Aporte del par al MUP.
            sumaGrupo += camino * dNivel;
        }
    }

    // MUP total del grupo.
    return sumaGrupo;
}