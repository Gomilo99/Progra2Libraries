#include <iostream>
#include "../include/Ejercicios.hpp"

int main() {
    Lista<int> target = Lista<int>::fromVector({1, 3, 2, 4, 3, 5});
    Lista<int> result = trendChangesInWindows(target, 4);

    std::cout << "trendChangesInWindows(k=4): " << result << "\n";
    // Salida esperada: [2, 2, 2]
    return 0;
}
