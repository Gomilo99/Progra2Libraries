#ifndef ARBOLN_HPP
#define ARBOLN_HPP

#include <string>
#include <climits>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "Lista.hpp"
#include "Cola.hpp"
#include "Pila.hpp"

using namespace std;

/**
 * @brief Nodo para arbol N-ario en representacion hijo-izq/hermano-der.
 * @tparam T Tipo de dato almacenado.
 */
template <typename T>
class NodoN {
private:
    T info;
    NodoN<T>* hijoIzq;
    NodoN<T>* hnoDer;

public:
    /**
     * @brief Construye un nodo N-ario.
     * @param value Valor almacenado.
     */
    explicit NodoN(const T& value) : info(value), hijoIzq(NULL), hnoDer(NULL) {}

    /** @brief Retorna el valor del nodo. */
    const T& getInfo() const { return info; }

    /** @brief Actualiza el valor del nodo. */
    void setInfo(const T& value) { info = value; }

    /** @brief Retorna el primer hijo del nodo. */
    NodoN<T>* getHijoIzq() const { return hijoIzq; }

    /** @brief Retorna el hermano derecho del nodo. */
    NodoN<T>* getHnoDer() const { return hnoDer; }

    /** @brief Actualiza el primer hijo del nodo. */
    void setHijoIzq(NodoN<T>* ptr) { hijoIzq = ptr; }

    /** @brief Actualiza el hermano derecho del nodo. */
    void setHnoDer(NodoN<T>* ptr) { hnoDer = ptr; }
};

/**
 * @brief Arbol N-ario generico con operaciones de clase y ejercicios.
 * @tparam T Tipo de dato almacenado.
 */
template <typename T>
class ArbolN {
private:
    NodoN<T>* nodoRaiz;
    int peso;

    NodoN<T>* copiarSubarbol(const NodoN<T>* ptr) const {
        if (!ptr) {
            return NULL;
        }

        NodoN<T>* nuevo = new NodoN<T>(ptr->getInfo());

        NodoN<T>* hijoSrc = ptr->getHijoIzq();
        NodoN<T>* ultimoHijoNuevo = NULL;

        while (hijoSrc) {
            NodoN<T>* hijoCopia = copiarSubarbol(hijoSrc);
            if (!ultimoHijoNuevo) {
                nuevo->setHijoIzq(hijoCopia);
            } else {
                ultimoHijoNuevo->setHnoDer(hijoCopia);
            }
            ultimoHijoNuevo = hijoCopia;
            hijoSrc = hijoSrc->getHnoDer();
        }

        return nuevo;
    }

    int contarNodos(NodoN<T>* ptr) const {
        if (!ptr) {
            return 0;
        }
        int total = 1;
        NodoN<T>* hijo = ptr->getHijoIzq();
        while (hijo) {
            total += contarNodos(hijo);
            hijo = hijo->getHnoDer();
        }
        return total;
    }

    int destruirSubarbol(NodoN<T>* ptr) {
        if (!ptr) {
            return 0;
        }

        int total = 1;
        NodoN<T>* hijo = ptr->getHijoIzq();
        while (hijo) {
            NodoN<T>* sig = hijo->getHnoDer();
            total += destruirSubarbol(hijo);
            hijo = sig;
        }
        delete ptr;
        return total;
    }

    NodoN<T>* buscarNodoRec(NodoN<T>* ptr, const T& valor) const {
        if (!ptr) {
            return NULL;
        }
        if (ptr->getInfo() == valor) {
            return ptr;
        }

        NodoN<T>* hijo = ptr->getHijoIzq();
        while (hijo) {
            NodoN<T>* found = buscarNodoRec(hijo, valor);
            if (found) {
                return found;
            }
            hijo = hijo->getHnoDer();
        }

        return NULL;
    }

