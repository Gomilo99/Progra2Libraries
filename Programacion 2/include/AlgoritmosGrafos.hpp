#ifndef ALGORITMOS_GRAFOS_HPP
#define ALGORITMOS_GRAFOS_HPP

#include <map>
#include <vector>
#include <limits>
#include <utility>
#include <stdexcept>
#include "Grafos.hpp"
#include "Cola.hpp"
#include "Pila.hpp"

using namespace std;

/**
 * @brief Construye un mapeo vertice -> indice [0..n-1] para un grafo.
 *
 * Requiere que T sea comparable con operator< para usar map.
 */
template <typename T>
map<T, int> construirMapaIndices(const Grafo<T>& g) {
    map<T, int> idDe;
    Lista<T> vertices = g.getVertices();

    int indice = 0;
    while (!vertices.esVacia()) {
        T v = vertices.consultar(1);
        vertices.eliminar(1);
        idDe[v] = indice;
        ++indice;
    }

    return idDe;
}

/**
 * @brief Busca el indice de un vertice en el mapa.
 * @throw invalid_argument Si el vertice no existe en el mapeo.
 */
template <typename T>
int indiceDe(const map<T, int>& idDe, const T& v) {
    typename map<T, int>::const_iterator it = idDe.find(v);
    if (it == idDe.end()) {
        throw invalid_argument("Vertice no existe en el mapeo");
    }
    return it->second;
}

/**
 * @brief Verifica existencia de arista en matriz de adyacencia (0-based).
 * @throw invalid_argument Si u o v estan fuera de rango.
 */
inline bool existeAristaMatriz(const vector< vector<int> >& matriz, int u, int v) {
    if (u < 0 || v < 0 || u >= (int)matriz.size() || v >= (int)matriz.size()) {
        throw invalid_argument("Indice fuera de rango en existeAristaMatriz");
    }
    return matriz[u][v] != 0;
}

/**
 * @brief Construye adyacencia desde aristas (0-based).
 *
 * Si dirigido=false agrega ambos sentidos.
 */
inline vector< vector<int> > construirGrafoListaAdyacencia(int n,
                                                           const vector< pair<int, int> >& aristas,
                                                           bool dirigido = false) {
    if (n < 0) {
        throw invalid_argument("n no puede ser negativo");
    }

    vector< vector<int> > ady(n);
    for (int i = 0; i < (int)aristas.size(); ++i) {
        int u = aristas[i].first;
        int v = aristas[i].second;
        if (u < 0 || v < 0 || u >= n || v >= n) {
            throw invalid_argument("Arista fuera de rango en construirGrafoListaAdyacencia");
        }

        ady[u].push_back(v);
        if (!dirigido && u != v) {
            ady[v].push_back(u);
        }
    }

    return ady;
}

/**
 * @brief Grado en adyacencia indexada (0-based). O(grado(v)).
 */
inline int gradoNodoAdyacencia(const vector< vector<int> >& ady, int v) {
    if (v < 0 || v >= (int)ady.size()) {
        throw invalid_argument("Indice fuera de rango en gradoNodoAdyacencia");
    }
    return (int)ady[v].size();
}

template <typename T>
void dfsRecMapeado(const Grafo<T>& g,
                   const T& v,
                   const map<T, int>& idDe,
                   vector<bool>& visitado,
                   Lista<T>& recorrido) {
    int idxV = indiceDe(idDe, v);
    visitado[idxV] = true;
    recorrido.insertar(v, recorrido.getLong() + 1);

    Lista<T> vecinos = g.getVecinos(v);
    while (!vecinos.esVacia()) {
        T w = vecinos.consultar(1);
        vecinos.eliminar(1);

        int idxW = indiceDe(idDe, w);
        if (!visitado[idxW]) {
            dfsRecMapeado(g, w, idDe, visitado, recorrido);
        }
    }
}

/**
 * @brief BFS desde un inicio usando mapeo + vector de visitados.
 * @throw invalid_argument si inicio no existe.
 */
