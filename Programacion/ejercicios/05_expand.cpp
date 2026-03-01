#include <iostream>
#include "../include/Ejercicios.hpp"

using namespace std;

int main() {
    Lista<Lista<int> > target;

    Lista<int> a; a.insertar(1, 1); a.insertar(3, 2);
    Lista<int> b; b.insertar(3, 1); b.insertar(3, 2);
    Lista<int> c; c.insertar(5, 1); c.insertar(2, 2);

    target.insertar(a, 1);
    target.insertar(b, 2);
    target.insertar(c, 3);

    Lista<int> result = expand(target);
    cout << "expand(compact): " << result << "  // Esperada: [1, 1, 1, 3, 3, 3, 5, 5]\n";
    return 0;
}
