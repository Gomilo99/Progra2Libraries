/* 
# Descripción del problema
Un grupo de n personas se reúne en círculo cada año para participar. Cada una representa una virtud o debilidad humana, y se sientan según el orden en que fueron convocados. El juego comienza con una persona seleccionada al azar, quien sostiene el Pan. Luego, el Pan es pasado sucesivamente a la persona a su lado, avanzando en sentido horario, mientras se cuenta en voz alta del 1 al k.
Quien reciba el Pan cuando se llega a k es juzgado por sus actos... y eliminado del juego.
Pero la tradición guarda una regla divina:
"Cada vez que alguien sea eliminado, la dirección del paso del Pan cambiará." Es decir, si se venía pasando a la derecha, ahora irá a la izquierda, y viceversa.
Así continúa la ceremonia hasta que solo quede uno... el elegido.
## Formato de Entrada
Primero se lee un entero n con el número de casos de prueba, luego, las siguientes n líneas se presentan n enteros que serán los valores k para cada caso de prueba. Seguido a lo anterior, sigue un número finito de líneas (no definido) con máximo n
cadenas separadas por espacios, cada cadena en una misma línea pertenece a una lista diferente, por lo que no siempre habrán n cadenas. Tenga en cuenta que las listas de más a la izquierda siempre tendrán igual o más elementos que las listas de la derecha.
## Ejemplo de Entrada
2
3
5
judas juan
iscariote simon
jacobo natanael
mateo felipe
pedro santiago
andres
tomas
jesus
## Formato de Salida
La salida será sencilla, en este caso simplemente van a ser n líneas por cada caso de prueba con el nombre del elegido.
*/
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <cstdlib>
#include "../include/Lista.hpp"

using namespace std;

int main() {
    int n;
    cin >> n;

    Lista<int> listaK;
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        listaK.insertar(k, listaK.getLong() + 1);
    }

    Lista<Lista<string> > casosNombres;
    for (int i = 0; i < n; ++i) {
        Lista<string> vacia;
        casosNombres.insertar(vacia, casosNombres.getLong() + 1);
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string linea;
    while (getline(cin, linea)) {
        if (linea.size() != 0){
            stringstream ss(linea);
            string nombre;
            int col = 1; // columna 1..n

            while (ss >> nombre && col <= n) {
                // Version de insercion directa usando estructura auxiliar
                //Lista<string> aux = casosNombres.consultar(col);
                //aux.insertar(nombre, aux.getLong() + 1);
                //casosNombres.modificar(col, aux);
                Lista<string> &aux = casosNombres.consultarRef(col);
                aux.insertar(nombre, aux.getLong() + 1);
                ++col;
            }
        }
    }

    // Debug de verificación
    for (int i = 1; i <= n; ++i) {
        if (i > 1) cout << "\n";
        cout << "Caso " << i << "  K=" << listaK.consultar(i)
            << "  Nombres=" << casosNombres.consultar(i);
    }
    //Proceso
    while(casosNombres.getLong() > 0){
        //Seleccion random de quien empieza con el pan
        Lista<string> nombres = casosNombres.consultar(1);
        cout << endl << "Nombres del caso: " << nombres; // Solo para verificar que se cargaron los nombres correctamente. Elimina esta línea en la versión final.
        int randomStart = rand() % nombres.getLong() + 1; // Asumiendo que n es el número de personas, y las personas están indexadas del 1 a n.
        nombres.rightShift(randomStart - 1); // Para que el randomStart quede en head.
            //cout << endl << "Nombres tras randomStart: " << nombres; // Solo para verificar que se aplicó el randomStart correctamente. Elimina esta línea en la versión final.
        while(nombres.getLong() > 1) {
            nombres.rightShift( (listaK.consultar(1) -1) % nombres.getLong()); // Para que el primer eliminado quede en head.
            //cout << endl << "Nombres tras aplicar K: " << nombres; // Solo para verificar que se aplicó el K correctamente. Elimina esta línea en la versión final.

            nombres.eliminar(1); // Eliminamos el primer eliminado.
            //cout << endl << "Nombres tras eliminar : " << nombres; // Solo para verificar que se eliminó el primer eliminado correctamente. Elimina esta línea en la versión final.

            nombres.invertir(); // Invertimos el sentido tras la primera eliminación.
            //cout << endl << "Nombres tras invertir el sentido: " << nombres; // Solo para verificar que se invirtió el sentido correctamente. Elimina esta línea en la versión final.
        }
        cout << endl << "Ganador: " << nombres.consultar(1) << endl; // Solo para verificar el ganador. Elimina esta línea en la versión final.

        casosNombres.eliminar(1); // Eliminamos el caso ya resuelto.
        listaK.eliminar(1); // Eliminamos el K del caso ya resuelto.
        
    }
    return 0;
}