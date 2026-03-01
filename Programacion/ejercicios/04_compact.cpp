#include <iostream>
#include "../include/Ejercicios.hpp"

using namespace std;

int main() {
    int data[] = {1, 1, 1, 3, 3, 3, 5, 5};
    Lista<int> l;
    for (int i = 0; i < 8; ++i) l.insertar(data[i], l.getLong() + 1);
    Lista<Lista<int> > result = compact(l);

    cout << "compact: [";
    for (int i = 1; i <= result.getLong(); ++i) {
        cout << result.consultar(i);
        if (i < result.getLong()) cout << ", ";
    }
    cout << "]  // Esperada: [[1, 3], [3, 3], [5, 2]]\n";
    return 0;
}
