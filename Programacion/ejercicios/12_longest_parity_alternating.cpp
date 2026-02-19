#include <iostream>
#include "../include/Ejercicios.hpp"

int main() {
    Lista<int> target = Lista<int>::fromVector({1, 3, 2, 4, 3, 5, 5, 2});
    int result = longestParityAlternatingSublist(target);

    std::cout << "longestParityAlternatingSublist: " << result << "\n";
    // Salida esperada: 2
    return 0;
}