    NodoN<T>* getPadreRec(NodoN<T>* ptr, const T& valor) const {
        if (!ptr) {
            return NULL;
        }

        NodoN<T>* hijo = ptr->getHijoIzq();
        while (hijo) {
            if (hijo->getInfo() == valor) {
                return ptr;
            }
            NodoN<T>* padre = getPadreRec(hijo, valor);
            if (padre) {
                return padre;
            }
            hijo = hijo->getHnoDer();
        }

        return NULL;
    }

    void preOrden(NodoN<T>* ptr, Lista<T>& result) const {
        if (ptr) {
            result.insertar(ptr->getInfo(), result.getLong() + 1);
            NodoN<T>* hijo = ptr->getHijoIzq();
            while (hijo) {
                preOrden(hijo, result);
                hijo = hijo->getHnoDer();
            }
        }
    }

    void postOrden(NodoN<T>* ptr, Lista<T>& result) const {
        if (ptr) {
            NodoN<T>* hijo = ptr->getHijoIzq();
            while (hijo) {
                postOrden(hijo, result);
                hijo = hijo->getHnoDer();
            }
            result.insertar(ptr->getInfo(), result.getLong() + 1);
        }
    }

    void inOrden(NodoN<T>* ptr, Lista<T>& result) const {
        if (!ptr) {
            return;
        }

        NodoN<T>* hijo = ptr->getHijoIzq();
        if (hijo) {
            inOrden(hijo, result);
            hijo = hijo->getHnoDer();
        }

        result.insertar(ptr->getInfo(), result.getLong() + 1);

        while (hijo) {
            inOrden(hijo, result);
            hijo = hijo->getHnoDer();
        }
    }

    void getHojas(NodoN<T>* ptr, Lista<T>& result) const {
        if (!ptr) {
            return;
        }

        if (!ptr->getHijoIzq()) {
            result.insertar(ptr->getInfo(), result.getLong() + 1);
            return;
        }

        NodoN<T>* hijo = ptr->getHijoIzq();
        while (hijo) {
            getHojas(hijo, result);
            hijo = hijo->getHnoDer();
        }
    }

    bool buscarRutaRec(NodoN<T>* ptr, const T& x, vector<NodoN<T>*>& ruta) const {
        if (!ptr) {
            return false;
        }

        ruta.push_back(ptr);
        if (ptr->getInfo() == x) {
            return true;
        }

        NodoN<T>* hijo = ptr->getHijoIzq();
        while (hijo) {
            if (buscarRutaRec(hijo, x, ruta)) {
                return true;
            }
            hijo = hijo->getHnoDer();
        }

        ruta.pop_back();
        return false;
    }

    string trim(const string& s) const {
        size_t ini = 0;
        while (ini < s.size()) {
            char c = s[ini];
            if (c != ' ' && c != '\t' && c != '\n' && c != '\r') {
                break;
            }
            ++ini;
        }

        size_t fin = s.size();
        while (fin > ini) {
            char c = s[fin - 1];
            if (c != ' ' && c != '\t' && c != '\n' && c != '\r') {
                break;
            }
            --fin;
        }

        return s.substr(ini, fin - ini);
    }

    bool tokenAValor(const string& token, T& valor) const {
        istringstream in(token);
        in >> valor;
        if (!in) {
            return false;
        }

        char extra = '\0';
        if (in >> extra) {
            return false;
        }
        return true;
    }

    void imprimirJerarquicoRec(NodoN<T>* ptr, int nivel, ostream& os) const {
        if (!ptr) {
            return;
        }

        for (int i = 0; i < nivel; ++i) {
            os << "  ";
        }
        os << ptr->getInfo() << "\n";

        NodoN<T>* hijo = ptr->getHijoIzq();
        while (hijo) {
            imprimirJerarquicoRec(hijo, nivel + 1, os);
            hijo = hijo->getHnoDer();
        }
    }

public:
    /** @brief Construye un arbol N-ario vacio. */
    ArbolN() : nodoRaiz(NULL), peso(0) {}

