#include <iostream>
#include <vector>
#include "../include/Lista.hpp"

using namespace std;

int main() {
    vector<int> data = {1, 2, 3, 4, 5};
    Lista<int> result = Lista<int>::fromVector(data);

    result.rightShift(2);

    cout << "rightShift(2): " << result << "  // Esperada: [4, 5, 1, 2, 3]\n";
    return 0;
}
