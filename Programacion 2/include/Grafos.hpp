#ifndef ARBOLN_HPP
#define ARBOLN_HPP

/*
Librería basada en las clases dadas en Algoritmos 2

*/

#include <list>
#include <vector>
#include <iostream>

using namespace std;
template <typename T>

class NodoArco{
    private:
        // Attributes
        NodoVertice<T> *info;
        NodoArco *next;
        float peso;
        // 
    public:
        explicit NodoArco() : info(NULL), next(NULL), peso(0) {}
        explicit NodoArco(NodoVertice<T> *value, NodoArco<T> *next, float weight) :
        info(value), next(next), peso(weight) {}

        // getters
        NodoVertice<T>* getInfo() const { return info; }
        NodoArco<T>* getNext() const { return next; }
        float& getPeso() const { return peso; }

        // setters

};

template <typename T>
class NodoVertice{
    private:
        // Attributes
        T info;
        NodoVertice<T> *next;
        NodoArco<T> *AdyListHead;
    public:

};

template <typename T>
class Grafo{
    private:
        // Attributes
        NodoVertice<T> *verticeHead;
        int nVertices, nArcos;
        bool esDirigido;

        // Methods
    public:
        

};
#endif