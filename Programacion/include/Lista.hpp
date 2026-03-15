#ifndef LISTA_HPP
#define LISTA_HPP

#include <iostream>
#include <stdexcept>
#include "Nodo.hpp"

using namespace std;

/**
 * @brief Lista simplemente enlazada generica.
 * @tparam T Tipo de dato almacenado.
 */
template <typename T>
class Lista {
private:
    Nodo<T>* head;
    Nodo<T>* tail;
    int length;

public:
    /**
     * @brief Construye una lista vacia.
     */
    Lista() : head(NULL), tail(NULL), length(0) {}

    /**
     * @brief Constructor de copia.
     * @param other Lista origen.
     */
    Lista(const Lista<T>& other) : head(NULL), tail(NULL), length(0) {
        Nodo<T> *current = other.head;
        while (current) {
            insertar(current->getInfo(), length + 1);
            current = current->getNext();
        }
    }

    /**
     * @brief Construye una lista con un elemento inicial.
     * @param element Primer elemento.
     */
    Lista(const T&element) : head(new Nodo<T>(element)), tail(head), length(1) {}

    /**
     * @brief Operador de asignacion por copia.
     * @param other Lista origen.
     * @return Referencia a esta lista.
     */
    Lista<T>& operator=(const Lista<T>& other) {
        if (this == &other) {
            return *this;
        }
        vaciar();
        Nodo<T> *current = other.head;
        while (current) {
            insertar(current->getInfo(), length + 1);
            current = current->getNext();
        }
        return *this;
    }

    /**
     * @brief Destructor.
     */
    ~Lista() {
        vaciar();
    }

    /**
     * @brief Retorna la longitud actual.
     * @return Cantidad de elementos.
     */
    int getLong() const {
        return length;
    }

    /**
     * @brief Indica si la lista esta vacia.
     * @return true si no tiene elementos.
     */
    bool esVacia() const {
        return length == 0;
    }

    /**
     * @brief Consulta un elemento por posicion (1..n).
     * @param pos Posicion 1-based.
     * @return Copia del elemento en pos.
     * @throw out_of_range Si pos es invalida.
     */
    T consultar(int pos) const {
        if (pos < 1 || pos > length) {
            throw out_of_range("Posicion invalida en consultar");
        }

        if (pos == 1) {
            return head->getInfo();
        }

        if (pos == length) {
            return tail->getInfo();
        }

        Nodo<T> *current = head;
        for (int i = 1; i < pos; ++i) {
            current = current->getNext();
        }
        return current->getInfo();
    }

    /**
     * @brief Inserta un elemento en una posicion (1..n+1).
     * @param element Elemento a insertar.
     * @param pos Posicion destino 1-based.
     * @throw out_of_range Si pos es invalida.
     */
    void insertar(const T& element, int pos) {
        if (pos < 1 || pos > length + 1) {
            throw out_of_range("Posicion invalida en insertar");
        }

        Nodo<T> *newNode = new Nodo<T>(element);

        if (length == 0) {
            head = newNode;
            tail = newNode;
            length = 1;
            return;
        }

        if (pos == 1) {
            newNode->setNext(head);
            head = newNode;
            ++length;
            return;
        }

        if (pos == length + 1) {
            tail->setNext(newNode);
            tail = newNode;
            ++length;
            return;
        }

        Nodo<T> *prev = head;
        for (int i = 1; i < pos - 1; ++i) {
            prev = prev->getNext();
        }

        newNode->setNext(prev->getNext());
        prev->setNext(newNode);
        ++length;
    }

    /**
     * @brief Elimina el elemento en una posicion (1..n).
     * @param pos Posicion a eliminar.
     * @throw out_of_range Si pos es invalida.
     */
    void eliminar(int pos) {
        if (pos < 1 || pos > length) {
            throw out_of_range("Posicion invalida en eliminar");
        }

        if (length == 1) {
            delete head;
            head = NULL;
            tail = NULL;
            length = 0;
            return;
        }

        if (pos == 1) {
            Nodo<T> *toDelete = head;
            head = head->getNext();
            delete toDelete;
            --length;
            return;
        }

        if (pos == length) {
            Nodo<T> *prev = head;
            while (prev->getNext() != tail) {
                prev = prev->getNext();
            }
            delete tail;
            tail = prev;
            tail->setNext(NULL);
            --length;
            return;
        }

        Nodo<T> *prev = head;
        for (int i = 1; i < pos - 1; ++i) {
            prev = prev->getNext();
        }

        Nodo<T> *toDelete = prev->getNext();
        prev->setNext(toDelete->getNext());
        delete toDelete;
        --length;
    }

    /**
     * @brief Busca la primera ocurrencia de un elemento.
     * @param element Elemento buscado.
     * @return Posicion 1-based o -1 si no existe.
     */
    int buscar(const T& element) const {
        Nodo<T> *current = head;
        int pos = 1;
        while (current) {
            if (current->getInfo() == element) {
                return pos;
            }
            current = current->getNext();
            ++pos;
        }
        return -1;
    }

    /**
     * @brief Invierte el orden de la lista en sitio.
     */
    void invertir() {
        Nodo<T>* prev = NULL;
        Nodo<T>* current = head;
        tail = head;

        while (current) {
            Nodo<T> *nextNode = current->getNext();
            current->setNext(prev);
            prev = current;
            current = nextNode;
        }

        head = prev;
    }

    /**
     * @brief Retorna una copia de la lista.
     * @return Copia completa.
     */
    Lista<T> copiar() const {
        return Lista<T>(*this);
    }

    /**
     * @brief Elimina todos los nodos de la lista.
     */
    void vaciar() {
        Nodo<T>* current = head;
        while (current) {
            Nodo<T>* nextNode = current->getNext();
            delete current;
            current = nextNode;
        }
        head = NULL;
        tail = NULL;
        length = 0;
    }

    /**
     * @brief Concatena esta lista con otra.
     * @param target Lista a anexar.
     * @return Nueva lista con ambos contenidos.
     */
    Lista<T> concatenar(const Lista<T>& target) const {
        Lista<T> result(*this);
        Nodo<T>* current = target.head;
        while (current) {
            result.insertar(current->getInfo(), result.getLong() + 1);
            current = current->getNext();
        }
        return result;
    }

    /**
     * @brief Alias de vaciar().
     */
    void destruir() {
        vaciar();
    }

    /**
     * @brief Intercambia dos posiciones.
     * @param pos1 Primera posicion.
     * @param pos2 Segunda posicion.
     * @throw out_of_range Si alguna posicion es invalida.
     */
    void intercambiar(int pos1, int pos2) {
        if (pos1 < 1 || pos1 > length || pos2 < 1 || pos2 > length) {
            throw out_of_range("Posicion invalida en intercambiar");
        }
        if (pos1 == pos2) {
            return;
        }

        T a = consultar(pos1);
        T b = consultar(pos2);
        modificar(pos1, b);
        modificar(pos2, a);
    }

    /**
     * @brief Reemplaza el valor en una posicion.
     * @param pos Posicion a modificar.
     * @param element Nuevo valor.
     * @throw out_of_range Si pos es invalida.
     */
    void modificar(int pos, const T& element) {
        if (pos < 1 || pos > length) {
            throw out_of_range("Posicion invalida en modificar");
        }

        if (pos == 1) {
            head->setInfo(element);
            return;
        }

        if (pos == length) {
            tail->setInfo(element);
            return;
        }

        Nodo<T>* current = head;
        for (int i = 1; i < pos; ++i) {
            current = current->getNext();
        }
        current->setInfo(element);
    }

