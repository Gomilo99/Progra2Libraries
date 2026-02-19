#ifndef EJERCICIOS_HPP
#define EJERCICIOS_HPP

#include <cmath>
#include <stdexcept>
#include "Lista.hpp"
#include "Cola.hpp"

inline Lista<int> sortedIntersect(Lista<int> a, Lista<int> b) {
    Lista<int> result;
    while (!a.esVacia() && !b.esVacia()) {
        int valorA = a.consultar(1);
        int valorB = b.consultar(1);

        if (valorA == valorB) {
            result.insertar(valorA, result.getLong() + 1);
            a.eliminar(1);
            b.eliminar(1);
        } else if (valorA < valorB) {
            a.eliminar(1);
        } else {
            b.eliminar(1);
        }
    }
    return result;
}

inline Lista<Lista<int>> compact(Lista<int> target) {
    Lista<Lista<int>> result;
    if (target.esVacia()) {
        return result;
    }

    int actual = target.consultar(1);
    int contador = 0;

    while (!target.esVacia()) {
        int valor = target.consultar(1);
        target.eliminar(1);

        if (valor == actual) {
            ++contador;
        } else {
            Lista<int> par;
            par.insertar(actual, 1);
            par.insertar(contador, 2);
            result.insertar(par, result.getLong() + 1);
            actual = valor;
            contador = 1;
        }
    }

    Lista<int> par;
    par.insertar(actual, 1);
    par.insertar(contador, 2);
    result.insertar(par, result.getLong() + 1);

    return result;
}

inline Lista<int> expand(Lista<Lista<int>> target) {
    Lista<int> result;

    while (!target.esVacia()) {
        Lista<int> par = target.consultar(1);
        target.eliminar(1);

        int valor = par.consultar(1);
        int repeticiones = par.consultar(2);

        for (int i = 0; i < repeticiones; ++i) {
            result.insertar(valor, result.getLong() + 1);
        }
    }

    return result;
}

inline Lista<float> mediaMovil(Lista<float> target, int window) {
    if (window <= 0) {
        throw std::invalid_argument("window debe ser positivo");
    }

    Lista<float> result;
    Cola<float> cola;
    float suma = 0.0f;

    while (!target.esVacia()) {
        float valor = target.consultar(1);
        target.eliminar(1);

        cola.encolar(valor);
        suma += valor;

        if (cola.getLong() > window) {
            suma -= cola.getFrente();
            cola.desencolar();
        }

        if (cola.getLong() == window) {
            result.insertar(suma / window, result.getLong() + 1);
        }
    }

    return result;
}

inline Lista<float> rollingStandardDeviation(Lista<float> target, int window) {
    if (window <= 0) {
        throw std::invalid_argument("window debe ser positivo");
    }

    Lista<float> result;
    Cola<float> cola;
    float suma = 0.0f;
    float sumaCuadrados = 0.0f;

    while (!target.esVacia()) {
        float valor = target.consultar(1);
        target.eliminar(1);

        cola.encolar(valor);
        suma += valor;
        sumaCuadrados += valor * valor;

        if (cola.getLong() > window) {
            float frente = cola.getFrente();
            cola.desencolar();
            suma -= frente;
            sumaCuadrados -= frente * frente;
        }

        if (cola.getLong() == window) {
            float media = suma / window;
            float varianza = (sumaCuadrados / window) - (media * media);
            if (varianza < 0.0f) {
                varianza = 0.0f;
            }
            result.insertar(std::sqrt(varianza), result.getLong() + 1);
        }
    }

    return result;
}

