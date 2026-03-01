#include <iostream>
#include "../include/Lista.hpp"

using namespace std;

int main() {
    int data[] = {1, 4, 7, 10, 2, 3, 9, 11};
    Lista<int> target;
    for (int i = 0; i < 8; ++i) target.insertar(data[i], target.getLong() + 1);
    Lista<int> result = target.partialReorderHalvesSorted();

    cout << "partialReorderHalvesSorted: " << result << "  // Esperada: [1, 2, 3, 4, 7, 9, 10, 11]\n";
    return 0;
}
