#include <iostream>
#include "../include/Lista.hpp"

int main() {
    Lista<int> l = Lista<int>::fromVector({1, 2, 3, 4, 5});

    l.rightShift(2);

    std::cout << "rightShift(2): " << l << "\n";
    // Salida esperada: [4, 5, 1, 2, 3]
    return 0;
}
