#include <iostream>
#include "../include/Ejercicios.hpp"

using namespace std;

int main() {
    float data[] = {1, 2, 3, 4, 5};
    Lista<float> target;
    for (int i = 0; i < 5; ++i) target.insertar(data[i], target.getLong() + 1);
    Lista<float> result = rollingStandardDeviation(target, 3);

    cout << "rollingStandardDeviation: " << result << "  // Esperada aprox: [0.816, 0.816, 0.816]\n";
    return 0;
}
