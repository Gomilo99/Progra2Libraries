#include <iostream>
#include "../include/Ejercicios.hpp"

int main() {
    Lista<int> l = Lista<int>::fromVector({1, 1, 1, 3, 3, 3, 5, 5});
    Lista<Lista<int>> result = compact(l);

    std::cout << "compact: [";
    for (int i = 1; i <= result.getLong(); ++i) {
        std::cout << result.consultar(i);
        if (i < result.getLong()) std::cout << ", ";
    }
    std::cout << "]\n";
    // Salida esperada: [[1, 3], [3, 3], [5, 2]]
    return 0;
}
