#include <iostream>
#include "../include/Ejercicios.hpp"

using namespace std;

int main() {
    float data[] = {1, 2, 3, 4, 5};
    Lista<float> target;
    for (int i = 0; i < 5; ++i) target.insertar(data[i], target.getLong() + 1);
    Lista<float> result = mediaMovil(target, 3);

    cout << "mediaMovil: " << result << "  // Esperada aprox: [2, 3, 4]\n";
    return 0;
}
