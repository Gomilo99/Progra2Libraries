#include <iostream>
#include "../include/Ejercicios.hpp"

int main() {
    Lista<int> target = Lista<int>::fromVector({1, 3, 2, 4, 3, 5, 5, 2});
    int result = longestZigZagSublist(target);

    std::cout << "longestZigZagSublist: " << result << "\n";
    // Salida esperada: 6
    return 0;
}
