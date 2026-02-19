#include <iostream>
#include "../include/Lista.hpp"

int main() {
    Lista<int> l = Lista<int>::fromVector({1, 2, 3, 4, 5, 6});
    Lista<int> result = l.partialReorderOddEvenSorted();

    std::cout << "partialReorder mod1: " << result << "\n";
    // Salida esperada: [1, 2, 3, 4, 5, 6]
    return 0;
}
