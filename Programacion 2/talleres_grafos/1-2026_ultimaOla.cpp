#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "../include/Grafos.hpp"
#include "../include/Cola.hpp"
#include "../include/VisualizacionGrafos.hpp"
/* Descripcion del taller

2. Enunciado
La Última Ola: Sobrevivientes de Programación II
No todos llegaron hasta aquí.. Durante el semestre, múltiples evaluaciones fueron aplicadas.
Algunas fueron justas. Otras... discutibles. Pero todas tuvieron el mismo efecto: una ola
masiva de estudiantes reprobados que se fue expandiendo silenciosamente por toda la
sección.
Al principio eran pocos. Un taller aquí, una clase allá. Pero luego... la propagación se volvió
inevitable. Se ha detectado que el “virus de reprobación” se propaga entre estudiantes que
tienen contacto directo. Basta con que un estudiante infectado tenga contacto con otro para
que, eventualmente, este también quede comprometido.
Sin embargo, no todo está perdido. Un pequeño grupo de estudiantes ha logrado sobrevivir
hasta este último taller. Pero el peligro sigue latente. Algunos de sus compañeros ya están
infectados... y la propagación no se detiene. Para entender correctamente el comportamiento
del virus, es importante interpretar la propagación en términos de “olas”.
Todos los estudiantes inicialmente infectados comienzan en el mismo instante (tiempo 0). A
partir de ese momento, el virus se propaga de la siguiente manera:
● En la primera ola, todos los estudiantes infectados contagian a sus contactos directos.
● En la siguiente ola, los nuevos infectados contagian a sus propios contactos, y así
sucesivamente.
● Este proceso continúa hasta que no sea posible infectar a más estudiantes.
Cada estudiante se infecta en el momento en que el virus llega a él por primera vez. No es
posible que un estudiante se infecte más de una vez.
Se sabe que:
● Cada estudiante está identificado por un número entero entre 0 y N - 1.
● Cada estudiante puede tener contacto directo con otros estudiantes.
● La red de contactos forma un grafo conexo.
● Existen varios estudiantes inicialmente infectados al mismo tiempo.
Tu tarea, como uno de los pocos sobrevivientes funcionales, es analizar la red de contactos y
determinar qué estudiantes son alcanzados en la última ola de propagación.
3. Formato de Entrada
La primera línea contiene dos enteros: N M donde:
● N representa la cantidad de estudiantes (identificados desde 0 hasta N - 1).
● M representa la cantidad de contactos directos.
Las siguientes M líneas contienen dos enteros: u y v que indican que el estudiante u tiene
contacto directo con el estudiante v. Finalmente, se lee una línea con un entero: K que
representa la cantidad de estudiantes inicialmente infectados. Luego se lee una línea con K
enteros separados por espacios, que representan los estudiantes inicialmente infectados.

4. Ejemplo de Entrada
8 7
0 1
1 2
2 3
1 4
4 5
5 6
5 7
2
0 7
5. Formato de Salida
Se debe imprimir, en una sola línea y separados por espacios, los identificadores de los
estudiantes que son alcanzados en la última ola de propagación. La salida debe estar
ordenada en forma ascendente. PUEDE HABER MÁS DE UN NODO EN LA SALIDA.
6. Ejemplo de Salida
3
*/
using namespace std;

// Lee el grafo y la lista de infectados iniciales con el formato:
// N M, luego M aristas, luego K, luego K infectados.
void leerEntrada(Grafo<int>& ultimaOla, int& countEstuInfectados, Lista<int>& listaInfectados, int& nEstudiantes);

