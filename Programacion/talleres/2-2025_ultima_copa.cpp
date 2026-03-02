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


/* Enunciado del problema:
# Las reglas del brindis
El Maestro comienza siempre en el primer invitado, avanzando por el círculo siguiendo el recorrido de los sirvientes (lo que los profanos llamarían “sentido de las agujas del reloj”). Cuenta K brindis y al invitado en ese punto se le retira la copa, quedando fuera del juego.
Pero aquí la tradición se retuerce: cada vez que alguien queda sin copa, el sentido del recorrido se invierte; lo que antes era avanzar por el flujo de los sirvientes ahora es retroceder contra ellos. La cantidad de pasos para llegar al siguiente invitado no siempre es la misma: depende de la numeración inicial del eliminado.
- Si su número original en el círculo era par, se avanza P pasos.
- Si era impar, se avanza Q pasos.
El brindis continúa, alternando el sentido con cada eliminación, hasta que queda un único invitado con copa. Ese invitado se acerca al Maestro, recibe de sus manos la Última Copa y pronuncia un juramento que nadie en la sala osa repetir en voz alta.

## Formato de Entrada
Primero se lee un entero n con el número de casos de prueba, luego, las siguientes n pares de líneas representan:
- la primera línea: 3 enteros: K, P, Q que representan los valores K, P y Q mencionados en el enunciado
- la segunda línea: lista de nombres de personas, entre comillas, separados por comas y espacios.

## Ejemplo de Entrada
2
4 5 2
“alvaro espinoza”, “tobias”, “lord Hansell Campbell”, “mariana”
2 3 2
“alvaro espinoza”, “jimmy hendrix”, “slash”, “steven tyler”

## Formato de Salida
La salida será sencilla, en este caso simplemente van a ser n líneas por cada caso de prueba con el nombre del elegido, sin comillas. Para la entrada anterior. La salida es:
alvaro espinoza
steven
*/
static string trim(const string& s);
static void replaceAll(string& s, const string& from, const string& to);
static string normalizeQuotes(string s);
static Lista<string> splitCSVSimpleToLista(string s);

int main() {
    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //bool firstLine = true;

    for (int caso = 1; caso <= t; ++caso) {
        string lineaNums, lineaNombres;
        getline(cin, lineaNums);      // ej: 4 5 2
        getline(cin, lineaNombres);   // ej: “alvaro...”, “tobias”, ...

        int K, P, Q;
        stringstream ss(lineaNums);
        ss >> K >> P >> Q;

        Lista<string> nombres = splitCSVSimpleToLista(lineaNombres);
        Lista<int> indices;
        for (int i = 1; i <= nombres.getLong(); ++i) {
            indices.insertar(i, indices.getLong() + 1);
        }
        cout << nombres << endl; // Solo para verificar que se parseó correctamente. Elimina esta línea en la versión final.
        cout << indices << endl; // Solo para verificar que se asignaron índices correctamente. Elimina esta línea en la versión final.
        
        while(nombres.getLong() > 1) {
            int truePos = ( (K - 1) % indices.getLong() ) + 1;

            int idOriginalEliminado = indices.consultar(truePos);
            cout << "Posición a eliminar (1-based): " << truePos << " (id original=" << idOriginalEliminado << ")" << endl; // Solo para verificar la posición calculada. Elimina esta línea en la versión final.

            cout << "Nombre a eliminar: " << nombres.consultar(truePos) << endl; // Solo para verificar el nombre calculado. Elimina esta línea en la versión final.
            nombres.eliminar(truePos);
            indices.eliminar(truePos);

            if (idOriginalEliminado % 2 == 0) {
                K = P;
            } else {
                K = Q;
            }

            if (nombres.getLong() > 1) {
                /*En el sentido viejo, el siguiente punto de inicio (al invertir)
                es el anterior del eliminado. Lo guardamos como posición en la
                lista resultante tras eliminar.
                */
                int posAnteriorViejo;
                if (truePos == 1) {
                    posAnteriorViejo = nombres.getLong(); // Si eliminamos el head, el anterior es el tail.
                } else {
                    posAnteriorViejo = truePos - 1;
                }

                // Cambiamos sentido real invirtiendo ambas listas.
                nombres.invertir();
                indices.invertir();

                cout << "Estado nombres tras invertir: " << nombres << endl; // Solo para verificar el estado tras invertir. Elimina esta línea en la versión final.
                cout << "Estado indices tras invertir: " << indices << endl; // Solo para verificar el estado tras invertir. Elimina esta línea en la versión final.

                // Reubicamos para que el "siguiente en el nuevo sentido" quede en head.
                int shift = posAnteriorViejo % nombres.getLong();
                if (shift != 0) {
                    nombres.rightShift(shift);
                    indices.rightShift(shift);
                }
            }

            cout << "Estado nombres: " << nombres << endl;
            cout << "Estado indices: " << indices << endl;
        }
        cout << "Ganador: " << nombres.consultar(1) << endl << "-----------------------------" << endl; // Solo para verificar el ganador. Elimina esta línea en la versión final.
        
        /*
        if (!firstLine) cout << "\n";
        cout << "Caso " << caso << ": K=" << K << ", P=" << P << ", Q=" << Q;
        firstLine = false;
        for (int i = 1; i <= nombres.getLong(); ++i) {
            cout << "\n" << nombres.consultar(i);
        }
        */
        

    }
    

    return 0;
}

//Elimina espacios laterales de cada campo parseado. " hola " pasa a "hola"
static string trim(const string& s) {
    size_t i = 0, j = s.size();
    while (i < j && isspace((unsigned char)s[i])) ++i;
    while (j > i && isspace((unsigned char)s[j - 1])) --j;
    return s.substr(i, j - i);
}

// Reemplaza todas las ocurrencias de 'from' por 'to' en la cadena 's'. Ejemplo: replaceAll(s, "a", "x") convierte "banana" en "bxnxnx".
static void replaceAll(string& s, const string& from, const string& to) {
    size_t pos = 0;
    while ((pos = s.find(from, pos)) != string::npos) {
        s.replace(pos, from.size(), to);
        pos += to.size();
    }
}

// Normaliza comillas tipográficas a comillas estándar. Ejemplo: “hola” pasa a "hola"
static string normalizeQuotes(string s) {
    replaceAll(s, "\xE2\x80\x9C", "\""); // “
    replaceAll(s, "\xE2\x80\x9D", "\""); // ”
    return s;
}

// Parsea una línea CSV simple (sin saltos de línea dentro de campos) a una Lista<string>. Maneja comillas dobles para campos con comas. Ejemplo: splitCSVSimpleToLista("“alvaro...”, “tobias”, ...") devuelve una Lista con "alvaro...", "tobias", ...
static Lista<string> splitCSVSimpleToLista(string s) {
    s = normalizeQuotes(s);

    Lista<string> out;
    string current;
    bool inQuotes = false;

    for (size_t i = 0; i < s.size(); ++i) {
        char ch = s[i];

        if (ch == '"') {
            if (inQuotes && i + 1 < s.size() && s[i + 1] == '"') {
                current.push_back('"'); // comilla escapada ""
                ++i;
            } else {
                inQuotes = !inQuotes;
            }
        } else if (ch == ',' && !inQuotes) {
            out.insertar(trim(current), out.getLong() + 1);
            current.clear();
        } else {
            current.push_back(ch);
        }
    }

    out.insertar(trim(current), out.getLong() + 1);
    return out;
}