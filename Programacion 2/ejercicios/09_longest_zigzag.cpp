#include <iostream>
#include "../include/Ejercicios.hpp"

using namespace std;

int main() {
    int data[] = {1, 3, 2, 4, 3, 5, 5, 2};
    Lista<int> target;
    for (int i = 0; i < 8; ++i) target.insertar(data[i], target.getLong() + 1);
    int result = longestZigZagSublist(target);

    cout << "longestZigZagSublist: " << result << "  // Esperada: 6\n";
    return 0;
}
