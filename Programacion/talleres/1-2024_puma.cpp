#include <iostream>
#include <sstream>
#include <string>
#include "../include/Lista.hpp"

using namespace std;

/*
# Enunciado del problema:
los analistas necesitan calcular la “Moda”.
Ellos tienen sus archivos excel en formato “.csv” y no conocen otra forma de darte los datos,
por ello tú debes crear tu propio programa que sea capaz de leer archivos “.csv” y calcular la
Moda.
Explicación: La moda es una medida de tendencia central consistente en “El valor que más
se repite” en una población. En este caso, si tenemos una población:
X = [1, 7, 9, 8, 8, 4, 5]
Moda(X) = 8
## Formato de Entrada
Los archivos CSV (del inglés comma-separated values) son un tipo de documento en formato
abierto sencillo para representar datos en forma de tabla, en las que las columnas se separan
por comas y las filas por saltos de línea. Por ejemplo:
|Año|Marca|Modelo|Descripción|Precio|
|---|---|---|---|---|
|1997|Ford|E350|ac, abs, moon|3000.00|
|1999|Chevy|Venture|Extended Edition|4900.00|
|1999|Chevy|Venture|Extended Edition, Very Large|5000.00|
|1996|Jeep|Grand Cherokee|MUST SELL! air, moon roof, loaded|4799.00|
### Ejemplo de entrada
Marca,Precio
ford,4
ford,3
ford,4
chevrolet,4
ford,4
ford,3
ford,4
chevrolet,4
ford,4
ford,3
ford,4
chevrolet,4
ford,4
ford,3
ford,4
chevrolet,4
Datos a tener en cuenta:
- La primera fila son los nombres de las columnas.
- No habrá celdas en blanco.
- En caso de ser cadenas, estas serán simples, no contendrán espacios.
- IMPORTANTE: no hay espacios después de las comas.
## Formato de Salida
La salida será también en formato “.csv”, de una sola fila y debe devolver las modas
de cada columna. En caso de no haber moda, se retorna el valor “ninguna” para esa
columna. Salida del ejemplo anterior:
Marca,Precio
ford,4
*/

void separarCSV(const string& linea, Lista<string>& celdas) {
    stringstream ss(linea);
    string celda;

    while (getline(ss, celda, ',')) {
        celdas.insertar(celda, celdas.getLong() + 1);
    }
}

void imprimirFilaCSV(const Lista<string>& fila) {
    for (int i = 1; i <= fila.getLong(); ++i) {
        if (i > 1) {
            cout << ",";
        }
        cout << fila.consultar(i);
    }
}

string calcularModa(const Lista<string>& columna) {
    Lista<string> valoresUnicos;
    Lista<int> frecuencias;

    for (int i = 1; i <= columna.getLong(); ++i) {
        string valor = columna.consultar(i);
        int posicion = valoresUnicos.buscar(valor);

        if (posicion == -1) {
            valoresUnicos.insertar(valor, valoresUnicos.getLong() + 1);
            frecuencias.insertar(1, frecuencias.getLong() + 1);
        } else {
            frecuencias.modificar(posicion, frecuencias.consultar(posicion) + 1);
        }
    }

    int maxFrecuencia = 0;
    int posicionModa = -1;
    int cantidadMaximos = 0;

    for (int i = 1; i <= frecuencias.getLong(); ++i) {
        int frecuencia = frecuencias.consultar(i);

        if (frecuencia > maxFrecuencia) {
            maxFrecuencia = frecuencia;
            posicionModa = i;
            cantidadMaximos = 1;
        } else if (frecuencia == maxFrecuencia) {
            ++cantidadMaximos;
        }
    }

    if (maxFrecuencia <= 1 || cantidadMaximos > 1) {
        return "ninguna";
    }

    return valoresUnicos.consultar(posicionModa);
}

int main() {
    string linea;
    if (!getline(cin, linea)) {
        return 0;
    }

    Lista<string> encabezados;
    separarCSV(linea, encabezados);

    Lista<Lista<string> > columnas;
    for (int i = 1; i <= encabezados.getLong(); ++i) {
        columnas.insertar(Lista<string>(), columnas.getLong() + 1);
    }

    while (getline(cin, linea)) {
        Lista<string> fila;
        separarCSV(linea, fila);

        for (int i = 1; i <= encabezados.getLong(); ++i) {
            columnas.consultarRef(i).insertar(fila.consultar(i), columnas.consultarRef(i).getLong() + 1);
        }
    }

    Lista<string> modas;
    for (int i = 1; i <= columnas.getLong(); ++i) {
        modas.insertar(calcularModa(columnas.consultar(i)), modas.getLong() + 1);
    }

    imprimirFilaCSV(encabezados);
    cout << endl;
    imprimirFilaCSV(modas);

    return 0;
}