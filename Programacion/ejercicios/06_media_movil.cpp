#include <iostream>
#include "../include/Ejercicios.hpp"

int main() {
    Lista<float> target = Lista<float>::fromVector({1, 2, 3, 4, 5});
    Lista<float> result = mediaMovil(target, 3);

    std::cout << "mediaMovil(window=3): " << result << "\n";
    // Salida esperada aproximada: [2, 3, 4]
    return 0;
}
