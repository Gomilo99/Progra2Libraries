#include "../include/ArbolN.hpp"
#include <list>
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <cctype>
#include <vector>

using namespace std;

int SumaConjuntoIndependiente(ArbolN<int> a, bool incluirPadre, const vector<int>& eficienciasLocales);
void balanceoArboles(ArbolN<int> a, Lista<ArbolN<int> > *hojasPares, Lista<ArbolN<int> > *hojasImpares);

int main(){
    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    bool esPrimeraLinea = true;
    
    for(int caso = 1; caso <= t; caso++){
        int cantidadNodos;
        cin >> cantidadNodos;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Leer eficiencias locales
        vector<int> eficienciasLocales;
        for(int i = 0; i < cantidadNodos; i++){
            int efi;
            cin >> efi;
            eficienciasLocales.push_back(efi);
        }

        // Verificar las eficicias locales (DEBUGGER)
        for (size_t i = 0; i < eficienciasLocales.size(); ++i) {
            cout << eficienciasLocales[i] << " ";
        }

        // Ignora salto de línea
        cout << endl; // (DEBUGGER)
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Leer Árbol por entrada estándar
        ArbolN<int> arbol;
        for(int nodos = 0; nodos < cantidadNodos -1; nodos++){
            int padre, hijo;
            cin >> padre >> hijo;
            cout << "insertar: " <<padre << " " << hijo << endl; // (DEBUGGER)
            if(nodos == 0){
                arbol.insertarNodo(0, padre);
                arbol.insertarNodo(padre, hijo);
            }else{
                arbol.insertarNodo(padre, hijo);
            }
        }
        
        arbol.imprimirJerarquico(); // (DEBUGGER)
        cout << endl; // (DEBUGGER)

        // Calculo del MSI
        int msi = SumaConjuntoIndependiente(arbol, false, eficienciasLocales);

        // Construir Lista de Arboles y encontar niveles de hojas pares e impares
        Lista<ArbolN<int> > hojasPares, hojasImpares;
        ArbolN<int> aAux;
        hojasPares.insertar(aAux, 1);
        hojasImpares.insertar(aAux, 1);
        balanceoArboles(arbol, &hojasPares, &hojasImpares);
        int balance = hojasPares.getLong() - hojasImpares.getLong();

        // Calculo final del CHUPA
        int CHUPA = msi * balance;
        if(esPrimeraLinea){
            cout << CHUPA << endl;
            esPrimeraLinea = false;
        }else{
            cout << endl << CHUPA;
        }
    }
    return 0;
}
/*
Procedimiento que siendo sincero no entiendo bien como funciona pero debería estar correcto... Está hecho para que esté fuera de la clase pero si se hace con punteros debería ser mucho más sencillo, y tambien más eficiente en memoria y tiempo probablemente.
*/
int SumaConjuntoIndependiente(ArbolN<int> a, bool incluirPadre, const vector<int>& eficienciasLocales){
    if(a.esNulo()) return 0;

    int sumaTotal = 0;
    if(incluirPadre){
        Lista<ArbolN<int> > hijos = a.getHijos();
        while(!hijos.esVacia()){
            sumaTotal += SumaConjuntoIndependiente(hijos.consultar(1), false, eficienciasLocales);
            hijos.eliminar(1);
        }
    }else{
        int idNodo = a.getRaiz();
        if(idNodo <= 0 || idNodo > (int)eficienciasLocales.size()){
            throw out_of_range("ID de nodo fuera de rango para eficienciasLocales");
        }
        int sumaIncluye = eficienciasLocales.at(idNodo - 1);
        int sumaExcluye = 0;
        
        Lista<ArbolN<int> > hijos = a.getHijos();
        while(!hijos.esVacia()){
            sumaIncluye += SumaConjuntoIndependiente(hijos.consultar(1), true, eficienciasLocales);
            sumaExcluye += SumaConjuntoIndependiente(hijos.consultar(1), false, eficienciasLocales);
            hijos.eliminar(1);
        }
        if(sumaIncluye > sumaExcluye){
            sumaTotal = sumaIncluye;
        }else{
            sumaTotal = sumaExcluye;
        }
    }
    return sumaTotal;
}
/*
Procedimiento que encuentra las hojas en niveles pares e impares usando lógica de saber en que nivel estoy con un for. Debería ser más eficiente en tiempo y memoria si se hace dentro de la clase en si, pero lo puse así porque podía y por si acaso necesitaba practicar asi :)
*/
void balanceoArboles(ArbolN<int> a, Lista<ArbolN<int> > *hojasPares, Lista<ArbolN<int> > *hojasImpares){
    if(a.esNulo()) return;

    Cola<ArbolN<int> > colaAux;
    colaAux.encolar(a);
    int nivel = -1;
    while(!colaAux.esVacia()){
        int tamañoNivel = colaAux.getLong();
        nivel += 1;
        for(int i = 0; i<tamañoNivel; i++){
            ArbolN<int> subArbol = colaAux.getFrente();
            if(subArbol.esHoja()){
                if(nivel % 2 == 0){
                    hojasPares->insertar(subArbol, hojasPares->getLong() + 1);
                }else{
                    hojasImpares->insertar(subArbol, hojasImpares->getLong() + 1);
            }
            }
            
            Lista<ArbolN<int> > hijos = subArbol.getHijos();
            while(!hijos.esVacia()){
                subArbol = hijos.consultar(1);
                colaAux.encolar(subArbol);
                hijos.eliminar(1);
            }
            colaAux.desencolar();
        }
    }
    cout << "OK BALANCEO\n";
}