template <typename T>
Lista<T> bfsMapeado(const Grafo<T>& g, const T& inicio) {
    Lista<T> recorrido;
    if (g.esVacio()) {
        return recorrido;
    }

    map<T, int> idDe = construirMapaIndices(g);

    typename map<T, int>::const_iterator itInicio = idDe.find(inicio);
    if (itInicio == idDe.end()) {
        throw invalid_argument("Vertice inicial no existe en bfsMapeado");
    }

    vector<bool> visitado(g.getNNodos(), false);
    Cola<T> colaAux;

    colaAux.encolar(inicio);
    visitado[itInicio->second] = true;

    while (!colaAux.esVacia()) {
        T v = colaAux.getFrente();
        Lista<T> vecinos = g.getVecinos(v);

        while (!vecinos.esVacia()) {
            T w = vecinos.consultar(1);
            vecinos.eliminar(1);
            int idxW = indiceDe(idDe, w);

            if (!visitado[idxW]) {
                colaAux.encolar(w);
                visitado[idxW] = true;
            }
        }

        recorrido.insertar(v, recorrido.getLong() + 1);
        colaAux.desencolar();
    }

    return recorrido;
}

/**
 * @brief BFS por componentes en todo el grafo.
 */
template <typename T>
Lista<T> bfsMapeado(const Grafo<T>& g) {
    Lista<T> recorrido;
    if (g.esVacio()) {
        return recorrido;
    }

    map<T, int> idDe = construirMapaIndices(g);
    vector<bool> visitado(g.getNNodos(), false);
    Lista<T> vertices = g.getVertices();

    while (!vertices.esVacia()) {
        T s = vertices.consultar(1);
        vertices.eliminar(1);
        int idxS = indiceDe(idDe, s);

        if (!visitado[idxS]) {
            Cola<T> colaAux;
            visitado[idxS] = true;
            colaAux.encolar(s);

            while (!colaAux.esVacia()) {
                T v = colaAux.getFrente();
                Lista<T> vecinos = g.getVecinos(v);

                while (!vecinos.esVacia()) {
                    T w = vecinos.consultar(1);
                    vecinos.eliminar(1);
                    int idxW = indiceDe(idDe, w);

                    if (!visitado[idxW]) {
                        visitado[idxW] = true;
                        colaAux.encolar(w);
                    }
                }

                recorrido.insertar(v, recorrido.getLong() + 1);
                colaAux.desencolar();
            }
        }
    }

    return recorrido;
}

/**
 * @brief DFS desde un inicio usando mapeo + vector de visitados.
 * @throw invalid_argument si inicio no existe.
 */
template <typename T>
Lista<T> dfsMapeado(const Grafo<T>& g, const T& inicio) {
    Lista<T> recorrido;
    if (g.esVacio()) {
        return recorrido;
    }

    map<T, int> idDe = construirMapaIndices(g);
    typename map<T, int>::const_iterator itInicio = idDe.find(inicio);
    if (itInicio == idDe.end()) {
        throw invalid_argument("Vertice inicial no existe en dfsMapeado");
    }

    vector<bool> visitado(g.getNNodos(), false);
    dfsRecMapeado(g, inicio, idDe, visitado, recorrido);
    return recorrido;
}

/**
 * @brief DFS por componentes en todo el grafo.
 */
template <typename T>
Lista<T> dfsMapeado(const Grafo<T>& g) {
    Lista<T> recorrido;
    if (g.esVacio()) {
        return recorrido;
    }

    map<T, int> idDe = construirMapaIndices(g);
    vector<bool> visitado(g.getNNodos(), false);
    Lista<T> vertices = g.getVertices();

    while (!vertices.esVacia()) {
        T v = vertices.consultar(1);
        vertices.eliminar(1);
        int idxV = indiceDe(idDe, v);

        if (!visitado[idxV]) {
            dfsRecMapeado(g, v, idDe, visitado, recorrido);
        }
    }

    return recorrido;
}

/**
 * @brief DFS iterativo desde un inicio usando pila.
 */
