#include <iostream>
#include "../include/Lista.hpp"
#include "../include/Cola.hpp"
#include "../include/Pila.hpp"
#include "../include/Ejercicios.hpp"
#include <string>
#include <sstream>
#include <limits>
#include <cctype>
using namespace std;

static string trim(const string& s);
static void replaceAll(string& s, const string& from, const string& to);
static string normalizeQuotes(string s);
static Lista<string> splitCSVSimpleToLista(string s);

int main() {
    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    bool firstLine = true;

    for (int caso = 1; caso <= t; ++caso) {
        string lineaNums, lineaNombres;
        getline(cin, lineaNums);      // ej: 4 5 2
        getline(cin, lineaNombres);   // ej: “alvaro...”, “tobias”, ...

        int n, a, b;
        stringstream ss(lineaNums);
        ss >> n >> a >> b;

        Lista<string> nombres = splitCSVSimpleToLista(lineaNombres);
        
        
        if (!firstLine) cout << "\n";
        cout << "Caso " << caso << ": n=" << n << ", a=" << a << ", b=" << b;
        firstLine = false;
        for (int i = 1; i <= nombres.getLong(); ++i) {
            cout << "\n" << nombres.consultar(i);
        }
    }
    

    return 0;
}

//Elimina espacios laterales de cada campo parseado. " hola " pasa a "hola"
static string trim(const string& s) {
    size_t i = 0, j = s.size();
    while (i < j && isspace((unsigned char)s[i])) ++i;
    while (j > i && isspace((unsigned char)s[j - 1])) --j;
    return s.substr(i, j - i);
}

// Reemplaza todas las ocurrencias de 'from' por 'to' en la cadena 's'. Ejemplo: replaceAll(s, "a", "x") convierte "banana" en "bxnxnx".
static void replaceAll(string& s, const string& from, const string& to) {
    size_t pos = 0;
    while ((pos = s.find(from, pos)) != string::npos) {
        s.replace(pos, from.size(), to);
        pos += to.size();
    }
}

// Normaliza comillas tipográficas a comillas estándar. Ejemplo: “hola” pasa a "hola"
static string normalizeQuotes(string s) {
    replaceAll(s, "\xE2\x80\x9C", "\""); // “
    replaceAll(s, "\xE2\x80\x9D", "\""); // ”
    return s;
}

// Parsea una línea CSV simple (sin saltos de línea dentro de campos) a una Lista<string>. Maneja comillas dobles para campos con comas. Ejemplo: splitCSVSimpleToLista("“alvaro...”, “tobias”, ...") devuelve una Lista con "alvaro...", "tobias", ...
static Lista<string> splitCSVSimpleToLista(string s) {
    s = normalizeQuotes(s);

    Lista<string> out;
    string current;
    bool inQuotes = false;

    for (size_t i = 0; i < s.size(); ++i) {
        char ch = s[i];

        if (ch == '"') {
            if (inQuotes && i + 1 < s.size() && s[i + 1] == '"') {
                current.push_back('"'); // comilla escapada ""
                ++i;
            } else {
                inQuotes = !inQuotes;
            }
        } else if (ch == ',' && !inQuotes) {
            out.insertar(trim(current), out.getLong() + 1);
            current.clear();
        } else {
            current.push_back(ch);
        }
    }

    out.insertar(trim(current), out.getLong() + 1);
    return out;
}