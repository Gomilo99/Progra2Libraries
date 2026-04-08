#include <iostream>
#include "../include/ArbolN.hpp"

// Usamos el espacio de nombres estandar para no escribir std:: en cada linea.
using namespace std;

// -----------------------------------------------------------------------------
// leerYConstruirCaso
// -----------------------------------------------------------------------------
// Objetivo:
// 1) Leer un caso de prueba desde entrada estandar.
// 2) Guardar eficiencias en una Lista (posicion id -> eficiencia).
// 3) Construir el arbol usando SOLO metodos del TAD ArbolN.
//
// Idea de construccion:
// - Primero leemos todas las aristas (padre, hijo) como pendientes.
// - Insertamos la raiz 1.
// - Damos pasadas sobre pendientes:
//   si se puede insertar, la quitamos;
//   si no, la volvemos a dejar para otra pasada.
// - Si en una pasada completa no se inserto nada, la entrada es invalida.
// -----------------------------------------------------------------------------
bool leerYConstruirCaso(int &cantidadNodos, Lista<int> &eficiencias, ArbolN<int> &arbol) {
    // Lee la cantidad de nodos del caso.
    if (!(cin >> cantidadNodos)) {
        // Si falla la lectura, no hay caso valido.
        return false;
    }

    // Limpia eficiencias por si se reutiliza la lista.
    eficiencias.vaciar();

    // Lee la eficiencia de cada nodo (del id 1 al id n).
    for (int id = 1; id <= cantidadNodos; ++id) {
        // Valor de eficiencia del nodo actual.
        int valor;
        // Lee el valor.
        cin >> valor;
        // Inserta al final: la posicion en la lista coincide con el id del nodo.
        eficiencias.insertar(valor, eficiencias.getLong() + 1);
    }

    // Guardan aristas aun no procesadas.
    Lista<int> padresPendientes;
    Lista<int> hijosPendientes;

    // Lee n-1 aristas del formato: padre hijo.
    for (int i = 1; i <= cantidadNodos - 1; ++i) {
        int padre;
        int hijo;
        // Lee una arista.
        cin >> padre >> hijo;
        // Guarda el padre al final de su lista.
        padresPendientes.insertar(padre, padresPendientes.getLong() + 1);
        // Guarda el hijo al final de su lista (misma posicion que su padre).
        hijosPendientes.insertar(hijo, hijosPendientes.getLong() + 1);
    }

    // Reinicia arbol antes de construir.
    arbol.construir();

    // Caso borde: arbol vacio.
    if (cantidadNodos == 0) {
        return true;
    }

    // Inserta la raiz. Si el arbol esta vacio, insertarNodo crea la raiz con e.
    // El parametro padre no se usa en ese escenario.
    arbol.insertarNodo(0, 1);

    // Mientras existan aristas pendientes por insertar.
    while (!padresPendientes.esVacia()) {
        // Cantidad de pendientes al inicio de esta pasada.
        int pendientesActuales = padresPendientes.getLong();
        // Marca si esta pasada logro insertar al menos una arista.
        bool huboProgreso = false;

        // Procesa exactamente las pendientes que habia al iniciar la pasada.
        for (int i = 1; i <= pendientesActuales; ++i) {
            // Toma la primera arista pendiente.
            int padre = padresPendientes.consultar(1);
            int hijo = hijosPendientes.consultar(1);

            // La saca temporalmente de pendientes.
            padresPendientes.eliminar(1);
            hijosPendientes.eliminar(1);

            try {
                // Intenta insertar hijo bajo padre.
                arbol.insertarNodo(padre, hijo);
                // Si inserto, hubo avance real.
                huboProgreso = true;
            } catch (...) {
                // Si no pudo insertar, la arista vuelve a pendientes.
                padresPendientes.insertar(padre, padresPendientes.getLong() + 1);
                hijosPendientes.insertar(hijo, hijosPendientes.getLong() + 1);
            }
        }

        // Si no hubo ningun avance, la entrada no permite construir el arbol.
        if (!huboProgreso) {
            return false;
        }
    }

    // Si no quedan pendientes, el arbol se construyo completo.
    return true;
}