template <typename T>
Lista<T> dfsIterativoMapeado(const Grafo<T>& g, const T& inicio) {
    Lista<T> recorrido;
    if (g.esVacio()) {
        return recorrido;
    }

    map<T, int> idDe = construirMapaIndices(g);

    if (idDe.find(inicio) == idDe.end()) {
        throw invalid_argument("Vertice inicial no existe en dfsIterativoMapeado");
    }

    vector<bool> visitado(g.getNNodos(), false);
    Pila<T> pilaAux;
    pilaAux.apilar(inicio);

    while (!pilaAux.esVacia()) {
        T v = pilaAux.getTope();
        pilaAux.desapilar();
        int idxV = indiceDe(idDe, v);

        if (!visitado[idxV]) {
            visitado[idxV] = true;
            recorrido.insertar(v, recorrido.getLong() + 1);

            Lista<T> vecinos = g.getVecinos(v);
            vector<T> buffer;
            while (!vecinos.esVacia()) {
                buffer.push_back(vecinos.consultar(1));
                vecinos.eliminar(1);
            }

            for (int i = (int)buffer.size() - 1; i >= 0; --i) {
                int idxW = indiceDe(idDe, buffer[i]);
                if (!visitado[idxW]) {
                    pilaAux.apilar(buffer[i]);
                }
            }
        }
    }

    return recorrido;
}

/**
 * @brief DFS iterativo por componentes en todo el grafo.
 */
template <typename T>
Lista<T> dfsIterativoMapeado(const Grafo<T>& g) {
    Lista<T> recorrido;
    if (g.esVacio()) {
        return recorrido;
    }

    map<T, int> idDe = construirMapaIndices(g);

    vector<bool> visitado(g.getNNodos(), false);
    Lista<T> vertices = g.getVertices();

    while (!vertices.esVacia()) {
        T inicio = vertices.consultar(1);
        vertices.eliminar(1);
        int idxInicio = indiceDe(idDe, inicio);

        if (!visitado[idxInicio]) {
            Pila<T> pilaAux;
            pilaAux.apilar(inicio);

            while (!pilaAux.esVacia()) {
                T v = pilaAux.getTope();
                pilaAux.desapilar();
                int idxV = indiceDe(idDe, v);

                if (!visitado[idxV]) {
                    visitado[idxV] = true;
                    recorrido.insertar(v, recorrido.getLong() + 1);

                    Lista<T> vecinos = g.getVecinos(v);
                    vector<T> buffer;
                    while (!vecinos.esVacia()) {
                        buffer.push_back(vecinos.consultar(1));
                        vecinos.eliminar(1);
                    }

                    for (int i = (int)buffer.size() - 1; i >= 0; --i) {
                        int idxW = indiceDe(idDe, buffer[i]);
                        if (!visitado[idxW]) {
                            pilaAux.apilar(buffer[i]);
                        }
                    }
                }
            }
        }
    }

    return recorrido;
}

/**
 * @brief Cantidad de componentes conexas usando DFS.
 */
template <typename T>
int getNComponentesConexasMapeado(const Grafo<T>& g) {
    if (g.esVacio()) {
        return 0;
    }

    map<T, int> idDe = construirMapaIndices(g);

    vector<bool> visitado(g.getNNodos(), false);
    Lista<T> vertices = g.getVertices();
    int componentes = 0;

    while (!vertices.esVacia()) {
        T v = vertices.consultar(1);
        vertices.eliminar(1);
        int idxV = indiceDe(idDe, v);

        if (!visitado[idxV]) {
            Lista<T> dummy;
            dfsRecMapeado(g, v, idDe, visitado, dummy);
            ++componentes;
        }
    }

    return componentes;
}

template <typename T>
bool dfsCicloNoDirigidoRec(const Grafo<T>& g,
                           const T& v,
                           int padre,
                           const map<T, int>& idDe,
                           vector<bool>& visitado) {
    int idxV = indiceDe(idDe, v);
    visitado[idxV] = true;

    Lista<T> vecinos = g.getVecinos(v);
    while (!vecinos.esVacia()) {
        T w = vecinos.consultar(1);
        vecinos.eliminar(1);
        int idxW = indiceDe(idDe, w);

        if (!visitado[idxW]) {
            if (dfsCicloNoDirigidoRec(g, w, idxV, idDe, visitado)) {
                return true;
            }
        } else if (idxW != padre) {
            return true;
        }
    }

    return false;
}

