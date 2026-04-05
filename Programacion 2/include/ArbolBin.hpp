#ifndef ARBOLBIN_HPP
#define ARBOLBIN_HPP

#include <iostream>
#include <stdexcept>
#include "Lista.hpp"
#include "Cola.hpp"

using namespace std;

/**
 * @brief Nodo para arbol binario.
 * @tparam T Tipo de dato almacenado.
 */
template <typename T>
class NodoBin {
private:
    T info;
    NodoBin<T>* hijoIzq;
    NodoBin<T>* hijoDer;

public:
    /**
     * @brief Construye un nodo binario.
     * @param value Valor a almacenar.
     */
    explicit NodoBin(const T& value) : info(value), hijoIzq(NULL), hijoDer(NULL) {}

    /** @brief Retorna el valor almacenado. */
    const T& getInfo() const { return info; }

    /** @brief Actualiza el valor almacenado. */
    void setInfo(const T& value) { info = value; }

    /** @brief Retorna el hijo izquierdo. */
    NodoBin<T>* getHijoIzq() const { return hijoIzq; }

    /** @brief Retorna el hijo derecho. */
    NodoBin<T>* getHijoDer() const { return hijoDer; }

    /** @brief Actualiza el hijo izquierdo. */
    void setHijoIzq(NodoBin<T>* ptr) { hijoIzq = ptr; }

    /** @brief Actualiza el hijo derecho. */
    void setHijoDer(NodoBin<T>* ptr) { hijoDer = ptr; }
};

/**
 * @brief Arbol binario generico con operaciones de clase y ejercicios.
 * @tparam T Tipo de dato almacenado en cada nodo.
 */
template <typename T>
class ArbolBin {
private:
    NodoBin<T>* nodoRaiz;
    int peso;

    int buscarPosEnRango(const Lista<T>& lista, int ini, int fin, const T& valor) const {
        for (int i = ini; i <= fin; ++i) {
            if (lista.consultar(i) == valor) {
                return i;
            }
        }
        return -1;
    }

    NodoBin<T>* construirDesdeInPreRec(
        const Lista<T>& inOrdenRec,
        int inL,
        int inR,
        const Lista<T>& preOrdenRec,
        int& preIdx) {
        if (inL > inR) {
            return NULL;
        }

        if (preIdx > preOrdenRec.getLong()) {
            throw invalid_argument("Recorrido preorden incompleto");
        }

        T raizValor = preOrdenRec.consultar(preIdx);
        ++preIdx;

        int mid = buscarPosEnRango(inOrdenRec, inL, inR, raizValor);
        if (mid == -1) {
            throw invalid_argument("Recorridos inorden/preorden inconsistentes");
        }

        NodoBin<T>* nodo = new NodoBin<T>(raizValor);

        try {
            nodo->setHijoIzq(construirDesdeInPreRec(inOrdenRec, inL, mid - 1, preOrdenRec, preIdx));
            nodo->setHijoDer(construirDesdeInPreRec(inOrdenRec, mid + 1, inR, preOrdenRec, preIdx));
        } catch (...) {
            destruirSubarbol(nodo);
            throw;
        }

        return nodo;
    }

    NodoBin<T>* construirDesdeInPostRec(
        const Lista<T>& inOrdenRec,
        int inL,
        int inR,
        const Lista<T>& postOrdenRec,
        int& postIdx) {
        if (inL > inR) {
            return NULL;
        }

        if (postIdx < 1) {
            throw invalid_argument("Recorrido postorden incompleto");
        }

        T raizValor = postOrdenRec.consultar(postIdx);
        --postIdx;

        int mid = buscarPosEnRango(inOrdenRec, inL, inR, raizValor);
        if (mid == -1) {
            throw invalid_argument("Recorridos inorden/postorden inconsistentes");
        }

        NodoBin<T>* nodo = new NodoBin<T>(raizValor);

        try {
            nodo->setHijoDer(construirDesdeInPostRec(inOrdenRec, mid + 1, inR, postOrdenRec, postIdx));
            nodo->setHijoIzq(construirDesdeInPostRec(inOrdenRec, inL, mid - 1, postOrdenRec, postIdx));
        } catch (...) {
            destruirSubarbol(nodo);
            throw;
        }

        return nodo;
    }

