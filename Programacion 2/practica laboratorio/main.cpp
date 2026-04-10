#include <iostream>              // Incluyo la librería para poder usar entrada y salida estándar
#include <vector>                // Incluyo la librería para usar vectores dinámicos
#include "arbolN.hpp"            // Incluyo mi librería que define ArbolN y NodoAN

using namespace std;             // Uso el espacio de nombres estándar para no escribir std:: en todo

// Incluyo los prototipos de las funciones que voy a implementar
int calcularMejorSuma(NodoAN<int> *nodo, bool incluirPadre); // Declaro la función que calcula la mejor suma independiente
int contarHojasNivelPar(NodoAN<int> *nodo, int nivel);       // Declaro la función que cuenta hojas en niveles pares
int contarHojasNivelImpar(NodoAN<int> *nodo, int nivel);     // Declaro la función que cuenta hojas en niveles impares

int main() {
    int casos;                   // Variable para guardar el número de casos de prueba
    cin >> casos;                 // Leo cuántos casos voy a procesar

    for (int c = 0; c < casos; c++) { // Recorro cada caso de prueba
        int cantidadNodos;        // Variable para guardar cuántos nodos tiene el árbol
        cin >> cantidadNodos;     // Leo la cantidad de nodos

        vector<NodoAN<int>*> nodos(cantidadNodos + 1, nullptr); // Creo un vector para guardar punteros a cada nodo

        // Creo cada nodo y les asigno su valor
        for (int i = 1; i <= cantidadNodos; i++) { // Recorro cada posición
            nodos[i] = new NodoAN<int>();          // Reservo memoria para un nuevo nodo
            nodos[i]->construct();                 // Inicializo el nodo 
            int valor;                             // Variable para guardar el valor del nodo
            cin >> valor;                          // Leo el valor desde la entrada
            nodos[i]->setInfo(valor);              // Asigno el valor al nodo
        }

        // Leo relaciones padre-hijo y enlazo
        for (int i = 0; i < cantidadNodos - 1; i++) { // Recorro cada relación
            int padre, hijo;                         // Variables para guardar los índices de padre e hijo
            cin >> padre >> hijo;                    // Leo la relación

            if (nodos[padre]->getHijoIzquierdo() == nullptr) { // Si el padre no tiene hijo izquierdo
                nodos[padre]->setHijoIzquierdo(nodos[hijo]);   // Lo pongo como hijo izquierdo
            } else {                                           // Si ya tiene hijo izquierdo
                NodoAN<int> *hermano = nodos[padre]->getHijoIzquierdo(); // Empiezo desde el primer hijo
                while (hermano->getHermanoDerecho() != nullptr) {        // Recorro hasta el último hermano derecho
                    hermano = hermano->getHermanoDerecho();              // Avanzo al siguiente hermano
                }
                hermano->setHermanoDerecho(nodos[hijo]);                 // Enlazo el nuevo hijo como hermano derecho del último
            }
        }

        // La raíz es el nodo 1
        NodoAN<int> *raiz = nodos[1]; // Guardo el puntero al nodo raíz

        int mejorSuma = calcularMejorSuma(raiz, false); // Llamo a la función para calcular la mejor suma, indicando que el padre no está incluido

        // Cuento las hojas pares e impares
        int hojasPar = contarHojasNivelPar(raiz, 0);    // Cuento las hojas en niveles pares
        int hojasImpar = contarHojasNivelImpar(raiz, 0);// Cuento las hojas en niveles impares

        int balance = hojasPar - hojasImpar;            // Calculo el balance entre las hojas pares e impares

        cout << mejorSuma * balance << endl;            // Imprimo el resultado multiplicando mejor suma por balance

        // Libero la memoria
        for (int i = 1; i <= cantidadNodos; i++) {      // Recorro todos los nodos
            delete nodos[i];                            // Libero la memoria reservada para cada nodo
        }
    }

    return 0; // Fin del programa
}

// Implemento las funciones declaradas anteriormente

int calcularMejorSuma(NodoAN<int> *nodo, bool incluirPadre) {
    if (nodo == nullptr) { // Si el nodo es nulo, no hay nada que sumar
        return 0;
    }

    int suma = 0; // Variable para acumular la suma

    if (incluirPadre) { // Si el padre fue incluido, no puedo incluir este nodo
        NodoAN<int> *hijo = nodo->getHijoIzquierdo(); // Empiezo por el hijo izquierdo
        while (hijo != nullptr) {                     // Recorro todos los hijos
            suma += calcularMejorSuma(hijo, false);   // Llamo recursivamente indicando que este nodo no se incluye
            hijo = hijo->getHermanoDerecho();         // Paso al siguiente hermano
        }
    } else { // Si el padre no fue incluido, puedo elegir incluir o no este nodo
        int sumaIncluyendo = nodo->getInfo(); // Si lo incluyo, empiezo con su valor
        int sumaExcluyendo = 0;               // Si no lo incluyo, empiezo en 0

        NodoAN<int> *hijo = nodo->getHijoIzquierdo(); // Empiezo por el hijo izquierdo
        while (hijo != nullptr) {                     // Recorro todos los hijos
            sumaIncluyendo += calcularMejorSuma(hijo, true);  // Si incluyo este nodo, los hijos no se incluyen
            sumaExcluyendo += calcularMejorSuma(hijo, false); // Si no incluyo este nodo, puedo elegir lo mejor para cada hijo
            hijo = hijo->getHermanoDerecho();                 // Paso al siguiente hermano
        }

        if (sumaIncluyendo > sumaExcluyendo) { // Elijo la mejor opción
            suma = sumaIncluyendo;
        } else {
            suma = sumaExcluyendo;
        }
    }

    return suma; // Devuelvo la mejor suma calculada
}

int contarHojasNivelPar(NodoAN<int> *nodo, int nivel) {
    if (nodo == nullptr) { // Si el nodo es nulo, no hay hojas
        return 0;
    }

    if (nodo->getHijoIzquierdo() == nullptr && nivel % 2 == 0) { // Si es hoja y está en nivel par
        return 1; // Cuento una hoja
    }

    int total = 0; // Acumulador de hojas
    NodoAN<int> *hijo = nodo->getHijoIzquierdo(); // Empiezo por el hijo izquierdo
    while (hijo != nullptr) {                     // Recorro todos los hijos
        total += contarHojasNivelPar(hijo, nivel + 1); // Llamo recursivamente aumentando el nivel
        hijo = hijo->getHermanoDerecho();              // Paso al siguiente hermano
    }

    return total; // Devuelvo el total de hojas pares encontradas
}

int contarHojasNivelImpar(NodoAN<int> *nodo, int nivel) {
    if (nodo == nullptr) { // Si el nodo es nulo, no hay hojas
        return 0;
    }

    if (nodo->getHijoIzquierdo() == nullptr && nivel % 2 != 0) { // Si es hoja y está en nivel impar
        return 1; // Cuento una hoja
    }

    int total = 0; // Acumulador de hojas
    NodoAN<int> *hijo = nodo->getHijoIzquierdo(); // Empiezo por el hijo izquierdo
    while (hijo != nullptr) {                     // Recorro todos los hijos
        total += contarHojasNivelImpar(hijo, nivel + 1); // Llamo recursivamente aumentando el nivel
        hijo = hijo->getHermanoDerecho();                // Paso al siguiente hermano
    }

    return total; // Devuelvo el total de hojas impares encontradas
}
