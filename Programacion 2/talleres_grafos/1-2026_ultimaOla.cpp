#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "../include/Grafos.hpp"
#include "../include/Cola.hpp"

using namespace std;
void leerEntrada(Grafo<int>& ultimaOla, int& countEstuInfectados, Lista<int>& listaInfectados);

int main(){
    Grafo<int> ultimaOla(false);

    int countEstuInfectados = -1;
    Lista<int> listaInfectadosInicial;

    leerEntrada(ultimaOla, countEstuInfectados, listaInfectadosInicial);

    // 1. Mapeo de visitados o infectados
    map<int, bool> infectados;
    for(int i = 0; i < ultimaOla.getNNodos(); ++i){
        infectados[i] = false;
    }
    // Verificar las eficicias locales (DEBUGGER)
    //for (size_t i = 0; i < infectados.size(); ++i) {
        // cout << infectados[i] << "-> ";
    //}

    // 2. Encola los primeros infectados
    Cola<int> colaAux;
    while(!listaInfectadosInicial.esVacia()){
        int infected = listaInfectadosInicial.consultar(1);
        colaAux.encolar(infected);
        listaInfectadosInicial.eliminar(1);
    }
    // cout << "\ncola: " << colaAux << endl;

    // 3. Resolucion del problema
    Lista<int> vecinos;
    Lista<int> sobrevivientes;
    while(!colaAux.esVacia()){
        int v = colaAux.getFrente();
        infectados[v] = true;
        // cout << "vertice: " << v << "->" << infectados[v] << endl;;
        
        // Se vacia la lista de sobrevivientes hasta que quede la ultima
        vecinos = ultimaOla.getVecinos(v);
        if(!vecinos.esVacia()){
            Lista<int> aux(vecinos);
            int w = aux.consultar(1);
            if(!infectados[w]) sobrevivientes.vaciar();
            aux.eliminar(1);
        }

        while(!vecinos.esVacia()){
            int w = vecinos.consultar(1);
            if(!infectados[w]){
                sobrevivientes.insertar(w, sobrevivientes.getLong() +1);
                colaAux.encolar(w);
            }
            vecinos.eliminar(1);
        }
        // cout << "Sobrevivio: " << sobrevivientes << endl << endl; 
        colaAux.desencolar();
    }

    // cout << "\nSobrevivio: " << sobrevivientes;
    // 4.1 Imprime el primer sobreviviente sin salto de linea
    if(!sobrevivientes.esVacia()) {
        cout << sobrevivientes.consultar(1);
        sobrevivientes.eliminar(1);
    }
    // 4.2 Imprime los siguientes sobrevivientes
    while(!sobrevivientes.esVacia()){
        cout << endl << sobrevivientes.consultar(1);
        sobrevivientes.eliminar(1);
    }
    return 0;
}

void leerEntrada(Grafo<int>& ultimaOla, int& countEstuInfectados, Lista<int>& listaInfectados){

    // Cada linea deberia venir como: "estudianteA estudianteB"
    // y la lectura se mantiene hasta EOF.
    bool terminaLecturaGrafo = false;
    string linea;
    while (getline(cin, linea)) {
        // Solo se procesa una linea no vacia y con formato valido (exactamente 2 tokens).
        if (!linea.empty()) {
            // stringstream permite partir la linea en tokens por espacios.
            stringstream ss(linea);
            int estudianteA;
            int estudianteB;
            if(!terminaLecturaGrafo){
                // Si no se logran leer exactamente dos nombres, se descarta la linea.
                if (ss >> estudianteA >> estudianteB) {
                    // Si hay basura extra en la linea (mas de dos tokens), tambien se descarta.
                    string tokenExtra;
                    if (!(ss >> tokenExtra)) {
                        // Paso 1: garantizar que ambos estudiantes existan como vertices.
                        ultimaOla.insertarVertice(estudianteA);
                        ultimaOla.insertarVertice(estudianteB);

                        // Paso 2: agregar la conexion entre ambos.
                        // Como el grafo es no dirigido, internamente se agregan ambos sentidos.
                        ultimaOla.insertarArco(estudianteA, estudianteB);
                    }
                }else{
                    countEstuInfectados = estudianteA;
                    terminaLecturaGrafo = true;
                }
            }else{
                int infectado;
                while(ss >> infectado){
                    listaInfectados.insertar(infectado, listaInfectados.getLong() +1);
                }
                // cout << countEstuInfectados << "\nEst infectados: " << listaInfectados;
            }
        }
    }
}