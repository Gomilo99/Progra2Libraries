#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <cmath>
#include <climits>
#include <limits>
#include "arbolBin.hpp"

std::list<std::string> split(const std::string &str);
void readTrees();
void MUP(std::vector<ArbolBin<std::string>>& grupos, std::vector<std::list<std::string>>& pruebas);
int mayor(std::vector<int>& resultados);

int main()
{
    readTrees(); // main() todo inútil porque lo importante lo hace otra función

    return 0;
}

std::list<std::string> split(const std::string &str) // Función que pica una cadena con espacios en una lista de cadenas   
{                                                    // separadas originalmente por espacios.         
    std::list<std::string> palabras;
    std::istringstream iss(str);
    std::string aux;
    
    while (iss >> aux) // Manda el flujo de datos hasta llegar a un espacio, y luego se come el espacio.
    { 
        palabras.push_back(aux); // Se guarda en la lista.
    }
    return palabras; // Se devueleve la lista.
}

//std::cout << "llegó\n\n"; // Pequeño depurador con std::cout para los problemas que tuve en el código. está aquí solo porque sí.

void readTrees() {
    int n, k;
    std::cin >> n;                                                                      // Leemos la cantidad de casos de prueba.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');                 // Nos comemos el salto de línea como a un pescado en Semana Santa.

    for(int i = 0; i < n; i++) 
    {
        std::cin >> k;                                                                  // Leemos la cantidad de grupos a evaluar.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::vector<ArbolBin<std::string>> grupos;      // Vectores de árboles y de listas.
        std::vector<std::list<std::string>> pruebas;

        for(int j = 0; j < k; j++)
        {
            std::string arbol1, arbol2, nombres;        // Cadenas para guardar el flujo de una línea.

            arbol1.clear();
            arbol2.clear();
            nombres.clear();

            std::getline(std::cin, arbol1);           // Guardamos el flujo.
            std::getline(std::cin, arbol2);

            std::list<std::string> orden1 = split(arbol1);  // Picamos el flujo en los espacios.
            std::list<std::string> orden2 = split(arbol2);

            if(orden1.front() == "INORDEN")                                // Resumiendo, decidimos en qué lista de cadenas tenemos los datos
            {                                                              // del inorden y los del preorden o postorden. Por la división que hacemos,
                orden1.pop_front();                                        // en la primera posición siempre estará la palabra INORDEN/PREORDEN/POSTORDEN
                if(orden2.front() == "PREORDEN")                           // y me valgo de eso para decidir cuál está en dónde. Claro, también quito el .front()
                {                                                          // para que no se me cuele dicha palabra.
                    orden2.pop_front();
                    ArbolBin<std::string> tree(orden2, orden1);
                    grupos.push_back(tree);
                }else
                {
                    orden2.pop_front();
                    ArbolBin<std::string> tree(orden2, orden1, 0);
                    grupos.push_back(tree);
                }
            }else
            {
                orden2.pop_front();
                if(orden1.front() == "PREORDEN")
                {
                    orden1.pop_front();
                    ArbolBin<std::string> tree(orden1, orden2);
                    grupos.push_back(tree);
                }else
                {
                    orden1.pop_front();
                    ArbolBin<std::string> tree(orden1, orden2, 0);
                    grupos.push_back(tree);
                }
            }

            std::getline(std::cin, nombres);            // Guardamos los nombres de las víctimas del profesor de Programación 2 a evaluar. 
            pruebas.push_back(split(nombres));
        }

        MUP(grupos, pruebas);  // Función pa calcular la Métrica Universal de Padecimiento. 
    }
}

void MUP(std::vector<ArbolBin<std::string>>& grupos, std::vector<std::list<std::string>>& pruebas)
{
    int iteraciones = grupos.size();  // Aquí se obtiene la cantidad de grupos a evaluarles el MUP.
    std::vector<int> resultados;  //Aquí guardaremos los resultados de caada grupo.

    for(int i = 0; i < iteraciones; i++)
    {
        int sumaGrupo = 0;
        while(!pruebas[i].empty())           // Dentro de este ciclo se evalua la sumatoria de MUP completa para cada estudiante de prueba.
        {
            for(int j = 0; j < grupos[i].getPeso(); j++)              // Acá se evalúa por cada alumno con todos sus compañeros y se acumula para evaluar el siguiente.
            {
                int camino = 0, dNivel = 0;
                std::string alumno = grupos[i].getDato(j), sujeto = pruebas[i].front();
                if(sujeto != alumno)
                {
                    camino = grupos[i].caminoEntreNodos(sujeto, alumno).size() - 2;   // El menos dos dado que el método devuelve una lista de todos los nodos inluyendo a los objetivos
                    dNivel = abs(grupos[i].nivelNodo(alumno) - grupos[i].nivelNodo(sujeto));  // que son dos xd.
                    sumaGrupo += camino * dNivel;
                } 
            }
            pruebas[i].pop_front();
        }
        resultados.push_back(sumaGrupo);
    }

    int ganador = mayor(resultados);  //Se decide al ganador con esta función.

    std::cout << ganador << "\n";   // Se enseña al ganador.
}

int mayor(std::vector<int>& resultados)    // Busca el índice del grupo que obtuvo el mayor MUP.
{
    int max = INT_MIN, indice;
    for(int i = 0; i < resultados.size(); i++)
    {
        if(resultados[i] > max)
        {
            indice = i;
            max = resultados[i];
        }
    }

    return indice + 1;
}


// Gracias por leer c: