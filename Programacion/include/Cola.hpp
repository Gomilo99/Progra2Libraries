#ifndef COLA_HPP
#define COLA_HPP

#include <iostream>
#include <stdexcept>
#include "Nodo.hpp"

using namespace std;

/**
 * @brief Cola FIFO implementada con nodos enlazados.
 * @tparam T Tipo de dato almacenado.
 */
template <typename T>
class Cola {
private:
    Nodo<T>* frente;
    Nodo<T>* ultimo;
    int length;

public:
    /**
     * @brief Construye una cola vacia.
     */
    Cola() : frente(NULL), ultimo(NULL), length(0) {}

    /**
     * @brief Constructor de copia.
     * @param other Cola origen.
     */
    Cola(const Cola<T>& other) : frente(NULL), ultimo(NULL), length(0) {
        Nodo<T>* current = other.frente;
        while (current) {
            encolar(current->getInfo());
            current = current->getNext();
        }
    }

    /**
     * @brief Operador de asignacion por copia.
     * @param other Cola origen.
     * @return Referencia a esta cola.
     */
    Cola<T>& operator=(const Cola<T>& other) {
        if (this == &other) {
            return *this;
        }
        vaciar();
        Nodo<T>* current = other.frente;
        while (current) {
            encolar(current->getInfo());
            current = current->getNext();
        }
        return *this;
    }

    /**
     * @brief Destructor.
     */
    ~Cola() {
        vaciar();
    }

    /**
     * @brief Obtiene el primer elemento.
     * @return Elemento en el frente.
     * @throw out_of_range Si la cola esta vacia.
     */
    T getFrente() const {
        if (esVacia()) {
            throw out_of_range("Cola vacia");
        }
        return frente->getInfo();
    }

    /**
     * @brief Obtiene el ultimo elemento.
     * @return Elemento al final de la cola.
     * @throw out_of_range Si la cola esta vacia.
     */
    T getUltimo() const {
        if (esVacia()) {
            throw out_of_range("Cola vacia");
        }
        return ultimo->getInfo();
    }

    /**
     * @brief Retorna la cantidad de elementos.
     * @return Longitud actual.
     */
    int getLong() const {
        return length;
    }

    /**
     * @brief Indica si la cola no tiene elementos.
     * @return true si esta vacia, false en otro caso.
     */
    bool esVacia() const {
        return length == 0;
    }

    /**
     * @brief Inserta un elemento al final de la cola.
     * @param element Elemento a insertar.
     */
    void encolar(const T& element) {
        Nodo<T>* newNode = new Nodo<T>(element);
        if (length == 0) {
            frente = newNode;
            ultimo = newNode;
        } else {
            ultimo->setNext(newNode);
            ultimo = newNode;
        }
        ++length;
    }

    /**
     * @brief Elimina el elemento del frente.
     * @throw out_of_range Si la cola esta vacia.
     */
    void desencolar() {
        if (esVacia()) {
            throw out_of_range("Cola vacia");
        }

        Nodo<T>* toDelete = frente;
        frente = frente->getNext();
        delete toDelete;
        --length;

        if (length == 0) {
            ultimo = NULL;
        }
    }

    /**
     * @brief Elimina todos los elementos de la cola.
     */
    void vaciar() {
        while (!esVacia()) {
            Nodo<T>* toDelete = frente;
            frente = frente->getNext();
            delete toDelete;
            --length;
        }
        ultimo = NULL;
    }

    /**
     * @brief Alias de vaciar().
     */
    void destruir() {
        vaciar();
    }

    /**
     * @brief Imprime la cola con formato [a, b, c].
     * @param os Flujo de salida.
     */
    void print(ostream& os = cout) const {
        os << "[";
        Nodo<T>* current = frente;
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
     * @brief Alias de print().
     * @param os Flujo de salida.
     */
    void printCola(ostream& os = cout) const {
        print(os);
    }
};

/**
 * @brief Sobrecarga del operador << para Cola.
 * @tparam T Tipo de dato almacenado.
 * @param os Flujo de salida.
 * @param queue Cola a imprimir.
 * @return Flujo de salida.
 */
template <typename T>
ostream& operator<<(ostream& os, const Cola<T>& queue) {
    queue.print(os);
    return os;
}

#endif