/**
 * @brief Detecta ciclo en grafo no dirigido usando DFS.
 */
template <typename T>
bool tieneCicloNoDirigidoMapeado(const Grafo<T>& g) {
    if (g.esVacio()) {
        return false;
    }

    map<T, int> idDe = construirMapaIndices(g);

    vector<bool> visitado(g.getNNodos(), false);
    Lista<T> vertices = g.getVertices();

    while (!vertices.esVacia()) {
        T v = vertices.consultar(1);
        vertices.eliminar(1);
        int idx = indiceDe(idDe, v);
        if (!visitado[idx]) {
            if (dfsCicloNoDirigidoRec(g, v, -1, idDe, visitado)) {
                return true;
            }
        }
    }

    return false;
}

template <typename T>
bool dfsCicloDirigidoRec(const Grafo<T>& g,
                         const T& v,
                         const map<T, int>& idDe,
                         vector<int>& estado) {
    int idxV = indiceDe(idDe, v);
    estado[idxV] = 1;

    Lista<T> sucesores = g.getSucesores(v);
    while (!sucesores.esVacia()) {
        T w = sucesores.consultar(1);
        sucesores.eliminar(1);
        int idxW = indiceDe(idDe, w);

        if (estado[idxW] == 1) {
            return true;
        }
        if (estado[idxW] == 0 && dfsCicloDirigidoRec(g, w, idDe, estado)) {
            return true;
        }
    }

    estado[idxV] = 2;
    return false;
}

/**
 * @brief Detecta ciclo en grafo dirigido usando DFS de estados.
 */
template <typename T>
bool tieneCicloDirigidoMapeado(const Grafo<T>& g) {
    if (!g.getEsDirigido()) {
        throw invalid_argument("tieneCicloDirigidoMapeado requiere grafo dirigido");
    }

    map<T, int> idDe = construirMapaIndices(g);

    vector<int> estado(g.getNNodos(), 0);
    Lista<T> vertices = g.getVertices();
    while (!vertices.esVacia()) {
        T v = vertices.consultar(1);
        vertices.eliminar(1);
        int idx = indiceDe(idDe, v);
        if (estado[idx] == 0) {
            if (dfsCicloDirigidoRec(g, v, idDe, estado)) {
                return true;
            }
        }
    }

    return false;
}

/**
 * @brief Verifica si un grafo es bipartito (soporta desconexos).
 */
