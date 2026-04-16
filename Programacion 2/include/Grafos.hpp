#ifndef GRAFOS_HPP
#define GRAFOS_HPP

/*
Libreria basada en clases de Algoritmos 2.
Representacion: lista de vertices y, por cada vertice, lista de arcos.
*/

#include <iostream>
#include <stdexcept>
#include "Lista.hpp"

using namespace std;

template <typename T>
class NodoVertice;

/**
 * @brief Nodo de arco para lista de adyacencia.
 * @tparam T Tipo de dato del vertice.
 */
template <typename T>
class NodoArco {
private:
    NodoVertice<T>* destino;
    NodoArco<T>* nextA;
    float peso;

public:
    /** @brief Construye un arco vacio. */
    NodoArco() : destino(NULL), nextA(NULL), peso(0.0f) {}

    /**
     * @brief Construye un arco con destino, siguiente y peso.
     */
    NodoArco(NodoVertice<T>* ptrDestino, NodoArco<T>* ptrNext, float nuevoPeso)
        : destino(ptrDestino), nextA(ptrNext), peso(nuevoPeso) {}

    /** @brief Retorna vertice destino. */
    NodoVertice<T>* getVertice() const { return destino; }

    /** @brief Retorna siguiente arco. */
    NodoArco<T>* getNextArco() const { return nextA; }

    /** @brief Retorna peso del arco. */
    float getPeso() const { return peso; }

    /** @brief Actualiza vertice destino. */
    void setVertice(NodoVertice<T>* ptrDestino) { destino = ptrDestino; }

    /** @brief Actualiza siguiente arco. */
    void setNextArco(NodoArco<T>* ptrNext) { nextA = ptrNext; }

    /** @brief Actualiza peso del arco. */
    void setPeso(float nuevoPeso) { peso = nuevoPeso; }
};

/**
 * @brief Nodo de vertice para lista principal del grafo.
 * @tparam T Tipo de dato del vertice.
 */
template <typename T>
class NodoVertice {
private:
    T info;
    NodoVertice<T>* nextV;
    NodoArco<T>* arcosHead;

public:
    /** @brief Construye un vertice. */
    NodoVertice(const T& valor, NodoVertice<T>* sigV, NodoArco<T>* sigA)
        : info(valor), nextV(sigV), arcosHead(sigA) {}

    /** @brief Retorna valor del vertice. */
    const T& getInfo() const { return info; }

    /** @brief Retorna siguiente vertice. */
    NodoVertice<T>* getNextVertice() const { return nextV; }

    /** @brief Retorna cabeza de arcos salientes. */
    NodoArco<T>* getArcoHead() const { return arcosHead; }

    /** @brief Actualiza valor del vertice. */
    void setInfo(const T& valor) { info = valor; }

    /** @brief Actualiza puntero al siguiente vertice. */
    void setNextVertice(NodoVertice<T>* ptrSig) { nextV = ptrSig; }

    /** @brief Actualiza puntero a cabeza de arcos. */
    void setArcosHead(NodoArco<T>* ptrArco) { arcosHead = ptrArco; }
};

/**
 * @brief Grafo generico con soporte dirigido/no dirigido.
 *
 * La diferencia de comportamiento se controla con el atributo "dirigido".
 * No se requiere crear clases hijas para cada tipo.
 *
 * @tparam T Tipo de dato de cada vertice.
 */
template <typename T>
class Grafo {
private:
    NodoVertice<T>* verticeHead;
    int nVertices;
    int nArcos;
    bool dirigido;

    /** @brief Busca y retorna puntero interno del vertice o NULL si no existe. */
    NodoVertice<T>* buscarVerticePtr(const T& valor) const {
        NodoVertice<T>* actual = verticeHead;
        while (actual) {
            if (actual->getInfo() == valor) {
                return actual;
            }
            actual = actual->getNextVertice();
        }
        return NULL;
    }

    /** @brief Verifica si existe arco origen -> destino. */
    bool existeArcoInterno(NodoVertice<T>* origen, NodoVertice<T>* destino) const {
        if (!origen || !destino) {
            return false;
        }

        NodoArco<T>* arco = origen->getArcoHead();
        while (arco) {
            if (arco->getVertice() == destino) {
                return true;
            }
            arco = arco->getNextArco();
        }
        return false;
    }

    /** @brief Inserta arco simple origen -> destino al inicio de la lista de arcos. */
    void insertarArcoSimple(NodoVertice<T>* origen, NodoVertice<T>* destino, float peso) {
        NodoArco<T>* nuevo = new NodoArco<T>(destino, origen->getArcoHead(), peso);
        origen->setArcosHead(nuevo);
    }