    void imprimirRotadoRec(NodoBin<T>* ptr, int nivel, ostream& os) const {
        if (!ptr) {
            return;
        }
        imprimirRotadoRec(ptr->getHijoDer(), nivel + 1, os);
        for (int i = 0; i < nivel; ++i) {
            os << "    ";
        }
        os << ptr->getInfo() << "\n";
        imprimirRotadoRec(ptr->getHijoIzq(), nivel + 1, os);
    }

    NodoBin<T>* copiarSubarbol(const NodoBin<T>* ptr) const {
        if (!ptr) {
            return NULL;
        }
        NodoBin<T>* nuevo = new NodoBin<T>(ptr->getInfo());
        nuevo->setHijoIzq(copiarSubarbol(ptr->getHijoIzq()));
        nuevo->setHijoDer(copiarSubarbol(ptr->getHijoDer()));
        return nuevo;
    }

    int contarNodos(NodoBin<T>* ptr) const {
        if (!ptr) {
            return 0;
        }
        return 1 + contarNodos(ptr->getHijoIzq()) + contarNodos(ptr->getHijoDer());
    }

    int destruirSubarbol(NodoBin<T>* ptr) {
        if (!ptr) {
            return 0;
        }
        int borradosIzq = destruirSubarbol(ptr->getHijoIzq());
        int borradosDer = destruirSubarbol(ptr->getHijoDer());
        delete ptr;
        return 1 + borradosIzq + borradosDer;
    }

    NodoBin<T>* buscarNodo(NodoBin<T>* ptr, const T& valor) const {
        if (!ptr) {
            return NULL;
        }
        if (ptr->getInfo() == valor) {
            return ptr;
        }
        NodoBin<T>* izq = buscarNodo(ptr->getHijoIzq(), valor);
        if (izq) {
            return izq;
        }
        return buscarNodo(ptr->getHijoDer(), valor);
    }

    void preOrden(NodoBin<T>* ptr, Lista<T>& result) const {
        if (ptr) {
            result.insertar(ptr->getInfo(), result.getLong() + 1);
            preOrden(ptr->getHijoIzq(), result);
            preOrden(ptr->getHijoDer(), result);
        }
    }

    void inOrden(NodoBin<T>* ptr, Lista<T>& result) const {
        if (ptr) {
            inOrden(ptr->getHijoIzq(), result);
            result.insertar(ptr->getInfo(), result.getLong() + 1);
            inOrden(ptr->getHijoDer(), result);
        }
    }

    void postOrden(NodoBin<T>* ptr, Lista<T>& result) const {
        if (ptr) {
            postOrden(ptr->getHijoIzq(), result);
            postOrden(ptr->getHijoDer(), result);
            result.insertar(ptr->getInfo(), result.getLong() + 1);
        }
    }

    void getHojas(NodoBin<T>* ptr, Lista<T>& result) const {
        if (!ptr) {
            return;
        }
        if (!ptr->getHijoIzq() && !ptr->getHijoDer()) {
            result.insertar(ptr->getInfo(), result.getLong() + 1);
            return;
        }
        getHojas(ptr->getHijoIzq(), result);
        getHojas(ptr->getHijoDer(), result);
    }

    bool contiene(NodoBin<T>* ptr, const T& objetivo) const {
        if (!ptr) {
            return false;
        }
        if (ptr->getInfo() == objetivo) {
            return true;
        }
        return contiene(ptr->getHijoIzq(), objetivo) || contiene(ptr->getHijoDer(), objetivo);
    }

    bool esIsomorfo(NodoBin<T>* a, NodoBin<T>* b) const {
        if (!a && !b) {
            return true;
        }
        if (!a || !b) {
            return false;
        }
        return esIsomorfo(a->getHijoIzq(), b->getHijoIzq()) && esIsomorfo(a->getHijoDer(), b->getHijoDer());
    }

    NodoBin<T>* lcaPtrSimple(NodoBin<T>* ptr, const T& a, const T& b) const {
        if (!ptr) {
            return NULL;
        }

        if (ptr->getInfo() == a || ptr->getInfo() == b) {
            return ptr;
        }

        NodoBin<T>* izq = lcaPtrSimple(ptr->getHijoIzq(), a, b);
        NodoBin<T>* der = lcaPtrSimple(ptr->getHijoDer(), a, b);

        if (izq && der) {
            return ptr;
        }
        return izq ? izq : der;
    }

