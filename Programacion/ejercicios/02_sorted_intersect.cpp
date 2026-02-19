#include <iostream>
#include "../include/Ejercicios.hpp"

int main() {
    Lista<int> a = Lista<int>::fromVector({1, 2, 3, 4, 5, 6, 7});
    Lista<int> b = Lista<int>::fromVector({4, 5, 9, 12, 15});

    Lista<int> result = sortedIntersect(a, b);

    std::cout << "sortedIntersect: " << result << "\n";
    // Salida esperada: [4, 5]
    return 0;
}
