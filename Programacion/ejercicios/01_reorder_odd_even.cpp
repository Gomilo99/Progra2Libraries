#include <iostream>
#include "../include/Lista.hpp"

using namespace std;

int main() {
    Lista<int> l;
    int data[] = {1, 2, 3, 4, 5, 6, 7};
    int n = sizeof(data) / sizeof(data[0]);
    for (int i = 0; i < n; ++i) {
        l.insertar(data[i], l.getLong() + 1);
    }

    l.reorderOddAndEven();

    cout << "reorderOddAndEven: " << l << "  // Esperada: [1, 3, 5, 7, 2, 4, 6]\n";
    return 0;
}
