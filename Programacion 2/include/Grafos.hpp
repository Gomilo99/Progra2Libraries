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
        NodoVertice<T> *infoV;
        NodoArco *nextA;
        float peso;
    public:
        explicit NodoArco() : infoV(NULL), nextA(NULL), peso(0) {}
        explicit NodoArco(NodoVertice<T> *value, NodoArco<T> *next, float weight) :
        infoV(value), nextA(next), peso(weight) {}

        // getters
        NodoVertice<T>* getVertice() const { return infoV; }
        NodoArco<T>* getNextArco() const { return nextA; }
        float& getPeso() const { return peso; }

        // setters
        void setVertice(NodoVertice *verticeNew){ this->infoV = verticeNew; }
        void setNextArco(NodoArco *nextArcoNew){ this->nextA = nextArcoNew; }
        void setPeso(float pesoNew){ this->peso = pesoNew; }
};

template <typename T>
class NodoVertice{
    private:
        // Attributes
        T info;
        NodoVertice<T> *next;
        NodoArco<T> *arcosHead;
        int: nSucesores;
    public:
        NodoVertice(T newInfo, NodoVertice<T> *nextV, NodoArco<T> *arcoW) : info(newInfo),
        next(nextV), arcosHead(arcoW) {
            if(arcosHead){
                this->nSucesores = 1;
            }else{
                this->nSucesores = 0;
            }
        }

        // Getters
        T getInfo() { return this->info; }
        NodoVertice* getNextVertice(){ return this->next; }
        NodoArco* getArcoHead(){ return this->arcosHead; }


        // Setters
        void setInfo(T infoNew){ this->info = infoNew; }
        void setNextVertice(NodoVertice *verticeNew){ this->next = verticeNew; }
        void setArcosHead(NodoArco *arcosHeadNew){ this->arcosHead = arcosHeadNew; }

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
        // Constructores
        Grafo() : verticeHead(NULL), nVertices(0), nArcos(0), esDirigido(false) {}
        Grafo(T newV, T newW, int peso = 0) {
            NodoVertice<T> *nuevo = new NodoVertice<T>(newV);
            this->verticeHead = nuevo;
            nuevo = new NodoVertice<T>(newW);
            this->verticeHead->setNext(nuevo);
        }
        // Getters
        T getVerticeHead(){ return this->verticeHead->getInfo() }
        int getNNodos(){ return this->nVertices }
        int getNArcos(){ return this->nArcos }
        bool esDirigido(){ return this->esDirigido }

        // Setters
        void setVerticeHead(T verticeHeadNew){
            this->verticeHead = new NodoVertice<T>(verticeHeadNew);
            this->nVertices = 1;
            this->nArcos = 
        }
};
#endif