#include <iostream>
#include <vector>
#include "../include/Lista.hpp"
#include "../include/Cola.hpp"
#include "../include/Pila.hpp"

using namespace std;

int main() {
    cout << "==== PRUEBA DE CLASES LPC (C++98) ====\n\n";

    // ==========================
    // PRUEBAS CLASE LISTA
    // ==========================
    Lista<int> lista;
    lista.insertar(10, 1);
    lista.insertar(20, 2);
    lista.insertar(15, 2);
    cout << "Lista tras insertar: ";
    lista.printLista();
    cout << "  // Esperada: [10, 15, 20]\n";

    cout << "consultar(2): " << lista.consultar(2) << "  // Esperada: 15\n";
    cout << "buscar(20): " << lista.buscar(20) << "  // Esperada: 3\n";

    lista.modificar(2, 99);
    cout << "Lista tras modificar pos2->99: ";
    lista.printLista();
    cout << "  // Esperada: [10, 99, 20]\n";

    lista.intercambiar(1, 3);
    cout << "Lista tras intercambiar(1,3): ";
    lista.printLista();
    cout << "  // Esperada: [20, 99, 10]\n";

    lista.eliminar(2);
    cout << "Lista tras eliminar(2): ";
    lista.printLista();
    cout << "  // Esperada: [20, 10]\n";

    lista.invertir();
    cout << "Lista tras invertir: ";
    lista.printLista();
    cout << "  // Esperada: [10, 20]\n";

    Lista<int> copia = lista.copiar();
    cout << "Copia de lista: ";
    copia.printLista();
    cout << "  // Esperada: [10, 20]\n";

    Lista<int> otra;
    otra.insertar(30, 1);
    otra.insertar(40, 2);
    Lista<int> concat = lista.concatenar(otra);
    cout << "Concatenar [10,20] + [30,40]: ";
    concat.printLista();
    cout << "  // Esperada: [10, 20, 30, 40]\n";

    lista.vaciar();
    cout << "Lista tras vaciar, esVacia(): " << (lista.esVacia() ? "true" : "false") << "  // Esperada: true\n\n";

    // ==========================
    // PRUEBAS CLASE COLA
    // ==========================
    Cola<int> cola;
    cola.encolar(1);
    cola.encolar(2);
    cola.encolar(3);
    cout << "Cola tras encolar: ";
    cola.printCola();
    cout << "  // Esperada: [1, 2, 3]\n";
    cout << "Frente: " << cola.getFrente() << "  // Esperada: 1\n";
    cout << "Ultimo: " << cola.getUltimo() << "  // Esperada: 3\n";

    cola.desencolar();
    cout << "Cola tras desencolar: ";
    cola.printCola();
    cout << "  // Esperada: [2, 3]\n";

    cola.vaciar();
    cout << "Cola vacia? " << (cola.esVacia() ? "true" : "false") << "  // Esperada: true\n\n";

    // ==========================
    // PRUEBAS CLASE PILA
    // ==========================
    Pila<int> pila;
    pila.apilar(5);
    pila.apilar(6);
    pila.apilar(7);
    cout << "Pila tras apilar: ";
    pila.printPila();
    cout << "  // Esperada: [7, 6, 5]\n";
    cout << "Tope: " << pila.getTope() << "  // Esperada: 7\n";

    pila.desapilar();
    cout << "Pila tras desapilar: ";
    pila.printPila();
    cout << "  // Esperada: [6, 5]\n";

    pila.vaciar();
    cout << "Pila vacia? " << (pila.esVacia() ? "true" : "false") << "  // Esperada: true\n";

    return 0;
}
