#include <iostream>
#include <cassert>
#include "ArbolBin.hpp"
#include "ArbolN.hpp"
#include "Personaje.hpp"

using namespace std;

/*¨
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
*/
template <typename T>
void assertListaEq(const Lista<T>& lista, const T* expected, int n, const char* msg) {
    assert(lista.getLong() == n && msg);
    for (int i = 1; i <= n; ++i) {
        assert(lista.consultar(i) == expected[i - 1] && msg);
    }
}

ArbolBin<int> crearArbolBinEjercicio() {
    ArbolBin<int> a;
    a.insertarNodo(0, 1);
    a.insertarNodo(1, 2);
    a.insertarNodo(1, 3);
    a.insertarNodo(2, 4);
    a.insertarNodo(2, 5);
    a.insertarNodo(3, 6);
    a.insertarNodo(3, 7);
    return a;
}

ArbolN<int> crearArbolNEjercicio() {
    ArbolN<int> a;
    a.insertarNodo(0, 10);
    a.insertarNodo(10, 4);
    a.insertarNodo(10, 8);
    a.insertarNodo(10, 6);
    a.insertarNodo(4, 1);
    a.insertarNodo(4, 3);
    a.insertarNodo(6, 5);
    a.insertarNodo(6, 7);
    return a;
}

void probarEjerciciosArbolBin() {
    ArbolBin<int> a = crearArbolBinEjercicio();

    ArbolBin<int> iso;
    iso.insertarNodo(0, 9);
    iso.insertarNodo(9, 8);
    iso.insertarNodo(9, 7);
    iso.insertarNodo(8, 6);
    iso.insertarNodo(8, 5);
    iso.insertarNodo(7, 4);
    iso.insertarNodo(7, 3);

    assert(a.esIsomorfo(iso));

    iso.eliminarNodo(7, 3);
    assert(!a.esIsomorfo(iso));

    assert(a.lca(4, 5) == 2);
    assert(a.estaEnCamino(2, 4, 7));
    assert(!a.estaEnCamino(6, 4, 7));

    assert(a.esLCA(1, 4, 7));
    assert(!a.esLCA(2, 4, 7));

    assert(a.profundidadLCA(4, 5) == 1);
    assert(a.profundidadLCA(4, 42) == -1);
}

void probarEjerciciosArbolN() {
    ArbolN<int> a = crearArbolNEjercicio();

    assert(a.sumaInterna() == 16);

    const int caminoEsperado[] = {1, 4, 10, 6, 7};
    assertListaEq(a.camino(1, 7), caminoEsperado, 5, "camino n-ario");

    const int primosEsperados[] = {5, 7};
    assertListaEq(a.getPrimos(1), primosEsperados, 2, "primos");

    const int maxLevelEsperado[] = {4, 8, 6};
    assertListaEq(a.getMaxLevel(), maxLevelEsperado, 3, "max level");

    const int sumsEsperadas[] = {10, 18, 16};
    assertListaEq(a.getLevelsSuml(), sumsEsperadas, 3, "suma niveles");

    const int avgEsperado[] = {10};
    assertListaEq(a.getLevelWithMaxAverage(), avgEsperado, 1, "max average");

    const int zigzagEsperado[] = {10, 6, 8, 4, 1, 3, 5, 7};
    assertListaEq(a.Zigzag(), zigzagEsperado, 8, "zigzag");
}

void probarPrincesaMasCercana() {
    Personaje inicio("Inicio", false, false);
    Personaje dragon("Smaug", true, false);
    Personaje aldeano("Aldeano", false, false);
    Personaje princesa("Leia", false, true);

    ArbolN<Personaje> a;
    a.insertarNodo(Personaje(), inicio);
    a.insertarNodo(inicio, dragon);
    a.insertarNodo(inicio, aldeano);
    a.insertarNodo(inicio, princesa);

    assert(a.princesaMasCercana() == "Leia");
}

int main() {
    probarEjerciciosArbolBin();
    probarEjerciciosArbolN();
    probarPrincesaMasCercana();

    cout << "OK - metodos de ejercicios (ArbolBin y ArbolN)" << endl;
    return 0;
}
