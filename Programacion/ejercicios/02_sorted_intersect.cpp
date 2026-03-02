#include <iostream>
#include <vector>
#include "../include/Ejercicios.hpp"

using namespace std;

int main() {
    vector<int> va = {1, 2, 3, 4, 5, 6, 7};
    vector<int> vb = {4, 5, 9, 12, 15};

    Lista<int> a = Lista<int>::fromVector(va);
    Lista<int> b = Lista<int>::fromVector(vb);

    Lista<int> result = sortedIntersect(a, b);

    cout << "sortedIntersect: " << result << "  // Esperada: [4, 5]\n";
    return 0;
}
