#ifndef PILA_HPP
#define PILA_HPP

#include <iostream>
#include <stdexcept>
#include "Nodo.hpp"

using namespace std;

template <typename T>
class Pila {
private:
    Nodo<T>* tope;
    int length;

public:
    Pila() : tope(NULL), length(0) {}

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

    ~Pila() {
        vaciar();
    }

    int getLong() const {
        return length;
    }

    T getTope() const {
        if (esVacia()) {
            throw out_of_range("Pila vacia");
        }
        return tope->getInfo();
    }

    bool esVacia() const {
        return length == 0;
    }

    void apilar(const T& element) {
        Nodo<T>* newNode = new Nodo<T>(element, tope);
        tope = newNode;
        ++length;
    }

    void desapilar() {
        if (esVacia()) {
            throw out_of_range("Pila vacia");
        }

        Nodo<T>* toDelete = tope;
        tope = tope->getNext();
        delete toDelete;
        --length;
    }

    void vaciar() {
        while (!esVacia()) {
            Nodo<T>* toDelete = tope;
            tope = tope->getNext();
            delete toDelete;
            --length;
        }
    }

    void destruir() {
        vaciar();
    }

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

    void printPila(ostream& os = cout) const {
        print(os);
    }
};

template <typename T>
ostream& operator<<(ostream& os, const Pila<T>& stack) {
    stack.print(os);
    return os;
}

#endif
