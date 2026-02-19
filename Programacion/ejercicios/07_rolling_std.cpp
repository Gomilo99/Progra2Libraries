#include <iostream>
#include "../include/Ejercicios.hpp"

int main() {
    Lista<float> target = Lista<float>::fromVector({1, 2, 3, 4, 5});
    Lista<float> result = rollingStandardDeviation(target, 3);

    std::cout << "rollingStandardDeviation(window=3): " << result << "\n";
    // Salida esperada aproximada: [0.816, 0.816, 0.816]
    return 0;
}
