#ifndef COLA_HPP
#define COLA_HPP

#include <iostream>
#include <stdexcept>
#include "Nodo.hpp"

template <typename T>
class Cola {
private:
    Nodo<T>* frente;
    Nodo<T>* ultimo;
    int length;

public:
    Cola() : frente(nullptr), ultimo(nullptr), length(0) {}

    Cola(const Cola<T>& other) : frente(nullptr), ultimo(nullptr), length(0) {
        Nodo<T>* current = other.frente;
        while (current) {
            encolar(current->getInfo());
            current = current->getNext();
        }
    }

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

    ~Cola() {
        vaciar();
    }

    T getFrente() const {
        if (esVacia()) {
            throw std::out_of_range("Cola vacia");
        }
        return frente->getInfo();
    }

    T getUltimo() const {
        if (esVacia()) {
            throw std::out_of_range("Cola vacia");
        }
        return ultimo->getInfo();
    }

    int getLong() const {
        return length;
    }

    bool esVacia() const {
        return length == 0;
    }

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

    void desencolar() {
        if (esVacia()) {
            throw std::out_of_range("Cola vacia");
        }

        Nodo<T>* toDelete = frente;
        frente = frente->getNext();
        delete toDelete;
        --length;

        if (length == 0) {
            ultimo = nullptr;
        }
    }

    void vaciar() {
        while (!esVacia()) {
            Nodo<T>* toDelete = frente;
            frente = frente->getNext();
            delete toDelete;
            --length;
        }
        ultimo = nullptr;
    }

    void destruir() {
        vaciar();
    }

    void print(std::ostream& os = std::cout) const {
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
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Cola<T>& queue) {
    queue.print(os);
    return os;
}

#endif
