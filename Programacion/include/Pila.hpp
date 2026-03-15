#ifndef PILA_HPP
#define PILA_HPP

#include <iostream>
#include <stdexcept>
#include "Nodo.hpp"

using namespace std;

/**
 * @brief Pila LIFO implementada con nodos enlazados.
 * @tparam T Tipo de dato almacenado.
 */
template <typename T>
class Pila {
private:
    Nodo<T>* tope;
    int length;

public:
    /**
     * @brief Construye una pila vacia.
     */
    Pila() : tope(NULL), length(0) {}

    /**
     * @brief Constructor de copia.
     * @param other Pila origen.
     */
    Pila(const Pila<T>& other) : tope(NULL), length(0) {
        if (other.tope == NULL) {
            return;
        }

        int n = other.length;
        T* buffer = new T[n];
        Nodo<T>* current = other.tope;
        int i = n - 1;

        while (current) {
            buffer[i--] = current->getInfo();
            current = current->getNext();
        }

        for (int j = 0; j < n; ++j) {
            apilar(buffer[j]);
        }

        delete[] buffer;
    }

    /**
     * @brief Operador de asignacion por copia.
     * @param other Pila origen.
     * @return Referencia a esta pila.
     */
    Pila<T>& operator=(const Pila<T>& other) {
        if (this == &other) {
            return *this;
        }

        vaciar();

        if (other.tope == NULL) {
            return *this;
        }

        int n = other.length;
        T* buffer = new T[n];
        Nodo<T>* current = other.tope;
        int i = n - 1;

        while (current) {
            buffer[i--] = current->getInfo();
            current = current->getNext();
        }

        for (int j = 0; j < n; ++j) {
            apilar(buffer[j]);
        }

        delete[] buffer;
        return *this;
    }

    /**
     * @brief Destructor.
     */
    ~Pila() {
        vaciar();
    }

    /**
     * @brief Retorna la cantidad de elementos.
     * @return Longitud actual.
     */
    int getLong() const {
        return length;
    }

    /**
     * @brief Obtiene el elemento del tope.
     * @return Elemento del tope.
     * @throw out_of_range Si la pila esta vacia.
     */
    T getTope() const {
        if (esVacia()) {
            throw out_of_range("Pila vacia");
        }
        return tope->getInfo();
    }

    /**
     * @brief Indica si la pila esta vacia.
     * @return true si no hay elementos.
     */
    bool esVacia() const {
        return length == 0;
    }

    /**
     * @brief Inserta un elemento en el tope.
     * @param element Elemento a apilar.
     */
    void apilar(const T& element) {
        Nodo<T>* newNode = new Nodo<T>(element, tope);
        tope = newNode;
        ++length;
    }

    /**
     * @brief Elimina el elemento del tope.
     * @throw out_of_range Si la pila esta vacia.
     */
    void desapilar() {
        if (esVacia()) {
            throw out_of_range("Pila vacia");
        }

        Nodo<T>* toDelete = tope;
        tope = tope->getNext();
        delete toDelete;
        --length;
    }

    /**
     * @brief Elimina todos los elementos de la pila.
     */
    void vaciar() {
        while (!esVacia()) {
            Nodo<T>* toDelete = tope;
            tope = tope->getNext();
            delete toDelete;
            --length;
        }
    }

    /**
     * @brief Alias de vaciar().
     */
    void destruir() {
        vaciar();
    }

    /**
     * @brief Imprime la pila con formato [tope, ...].
     * @param os Flujo de salida.
     */
    void print(ostream& os = cout) const {
        os << "[";
        Nodo<T>* current = tope;
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
    void printPila(ostream& os = cout) const {
        print(os);
    }
};

/**
 * @brief Sobrecarga del operador << para Pila.
 * @tparam T Tipo de dato almacenado.
 * @param os Flujo de salida.
 * @param stack Pila a imprimir.
 * @return Flujo de salida.
 */
template <typename T>
ostream& operator<<(ostream& os, const Pila<T>& stack) {
    stack.print(os);
    return os;
}

#endif