    NodoBin<T>* lcaConExistencia(NodoBin<T>* ptr, const T& a, const T& b, bool& foundA, bool& foundB) const {
        if (!ptr) {
            return NULL;
        }

        bool foundAI = false;
        bool foundBI = false;
        bool foundAD = false;
        bool foundBD = false;

        NodoBin<T>* izq = lcaConExistencia(ptr->getHijoIzq(), a, b, foundAI, foundBI);
        NodoBin<T>* der = lcaConExistencia(ptr->getHijoDer(), a, b, foundAD, foundBD);

        foundA = foundAI || foundAD || (ptr->getInfo() == a);
        foundB = foundBI || foundBD || (ptr->getInfo() == b);

        if (izq && der) {
            return ptr;
        }

        if (ptr->getInfo() == a || ptr->getInfo() == b) {
            return ptr;
        }

        return izq ? izq : der;
    }

    int profundidadNodo(NodoBin<T>* ptr, NodoBin<T>* objetivo, int nivel) const {
        if (!ptr) {
            return -1;
        }
        if (ptr == objetivo) {
            return nivel;
        }

        int izq = profundidadNodo(ptr->getHijoIzq(), objetivo, nivel + 1);
        if (izq != -1) {
            return izq;
        }
        return profundidadNodo(ptr->getHijoDer(), objetivo, nivel + 1);
    }

public:
    /** @brief Construye un arbol binario vacio. */
    ArbolBin() : nodoRaiz(NULL), peso(0) {}

    /**
     * @brief Construye un arbol a partir de inorden y preorden/postorden.
     * @param inOrdenRec Recorrido inorden.
     * @param segundoRec Recorrido preorden o postorden.
     * @param segundoEsPreorden true si segundoRec es preorden; false si es postorden.
     */
    ArbolBin(const Lista<T>& inOrdenRec, const Lista<T>& segundoRec, bool segundoEsPreorden)
        : nodoRaiz(NULL), peso(0) {
        if (segundoEsPreorden) {
            construirDesdeInYPre(inOrdenRec, segundoRec);
        } else {
            construirDesdeInYPost(inOrdenRec, segundoRec);
        }
    }

    /**
     * @brief Constructor de copia.
     * @param other Arbol origen.
     */
    ArbolBin(const ArbolBin<T>& other) : nodoRaiz(copiarSubarbol(other.nodoRaiz)), peso(other.peso) {}

    /**
     * @brief Operador de asignacion por copia.
     * @param other Arbol origen.
     * @return Referencia a este arbol.
     */
    ArbolBin<T>& operator=(const ArbolBin<T>& other) {
        if (this == &other) {
            return *this;
        }
        vaciar();
        nodoRaiz = copiarSubarbol(other.nodoRaiz);
        peso = other.peso;
        return *this;
    }

    /** @brief Destructor. */
    ~ArbolBin() { vaciar(); }

    /** @brief Reinicia el arbol como vacio. */
    void construir() { vaciar(); }

    /**
     * @brief Copia otro arbol sobre el actual.
     * @param a Arbol origen.
     */
    void construir(const ArbolBin<T>& a) { *this = a; }

    /**
     * @brief Reconstruye el arbol desde inorden y preorden.
     * @param inOrdenRec Recorrido inorden.
     * @param preOrdenRec Recorrido preorden.
     * @throw invalid_argument Si los recorridos son invalidos.
     */
    void construirDesdeInYPre(const Lista<T>& inOrdenRec, const Lista<T>& preOrdenRec) {
        int n = inOrdenRec.getLong();
        if (n != preOrdenRec.getLong()) {
            throw invalid_argument("Inorden y preorden deben tener el mismo tamano");
        }

        vaciar();
        if (n == 0) {
            return;
        }

        for (int i = 1; i <= n; ++i) {
            T v = inOrdenRec.consultar(i);
            for (int j = i + 1; j <= n; ++j) {
                if (inOrdenRec.consultar(j) == v) {
                    throw invalid_argument("No se admiten valores duplicados al reconstruir");
                }
            }
        }

        for (int i = 1; i <= n; ++i) {
            T v = preOrdenRec.consultar(i);
            if (buscarPosEnRango(inOrdenRec, 1, n, v) == -1) {
                throw invalid_argument("Preorden contiene valores ausentes en inorden");
            }
            for (int j = i + 1; j <= n; ++j) {
                if (preOrdenRec.consultar(j) == v) {
                    throw invalid_argument("No se admiten valores duplicados al reconstruir");
                }
            }
        }

        int preIdx = 1;
        nodoRaiz = construirDesdeInPreRec(inOrdenRec, 1, n, preOrdenRec, preIdx);
        if (preIdx != n + 1) {
            vaciar();
            throw invalid_argument("Recorridos inorden/preorden inconsistentes");
        }
        peso = n;
    }

