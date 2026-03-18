#ifndef NODO_HPP
#define NODO_HPP

#include <cstddef>

using namespace std;

/**
 * @brief Nodo simple para estructuras enlazadas.
 * @tparam T Tipo de dato almacenado.
 */
template <typename T>
class Nodo {
private:
    T info;
    Nodo<T>* next;

public:
    /**
     * @brief Construye un nodo.
     * @param value Valor a almacenar.
     * @param nextNode Puntero al siguiente nodo.
     */
    Nodo(const T& value, Nodo<T>* nextNode = NULL) : info(value), next(nextNode) {}

    /**
     * @brief Retorna referencia modificable al valor almacenado.
     * @return Referencia al valor interno.
     */
    T& getInfo() { return info; }

    /**
     * @brief Retorna referencia constante al valor almacenado.
     * @return Referencia constante al valor interno.
     */
    const T& getInfo() const { return info; }

    /**
     * @brief Actualiza el valor almacenado.
     * @param value Nuevo valor.
     */
    void setInfo(const T& value) { info = value; }

    /**
     * @brief Retorna el puntero al siguiente nodo.
     * @return Puntero al siguiente nodo o NULL.
     */
    Nodo<T>* getNext() const { return next; }

    /**
     * @brief Actualiza el puntero al siguiente nodo.
     * @param nextNode Nuevo siguiente nodo.
     */
    void setNext(Nodo<T>* nextNode) { next = nextNode; }
};

#endif