template <typename T>
bool esBipartitoMapeado(const Grafo<T>& g) {
    if (g.esVacio()) {
        return true;
    }

    map<T, int> idDe = construirMapaIndices(g);

    vector<int> color(g.getNNodos(), -1);
    Lista<T> vertices = g.getVertices();

    while (!vertices.esVacia()) {
        T inicio = vertices.consultar(1);
        vertices.eliminar(1);
        int idxInicio = indiceDe(idDe, inicio);

        if (color[idxInicio] == -1) {
            Cola<T> colaAux;
            colaAux.encolar(inicio);
            color[idxInicio] = 0;

            while (!colaAux.esVacia()) {
                T v = colaAux.getFrente();
                colaAux.desencolar();
                int idxV = indiceDe(idDe, v);

                Lista<T> vecinos = g.getVecinos(v);
                while (!vecinos.esVacia()) {
                    T w = vecinos.consultar(1);
                    vecinos.eliminar(1);
                    int idxW = indiceDe(idDe, w);

                    if (color[idxW] == -1) {
                        color[idxW] = 1 - color[idxV];
                        colaAux.encolar(w);
                    } else if (color[idxW] == color[idxV]) {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

/**
 * @brief Orden topologico por Kahn (BFS de grados de entrada).
 * @throw invalid_argument Si el grafo no es dirigido.
 * @throw logic_error Si el grafo dirigido tiene ciclo.
 */
template <typename T>
Lista<T> ordenarTopologicoMapeado(const Grafo<T>& g) {
    if (!g.getEsDirigido()) {
        throw invalid_argument("ordenarTopologicoMapeado requiere grafo dirigido");
    }

    Lista<T> result;
    if (g.esVacio()) {
        return result;
    }

    map<T, int> idDe = construirMapaIndices(g);

    vector<int> gradoEntrada(g.getNNodos(), 0);
    Lista<T> vertices = g.getVertices();

    while (!vertices.esVacia()) {
        T v = vertices.consultar(1);
        vertices.eliminar(1);

        Lista<T> sucesores = g.getSucesores(v);
        while (!sucesores.esVacia()) {
            T w = sucesores.consultar(1);
            sucesores.eliminar(1);
            int idxW = indiceDe(idDe, w);
            gradoEntrada[idxW] = gradoEntrada[idxW] + 1;
        }
    }

    Cola<T> colaAux;
    vertices = g.getVertices();
    while (!vertices.esVacia()) {
        T v = vertices.consultar(1);
        vertices.eliminar(1);
        int idxV = indiceDe(idDe, v);
        if (gradoEntrada[idxV] == 0) {
            colaAux.encolar(v);
        }
    }

    int procesados = 0;
    while (!colaAux.esVacia()) {
        T v = colaAux.getFrente();
        colaAux.desencolar();
        result.insertar(v, result.getLong() + 1);
        ++procesados;

        Lista<T> sucesores = g.getSucesores(v);
        while (!sucesores.esVacia()) {
            T w = sucesores.consultar(1);
            sucesores.eliminar(1);
            int idxW = indiceDe(idDe, w);
            gradoEntrada[idxW] = gradoEntrada[idxW] - 1;
            if (gradoEntrada[idxW] == 0) {
                colaAux.encolar(w);
            }
        }
    }

    if (procesados != g.getNNodos()) {
        throw logic_error("El grafo dirigido tiene ciclo; no existe orden topologico");
    }

    return result;
}

/**
 * @brief BFS que llena padres sobre mapeo por indices.
 */
template <typename T>
bool bfsConPadresMapeado(const Grafo<T>& g,
                         const T& origen,
                         const T& destino,
                         const map<T, int>& idDe,
                         vector<int>& padres) {
    int n = (int)idDe.size();
    padres.assign(n, -1);

    vector<bool> visitado(n, false);
    Cola<T> colaAux;

    int idxOrigen = indiceDe(idDe, origen);
    int idxDestino = indiceDe(idDe, destino);

    visitado[idxOrigen] = true;
    colaAux.encolar(origen);

    while (!colaAux.esVacia()) {
        T a = colaAux.getFrente();
        colaAux.desencolar();
        int idxA = indiceDe(idDe, a);

        if (idxA == idxDestino) {
            return true;
        }

        Lista<T> vecinos = g.getVecinos(a);
        while (!vecinos.esVacia()) {
            T b = vecinos.consultar(1);
            vecinos.eliminar(1);
            int idxB = indiceDe(idDe, b);

            if (!visitado[idxB]) {
                visitado[idxB] = true;
                padres[idxB] = idxA;
                colaAux.encolar(b);
            }
        }
    }

    return visitado[idxDestino];
}

/**
 * @brief Reconstruye camino (origen -> destino) a partir de vector de padres.
 */
template <typename T>
Lista<T> reconstruirCaminoMapeado(const T& origen,
                                  const T& destino,
                                  const map<T, int>& idDe,
                                  const vector<int>& padres) {
    Lista<T> camino;

    int idxOrigen = indiceDe(idDe, origen);
    int idxDestino = indiceDe(idDe, destino);
    vector<int> indicesInvertidos;
    int actual = idxDestino;

    while (actual != -1 && actual != idxOrigen) {
        indicesInvertidos.push_back(actual);
        actual = padres[actual];
    }

    if (actual == -1) {
        return camino;
    }

    indicesInvertidos.push_back(idxOrigen);

    map<int, T> verticePorIndice;
    typename map<T, int>::const_iterator itMap = idDe.begin();
    while (itMap != idDe.end()) {
        verticePorIndice[itMap->second] = itMap->first;
        ++itMap;
    }

    for (int i = (int)indicesInvertidos.size() - 1; i >= 0; --i) {
        camino.insertar(verticePorIndice[indicesInvertidos[i]], camino.getLong() + 1);
    }

    return camino;
}

/**
 * @brief Camino mas corto en arcos de v a w pasando por intermedio.
 */
template <typename T>
Lista<T> getCaminoMasCortoArcosConIntermedioMapeado(const Grafo<T>& g,
                                                    const T& v,
                                                    const T& w,
                                                    const T& intermedio) {
    Lista<T> result;
    if (g.esVacio()) {
        return result;
    }

    map<T, int> idDe = construirMapaIndices(g);

    if (idDe.find(v) == idDe.end() || idDe.find(w) == idDe.end() || idDe.find(intermedio) == idDe.end()) {
        return result;
    }

    vector<int> padres1;
    vector<int> padres2;

    bool ok1 = bfsConPadresMapeado(g, v, intermedio, idDe, padres1);
    bool ok2 = bfsConPadresMapeado(g, intermedio, w, idDe, padres2);

    if (!ok1 || !ok2) {
        return result;
    }

    Lista<T> camino1 = reconstruirCaminoMapeado(v, intermedio, idDe, padres1);
    Lista<T> camino2 = reconstruirCaminoMapeado(intermedio, w, idDe, padres2);

    result = camino1;
    if (!camino2.esVacia()) {
        camino2.eliminar(1);
    }

    while (!camino2.esVacia()) {
        T vertice = camino2.consultar(1);
        camino2.eliminar(1);
        result.insertar(vertice, result.getLong() + 1);
    }

    return result;
}

/**
 * @brief Camino mas corto en cantidad de arcos de origen a destino.
 */
template <typename T>
Lista<T> getCaminoMasCortoArcosMapeado(const Grafo<T>& g,
                                       const T& origen,
                                       const T& destino) {
    Lista<T> result;
    if (g.esVacio()) {
        return result;
    }

    map<T, int> idDe = construirMapaIndices(g);

    if (idDe.find(origen) == idDe.end() || idDe.find(destino) == idDe.end()) {
        return result;
    }

    vector<int> padres;
    bool ok = bfsConPadresMapeado(g, origen, destino, idDe, padres);
    if (!ok) {
        return result;
    }

    return reconstruirCaminoMapeado(origen, destino, idDe, padres);
}

/**
 * @brief Extrae de la cola el indice con menor distancia.
 */
template <typename T>
T extraerMinSegunDist(Cola<T>& colaAux,
                      const map<T, int>& idDe,
                      const vector<float>& distancias) {
    int tamCola = colaAux.getLong();
    T v = colaAux.getFrente();
    float distMinima = numeric_limits<float>::infinity();

    for (int i = 0; i < tamCola; ++i) {
        T actual = colaAux.getFrente();
        colaAux.desencolar();
        int idxActual = indiceDe(idDe, actual);

        if (distancias[idxActual] < distMinima) {
            v = actual;
            distMinima = distancias[idxActual];
        }

        colaAux.encolar(actual);
    }

    bool eliminado = false;
    for (int i = 0; i < tamCola; ++i) {
        T actual = colaAux.getFrente();
        colaAux.desencolar();

        if (actual == v && !eliminado) {
            eliminado = true;
        } else {
            colaAux.encolar(actual);
        }
    }

    return v;
}

/**
 * @brief Dijkstra usando cola + extraccion por minima distancia.
 *
 * Retorna distancias por indice mapeado [0..n-1].
 */
template <typename T>
vector<float> dijkstraMapeado(const Grafo<T>& g, const T& origen) {
    if (g.esVacio()) {
        return vector<float>();
    }

    map<T, int> idDe = construirMapaIndices(g);

    typename map<T, int>::const_iterator itOrigen = idDe.find(origen);
    if (itOrigen == idDe.end()) {
        throw invalid_argument("Vertice origen no existe en dijkstraMapeado");
    }

    int n = g.getNNodos();
    vector<float> distancias(n, numeric_limits<float>::infinity());
    vector<bool> visitados(n, false);

    Cola<T> colaAux;
    int idxOrigen = itOrigen->second;
    distancias[idxOrigen] = 0.0f;
    colaAux.encolar(origen);

    while (!colaAux.esVacia()) {
        T v = extraerMinSegunDist(colaAux, idDe, distancias);
        int idxV = indiceDe(idDe, v);

        if (!visitados[idxV]) {
            visitados[idxV] = true;
            Lista<T> vecinos = g.getVecinos(v);

            while (!vecinos.esVacia()) {
                T w = vecinos.consultar(1);
                vecinos.eliminar(1);
                int idxW = indiceDe(idDe, w);
                float peso = g.getPesoArco(v, w);

                if ((distancias[idxV] + peso) < distancias[idxW]) {
                    distancias[idxW] = distancias[idxV] + peso;
                    colaAux.encolar(w);
                }
            }
        }
    }

    return distancias;
}

/**
 * @brief Distancias de Dijkstra como mapa vertice -> distancia.
 */
template <typename T>
map<T, float> dijkstraMapeadoComoMapa(const Grafo<T>& g, const T& origen) {
    map<T, int> idDe = construirMapaIndices(g);

    vector<float> dist = dijkstraMapeado(g, origen);
    map<T, float> out;

    typename map<T, int>::const_iterator it = idDe.begin();
    while (it != idDe.end()) {
        out[it->first] = dist[it->second];
        ++it;
    }

    return out;
}

/**
 * @brief Vertices alcanzables por una sola ruta directa <= km.
 */
template <typename T>
Lista<T> verticesAMenosDeMapeado(const Grafo<T>& g, const T& ciudad, float km) {
    Lista<T> result;
    Lista<T> vecinos = g.getVecinos(ciudad);

    while (!vecinos.esVacia()) {
        T w = vecinos.consultar(1);
        vecinos.eliminar(1);

        float peso = g.getPesoArco(ciudad, w);
        if (peso <= km) {
            result.insertar(w, result.getLong() + 1);
        }
    }

    return result;
}

/**
 * @brief True si existe camino entre origen y destino.
 */
template <typename T>
bool esDestinoAlcanzableMapeado(const Grafo<T>& g, const T& origen, const T& destino) {
    if (g.esVacio()) {
        return false;
    }

    map<T, int> idDe = construirMapaIndices(g);

    if (idDe.find(origen) == idDe.end() || idDe.find(destino) == idDe.end()) {
        return false;
    }

    vector<int> padres;
    return bfsConPadresMapeado(g, origen, destino, idDe, padres);
}

/**
 * @brief Invierte todos los arcos de un grafo dirigido.
 *
 * En grafo no dirigido devuelve una copia equivalente.
 */
template <typename T>
Grafo<T> reverseGraphMapeado(const Grafo<T>& g) {
    Grafo<T> inverso(g.getEsDirigido());

    Lista<T> vertices = g.getVertices();
    while (!vertices.esVacia()) {
        T v = vertices.consultar(1);
        vertices.eliminar(1);
        inverso.insertarVertice(v);
    }

    if (!g.getEsDirigido()) {
        Lista<T> verts = g.getVertices();
        while (!verts.esVacia()) {
            T v = verts.consultar(1);
            verts.eliminar(1);

            Lista<T> vecinos = g.getVecinos(v);
            while (!vecinos.esVacia()) {
                T w = vecinos.consultar(1);
                vecinos.eliminar(1);
                inverso.insertarArco(v, w, g.getPesoArco(v, w));
            }
        }
        return inverso;
    }

    Lista<T> origenes = g.getVertices();
    while (!origenes.esVacia()) {
        T v = origenes.consultar(1);
        origenes.eliminar(1);

        Lista<T> sucesores = g.getSucesores(v);
        while (!sucesores.esVacia()) {
            T w = sucesores.consultar(1);
            sucesores.eliminar(1);
            inverso.insertarArco(w, v, g.getPesoArco(v, w));
        }
    }

    return inverso;
}

#endif
