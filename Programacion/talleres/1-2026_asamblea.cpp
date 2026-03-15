#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include "../include/Lista.hpp"

using namespace std;
int main(){
    // Entrada n del total de circulos en la asamblea
    int totalCirculos;
    cin >> totalCirculos;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Procedimiento de entrada estántar
    Lista<string> secta;
    string linea;
    string nombre;
    for(int i = 0; i < totalCirculos; i++){
        getline(cin, linea);
        if (linea.size() != 0){
            stringstream ss(linea);
            while (ss >> nombre) {
                secta.insertar(nombre, secta.getLong() + 1);
            }
        }
        cout << secta << endl; // Debugger

        // Procedimiento principal 
        while(secta.getLong() > 1){
        // Devoto hace oracion
        string devoto = secta.consultar(1);
        secta.eliminar(1);

        // Devoto se mueve al final del circulo
        secta.insertar(devoto, secta.getLong()+1 );
        cout << "Lista Modificada: " << secta << endl;
        // Devoto Sacrificado
        cout << "Devoto sacrificado: " << secta.consultar(1) << endl; // Debugger
        secta.eliminar(1);
        }
        cout << "ILUMINACION ESPIRITUAL: " << secta << endl << "-------" << endl;
        if( (i+1) == totalCirculos && secta.getLong() == 1){
            //cout << secta.consultar(1);
            cout << "Devoto elegido para ritual del pollo: " << secta.consultar(1);
        }
        // Vaciar para dar pie al siguiente circulo
        secta.vaciar();
    }
    
    return 0;
}