    /**
     * @brief Calcula la moda unica de la lista.
     * @return Valor mas frecuente.
     * @throw logic_error Si la lista esta vacia o no hay moda unica.
     */
    T moda() const {
        if (esVacia()) {
            throw logic_error("No se puede calcular la moda de una lista vacia");
        }

        Lista<T> valoresUnicos;
        Lista<int> frecuencias;

        for (int i = 1; i <= length; ++i) {
            T valor = consultar(i);
            int posicion = valoresUnicos.buscar(valor);

            if (posicion == -1) {
                valoresUnicos.insertar(valor, valoresUnicos.getLong() + 1);
                frecuencias.insertar(1, frecuencias.getLong() + 1);
            } else {
                frecuencias.modificar(posicion, frecuencias.consultar(posicion) + 1);
            }
        }

        int maxFrecuencia = 0;
        int posicionModa = -1;
        int cantidadMaximos = 0;

        for (int i = 1; i <= frecuencias.getLong(); ++i) {
            int frecuencia = frecuencias.consultar(i);

            if (frecuencia > maxFrecuencia) {
                maxFrecuencia = frecuencia;
                posicionModa = i;
                cantidadMaximos = 1;
            } else if (frecuencia == maxFrecuencia) {
                ++cantidadMaximos;
            }
        }

        if (maxFrecuencia <= 1 || cantidadMaximos > 1) {
            throw logic_error("No hay moda unica en la lista");
        }

        return valoresUnicos.consultar(posicionModa);
    }

    /**
     * @brief Calcula la mediana de la lista.
     * @return Mediana como double.
     * @throw logic_error Si la lista esta vacia.
     */
    double mediana() const {
        if (esVacia()) {
            throw logic_error("No se puede calcular la mediana de una lista vacia");
        }

        Lista<T> ordenada(*this);

        for (int i = 2; i <= ordenada.getLong(); ++i) {
            T clave = ordenada.consultar(i);
            int j = i - 1;

            while (j >= 1 && ordenada.consultar(j) > clave) {
                ordenada.modificar(j + 1, ordenada.consultar(j));
                --j;
            }

            ordenada.modificar(j + 1, clave);
        }

        int n = ordenada.getLong();
        if (n % 2 == 1) {
            return static_cast<double>(ordenada.consultar((n + 1) / 2));
        }

        double izquierdo = static_cast<double>(ordenada.consultar(n / 2));
        double derecho = static_cast<double>(ordenada.consultar((n / 2) + 1));
        return (izquierdo + derecho) / 2.0;
    }

    /**
     * @brief Imprime la lista como [a, b, c].
     * @param os Flujo de salida.
     */
    void print(ostream& os = cout) const {
        os << "[";
        Nodo<T>* current = head;
        while (current) {
            os << current->getInfo();
            current = current->getNext();
            if (current) {
                os << ", ";
            }
        }
        os << "]";
    }
        /**
         * @brief Reordena dejando impares por indice primero y luego pares por indice.
         */
    void reorderOddAndEven() {
        if (!head || !head->getNext()) {
            return;
        }

        Nodo<T>* odd = head;
        Nodo<T>* even = head->getNext();
        Nodo<T>* firstEven = even;

        while (even && odd) {
            odd->setNext(even->getNext());
            odd = odd->getNext();

            if (odd) {
                even->setNext(odd->getNext());
                even = even->getNext();
            }
        }

        if (odd) {
            odd->setNext(firstEven);
        }

        if (even) {
            tail = even;
        } else {
            Nodo<T>* current = head;
            while (current->getNext()) {
                current = current->getNext();
            }
            tail = current;
        }
    }

    /**
     * @brief Desplaza circularmente a la derecha.
     * @param shift Cantidad de posiciones.
     */
    void rightShift(int shift) {
        if (length <= 1) {
            return;
        }

        int trueShift = shift % length;
        if (trueShift == 0) {
            return;
        }

        tail->setNext(head);
        int splitPos = length - trueShift;
        Nodo<T>* newTail = head;
        for (int i = 1; i < splitPos; ++i) {
            newTail = newTail->getNext();
        }

        head = newTail->getNext();
        newTail->setNext(NULL);
        tail = newTail;
    }