int main(){
    // false => grafo no dirigido.
    Grafo<int> ultimaOla(false);

    int countEstuInfectados = -1;
    int nEstudiantes = 0;
    Lista<int> listaInfectadosInicial;

    leerEntrada(ultimaOla, countEstuInfectados, listaInfectadosInicial, nEstudiantes);

    // distancia[i] guarda la PRIMERA ola en la que se infecta el estudiante i.
    // Interpretacion:
    // - distancia[i] = -1  => todavia no fue alcanzado por el virus.
    // - distancia[i] = 0   => era infectado inicial (tiempo 0).
    // - distancia[i] = d>0 => se infecto en la ola d.
    //
    // En un BFS, la primera vez que llegamos a un nodo siempre es por el camino
    // mas corto en cantidad de aristas, por eso esta distancia modela exactamente
    // la idea de "ola minima de contagio".
    vector<int> distancia(nEstudiantes, -1);

    // Encola los primeros infectados (multi-source BFS):
    // todos arrancan al mismo tiempo, por eso todos parten con distancia 0.
    Cola<int> colaAux;
    while(!listaInfectadosInicial.esVacia()){
        int infected = listaInfectadosInicial.consultar(1);
        // Se marca al encolar para evitar duplicados en la cola.
        // Este marcado temprano es clave: desde aqui ya se considera "infectado".
        if(infected >= 0 && infected < nEstudiantes && distancia[infected] == -1){
            distancia[infected] = 0;
            colaAux.encolar(infected);
        }
        listaInfectadosInicial.eliminar(1);
    }

    // Propagacion por olas:
    // cuando procesamos v, intentamos contagiar a cada vecino w en la siguiente ola.
    // Si v esta en ola t, cualquier vecino nuevo pasa a ola t+1.
    Lista<int> vecinos;
    while(!colaAux.esVacia()){
        int v = colaAux.getFrente();

        // Recorremos contactos directos de v.
        vecinos = ultimaOla.getVecinos(v);
        while(!vecinos.esVacia()){
            int w = vecinos.consultar(1);
            // Regla de infeccion unica:
            // solo si distancia[w] == -1, w aun no estaba infectado.
            // En ese caso se infecta ahora en la ola siguiente a la de v.
            // Si distancia[w] != -1, significa que ya fue infectado antes
            // (en una ola menor o igual), entonces NO se vuelve a encolar.
            if(distancia[w] == -1){
                distancia[w] = distancia[v] + 1;
                colaAux.encolar(w);
            }
            vecinos.eliminar(1);
        }

        colaAux.desencolar();
    }

    // ultimaOlaDist = ola mas tardia a la que llega el contagio.
    // Es simplemente el maximo valor almacenado en distancia.
    int ultimaOlaDist = -1;
    for(int i = 0; i < nEstudiantes; ++i){
        if(distancia[i] > ultimaOlaDist){
            ultimaOlaDist = distancia[i];
        }
    }

    // Se imprimen los estudiantes cuya distancia coincide con la ultima ola.
    // Recorrer de 0 a N-1 garantiza orden ascendente en la salida.
    bool primero = true;
    for(int i = 0; i < nEstudiantes; ++i){
        if(distancia[i] == ultimaOlaDist){
            if(!primero) cout << " ";
            cout << i;
            primero = false;
        }
    }
    exportarGrafoASVG(ultimaOla, "talleres_grafos/grafo_caso_mediano.svg", false, 1100, 800);
    return 0;
}

void leerEntrada(Grafo<int>& ultimaOla, int& countEstuInfectados, Lista<int>& listaInfectados, int& nEstudiantes){
    int m = 0;
    cin >> nEstudiantes >> m;

    // Se crean todos los vertices [0, N-1], incluso si alguno no aparece en aristas.
    for(int i = 0; i < nEstudiantes; ++i){
        ultimaOla.insertarVertice(i);
    }

    // Lectura de aristas del grafo de contactos.
    for(int i = 0; i < m; ++i){
        int estudianteA, estudianteB;
        cin >> estudianteA >> estudianteB;
        ultimaOla.insertarArco(estudianteA, estudianteB);
    }

    // Lectura de infectados iniciales (fuentes simultaneas del BFS).
    cin >> countEstuInfectados;
    for(int i = 0; i < countEstuInfectados; ++i){
        int infectado;
        cin >> infectado;
        listaInfectados.insertar(infectado, listaInfectados.getLong() + 1);
    }
}