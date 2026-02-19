#include <iostream>
#include "../include/Ejercicios.hpp"

int main() {
    Lista<int> target = Lista<int>::fromVector({4, 3, 2, 1, 2, 3});
    Lista<int> result = localInversionsInWindows(target, 4);

    std::cout << "localInversionsInWindows(k=4): " << result << "\n";
    // Salida esperada: [3, 2, 1]
    return 0;
}
