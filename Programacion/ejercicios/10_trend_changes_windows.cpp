#include <iostream>
#include "../include/Ejercicios.hpp"

using namespace std;

int main() {
    int data[] = {1, 3, 2, 4, 3, 5};
    Lista<int> target;
    for (int i = 0; i < 6; ++i) target.insertar(data[i], target.getLong() + 1);
    Lista<int> result = trendChangesInWindows(target, 4);

    cout << "trendChangesInWindows: " << result << "  // Esperada: [2, 2, 2]\n";
    return 0;
}