/*
MSI (maxima suma independiente) explicado simple:
1) incluir: tomo este nodo, entonces solo puedo sumar "excluir" de cada hijo.
2) excluir: no tomo este nodo, entonces de cada hijo tomo el mejor entre incluir/excluir.

Esta funcion recorre el arbol en DFS y devuelve dos resultados por referencia:
- incluir: mejor suma si obligatoriamente el nodo actual SI se toma.
- excluir: mejor suma si obligatoriamente el nodo actual NO se toma.
*/
void msiDfs(const ArbolN<int> &arbol, const Lista<int> &eficiencias, long &incluir, long &excluir) {
    // Caso base: arbol vacio.
    if (arbol.esNulo()) {
        // Si no hay nodo, ambas sumas son cero.
        incluir = 0;
        excluir = 0;
        return;
    }

    // Id del nodo actual (en este modelo, el valor almacenado es el id).
    int idNodo = arbol.getRaiz();

    // Si incluyo este nodo, empiezo con su propia eficiencia.
    incluir = eficiencias.consultar(idNodo);

    // Si excluyo este nodo, inicio en cero y sumo aportes de hijos.
    excluir = 0;

    // Obtiene lista de subarboles hijos del nodo actual.
    Lista< ArbolN<int> > hijos = arbol.getHijos();

    // Recorre cada hijo para combinar sus dos estados.
    for (int i = 1; i <= hijos.getLong(); ++i) {
        // Resultado MSI del hijo i.
        long incluirHijo = 0;
        long excluirHijo = 0;

        // Resuelve recursivamente ese subarbol hijo.
        msiDfs(hijos.consultar(i), eficiencias, incluirHijo, excluirHijo);

        // Si incluyo nodo actual, no puedo incluir hijo directo.
        incluir += excluirHijo;

        // Si excluyo nodo actual, de cada hijo tomo su mejor opcion.
        if (incluirHijo > excluirHijo) {
            excluir += incluirHijo;
        } else {
            excluir += excluirHijo;
        }
    }
}

// Balance de hojas: hoja en nivel par suma +1, en impar suma -1.
int balanceDfs(const ArbolN<int>& arbol, int nivel) {
    // Caso base: arbol vacio no aporta balance.
    if (arbol.esNulo()) {
        return 0;
    }

    // Si es hoja, retorna segun la paridad del nivel.
    if (arbol.esHoja()) {
        return ((nivel % 2) == 0) ? 1 : -1;
    }

    // Acumulador del balance de todos los hijos.
    int balance = 0;

    // Obtiene subarboles hijos para bajar un nivel.
    Lista< ArbolN<int> > hijos = arbol.getHijos();

    // Suma recursivamente el balance de cada hijo.
    for (int i = 1; i <= hijos.getLong(); ++i) {
        balance += balanceDfs(hijos.consultar(i), nivel + 1);
    }

    // Retorna el balance total del subarbol actual.
    return balance;
}

int main() {
    // Cantidad total de casos de prueba.
    int cantidadCasos;
    // Lee t.
    cin >> cantidadCasos;

    // Procesa cada caso de prueba.
    for (int caso = 1; caso <= cantidadCasos; ++caso) {
        // Se completara al leer el caso.
        int cantidadNodos = 0;
        // Eficiencias por id (posicion = id).
        Lista<int> eficiencias;
        // Arbol del caso actual.
        ArbolN<int> arbol;

        // Lee y construye el caso completo.
        bool ok = leerYConstruirCaso(cantidadNodos, eficiencias, arbol);

        // Valor por defecto si hay error o caso vacio.
        long respuesta = 0;

        // Solo resuelve si la lectura/construccion fue correcta.
        if (ok && cantidadNodos > 0 && !arbol.esNulo()) {
            // Estado MSI en la raiz.
            long incluir = 0;
            long excluir = 0;

            // Calcula MSI.
            msiDfs(arbol, eficiencias, incluir, excluir);

            // MSI final: maximo entre incluir o excluir la raiz.
            long msi = (incluir > excluir) ? incluir : excluir;

            // Calcula balance par-impar de hojas.
            int balance = balanceDfs(arbol, 0);

            // Definicion del problema: CHUPA = MSI * Balance.
            respuesta = msi * balance;
        }

        // Imprime respuesta del caso actual.
        cout << respuesta;

        // Salto de linea entre casos, excepto despues del ultimo.
        if (caso < cantidadCasos) {
            cout << "\n";
        }
    }

    // Fin de programa.
    return 0;
}
