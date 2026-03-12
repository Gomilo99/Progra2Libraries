#include <iostream>
#include "../include/Lista.hpp"
#include "../include/Cola.hpp"
#include "../include/Pila.hpp"
#include "../include/Ejercicios.hpp"
#include <string>
#include <sstream>
#include <limits>
#include <cctype>
using namespace std;
/* 
# Enunciado del problema:
los analistas necesitan calcular la “Moda”.
Ellos tienen sus archivos excel en formato “.csv” y no conocen otra forma de darte los datos,
por ello tú debes crear tu propio programa que sea capaz de leer archivos “.csv” y calcular la
Moda.
Explicación: La moda es una medida de tendencia central consistente en “El valor que más
se repite” en una población. En este caso, si tenemos una población:
𝑋 = [1, 7, 9, 8, 8, 4, 5]
𝑀𝑜𝑑𝑎(𝑋) = 8
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
● La primera fila son los nombres de las columnas.
● No habrá celdas en blanco.
● En caso de ser cadenas, estas serán simples, no contendrán espacios
● IMPORTANTE: no hay espacios después de las comas
## Formato de Salida
La salida será también en formato “.csv”, de una sola fila y debe devolver las modas
de cada columna. En caso de no haber moda, se retorna el valor “ninguna” para esa
columna. Salida de ejemplo anterior:
Marca,Precio
ford, 4
 */
int main(){

    return 0;
}