    /** @brief Libera una lista de arcos. */
    void liberarArcos(NodoArco<T>* headArcos) {
        NodoArco<T>* actual = headArcos;
        while (actual) {
            NodoArco<T>* sig = actual->getNextArco();
            delete actual;
            actual = sig;
        }
    }

    /** @brief Copia profunda del contenido de otro grafo. */
    void copiarDesde(const Grafo<T>& other) {
        dirigido = other.dirigido;
        nVertices = 0;
        nArcos = 0;
        verticeHead = NULL;

        Lista<T> vertices = other.getVertices();
        while (!vertices.esVacia()) {
            T valor = vertices.consultar(1);
            insertarVertice(valor);
            vertices.eliminar(1);
        }

        NodoVertice<T>* actual = other.verticeHead;
        while (actual) {
            NodoArco<T>* arco = actual->getArcoHead();
            while (arco) {
                insertarArco(actual->getInfo(), arco->getVertice()->getInfo(), arco->getPeso());
                arco = arco->getNextArco();
            }
            actual = actual->getNextVertice();
        }
    }

public:
    /**
     * @brief Construye un grafo vacio.
     * @param esDirigido true para dirigido, false para no dirigido.
     */
    explicit Grafo(bool esDirigido = false)
        : verticeHead(NULL), nVertices(0), nArcos(0), dirigido(esDirigido) {}

    /** @brief Constructor de copia. */
    Grafo(const Grafo<T>& other) : verticeHead(NULL), nVertices(0), nArcos(0), dirigido(false) {
        copiarDesde(other);
    }

    /** @brief Operador de asignacion por copia. */
    Grafo<T>& operator=(const Grafo<T>& other) {
        if (this == &other) {
            return *this;
        }
        vaciar();
        copiarDesde(other);
        return *this;
    }

    /** @brief Destructor. */
    ~Grafo() {
        vaciar();
    }

    /** @brief Retorna true si el grafo es dirigido. */
    bool getEsDirigido() const { return dirigido; }

    /** @brief Retorna cantidad de vertices. */
    int getNNodos() const { return nVertices; }

    /** @brief Retorna cantidad de arcos/aristas logicas. */
    int getNArcos() const { return nArcos; }

    /** @brief Retorna true si no hay vertices. */
    bool esVacio() const { return nVertices == 0; }

    /**
     * @brief Retorna lista de vertices del grafo.
     * @return Lista con todos los vertices.
     */
    Lista<T> getVertices() const {
        Lista<T> result;
        NodoVertice<T>* actual = verticeHead;
        while (actual) {
            result.insertar(actual->getInfo(), result.getLong() + 1);
            actual = actual->getNextVertice();
        }
        return result;
    }

    /**
     * @brief Verifica existencia de un vertice.
     */
    bool existeVertice(const T& valor) const {
        return buscarVerticePtr(valor) != NULL;
    }

    /**
     * @brief Inserta un vertice si no existe.
     *
     * Operacion idempotente: si ya existe, no hace cambios.
     */
    void insertarVertice(const T& valor) {
        if (existeVertice(valor)) {
            return;
        }

        NodoVertice<T>* nuevo = new NodoVertice<T>(valor, verticeHead, NULL);
        verticeHead = nuevo;
        ++nVertices;
    }

    /**
     * @brief Inserta un arco/arista segun tipo de grafo.
     *
     * En dirigido inserta v->w.
     * En no dirigido inserta v->w y w->v.
     * Si vertices no existen, se crean.
     */
    void insertarArco(const T& v, const T& w, float peso = 1.0f) {
        if (!existeVertice(v)) {
            insertarVertice(v);
        }
        if (!existeVertice(w)) {
            insertarVertice(w);
        }

        NodoVertice<T>* origen = buscarVerticePtr(v);
        NodoVertice<T>* destino = buscarVerticePtr(w);

        bool agregoVW = false;
        bool agregoWV = false;

        if (!existeArcoInterno(origen, destino)) {
            insertarArcoSimple(origen, destino, peso);
            agregoVW = true;
        }

        if (!dirigido && origen != destino && !existeArcoInterno(destino, origen)) {
            insertarArcoSimple(destino, origen, peso);
            agregoWV = true;
        }

        if (dirigido) {
            if (agregoVW) {
                ++nArcos;
            }
        } else {
            if (origen == destino) {
                if (agregoVW) {
                    ++nArcos;
                }
            } else if (agregoVW || agregoWV) {
                ++nArcos;
            }
        }
    }

    /**
     * @brief Verifica si existe arco v->w.
     */
    bool existeArco(const T& v, const T& w) const {
        NodoVertice<T>* origen = buscarVerticePtr(v);
        NodoVertice<T>* destino = buscarVerticePtr(w);
        return existeArcoInterno(origen, destino);
    }

