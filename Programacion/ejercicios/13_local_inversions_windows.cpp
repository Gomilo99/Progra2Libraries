#include <iostream>
#include "../include/Ejercicios.hpp"

using namespace std;

int main() {
    int data[] = {4, 3, 2, 1, 2, 3};
    Lista<int> target;
    for (int i = 0; i < 6; ++i) target.insertar(data[i], target.getLong() + 1);
    Lista<int> result = localInversionsInWindows(target, 4);

    cout << "localInversionsInWindows: " << result << "  // Esperada: [3, 2, 1]\n";
    return 0;
}
