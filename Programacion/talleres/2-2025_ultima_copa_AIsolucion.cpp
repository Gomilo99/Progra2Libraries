#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <cctype>
#include "../include/Lista.hpp"

using namespace std;

struct Invitado {
    string nombre;
    int idOriginal;

    Invitado() : nombre(""), idOriginal(0) {}
    Invitado(const string& n, int id) : nombre(n), idOriginal(id) {}
};

static string trim(const string& s);
static void replaceAll(string& s, const string& from, const string& to);
static string normalizeQuotes(string s);
static Lista<string> splitCSVSimpleToLista(string s);
static int avanzarCircular(int posicionActual, int pasos, int direccion, int m);

int main() {
    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool primeraLineaSalida = true;

    for (int caso = 1; caso <= t; ++caso) {
        string lineaNums;
        string lineaNombres;

        getline(cin, lineaNums);
        getline(cin, lineaNombres);

        int K, P, Q;
        stringstream ss(lineaNums);
        ss >> K >> P >> Q;

        Lista<string> nombres = splitCSVSimpleToLista(lineaNombres);

        Lista<Invitado> vivos;
        for (int i = 1; i <= nombres.getLong(); ++i) {
            Invitado inv(nombres.consultar(i), i);
            vivos.insertar(inv, vivos.getLong() + 1);
        }

        int direccion = 1;
        int posicionActual = 1;

        while (vivos.getLong() > 1) {
            int m = vivos.getLong();

            int posicionEliminado = avanzarCircular(posicionActual, K - 1, direccion, m);
            Invitado eliminado = vivos.consultar(posicionEliminado);
            vivos.eliminar(posicionEliminado);

            if (eliminado.idOriginal % 2 == 0) {
                K = P;
            } else {
                K = Q;
            }

            int mNuevo = vivos.getLong();
            if (mNuevo == 1) {
                break;
            }

            if (direccion == 1) {
                posicionActual = posicionEliminado - 1;
                if (posicionActual < 1) {
                    posicionActual = mNuevo;
                }
            } else {
                posicionActual = posicionEliminado;
                if (posicionActual > mNuevo) {
                    posicionActual = 1;
                }
            }

            direccion = -direccion;
        }

        if (!primeraLineaSalida) {
            cout << "\n";
        }
        cout << vivos.consultar(1).nombre;
        primeraLineaSalida = false;
    }

    return 0;
}

// Quita espacios al inicio y al final de un string.
static string trim(const string& s) {
    size_t i = 0;
    size_t j = s.size();

    while (i < j && isspace((unsigned char)s[i])) {
        ++i;
    }

    while (j > i && isspace((unsigned char)s[j - 1])) {
        --j;
    }

    return s.substr(i, j - i);
}

// Reemplaza todas las apariciones de 'from' por 'to' dentro de 's'.
static void replaceAll(string& s, const string& from, const string& to) {
    size_t pos = 0;
    while ((pos = s.find(from, pos)) != string::npos) {
        s.replace(pos, from.size(), to);
        pos += to.size();
    }
}

// Convierte comillas tipográficas UTF-8 (“ ”) a comillas ASCII (").
static string normalizeQuotes(string s) {
    replaceAll(s, "\xE2\x80\x9C", "\"");
    replaceAll(s, "\xE2\x80\x9D", "\"");
    return s;
}

// Parser CSV simple: separa por comas fuera de comillas y admite "" como comilla escapada.
static Lista<string> splitCSVSimpleToLista(string s) {
    s = normalizeQuotes(s);

    Lista<string> out;
    string current;
    bool inQuotes = false;

    for (size_t i = 0; i < s.size(); ++i) {
        char ch = s[i];

        if (ch == '"') {
            if (inQuotes && i + 1 < s.size() && s[i + 1] == '"') {
                current.push_back('"');
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

// Avanza en forma circular sobre posiciones 1..m.
// direccion = 1  -> sentido horario (índices crecientes)
// direccion = -1 -> sentido antihorario (índices decrecientes)
static int avanzarCircular(int posicionActual, int pasos, int direccion, int m) {
    int base = posicionActual - 1;
    int p = pasos % m;

    if (direccion == 1) {
        return ((base + p) % m) + 1;
    }

    int r = (base - p) % m;
    if (r < 0) {
        r += m;
    }
    return r + 1;
}