    /**
     * @brief Reconstruye el arbol desde inorden y postorden.
     * @param inOrdenRec Recorrido inorden.
     * @param postOrdenRec Recorrido postorden.
     * @throw invalid_argument Si los recorridos son invalidos.
     */
    void construirDesdeInYPost(const Lista<T>& inOrdenRec, const Lista<T>& postOrdenRec) {
        int n = inOrdenRec.getLong();
        if (n != postOrdenRec.getLong()) {
            throw invalid_argument("Inorden y postorden deben tener el mismo tamano");
        }

        vaciar();
        if (n == 0) {
            return;
        }

        for (int i = 1; i <= n; ++i) {
            T v = inOrdenRec.consultar(i);
            for (int j = i + 1; j <= n; ++j) {
                if (inOrdenRec.consultar(j) == v) {
                    throw invalid_argument("No se admiten valores duplicados al reconstruir");
                }
            }
        }

        for (int i = 1; i <= n; ++i) {
            T v = postOrdenRec.consultar(i);
            if (buscarPosEnRango(inOrdenRec, 1, n, v) == -1) {
                throw invalid_argument("Postorden contiene valores ausentes en inorden");
            }
            for (int j = i + 1; j <= n; ++j) {
                if (postOrdenRec.consultar(j) == v) {
                    throw invalid_argument("No se admiten valores duplicados al reconstruir");
                }
            }
        }

        int postIdx = n;
        nodoRaiz = construirDesdeInPostRec(inOrdenRec, 1, n, postOrdenRec, postIdx);
        if (postIdx != 0) {
            vaciar();
            throw invalid_argument("Recorridos inorden/postorden inconsistentes");
        }
        peso = n;
    }

    /**
     * @brief Imprime el arbol en formato rotado (derecha-arriba, izquierda-abajo).
     */
    void imprimirRotado() const {
        if (!nodoRaiz) {
            cout << "(arbol vacio)";
            return;
        }
        imprimirRotadoRec(nodoRaiz, 0, cout);
    }

    /**
     * @brief Imprime el arbol por niveles.
     */
    void imprimirPorNiveles() const {
        if (!nodoRaiz) {
            cout << "(arbol vacio)";
            return;
        }

        Cola<NodoBin<T>*> colaAux;
        colaAux.encolar(nodoRaiz);
        int nivel = 0;

        while (!colaAux.esVacia()) {
            int tamNivel = colaAux.getLong();
            cout << "Nivel " << nivel << ": ";

            for (int i = 1; i <= tamNivel; ++i) {
                NodoBin<T>* ptr = colaAux.getFrente();
                colaAux.desencolar();

                cout << ptr->getInfo();
                if (i < tamNivel) {
                    cout << ", ";
                }

                if (ptr->getHijoIzq()) {
                    colaAux.encolar(ptr->getHijoIzq());
                }
                if (ptr->getHijoDer()) {
                    colaAux.encolar(ptr->getHijoDer());
                }
            }

            if (!colaAux.esVacia()) {
                cout << "\n";
            }
            ++nivel;
        }

        cout << "\n";
    }

    /**
     * @brief Obtiene la informacion de la raiz.
     * @return Valor en raiz.
     * @throw logic_error Si el arbol es nulo.
     */
    T getRaiz() const {
        if (!nodoRaiz) {
            throw logic_error("Arbol vacio");
        }
        return nodoRaiz->getInfo();
    }

    /** @brief Retorna la cantidad de nodos del arbol. */
    int getPeso() const { return peso; }

    /** @brief Indica si el arbol esta vacio. */
    bool esNulo() const { return nodoRaiz == NULL; }

    /** @brief Indica si la raiz es hoja. */
    bool esHoja() const {
        return nodoRaiz != NULL && nodoRaiz->getHijoIzq() == NULL && nodoRaiz->getHijoDer() == NULL;
    }