inline Lista<int> localInversionsInWindows(Lista<int> target, int k) {
    if (k <= 1) {
        Lista<int> vacia;
        return vacia;
    }

    Lista<int> result;
    Cola<int> window;
    int counter = 0;

    for (int i = 1; i <= k && !target.esVacia(); ++i) {
        int actual = target.consultar(1);
        target.eliminar(1);

        if (window.getLong() >= 1 && window.getUltimo() > actual) {
            ++counter;
        }

        window.encolar(actual);
    }

    if (window.getLong() == k) {
        result.insertar(counter, result.getLong() + 1);
    }

    while (!target.esVacia()) {
        int primero = window.getFrente();
        int siguientePrimero;

        window.desencolar();
        if (!window.esVacia()) {
            siguientePrimero = window.getFrente();
            if (primero > siguientePrimero) {
                --counter;
            }
        }

        int actual = target.consultar(1);
        target.eliminar(1);

        if (!window.esVacia() && window.getUltimo() > actual) {
            ++counter;
        }

        window.encolar(actual);
        result.insertar(counter, result.getLong() + 1);
    }

    return result;
}

inline int longestZigZagSublist(Lista<int> target) {
    if (target.getLong() < 3) {
        return target.getLong();
    }

    int ant2 = target.consultar(1);
    target.eliminar(1);
    int ant1 = target.consultar(1);
    target.eliminar(1);

    int counter = 0;
    int maxCounter = 0;

    while (!target.esVacia()) {
        int actual = target.consultar(1);
        target.eliminar(1);

        if ((ant2 < ant1 && ant1 > actual) || (ant2 > ant1 && ant1 < actual)) {
            ++counter;
        } else {
            if (counter > maxCounter) {
                maxCounter = counter;
            }
            counter = 0;
        }

        ant2 = ant1;
        ant1 = actual;
    }

    if (counter > maxCounter) {
        maxCounter = counter;
    }

    if (maxCounter == 0) {
        return 1;
    }

    return maxCounter + 2;
}

inline int longestParityAlternatingSublist(Lista<int> target) {
    if (target.esVacia()) {
        return 0;
    }

    int maxLen = 1;
    int actualLen = 1;
    int anterior = target.consultar(1);
    target.eliminar(1);

    while (!target.esVacia()) {
        int actual = target.consultar(1);
        target.eliminar(1);

        bool alterna = ((anterior % 2 == 0) && (actual % 2 != 0)) || ((anterior % 2 != 0) && (actual % 2 == 0));
        if (alterna) {
            ++actualLen;
        } else {
            actualLen = 1;
        }

        if (actualLen > maxLen) {
            maxLen = actualLen;
        }

        anterior = actual;
    }

    return maxLen;
}

inline Lista<int> trendChangesInWindows(Lista<int> target, int k) {
    Lista<int> result;
    if (k <= 1 || target.getLong() < k) {
        return result;
    }

    Cola<int> window;
    Cola<int> signos;
    int counter = 0;

    for (int i = 1; i <= k; ++i) {
        int actual = target.consultar(1);
        target.eliminar(1);

        int signoActual = 0;
        if (window.getLong() >= 1) {
            if (window.getUltimo() < actual) {
                signoActual = 1;
            } else if (window.getUltimo() > actual) {
                signoActual = -1;
            }

            if (signos.getLong() > 0) {
                int s1 = signos.getUltimo();
                if ((s1 == 1 && signoActual == -1) || (s1 == -1 && signoActual == 1)) {
                    ++counter;
                }
            }
            signos.encolar(signoActual);
        }

        window.encolar(actual);
    }

    result.insertar(counter, result.getLong() + 1);

    while (!target.esVacia()) {
        window.desencolar();

        int s1 = signos.getFrente();
        signos.desencolar();
        int s2 = signos.getFrente();

        if ((s1 == 1 && s2 == -1) || (s1 == -1 && s2 == 1)) {
            --counter;
        }

        int actual = target.consultar(1);
        target.eliminar(1);

        int signoActual = 0;
        if (window.getUltimo() < actual) {
            signoActual = 1;
        } else if (window.getUltimo() > actual) {
            signoActual = -1;
        }

        s1 = signos.getUltimo();
        if ((s1 == 1 && signoActual == -1) || (s1 == -1 && signoActual == 1)) {
            ++counter;
        }

        signos.encolar(signoActual);
        window.encolar(actual);
        result.insertar(counter, result.getLong() + 1);
    }

    return result;
}

#endif
