#include <iostream>
#include <vector>
#include "../include/Ejercicios.hpp"

using namespace std;

int main() {
    cout << "==== PRUEBA DE EJERCICIOS LPC (C++11) ====\n\n";

    // -------------------------------------------------
    // 1) sortedIntersect
    // -------------------------------------------------
    {
        vector<int> aData = {1, 2, 3, 4, 5, 6, 7};
        vector<int> bData = {4, 5, 9, 12, 15};
        Lista<int> a = Lista<int>::fromVector(aData);
        Lista<int> b = Lista<int>::fromVector(bData);
        Lista<int> r = sortedIntersect(a, b);
        cout << "sortedIntersect: " << r << "  // Esperada: [4, 5]\n";
    }

    // -------------------------------------------------
    // 2) compact / expand
    // -------------------------------------------------
    {
        vector<int> data = {1, 1, 1, 3, 3, 3, 5, 5};
        Lista<int> l = Lista<int>::fromVector(data);
        Lista<Lista<int> > c = compact(l);

        cout << "compact: [";
        for (int i = 1; i <= c.getLong(); ++i) {
            cout << c.consultar(i);
            if (i < c.getLong()) cout << ", ";
        }
        cout << "]  // Esperada: [[1, 3], [3, 3], [5, 2]]\n";

        Lista<int> ex = expand(c);
        cout << "expand(compact): " << ex << "  // Esperada: [1, 1, 1, 3, 3, 3, 5, 5]\n";
    }

    // -------------------------------------------------
    // 3) mediaMovil
    // -------------------------------------------------
    {
        vector<float> data = {1, 2, 3, 4, 5};
        Lista<float> l = Lista<float>::fromVector(data);
        Lista<float> r = mediaMovil(l, 3);
        cout << "mediaMovil: " << r << "  // Esperada aprox: [2, 3, 4]\n";
    }

    // -------------------------------------------------
    // 4) rollingStandardDeviation
    // -------------------------------------------------
    {
        vector<float> data = {1, 2, 3, 4, 5};
        Lista<float> l = Lista<float>::fromVector(data);
        Lista<float> r = rollingStandardDeviation(l, 3);
        cout << "rollingStandardDeviation: " << r << "  // Esperada aprox: [0.816, 0.816, 0.816]\n";
    }

    // -------------------------------------------------
    // 5) localInversionsInWindows
    // -------------------------------------------------
    {
        vector<int> data = {4, 3, 2, 1, 2, 3};
        Lista<int> l = Lista<int>::fromVector(data);
        Lista<int> r = localInversionsInWindows(l, 4);
        cout << "localInversionsInWindows: " << r << "  // Esperada: [3, 2, 1]\n";
    }

    // -------------------------------------------------
    // 6) longestZigZagSublist
    // -------------------------------------------------
    {
        vector<int> data = {1, 3, 2, 4, 3, 5, 5, 2};
        Lista<int> l = Lista<int>::fromVector(data);
        int r = longestZigZagSublist(l);
        cout << "longestZigZagSublist: " << r << "  // Esperada: 6\n";
    }

    // -------------------------------------------------
    // 7) longestParityAlternatingSublist
    // -------------------------------------------------
    {
        vector<int> data = {1, 3, 2, 4, 3, 5, 5, 2};
        Lista<int> l = Lista<int>::fromVector(data);
        int r = longestParityAlternatingSublist(l);
        cout << "longestParityAlternatingSublist: " << r << "  // Esperada: 2\n";
    }

    // -------------------------------------------------
    // 8) trendChangesInWindows
    // -------------------------------------------------
    {
        vector<int> data = {1, 3, 2, 4, 3, 5};
        Lista<int> l = Lista<int>::fromVector(data);
        Lista<int> r = trendChangesInWindows(l, 4);
        cout << "trendChangesInWindows: " << r << "  // Esperada: [2, 2, 2]\n";
    }

    // -------------------------------------------------
    // 9) Métodos de Lista de parciales (pointer-only)
    // -------------------------------------------------
    {
        vector<int> d1 = {1, 2, 3, 4, 5, 6, 7};
        Lista<int> l1 = Lista<int>::fromVector(d1);
        l1.reorderOddAndEven();
        cout << "reorderOddAndEven: " << l1 << "  // Esperada: [1, 3, 5, 7, 2, 4, 6]\n";

        vector<int> d2 = {1, 2, 3, 4, 5};
        Lista<int> l2 = Lista<int>::fromVector(d2);
        l2.rightShift(2);
        cout << "rightShift(2): " << l2 << "  // Esperada: [4, 5, 1, 2, 3]\n";

        vector<int> d3 = {1, 2, 3, 4, 5, 6};
        Lista<int> l3 = Lista<int>::fromVector(d3);
        Lista<int> r3 = l3.partialReorderOddEvenSorted();
        cout << "partialReorderOddEvenSorted: " << r3 << "  // Esperada: [1, 2, 3, 4, 5, 6]\n";

        vector<int> d4 = {1, 4, 7, 10, 2, 3, 9, 11};
        Lista<int> l4 = Lista<int>::fromVector(d4);
        Lista<int> r4 = l4.partialReorderHalvesSorted();
        cout << "partialReorderHalvesSorted: " << r4 << "  // Esperada: [1, 2, 3, 4, 7, 9, 10, 11]\n";
    }

    return 0;
}