    /**
     * @brief Retorna una copia del subarbol izquierdo.
     * @return Arbol con el hijo izquierdo como raiz.
     */
    ArbolBin<T> getHijoIzq() const {
        ArbolBin<T> out;
        if (nodoRaiz && nodoRaiz->getHijoIzq()) {
            out.nodoRaiz = copiarSubarbol(nodoRaiz->getHijoIzq());
            out.peso = contarNodos(out.nodoRaiz);
        }
        return out;
    }

    /**
     * @brief Retorna una copia del subarbol derecho.
     * @return Arbol con el hijo derecho como raiz.
     */
    ArbolBin<T> getHijoDer() const {
        ArbolBin<T> out;
        if (nodoRaiz && nodoRaiz->getHijoDer()) {
            out.nodoRaiz = copiarSubarbol(nodoRaiz->getHijoDer());
            out.peso = contarNodos(out.nodoRaiz);
        }
        return out;
    }

    /** @brief Recorrido en preorden. */
    Lista<T> preOrden() const {
        Lista<T> result;
        preOrden(nodoRaiz, result);
        return result;
    }

    /** @brief Recorrido en inorden. */
    Lista<T> inOrden() const {
        Lista<T> result;
        inOrden(nodoRaiz, result);
        return result;
    }

    /** @brief Recorrido en postorden. */
    Lista<T> postOrden() const {
        Lista<T> result;
        postOrden(nodoRaiz, result);
        return result;
    }

    /**
     * @brief Recorrido por niveles (BFS).
     * @return Lista con el recorrido.
     */
    Lista<T> porNiveles() const {
        Lista<T> result;
        if (!nodoRaiz) {
            return result;
        }

        Cola<NodoBin<T>*> colaAux;
        colaAux.encolar(nodoRaiz);

        while (!colaAux.esVacia()) {
            NodoBin<T>* ptr = colaAux.getFrente();
            colaAux.desencolar();
            result.insertar(ptr->getInfo(), result.getLong() + 1);

            if (ptr->getHijoIzq()) {
                colaAux.encolar(ptr->getHijoIzq());
            }
            if (ptr->getHijoDer()) {
                colaAux.encolar(ptr->getHijoDer());
            }
        }

        return result;
    }

    /**
     * @brief Obtiene todas las hojas del arbol.
     * @return Lista con hojas.
     */
    Lista<T> getHojas() const {
        Lista<T> result;
        getHojas(nodoRaiz, result);
        return result;
    }

    /** @brief Elimina todos los nodos del arbol. */
    void vaciar() {
        peso -= destruirSubarbol(nodoRaiz);
        nodoRaiz = NULL;
        peso = 0;
    }

    /** @brief Alias de vaciar(). */
    void destruir() { vaciar(); }

    /**
     * @brief Inserta un nodo hijo de "padre".
     *
     * Si el arbol esta vacio, inserta e como raiz y no usa padre.
     * Si padre existe y tiene hueco en izquierdo o derecho, inserta ahi.
     *
     * @param padre Valor del nodo padre.
     * @param e Valor a insertar.
     * @throw out_of_range Si el padre no existe.
     * @throw logic_error Si el padre ya tiene dos hijos.
     */
    void insertarNodo(const T& padre, const T& e) {
        if (!nodoRaiz) {
            nodoRaiz = new NodoBin<T>(e);
            peso = 1;
            return;
        }

        NodoBin<T>* ptrPadre = buscarNodo(nodoRaiz, padre);
        if (!ptrPadre) {
            throw out_of_range("Padre no encontrado");
        }

        if (!ptrPadre->getHijoIzq()) {
            ptrPadre->setHijoIzq(new NodoBin<T>(e));
            ++peso;
            return;
        }

        if (!ptrPadre->getHijoDer()) {
            ptrPadre->setHijoDer(new NodoBin<T>(e));
            ++peso;
            return;
        }

        throw logic_error("El padre ya tiene dos hijos");
    }

