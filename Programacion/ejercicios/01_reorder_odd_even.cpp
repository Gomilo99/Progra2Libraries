#include <iostream>
#include "../include/Lista.hpp"

int main() {
    Lista<int> l;
    for (int v : {1, 2, 3, 4, 5, 6, 7}) {
        l.insertar(v, l.getLong() + 1);
    }

    l.reorderOddAndEven();

    std::cout << "Resultado reorderOddAndEven: " << l << "\n";
    // Salida esperada: [1, 3, 5, 7, 2, 4, 6]
    return 0;
}