    /**
     * @brief Retorna el peso del arco v->w.
     * @throw invalid_argument Si v o w no existen o no hay arco v->w.
     */
    float getPesoArco(const T& v, const T& w) const {
        NodoVertice<T>* origen = buscarVerticePtr(v);
        NodoVertice<T>* destino = buscarVerticePtr(w);

        if (!origen || !destino) {
            throw invalid_argument("Vertice no existe en getPesoArco");
        }

        NodoArco<T>* arco = origen->getArcoHead();
        while (arco) {
            if (arco->getVertice() == destino) {
                return arco->getPeso();
            }
            arco = arco->getNextArco();
        }

        throw invalid_argument("Arco no existe en getPesoArco");
    }

    /**
     * @brief Retorna sucesores de v.
     * @throw invalid_argument Si v no existe.
     */
    Lista<T> getSucesores(const T& v) const {
        NodoVertice<T>* origen = buscarVerticePtr(v);
        if (!origen) {
            throw invalid_argument("Vertice no existe en getSucesores");
        }

        Lista<T> result;
        NodoArco<T>* arco = origen->getArcoHead();
        while (arco) {
            result.insertar(arco->getVertice()->getInfo(), result.getLong() + 1);
            arco = arco->getNextArco();
        }
        return result;
    }

    /**
     * @brief Retorna predecesores de v.
     *
     * En no dirigido coincide con vecinos.
     * @throw invalid_argument Si v no existe.
     */
    Lista<T> getPredecesores(const T& v) const {
        NodoVertice<T>* destino = buscarVerticePtr(v);
        if (!destino) {
            throw invalid_argument("Vertice no existe en getPredecesores");
        }

        if (!dirigido) {
            return getSucesores(v);
        }

        Lista<T> result;
        NodoVertice<T>* actual = verticeHead;
        while (actual) {
            if (existeArcoInterno(actual, destino)) {
                result.insertar(actual->getInfo(), result.getLong() + 1);
            }
            actual = actual->getNextVertice();
        }
        return result;
    }

    /**
     * @brief Retorna vecinos de v.
     *
     * En no dirigido: vecinos directos.
     * En dirigido: sucesores de v.
     * @throw invalid_argument Si v no existe.
     */
    Lista<T> getVecinos(const T& v) const {
        return getSucesores(v);
    }

    /**
     * @brief Retorna grado del vertice.
     *
     * En dirigido retorna grado de salida.
     * En no dirigido retorna cantidad de vecinos.
     * @throw invalid_argument Si v no existe.
     */
    int getGradoVertice(const T& v) const {
        return getVecinos(v).getLong();
    }

    /**
     * @brief Imprime el grafo en formato de lista de adyacencia.
     */
    void imprimirAdyacencia(ostream& os = cout) const {
        if (!verticeHead) {
            os << "(grafo vacio)";
            return;
        }

        NodoVertice<T>* vertice = verticeHead;
        while (vertice) {
            os << vertice->getInfo() << " -> [";
            NodoArco<T>* arco = vertice->getArcoHead();
            bool primero = true;

            while (arco) {
                if (!primero) {
                    os << ", ";
                }
                os << arco->getVertice()->getInfo();
                primero = false;
                arco = arco->getNextArco();
            }

            os << "]";
            vertice = vertice->getNextVertice();
            if (vertice) {
                os << "\n";
            }
        }
    }

    /**
     * @brief Imprime adyacencia con formato ASCII extendido.
     */
    void imprimirAdyacenciaDetallada(ostream& os = cout) const {
        if (!verticeHead) {
            os << "(grafo vacio)";
            return;
        }

        os << "Grafo " << (dirigido ? "dirigido" : "no dirigido")
           << " | Vertices: " << nVertices
           << " | Arcos/Aristas: " << nArcos << "\n";

        NodoVertice<T>* vertice = verticeHead;
        while (vertice) {
            os << "+- " << vertice->getInfo() << "\n";
            NodoArco<T>* arco = vertice->getArcoHead();

            if (!arco) {
                os << "   `- (sin conexiones)\n";
            } else {
                while (arco) {
                    os << "   |- " << arco->getVertice()->getInfo()
                       << " (peso=" << arco->getPeso() << ")\n";
                    arco = arco->getNextArco();
                }
            }

            vertice = vertice->getNextVertice();
        }
    }

    /**
     * @brief Libera todo el contenido del grafo.
     */
    void vaciar() {
        NodoVertice<T>* actual = verticeHead;
        while (actual) {
            NodoVertice<T>* sig = actual->getNextVertice();
            liberarArcos(actual->getArcoHead());
            delete actual;
            actual = sig;
        }

        verticeHead = NULL;
        nVertices = 0;
        nArcos = 0;
    }
};

#endif