    /**
     * @brief Elimina del arbol el nodo e si es hijo directo de padre.
     *
     * Elimina todo el subarbol cuya raiz sea ese hijo.
     *
     * @param padre Valor del padre.
     * @param e Valor del hijo a eliminar.
     */
    void eliminarNodo(const T& padre, const T& e) {
        if (!nodoRaiz) {
            return;
        }

        NodoBin<T>* ptrPadre = buscarNodo(nodoRaiz, padre);
        if (!ptrPadre) {
            return;
        }

        NodoBin<T>* izq = ptrPadre->getHijoIzq();
        if (izq && izq->getInfo() == e) {
            ptrPadre->setHijoIzq(NULL);
            int borrados = destruirSubarbol(izq);
            peso -= borrados;
            if (peso < 0) {
                peso = 0;
            }
            return;
        }

        NodoBin<T>* der = ptrPadre->getHijoDer();
        if (der && der->getInfo() == e) {
            ptrPadre->setHijoDer(NULL);
            int borrados = destruirSubarbol(der);
            peso -= borrados;
            if (peso < 0) {
                peso = 0;
            }
        }
    }

    /**
     * @brief Evalua isomorfismo estructural con otro arbol.
     * @param b Arbol a comparar.
     * @return true si comparten la misma estructura.
     */
    bool esIsomorfo(const ArbolBin<T>& b) const {
        return esIsomorfo(nodoRaiz, b.nodoRaiz);
    }

    /**
     * @brief Retorna el LCA de a y b por valor.
     * @param a Primer valor.
     * @param b Segundo valor.
     * @return Valor del LCA o T() si alguno no existe.
     */
    T lca(const T& a, const T& b) const {
        bool foundA = false;
        bool foundB = false;
        NodoBin<T>* ptrLca = lcaConExistencia(nodoRaiz, a, b, foundA, foundB);
        if (ptrLca && foundA && foundB) {
            return ptrLca->getInfo();
        }
        return T();
    }

    /**
     * @brief Verifica si x pertenece al camino unico entre u y v.
     * @param x Nodo candidato.
     * @param u Primer extremo.
     * @param v Segundo extremo.
     * @return true si x esta en el camino u-v.
     */
    bool estaEnCamino(const T& x, const T& u, const T& v) const {
        bool foundU = false;
        bool foundV = false;
        NodoBin<T>* w = lcaConExistencia(nodoRaiz, u, v, foundU, foundV);
        if (!w || !foundU || !foundV) {
            return false;
        }

        NodoBin<T>* px = buscarNodo(nodoRaiz, x);
        if (!px) {
            return false;
        }

        return contiene(w, x) && (contiene(px, u) || contiene(px, v));
    }

    /**
     * @brief Verifica si x es el ancestro comun mas cercano de u y v.
     * @param x Candidato a LCA.
     * @param u Primer nodo.
     * @param v Segundo nodo.
     * @return true si x es LCA.
     */
    bool esLCA(const T& x, const T& u, const T& v) const {
        NodoBin<T>* ptr = buscarNodo(nodoRaiz, x);
        if (!ptr) {
            return false;
        }

        if (!contiene(ptr, u) || !contiene(ptr, v)) {
            return false;
        }

        if (ptr->getInfo() == u || ptr->getInfo() == v) {
            return true;
        }

        bool ambosIzq = contiene(ptr->getHijoIzq(), u) && contiene(ptr->getHijoIzq(), v);
        bool ambosDer = contiene(ptr->getHijoDer(), u) && contiene(ptr->getHijoDer(), v);

        return !ambosIzq && !ambosDer;
    }

    /**
     * @brief Verifica si ancestro es ancestro de objetivo.
     * @param ancestro Valor del posible ancestro.
     * @param objetivo Valor objetivo.
     * @return true si objetivo esta en el subarbol de ancestro.
     */
    bool esAncestro(const T& ancestro, const T& objetivo) const {
        NodoBin<T>* ptr = buscarNodo(nodoRaiz, ancestro);
        if (!ptr) {
            return false;
        }
        return contiene(ptr, objetivo);
    }

    /**
     * @brief Profundidad del LCA de u y v.
     * @param u Primer valor.
     * @param v Segundo valor.
     * @return Nivel del LCA o -1 si alguno no existe.
     */
    int profundidadLCA(const T& u, const T& v) const {
        bool foundU = false;
        bool foundV = false;
        NodoBin<T>* ptrLca = lcaConExistencia(nodoRaiz, u, v, foundU, foundV);

        if (!ptrLca || !foundU || !foundV) {
            return -1;
        }

        return profundidadNodo(nodoRaiz, ptrLca, 0);
    }
};

#endif
