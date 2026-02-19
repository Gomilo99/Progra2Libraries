#include <iostream>
#include "../include/Lista.hpp"

int main() {
    Lista<int> target = Lista<int>::fromVector({1, 4, 7, 10, 2, 3, 9, 11});
    Lista<int> result = target.partialReorderHalvesSorted();

    std::cout << "partialReorder mod2: " << result << "\n";
    // Salida esperada: [1, 2, 3, 4, 7, 9, 10, 11]
    return 0;
}
