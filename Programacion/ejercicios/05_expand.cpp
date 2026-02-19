#include <iostream>
#include "../include/Ejercicios.hpp"

int main() {
    Lista<Lista<int>> target;

    Lista<int> a; a.insertar(1, 1); a.insertar(3, 2);
    Lista<int> b; b.insertar(3, 1); b.insertar(2, 2);
    Lista<int> c; c.insertar(5, 1); c.insertar(1, 2);
    Lista<int> d; d.insertar(6, 1); d.insertar(3, 2);

    target.insertar(a, 1);
    target.insertar(b, 2);
    target.insertar(c, 3);
    target.insertar(d, 4);

    Lista<int> result = expand(target);
    std::cout << "expand: " << result << "\n";
    // Salida esperada: [1, 1, 1, 3, 3, 5, 6, 6, 6]
    return 0;
}