    /**
     * @brief Mezcla sublistas de indices impares y pares, asumiendo orden en ambas.
     * @return Nueva lista parcialmente reordenada.
     */
    Lista<T> partialReorderOddEvenSorted() const {
        Lista<T> result;
        if (!head) {
            return result;
        }

        Nodo<T>* odd = head;
        Nodo<T>* even = head->getNext();

        while (odd && even) {
            if (odd->getInfo() <= even->getInfo()) {
                result.insertar(odd->getInfo(), result.getLong() + 1);
                odd = odd->getNext();
                if (odd) odd = odd->getNext();
            } else {
                result.insertar(even->getInfo(), result.getLong() + 1);
                even = even->getNext();
                if (even) even = even->getNext();
            }
        }

        while (odd) {
            result.insertar(odd->getInfo(), result.getLong() + 1);
            odd = odd->getNext();
            if (odd) odd = odd->getNext();
        }

        while (even) {
            result.insertar(even->getInfo(), result.getLong() + 1);
            even = even->getNext();
            if (even) even = even->getNext();
        }

        return result;
    }

    /**
     * @brief Mezcla dos mitades ordenadas de la lista.
     * @return Nueva lista mezclada.
     */
    Lista<T> partialReorderHalvesSorted() const {
        Lista<T> result;
        if (!head) {
            return result;
        }

        int half = length / 2;
        Nodo<T>* p1 = head;
        Nodo<T>* p2 = head;
        for (int i = 0; i < half; ++i) {
            p2 = p2->getNext();
        }

        while (p1 != p2 && p2) {
            if (p1->getInfo() <= p2->getInfo()) {
                result.insertar(p1->getInfo(), result.getLong() + 1);
                p1 = p1->getNext();
            } else {
                result.insertar(p2->getInfo(), result.getLong() + 1);
                p2 = p2->getNext();
            }
        }

        while (p1 != p2) {
            result.insertar(p1->getInfo(), result.getLong() + 1);
            p1 = p1->getNext();
        }

        while (p2) {
            result.insertar(p2->getInfo(), result.getLong() + 1);
            p2 = p2->getNext();
        }

        return result;
    }

    /**
     * @brief Consulta por referencia constante (1..n).
     * @param pos Posicion 1-based.
     * @return Referencia constante al elemento.
     * @throw out_of_range Si pos es invalida.
     */
    const T& consultarRef(int pos) const {
        if (pos < 1 || pos > length) {
            throw out_of_range("Posicion invalida en consultarRef");
        }
        if (pos == 1) return head->getInfo();
        if (pos == length) return tail->getInfo();

        Nodo<T> *current = head;
        for (int i = 1; i < pos; ++i) {
            current = current->getNext();
        }
        return current->getInfo();
    }

    /**
     * @brief Consulta por referencia modificable (1..n).
     * @param pos Posicion 1-based.
     * @return Referencia modificable al elemento.
     * @throw out_of_range Si pos es invalida.
     */
    T& consultarRef(int pos) {
        if (pos < 1 || pos > length) {
            throw out_of_range("Posicion invalida en consultarRef");
        }
        if (pos == 1) return head->getInfo();
        if (pos == length) return tail->getInfo();

        Nodo<T> *current = head;
        for (int i = 1; i < pos; ++i) {
            current = current->getNext();
        }
        return current->getInfo();
    }
};

/**
 * @brief Sobrecarga del operador << para Lista.
 * @tparam T Tipo de dato almacenado.
 * @param os Flujo de salida.
 * @param list Lista a imprimir.
 * @return Flujo de salida.
 */
template <typename T>
ostream& operator<<(ostream& os, const Lista<T>& list) {
    list.print(os);
    return os;
}

#endif
