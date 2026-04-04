#include <iostream>
#include <cassert>
#include "ArbolBin.hpp"
#include "ArbolN.hpp"

using namespace std;
/*
La macro assert evalúa una condición dada y, si resulta ser falsa, invoca la función interna 
    _assert para manejar la situación de error. Para generar un reporte detallado, transmite la 
    propia expresión evaluada como una cadena de texto, junto con las macros que indican el 
    archivo y el número de línea actuales.
    
La función plantilla assertListaEq verifica mediante aserciones que una estructura Lista<T> 
    coincida exactamente en longitud y contenido con un arreglo esperado de tamaño n. 
    Si la longitud o algún elemento difieren, la aserción falla evaluando el mensaje de 
    error msg proporcionado.

En este código, se definen dos funciones de prueba, probarArbolBinClase() y probarArbolNClase(),
    que verifican el correcto funcionamiento de las clases ArbolBin y ArbolN respectivamente. 
    Estas funciones utilizan assert para validar diversas operaciones como inserción, 
    eliminación, recorridos y copias de árboles. Si todas las aserciones pasan sin errores, 
    se imprimirá un mensaje de éxito al final del programa.
*/
template <typename T>
void assertListaEq(const Lista<T>& lista, const T* expected, int n, const char* msg) {
    assert(lista.getLong() == n && msg);
    for (int i = 1; i <= n; ++i) {
        assert(lista.consultar(i) == expected[i - 1] && msg);
    }
}

void probarArbolBinClase() {
    ArbolBin<int> a;
    assert(a.esNulo());
    assert(a.getPeso() == 0);

    a.insertarNodo(0, 1);
    a.insertarNodo(1, 2);
    a.insertarNodo(1, 3);
    a.insertarNodo(2, 4);
    a.insertarNodo(2, 5);
    a.insertarNodo(3, 6);

    assert(!a.esNulo());
    assert(a.getRaiz() == 1);
    assert(a.getPeso() == 6);
    assert(!a.esHoja());

    const int pre[] = {1, 2, 4, 5, 3, 6};
    const int in[] = {4, 2, 5, 1, 6, 3};
    const int post[] = {4, 5, 2, 6, 3, 1};
    const int niv[] = {1, 2, 3, 4, 5, 6};
    const int hojas[] = {4, 5, 6};

    assertListaEq(a.preOrden(), pre, 6, "preorden binario");
    assertListaEq(a.inOrden(), in, 6, "inorden binario");
    assertListaEq(a.postOrden(), post, 6, "postorden binario");
    assertListaEq(a.porNiveles(), niv, 6, "niveles binario");
    assertListaEq(a.getHojas(), hojas, 3, "hojas binario");

    ArbolBin<int> hi = a.getHijoIzq();
    assert(hi.getRaiz() == 2);
    assert(hi.getPeso() == 3);

    ArbolBin<int> hd = a.getHijoDer();
    assert(hd.getRaiz() == 3);
    assert(hd.getPeso() == 2);

    ArbolBin<int> copia;
    copia.construir(a);
    assert(copia.getPeso() == 6);
    assert(copia.getRaiz() == 1);

    a.eliminarNodo(2, 4);
    assert(a.getPeso() == 5);

    a.vaciar();
    assert(a.esNulo());

    copia.destruir();
    assert(copia.esNulo());
}

void probarArbolNClase() {
    ArbolN<int> a;
    assert(a.esNulo());
    assert(a.getPeso() == 0);

    a.insertarNodo(0, 1);
    a.insertarNodo(1, 2);
    a.insertarNodo(1, 3);
    a.insertarNodo(1, 4);
    a.insertarNodo(2, 5);
    a.insertarNodo(2, 6);
    a.insertarNodo(3, 7);
    a.insertarNodo(4, 8);

    assert(!a.esNulo());
    assert(a.getRaiz() == 1);
    assert(a.getPeso() == 8);
    assert(!a.esHoja());

    const int pre[] = {1, 2, 5, 6, 3, 7, 4, 8};
    const int in[] = {5, 2, 6, 1, 7, 3, 8, 4};
    const int post[] = {5, 6, 2, 7, 3, 8, 4, 1};
    const int niv[] = {1, 2, 3, 4, 5, 6, 7, 8};
    const int hojas[] = {5, 6, 7, 8};

    assertListaEq(a.preOrden(), pre, 8, "preorden n-ario");
    assertListaEq(a.inOrden(), in, 8, "inorden n-ario");
    assertListaEq(a.postOrden(), post, 8, "postorden n-ario");
    assertListaEq(a.porNiveles(), niv, 8, "niveles n-ario");
    assertListaEq(a.getHojas(), hojas, 4, "hojas n-ario");

    Lista<ArbolN<int> > hijos = a.getHijos();
    assert(hijos.getLong() == 3);
    assert(hijos.consultar(1).getRaiz() == 2);
    assert(hijos.consultar(2).getRaiz() == 3);
    assert(hijos.consultar(3).getRaiz() == 4);

    ArbolN<int> copia;
    copia.construir(a);
    assert(copia.getPeso() == 8);
    assert(copia.getRaiz() == 1);

    a.eliminarNodo(2, 5);
    assert(a.getPeso() == 7);

    a.vaciar();
    assert(a.esNulo());

    copia.destruir();
    assert(copia.esNulo());
}

int main() {
    probarArbolBinClase();
    probarArbolNClase();
    cout << "OK - metodos de clase (ArbolBin y ArbolN)" << endl;
    return 0;
}
