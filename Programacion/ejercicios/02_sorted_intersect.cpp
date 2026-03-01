#include <iostream>
#include "../include/Ejercicios.hpp"

using namespace std;

int main() {
    int va[] = {1, 2, 3, 4, 5, 6, 7};
    int vb[] = {4, 5, 9, 12, 15};

    Lista<int> a;
    Lista<int> b;
    for (int i = 0; i < 7; ++i) a.insertar(va[i], a.getLong() + 1);
    for (int i = 0; i < 5; ++i) b.insertar(vb[i], b.getLong() + 1);

    Lista<int> result = sortedIntersect(a, b);

    cout << "sortedIntersect: " << result << "  // Esperada: [4, 5]\n";
    return 0;
}