    /**
     * @brief Construye un arbol N-ario leyendo relaciones "padre, hijo" desde un flujo.
     * @param entrada Flujo de entrada (por ejemplo cin o ifstream).
     */
    explicit ArbolN(istream& entrada) : nodoRaiz(NULL), peso(0) {
        construirDesdeEntradaEstandar(entrada);
    }

    /**
     * @brief Constructor de copia.
     * @param other Arbol origen.
     */
    ArbolN(const ArbolN<T>& other) : nodoRaiz(copiarSubarbol(other.nodoRaiz)), peso(other.peso) {}

    /**
     * @brief Operador de asignacion por copia.
     * @param other Arbol origen.
     * @return Referencia a este arbol.
     */
    ArbolN<T>& operator=(const ArbolN<T>& other) {
        if (this == &other) {
            return *this;
        }
        vaciar();
        nodoRaiz = copiarSubarbol(other.nodoRaiz);
        peso = other.peso;
        return *this;
    }

    /** @brief Destructor. */
    ~ArbolN() { vaciar(); }

    /** @brief Reinicia el arbol como vacio. */
    void construir() { vaciar(); }

    /**
     * @brief Copia otro arbol sobre el actual.
     * @param a Arbol origen.
     */
    void construir(const ArbolN<T>& a) { *this = a; }

    /**
     * @brief Reconstruye el arbol leyendo relaciones "padre, hijo" desde entrada estandar.
     *
     * Tambien puede recibir cualquier flujo (por ejemplo istringstream)
     * para pruebas o lecturas personalizadas.
     *
     * Esta version procesa linea por linea: busca el padre actual y enlaza el hijo.
     * Por simplicidad, la entrada debe estar ordenada de forma que el padre ya exista
     * al momento de leer cada relacion (la primera linea define la raiz).
     *
     * @param entrada Flujo con lineas en formato "padre, hijo".
     * @throw invalid_argument Si el formato o las relaciones son invalidas.
     */
    void construirDesdeEntradaEstandar(istream& entrada = cin) {
        vaciar();

        string linea;
        bool leyoRelaciones = false;

        while (getline(entrada, linea)) {
            string limpia = trim(linea);
            if (limpia.empty()) {
                continue;
            }

            size_t coma = limpia.find(',');
            if (coma == string::npos || limpia.find(',', coma + 1) != string::npos) {
                throw invalid_argument("Formato invalido: se esperaba 'padre, hijo'");
            }

            string tokPadre = trim(limpia.substr(0, coma));
            string tokHijo = trim(limpia.substr(coma + 1));
            if (tokPadre.empty() || tokHijo.empty()) {
                throw invalid_argument("Formato invalido: padre o hijo vacio");
            }

            T padreVal;
            T hijoVal;
            if (!tokenAValor(tokPadre, padreVal) || !tokenAValor(tokHijo, hijoVal)) {
                throw invalid_argument("No se pudo interpretar padre o hijo");
            }

            if (padreVal == hijoVal) {
                throw invalid_argument("Relacion padre-hijo invalida: padre == hijo");
            }

            leyoRelaciones = true;

            if (!nodoRaiz) {
                nodoRaiz = new NodoN<T>(padreVal);
                peso = 1;
            }

            NodoN<T>* ptrPadre = buscarNodoRec(nodoRaiz, padreVal);
            if (!ptrPadre) {
                vaciar();
                throw invalid_argument("Padre no encontrado: la entrada debe venir ordenada");
            }

            if (buscarNodoRec(nodoRaiz, hijoVal) != NULL) {
                vaciar();
                throw invalid_argument("Nodo hijo duplicado o con multiples padres");
            }

            NodoN<T>* nuevoHijo = new NodoN<T>(hijoVal);
            NodoN<T>* primerHijo = ptrPadre->getHijoIzq();
            if (!primerHijo) {
                ptrPadre->setHijoIzq(nuevoHijo);
            } else {
                NodoN<T>* ult = primerHijo;
                while (ult->getHnoDer()) {
                    ult = ult->getHnoDer();
                }
                ult->setHnoDer(nuevoHijo);
            }
            ++peso;
        }

        if (!entrada.eof()) {
            vaciar();
            throw invalid_argument("Error al leer la entrada de relaciones");
        }

        if (!leyoRelaciones) {
            vaciar();
        }
    }

