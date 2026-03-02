#include <iostream>
#include <vector>
#include "../include/Lista.hpp"

using namespace std;

int main() {
    vector<int> data = {1, 2, 3, 4, 5, 6, 7};
    Lista<int> l = Lista<int>::fromVector(data);
    
    l.reorderOddAndEven();

    cout << "reorderOddAndEven: " << l << "  // Esperada: [1, 3, 5, 7, 2, 4, 6]\n";
    return 0;
}
