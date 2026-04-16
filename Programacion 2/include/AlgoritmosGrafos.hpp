#ifndef ALGORITMOS_GRAFOS_HPP
#define ALGORITMOS_GRAFOS_HPP

#include <map>
#include <vector>
#include <stdexcept>
#include "Grafos.hpp"

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

template <typename T>
void dfsRecMapeado(const Grafo<T>& g, const T& v, const map<T, int>& idDe, 
    vector<bool>& visitado, Lista<T>& recorrido) {
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

        if (visitado[idxS]) {
            continue;
        }

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

#endif