    /**
     * @brief Imprime el arbol en forma jerarquica.
     */
    void imprimirJerarquico() const {
        if (!nodoRaiz) {
            cout << "(arbol vacio)";
            return;
        }
        imprimirJerarquicoRec(nodoRaiz, 0, cout);
    }

    /**
     * @brief Imprime el arbol por niveles.
     */
    void imprimirPorNiveles() const {
        if (!nodoRaiz) {
            cout << "(arbol vacio)";
            return;
        }

        Cola<NodoN<T>*> colaAux;
        colaAux.encolar(nodoRaiz);
        int nivel = 0;

        while (!colaAux.esVacia()) {
            int tamNivel = colaAux.getLong();
            cout << "Nivel " << nivel << ": ";

            for (int i = 1; i <= tamNivel; ++i) {
                NodoN<T>* ptr = colaAux.getFrente();
                colaAux.desencolar();

                cout << ptr->getInfo();
                if (i < tamNivel) {
                    cout << ", ";
                }

                NodoN<T>* hijo = ptr->getHijoIzq();
                while (hijo) {
                    colaAux.encolar(hijo);
                    hijo = hijo->getHnoDer();
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
     * @brief Retorna la informacion de la raiz.
     * @return Valor en la raiz.
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
    bool esHoja() const { return nodoRaiz != NULL && nodoRaiz->getHijoIzq() == NULL; }

    /**
     * @brief Retorna copias de los subarboles hijos de la raiz.
     * @return Lista con cada hijo como arbol independiente.
     */
    Lista<ArbolN<T> > getHijos() const {
        Lista<ArbolN<T> > result;
        if (!nodoRaiz) {
            return result;
        }

        NodoN<T>* hijo = nodoRaiz->getHijoIzq();
        while (hijo) {
            ArbolN<T> sub;
            sub.nodoRaiz = copiarSubarbol(hijo);
            sub.peso = contarNodos(sub.nodoRaiz);
            result.insertar(sub, result.getLong() + 1);
            hijo = hijo->getHnoDer();
        }

        return result;
    }

    /** @brief Busca un nodo por valor y retorna su puntero interno. */
    NodoN<T>* buscarNodo(const T& valor) const { return buscarNodoRec(nodoRaiz, valor); }

    /** @brief Retorna el puntero al padre de un valor. */
    NodoN<T>* getPadreNodo(const T& valor) const { return getPadreRec(nodoRaiz, valor); }

    /** @brief Recorrido preorden. */
    Lista<T> preOrden() const {
        Lista<T> result;
        preOrden(nodoRaiz, result);
        return result;
    }

    /** @brief Recorrido inorden para representacion N-aria usada en clase. */
    Lista<T> inOrden() const {
        Lista<T> result;
        inOrden(nodoRaiz, result);
        return result;
    }

    /** @brief Recorrido postorden. */
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

        Cola<NodoN<T>*> colaAux;
        colaAux.encolar(nodoRaiz);

        while (!colaAux.esVacia()) {
            NodoN<T>* ptr = colaAux.getFrente();
            colaAux.desencolar();
            result.insertar(ptr->getInfo(), result.getLong() + 1);

            NodoN<T>* hijo = ptr->getHijoIzq();
            while (hijo) {
                colaAux.encolar(hijo);
                hijo = hijo->getHnoDer();
            }
        }

        return result;
    }

    /**
     * @brief Retorna las hojas del arbol.
     * @return Lista con valores hoja.
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
     * @brief Inserta e como hijo de padre.
     *
     * Si el arbol esta vacio, e se inserta como raiz.
     *
     * @param padre Valor del padre.
     * @param e Valor a insertar.
     * @throw out_of_range Si padre no existe.
     */
    void insertarNodo(const T& padre, const T& e) {
        if (!nodoRaiz) {
            nodoRaiz = new NodoN<T>(e);
            peso = 1;
            return;
        }

        NodoN<T>* ptrPadre = buscarNodoRec(nodoRaiz, padre);
        if (!ptrPadre) {
            throw out_of_range("Padre no encontrado");
        }

        NodoN<T>* nuevo = new NodoN<T>(e);
        NodoN<T>* primerHijo = ptrPadre->getHijoIzq();
        if (!primerHijo) {
            ptrPadre->setHijoIzq(nuevo);
        } else {
            NodoN<T>* hijo = primerHijo;
            while (hijo->getHnoDer()) {
                hijo = hijo->getHnoDer();
            }
            hijo->setHnoDer(nuevo);
        }

        ++peso;
    }

    /**
     * @brief Elimina e si es hijo directo de padre (eliminando su subarbol).
     * @param padre Valor del padre.
     * @param e Valor del hijo a remover.
     */
    void eliminarNodo(const T& padre, const T& e) {
        if (!nodoRaiz) {
            return;
        }

        NodoN<T>* ptrPadre = buscarNodoRec(nodoRaiz, padre);
        if (!ptrPadre || !ptrPadre->getHijoIzq()) {
            return;
        }

        NodoN<T>* primerHijo = ptrPadre->getHijoIzq();
        if (primerHijo->getInfo() == e) {
            NodoN<T>* borrar = primerHijo;
            ptrPadre->setHijoIzq(borrar->getHnoDer());
            borrar->setHnoDer(NULL);

            int borrados = destruirSubarbol(borrar);
            peso -= borrados;
            if (peso < 0) {
                peso = 0;
            }
            return;
        }

        NodoN<T>* prev = primerHijo;
        NodoN<T>* cur = prev->getHnoDer();

        while (cur) {
            if (cur->getInfo() == e) {
                NodoN<T>* sig = cur->getHnoDer();
                cur->setHnoDer(NULL);
                int borrados = destruirSubarbol(cur);
                prev->setHnoDer(sig);

                peso -= borrados;
                if (peso < 0) {
                    peso = 0;
                }
                return;
            }
            prev = cur;
            cur = cur->getHnoDer();
        }
    }

    /**
     * @brief Suma de nodos internos por nivel (sin extremos de cada nivel).
     * @return Suma total interna.
     */
    int sumaInterna() const {
        if (!nodoRaiz) {
            return 0;
        }

        Cola<NodoN<T>*> colaAux;
        colaAux.encolar(nodoRaiz);
        int result = 0;

        while (!colaAux.esVacia()) {
            int tamNivel = colaAux.getLong();
            int sumaNivel = 0;
            int primero = 0;
            int ultimo = 0;

            for (int i = 1; i <= tamNivel; ++i) {
                NodoN<T>* ptr = colaAux.getFrente();
                colaAux.desencolar();

                int valor = static_cast<int>(ptr->getInfo());
                sumaNivel += valor;

                if (i == 1) {
                    primero = valor;
                }
                if (i == tamNivel) {
                    ultimo = valor;
                }

                NodoN<T>* hijo = ptr->getHijoIzq();
                while (hijo) {
                    colaAux.encolar(hijo);
                    hijo = hijo->getHnoDer();
                }
            }

            if (tamNivel >= 3) {
                result += (sumaNivel - primero - ultimo);
            }
        }

        return result;
    }

    /**
     * @brief Camino entre dos nodos n y m (incluyendolos).
     * @param n Nodo origen.
     * @param m Nodo destino.
     * @return Lista con el camino n -> ... -> m.
     */
    Lista<T> camino(const T& n, const T& m) const {
        Lista<T> result;
        vector<NodoN<T>*> rutaN;
        vector<NodoN<T>*> rutaM;

        bool foundN = buscarRutaRec(nodoRaiz, n, rutaN);
        bool foundM = buscarRutaRec(nodoRaiz, m, rutaM);

        if (!foundN || !foundM) {
            return result;
        }

        int i = 0;
        int minLen = (rutaN.size() < rutaM.size()) ? static_cast<int>(rutaN.size()) : static_cast<int>(rutaM.size());
        while (i < minLen && rutaN[i] == rutaM[i]) {
            ++i;
        }

        int idxAncestro = i - 1;
        if (idxAncestro < 0) {
            return result;
        }

        for (int j = static_cast<int>(rutaN.size()) - 1; j >= idxAncestro; --j) {
            result.insertar(rutaN[j]->getInfo(), result.getLong() + 1);
        }

        for (int j = idxAncestro + 1; j < static_cast<int>(rutaM.size()); ++j) {
            result.insertar(rutaM[j]->getInfo(), result.getLong() + 1);
        }

        return result;
    }

    /**
     * @brief Retorna los primos de un nodo e.
     * @param e Nodo objetivo.
     * @return Lista de primos.
     */
    Lista<T> getPrimos(const T& e) const {
        Lista<T> result;

        NodoN<T>* padre = getPadreRec(nodoRaiz, e);
        if (!padre) {
            return result;
        }

        NodoN<T>* abuelo = getPadreRec(nodoRaiz, padre->getInfo());
        if (!abuelo) {
            return result;
        }

        NodoN<T>* tio = abuelo->getHijoIzq();
        while (tio) {
            if (tio != padre) {
                NodoN<T>* primo = tio->getHijoIzq();
                while (primo) {
                    result.insertar(primo->getInfo(), result.getLong() + 1);
                    primo = primo->getHnoDer();
                }
            }
            tio = tio->getHnoDer();
        }

        return result;
    }

    /**
     * @brief Nivel con suma maxima.
     * @return Lista de valores del nivel ganador.
     */
    Lista<int> getMaxLevel() const {
        Lista<int> result;
        if (!nodoRaiz) {
            return result;
        }

        Cola<NodoN<T>*> colaAux;
        colaAux.encolar(nodoRaiz);

        int maxSuma = INT_MIN;

        while (!colaAux.esVacia()) {
            int tamNivel = colaAux.getLong();
            int sumaNivel = 0;
            Lista<int> nivelAux;

            for (int i = 1; i <= tamNivel; ++i) {
                NodoN<T>* ptr = colaAux.getFrente();
                colaAux.desencolar();

                int valor = static_cast<int>(ptr->getInfo());
                sumaNivel += valor;
                nivelAux.insertar(valor, nivelAux.getLong() + 1);

                NodoN<T>* hijo = ptr->getHijoIzq();
                while (hijo) {
                    colaAux.encolar(hijo);
                    hijo = hijo->getHnoDer();
                }
            }

            if (sumaNivel >= maxSuma) {
                maxSuma = sumaNivel;
                result = nivelAux;
            }
        }

        return result;
    }

    /**
     * @brief Suma de elementos por cada nivel de 0 a N.
     * @return Lista de sumas por nivel.
     */
    Lista<int> getLevelsSuml() const {
        Lista<int> result;
        if (!nodoRaiz) {
            return result;
        }

        Cola<NodoN<T>*> colaAux;
        colaAux.encolar(nodoRaiz);

        while (!colaAux.esVacia()) {
            int tamNivel = colaAux.getLong();
            int sumaNivel = 0;

            for (int i = 1; i <= tamNivel; ++i) {
                NodoN<T>* ptr = colaAux.getFrente();
                colaAux.desencolar();

                sumaNivel += static_cast<int>(ptr->getInfo());

                NodoN<T>* hijo = ptr->getHijoIzq();
                while (hijo) {
                    colaAux.encolar(hijo);
                    hijo = hijo->getHnoDer();
                }
            }

            result.insertar(sumaNivel, result.getLong() + 1);
        }

        return result;
    }

    /**
     * @brief Nivel con promedio maximo.
     * @return Lista de elementos del nivel con mayor promedio.
     */
    Lista<int> getLevelWithMaxAverage() const {
        Lista<int> result;
        if (!nodoRaiz) {
            return result;
        }

        Cola<NodoN<T>*> colaAux;
        colaAux.encolar(nodoRaiz);

        double maxProm = -1e100;

        while (!colaAux.esVacia()) {
            int tamNivel = colaAux.getLong();
            int sumaNivel = 0;
            Lista<int> nivelAux;

            for (int i = 1; i <= tamNivel; ++i) {
                NodoN<T>* ptr = colaAux.getFrente();
                colaAux.desencolar();

                int valor = static_cast<int>(ptr->getInfo());
                sumaNivel += valor;
                nivelAux.insertar(valor, nivelAux.getLong() + 1);

                NodoN<T>* hijo = ptr->getHijoIzq();
                while (hijo) {
                    colaAux.encolar(hijo);
                    hijo = hijo->getHnoDer();
                }
            }

            double prom = static_cast<double>(sumaNivel) / static_cast<double>(tamNivel);
            if (prom > maxProm) {
                maxProm = prom;
                result = nivelAux;
            }
        }

        return result;
    }

    /**
     * @brief Recorrido por niveles en zigzag.
     * @return Lista de recorrido zigzag.
     */
    Lista<int> Zigzag() const {
        Lista<int> result;
        if (!nodoRaiz) {
            return result;
        }

        Cola<NodoN<T>*> colaAux;
        colaAux.encolar(nodoRaiz);
        bool izqDer = true;

        while (!colaAux.esVacia()) {
            int tamNivel = colaAux.getLong();
            vector<int> nivel;
            nivel.reserve(static_cast<size_t>(tamNivel));

            for (int i = 1; i <= tamNivel; ++i) {
                NodoN<T>* ptr = colaAux.getFrente();
                colaAux.desencolar();

                nivel.push_back(static_cast<int>(ptr->getInfo()));

                NodoN<T>* hijo = ptr->getHijoIzq();
                while (hijo) {
                    colaAux.encolar(hijo);
                    hijo = hijo->getHnoDer();
                }
            }

            if (izqDer) {
                for (size_t i = 0; i < nivel.size(); ++i) {
                    result.insertar(nivel[i], result.getLong() + 1);
                }
            } else {
                for (int i = static_cast<int>(nivel.size()) - 1; i >= 0; --i) {
                    result.insertar(nivel[static_cast<size_t>(i)], result.getLong() + 1);
                }
            }

            izqDer = !izqDer;
        }

        return result;
    }

    /**
     * @brief Retorna la princesa accesible mas cercana a la raiz.
     * @return Nombre de princesa o cadena vacia si no existe.
     */
    string princesaMasCercana() const {
        if (!nodoRaiz) {
            return "";
        }

        Cola<NodoN<T>*> colaAux;
        colaAux.encolar(nodoRaiz);

        while (!colaAux.esVacia()) {
            NodoN<T>* ptr = colaAux.getFrente();
            colaAux.desencolar();

            if (ptr->getInfo().esDragon()) {
                continue;
            }

            if (ptr->getInfo().esPrincesa()) {
                return ptr->getInfo().getNombre();
            }

            NodoN<T>* hijo = ptr->getHijoIzq();
            while (hijo) {
                colaAux.encolar(hijo);
                hijo = hijo->getHnoDer();
            }
        }

        return "";
    }
};

#endif
