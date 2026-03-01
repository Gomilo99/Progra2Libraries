#include <iostream>
#include "../include/Lista.hpp"

using namespace std;

int main() {
    int data[] = {1, 2, 3, 4, 5, 6};
    Lista<int> l;
    for (int i = 0; i < 6; ++i) l.insertar(data[i], l.getLong() + 1);
    Lista<int> result = l.partialReorderOddEvenSorted();

    cout << "partialReorderOddEvenSorted: " << result << "  // Esperada: [1, 2, 3, 4, 5, 6]\n";
    return 0;
}
