#include "../include/ArbolN.hpp"
#include <list>
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <cctype>
#include <vector>
/* 
## Enunciado

Año 2045. Tras el primer contacto hostil con una civilización extraterrestre, las 
fuerzas humanas han debido reorganizar sus operaciones bajo una estructura estricta de 
despliegue táctico. Cada misión se planifica como una cadena de avance desde una base 
principal hacia múltiples posiciones estratégicas, donde cada unidad depende 
directamente de una unidad superior para recibir recursos, órdenes y soporte. Esta 
organización forma naturalmente una estructura jerárquica donde cada posición tiene un }
único superior, dando lugar a un árbol **n-ario** enraizado en la base central.

Cada nodo del árbol representa una unidad desplegada en el campo, y su valor entero 
indica su efecto sobre la estabilidad de la operación. Valores positivos representan 
condiciones favorables como refuerzos, terreno seguro o superioridad tecnológica, 
mientras que valores negativos reflejan interferencias alienígenas, emboscadas o fallas 
logísticas. A medida que una operación avanza desde la base hacia posiciones más 
profundas, estos efectos se acumulan y determinan si la misión puede continuar.

Para formalizar este comportamiento, se define la estabilidad acumulada de una posición v como:
$$E(v)=\sum_{u\in camino(raiz \rightarrow v)}val(u)$$

El alto mando establece que una posición v es operativamente alcanzable si, durante todo el trayecto desde la base hasta dicha posición, la estabilidad acumulada nunca cae por debajo de cero. Es decir, se debe cumplir que:

$$E(u) \geq 0 \quad \forall u \in camino(raiz \rightarrow v)$$

Si en algún punto del avance la estabilidad se vuelve negativa, la operación se considera comprometida en ese punto, y ninguna de las posiciones que dependen de él puede ser alcanzada. Esta condición no puede evaluarse localmente, ya que depende de todo el historial del trayecto.

Dado un árbol t que representa el despliegue de unidades, su tarea consiste en determinar cuántas posiciones son alcanzables bajo este criterio.

## Formato de Entrada
Un número t indicando cuántos casos de prueba hay.
Para cada caso:
1. Una línea con un número n: cantidad de nodos del árbol.
2. Una línea con n enteros, donde el i-ésimo representa la valor del nodo i.
3. n - 1 líneas, cada una con dos enteros u v, indicando que v es hijo de u. Se garantiza que el nodo 1 es la raíz y que cada árbol es un árbol válido.

## Ejemplo de Entrada
2
5
3 -2 4 -1 2
1 2
1 3
2 4
3 5
4
2 -3 1 5
1 2
2 3
3 4

## Formato de Salida
Por cada caso, imprimir en una sola línea un número entero que representa la cantidad de posiciones alcanzables.

## Ejemplo de Salida
5
1
*/

void esOpeAlcanzable(ArbolN<int> a, int posicionV, const vector<int> &valoresEstabilidad, vector<int> &alcanzables);

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
        vector<int> valoresEstabilidad;
        for(int i = 0; i < cantidadNodos; i++){
            int efi;
            cin >> efi;
            valoresEstabilidad.push_back(efi);
        }

        /*
        // Verificar las eficicias locales (DEBUGGER)
        for (size_t i = 0; i < valoresEstabilidad.size(); ++i) {
            cout << valoresEstabilidad[i] << " ";
        }

        // Ignora salto de línea
        cout << endl; // (DEBUGGER)
        */
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Leer Árbol por entrada estándar
        ArbolN<int> arbol;
        for(int nodos = 0; nodos < cantidadNodos -1; nodos++){
            int padre, hijo;
            cin >> padre >> hijo;
            //cout << "insertar: " <<padre << " " << hijo << endl; // (DEBUGGER)
            if(nodos == 0){
                arbol.insertarNodo(0, padre);
                arbol.insertarNodo(padre, hijo);
            }else{
                arbol.insertarNodo(padre, hijo);
            }
        }
        //arbol.imprimirJerarquico(); // (DEBUGGER)
        //cout << endl; // (DEBUGGER)

        // Resolucion del ejercicio
        // Llenado de vector de alcanzables estilo grafos
        vector<int> alcanzables;
        for(int i = 0; i < arbol.getPeso(); i++){
            alcanzables.push_back(0);
        }
        // Reviso si los elementos no marcados son alcanzables o no
        Lista<int> recorrido = arbol.preOrden();
        int i = 0;
        while(!recorrido.esVacia()){
            int posicionV = recorrido.consultar(1);

            //cout << "keloke " << valoresEstabilidad.at(i) << " a "; // (DEBUGGER)

            // si el elemento no fue alcanzado no lo recorre
            if(alcanzables.at(i) == 0){
                //cout << "mamaguevo"; // (DEBUGGER)
                esOpeAlcanzable(arbol, posicionV, valoresEstabilidad, alcanzables);
            }
            i++;
            recorrido.eliminar(1);
        }

        /*
        // Verificar las eficicias locales (DEBUGGER)
        for (size_t i = 0; i < alcanzables.size(); ++i) {
            cout << "->" << alcanzables[i] << " ";
        }
        */
        
        // sumo las posiciones que mantuvieron su alcanzabilidad
        int posAlcanzables = 0;
        for(int i = 0; i < arbol.getPeso(); i++){
            if(alcanzables[i] == 1) posAlcanzables += 1;
        }

        // retorno y evito una linea vacia al final
        if(esPrimeraLinea){
            cout << posAlcanzables << endl;
        }else{
            cout << endl << posAlcanzables;
        }
    }
    return 0;
}
void esOpeAlcanzable(ArbolN<int> a, int posicionV, const vector<int> &valoresEstabilidad, vector<int> &alcanzables) {
    Lista<int> camino;
    int estabilidadAcumulada = 0;

    camino = a.camino(a.getRaiz(), posicionV);
    //cout << camino << "  "; // (DEBUGGER)
    while(!camino.esVacia() && estabilidadAcumulada >= 0){
        // revisa el token del vector y evita leaks
        int idNodo = camino.consultar(1);
        // cout << idNodo << endl; // (DEBUGGER)
        if(idNodo <= 0 || idNodo > (int)valoresEstabilidad.size()){
            throw out_of_range("ID de nodo fuera de rango para eficienciasLocales");
        }

        estabilidadAcumulada += valoresEstabilidad.at(idNodo - 1);
        // cout << " ea: " << estabilidadAcumulada << endl; // (DEBUGGER)

        // si la suma acumulada se mantiene mayor a 0 entonces marco el nodo como alcanzable para no recorrerlo luego
        if(estabilidadAcumulada >= 0) alcanzables[idNodo - 1] = 1;
        camino.eliminar(1);
    }

    // Marca los elemenos del camino que no sean alcanzables
    while(!camino.esVacia()){
        int idNodo = camino.consultar(1);
        if(idNodo <= 0 || idNodo > (int)valoresEstabilidad.size()){
            throw out_of_range("ID de nodo fuera de rango para eficienciasLocales");
        }

        alcanzables[idNodo - 1] = -1;
        camino.eliminar(1);
    }
}