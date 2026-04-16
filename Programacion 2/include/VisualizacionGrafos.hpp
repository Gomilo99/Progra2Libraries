#ifndef VISUALIZACION_GRAFOS_HPP
#define VISUALIZACION_GRAFOS_HPP

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <cmath>
#include "Grafos.hpp"

using namespace std;

inline int vgMaxInt(int a, int b) {
    return (a > b) ? a : b;
}

inline string vgRepetir(char c, int n) {
    if (n <= 0) {
        return "";
    }
    return string((size_t)n, c);
}

inline string vgIntATexto(int valor) {
    ostringstream oss;
    oss << valor;
    return oss.str();
}

inline string vgFloatATexto(float valor, int decimales = 1) {
    ostringstream oss;
    oss << fixed << setprecision(decimales) << valor;
    return oss.str();
}

template <typename T>
string vgATexto(const T& valor) {
    ostringstream oss;
    oss << valor;
    return oss.str();
}

template <typename T>
void vgConstruirIndiceYVertices(const Grafo<T>& g,
                                map<T, int>& idDe,
                                vector<T>& verticeDe) {
    idDe.clear();
    verticeDe.clear();

    Lista<T> vertices = g.getVertices();
    int indice = 0;

    while (!vertices.esVacia()) {
        T v = vertices.consultar(1);
        vertices.eliminar(1);
        idDe[v] = indice;
        verticeDe.push_back(v);
        ++indice;
    }
}

template <typename T>
int vgAnchoMaxEtiqueta(const vector<T>& verticeDe) {
    int ancho = 1;

    for (int i = 0; i < (int)verticeDe.size(); ++i) {
        int largo = (int)vgATexto(verticeDe[i]).size();
        if (largo > ancho) {
            ancho = largo;
        }
    }

    return ancho;
}

inline string vgEscaparDot(const string& s) {
    string out;
    for (int i = 0; i < (int)s.size(); ++i) {
        char c = s[i];
        if (c == '\\' || c == '"') {
            out.push_back('\\');
        }
        out.push_back(c);
    }
    return out;
}

inline string vgEscaparXML(const string& s) {
    string out;
    for (int i = 0; i < (int)s.size(); ++i) {
        char c = s[i];
        if (c == '&') {
            out += "&amp;";
        } else if (c == '<') {
            out += "&lt;";
        } else if (c == '>') {
            out += "&gt;";
        } else if (c == '"') {
            out += "&quot;";
        } else if (c == '\'') {
            out += "&apos;";
        } else {
            out.push_back(c);
        }
    }
    return out;
}

inline double vgPI() {
    return 3.14159265358979323846;
}

struct vgPunto {
    double x;
    double y;
    vgPunto() : x(0.0), y(0.0) {}
    vgPunto(double x0, double y0) : x(x0), y(y0) {}
};

inline vgPunto vgPuntoEnCirculo(int indice,
                                int total,
                                double cx,
                                double cy,
                                double radio) {
    if (total <= 0) {
        return vgPunto(cx, cy);
    }

    double angulo = (2.0 * vgPI() * (double)indice) / (double)total - (vgPI() / 2.0);
    return vgPunto(cx + radio * cos(angulo), cy + radio * sin(angulo));
}

/**
 * @brief Imprime un resumen del grafo en un recuadro ASCII.
 */
template <typename T>
void imprimirResumenGrafoCLI(const Grafo<T>& g, ostream& os = cout) {
    string tipo = g.getEsDirigido() ? "Dirigido" : "No dirigido";
    string linea1 = " Tipo      : " + tipo;
    string linea2 = " Vertices  : " + vgIntATexto(g.getNNodos());
    string linea3 = " Arcos     : " + vgIntATexto(g.getNArcos());

    int ancho = (int)linea1.size();
    ancho = vgMaxInt(ancho, (int)linea2.size());
    ancho = vgMaxInt(ancho, (int)linea3.size());

    os << "+" << vgRepetir('-', ancho + 2) << "+\n";
    os << "| " << linea1 << vgRepetir(' ', ancho - (int)linea1.size()) << " |\n";
    os << "| " << linea2 << vgRepetir(' ', ancho - (int)linea2.size()) << " |\n";
    os << "| " << linea3 << vgRepetir(' ', ancho - (int)linea3.size()) << " |\n";
    os << "+" << vgRepetir('-', ancho + 2) << "+";
}

/**
 * @brief Imprime lista de adyacencia con formato alineado para CLI.
 */
template <typename T>
void imprimirListaAdyacenciaCLI(const Grafo<T>& g,
                                bool mostrarPesos = true,
                                ostream& os = cout) {
    map<T, int> idDe;
    vector<T> verticeDe;
    vgConstruirIndiceYVertices(g, idDe, verticeDe);

    if (verticeDe.empty()) {
        os << "(grafo vacio)";
        return;
    }

    int anchoEtiqueta = vgAnchoMaxEtiqueta(verticeDe);

    os << "Lista de adyacencia\n";
    os << vgRepetir('=', 20) << "\n";

    for (int i = 0; i < (int)verticeDe.size(); ++i) {
        T v = verticeDe[i];
        string etiqueta = vgATexto(v);

        os << setw(anchoEtiqueta) << etiqueta << " | ";

        Lista<T> sucesores = g.getSucesores(v);
        if (sucesores.esVacia()) {
            os << "(sin conexiones)";
        } else {
            bool primero = true;
            while (!sucesores.esVacia()) {
                T w = sucesores.consultar(1);
                sucesores.eliminar(1);

                if (!primero) {
                    os << "  ->  ";
                }

                os << vgATexto(w);
                if (mostrarPesos) {
                    os << " {" << vgFloatATexto(g.getPesoArco(v, w)) << "}";
                }

                primero = false;
            }
        }

        if (i + 1 < (int)verticeDe.size()) {
            os << "\n";
        }
    }
}

/**
 * @brief Imprime matriz de adyacencia (1/0 o peso) con cabeceras.
 *
 * Nota: orientado a grafos pequenos/medianos para inspeccion visual.
 */
template <typename T>
void imprimirMatrizAdyacenciaCLI(const Grafo<T>& g,
                                 bool mostrarPesos = false,
                                 ostream& os = cout) {
    map<T, int> idDe;
    vector<T> verticeDe;
    vgConstruirIndiceYVertices(g, idDe, verticeDe);

    int n = (int)verticeDe.size();
    if (n == 0) {
        os << "(grafo vacio)";
        return;
    }

    int anchoEtiqueta = vgAnchoMaxEtiqueta(verticeDe);
    int anchoCelda = vgMaxInt(3, anchoEtiqueta + 1);

    os << "Matriz de adyacencia";
    if (mostrarPesos) {
        os << " (pesos)";
    }
    os << "\n";

    os << setw(anchoEtiqueta) << " " << " |";
    for (int j = 0; j < n; ++j) {
        os << " " << setw(anchoCelda) << vgATexto(verticeDe[j]);
    }
    os << "\n";

    os << vgRepetir('-', anchoEtiqueta) << "-+" << vgRepetir('-', (anchoCelda + 1) * n) << "\n";

    for (int i = 0; i < n; ++i) {
        T v = verticeDe[i];
        os << setw(anchoEtiqueta) << vgATexto(v) << " |";

        for (int j = 0; j < n; ++j) {
            T w = verticeDe[j];
            string celda = ".";

            if (g.existeArco(v, w)) {
                if (mostrarPesos) {
                    celda = vgFloatATexto(g.getPesoArco(v, w));
                } else {
                    celda = "1";
                }
            }

            os << " " << setw(anchoCelda) << celda;
        }

        if (i + 1 < n) {
            os << "\n";
        }
    }
}

/**
 * @brief Vista completa en CLI: resumen + lista + matriz binaria.
 */
template <typename T>
void imprimirGrafoBonitoCLI(const Grafo<T>& g, ostream& os = cout) {
    imprimirResumenGrafoCLI(g, os);
    os << "\n\n";
    imprimirListaAdyacenciaCLI(g, true, os);
    os << "\n\n";
    imprimirMatrizAdyacenciaCLI(g, false, os);
}

/**
 * @brief Genera la descripcion DOT de Graphviz del grafo.
 *
 * Permite nodos en circulo y flechas reales al renderizar con dot.
 */
template <typename T>
string generarDOT(const Grafo<T>& g, bool mostrarPesos = true) {
    map<T, int> idDe;
    vector<T> verticeDe;
    vgConstruirIndiceYVertices(g, idDe, verticeDe);

    bool dirigido = g.getEsDirigido();
    string opArista = dirigido ? " -> " : " -- ";

    ostringstream oss;
    oss << (dirigido ? "digraph" : "graph") << " G {\n";
    oss << "  rankdir=LR;\n";
    oss << "  graph [splines=true, overlap=false];\n";
    oss << "  node [shape=circle, style=filled, fillcolor=\"#EEF6FF\", color=\"#2E5D8A\", penwidth=1.2, fontname=\"Helvetica\"];\n";
    if (dirigido) {
        oss << "  edge [color=\"#4A4A4A\", arrowsize=0.8, penwidth=1.1, fontname=\"Helvetica\"];\n";
    } else {
        oss << "  edge [color=\"#4A4A4A\", penwidth=1.1, fontname=\"Helvetica\"];\n";
    }

    for (int i = 0; i < (int)verticeDe.size(); ++i) {
        string sv = vgATexto(verticeDe[i]);
        string ev = vgEscaparDot(sv);
        oss << "  \"" << ev << "\";\n";
    }

    for (int i = 0; i < (int)verticeDe.size(); ++i) {
        T v = verticeDe[i];
        int idxV = idDe[v];
        string sv = vgEscaparDot(vgATexto(v));

        Lista<T> sucesores = g.getSucesores(v);
        while (!sucesores.esVacia()) {
            T w = sucesores.consultar(1);
            sucesores.eliminar(1);
            int idxW = idDe[w];

            bool emitir = true;
            if (!dirigido && idxV > idxW) {
                emitir = false;
            }

            if (emitir) {
                string sw = vgEscaparDot(vgATexto(w));
                oss << "  \"" << sv << "\"" << opArista << "\"" << sw << "\"";
                if (mostrarPesos) {
                    oss << " [label=\"" << vgEscaparDot(vgFloatATexto(g.getPesoArco(v, w))) << "\"]";
                }
                oss << ";\n";
            }
        }
    }

    oss << "}\n";
    return oss.str();
}

/**
 * @brief Exporta el grafo a archivo DOT para renderizar con Graphviz.
 */
template <typename T>
bool exportarGrafoADOT(const Grafo<T>& g,
                       const string& rutaDot,
                       bool mostrarPesos = true) {
    ofstream archivo(rutaDot.c_str());
    if (!archivo.is_open()) {
        return false;
    }

    archivo << generarDOT(g, mostrarPesos);
    archivo.close();
    return true;
}

/**
 * @brief Genera SVG auto-contenido del grafo con layout circular.
 *
 * No depende de Graphviz ni librerias externas.
 */
template <typename T>
string generarSVG(const Grafo<T>& g,
                  bool mostrarPesos = true,
                  int ancho = 1100,
                  int alto = 800) {
    map<T, int> idDe;
    vector<T> verticeDe;
    vgConstruirIndiceYVertices(g, idDe, verticeDe);

    bool dirigido = g.getEsDirigido();
    int n = (int)verticeDe.size();

    ostringstream oss;
    oss << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    oss << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"" << ancho
        << "\" height=\"" << alto << "\" viewBox=\"0 0 " << ancho << " " << alto << "\">\n";
    oss << "  <rect x=\"0\" y=\"0\" width=\"" << ancho << "\" height=\"" << alto
        << "\" fill=\"#FAFBFD\"/>\n";
    oss << "  <style>\n";
    oss << "    .nodo{fill:#EEF6FF;stroke:#2E5D8A;stroke-width:1.6;}\n";
    oss << "    .textoNodo{font-family:DejaVu Sans,Arial,sans-serif;font-size:14px;fill:#12344D;text-anchor:middle;dominant-baseline:middle;}\n";
    oss << "    .arista{stroke:#4A4A4A;stroke-width:1.5;fill:none;}\n";
    oss << "    .peso{font-family:DejaVu Sans,Arial,sans-serif;font-size:12px;fill:#2C3E50;text-anchor:middle;dominant-baseline:middle;}\n";
    oss << "    .titulo{font-family:DejaVu Sans,Arial,sans-serif;font-size:18px;fill:#0F172A;font-weight:bold;}\n";
    oss << "  </style>\n";

    if (dirigido) {
        oss << "  <defs>\n";
        oss << "    <marker id=\"flecha\" markerWidth=\"10\" markerHeight=\"7\" refX=\"9\" refY=\"3.5\" orient=\"auto\">\n";
        oss << "      <polygon points=\"0 0, 10 3.5, 0 7\" fill=\"#4A4A4A\"/>\n";
        oss << "    </marker>\n";
        oss << "  </defs>\n";
    }

    string titulo = dirigido ? "Grafo dirigido" : "Grafo no dirigido";
    oss << "  <text class=\"titulo\" x=\"20\" y=\"35\">" << vgEscaparXML(titulo)
        << " | Vertices: " << n << " | Arcos: " << g.getNArcos() << "</text>\n";

    if (n == 0) {
        oss << "  <text class=\"textoNodo\" x=\"" << (ancho / 2)
            << "\" y=\"" << (alto / 2) << "\">(grafo vacio)</text>\n";
        oss << "</svg>\n";
        return oss.str();
    }

    vector<vgPunto> pos(n);
    double cx = (double)ancho / 2.0;
    double cy = (double)alto / 2.0 + 20.0;
    double radioNodos = 36.0;
    double radioLayout = ((double)(ancho < alto ? ancho : alto) * 0.36);
    if (n == 1) {
        radioLayout = 0.0;
    }

    for (int i = 0; i < n; ++i) {
        pos[i] = vgPuntoEnCirculo(i, n, cx, cy, radioLayout);
    }

    for (int i = 0; i < n; ++i) {
        T v = verticeDe[i];
        int idxV = idDe[v];
        Lista<T> sucesores = g.getSucesores(v);

        while (!sucesores.esVacia()) {
            T w = sucesores.consultar(1);
            sucesores.eliminar(1);
            int idxW = idDe[w];

            bool emitir = true;
            if (!dirigido && idxV > idxW) {
                emitir = false;
            }

            if (emitir) {
                vgPunto a = pos[idxV];
                vgPunto b = pos[idxW];

                if (idxV == idxW) {
                    double lx = a.x + radioNodos + 12.0;
                    double ly = a.y - radioNodos - 12.0;
                    oss << "  <path class=\"arista\" d=\"M " << (a.x + radioNodos * 0.7)
                        << " " << (a.y - radioNodos * 0.7)
                        << " C " << (a.x + radioNodos + 35.0) << " " << (a.y - radioNodos - 35.0)
                        << ", " << (a.x - radioNodos - 35.0) << " " << (a.y - radioNodos - 35.0)
                        << ", " << (a.x - radioNodos * 0.7) << " " << (a.y - radioNodos * 0.7)
                        << "\"";
                    if (dirigido) {
                        oss << " marker-end=\"url(#flecha)\"";
                    }
                    oss << "/>\n";

                    if (mostrarPesos) {
                        oss << "  <text class=\"peso\" x=\"" << lx << "\" y=\"" << ly
                            << "\">" << vgEscaparXML(vgFloatATexto(g.getPesoArco(v, w))) << "</text>\n";
                    }
                } else {
                    double dx = b.x - a.x;
                    double dy = b.y - a.y;
                    double len = sqrt(dx * dx + dy * dy);
                    if (len < 1e-6) {
                        len = 1.0;
                    }

                    double ux = dx / len;
                    double uy = dy / len;
                    double x1 = a.x + ux * radioNodos;
                    double y1 = a.y + uy * radioNodos;
                    double x2 = b.x - ux * radioNodos;
                    double y2 = b.y - uy * radioNodos;

                    oss << "  <line class=\"arista\" x1=\"" << x1 << "\" y1=\"" << y1
                        << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\"";
                    if (dirigido) {
                        oss << " marker-end=\"url(#flecha)\"";
                    }
                    oss << "/>\n";

                    if (mostrarPesos) {
                        double nx = -uy;
                        double ny = ux;
                        double lx = (x1 + x2) / 2.0 + nx * 10.0;
                        double ly = (y1 + y2) / 2.0 + ny * 10.0;
                        oss << "  <text class=\"peso\" x=\"" << lx << "\" y=\"" << ly
                            << "\">" << vgEscaparXML(vgFloatATexto(g.getPesoArco(v, w))) << "</text>\n";
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        string etiqueta = vgEscaparXML(vgATexto(verticeDe[i]));
        oss << "  <circle class=\"nodo\" cx=\"" << pos[i].x << "\" cy=\"" << pos[i].y
            << "\" r=\"" << radioNodos << "\"/>\n";
        oss << "  <text class=\"textoNodo\" x=\"" << pos[i].x << "\" y=\"" << pos[i].y
            << "\">" << etiqueta << "</text>\n";
    }

    oss << "</svg>\n";
    return oss.str();
}

/**
 * @brief Exporta SVG del grafo para visualizacion portable.
 */
template <typename T>
bool exportarGrafoASVG(const Grafo<T>& g,
                       const string& rutaSvg,
                       bool mostrarPesos = true,
                       int ancho = 1100,
                       int alto = 800) {
    ofstream archivo(rutaSvg.c_str());
    if (!archivo.is_open()) {
        return false;
    }

    archivo << generarSVG(g, mostrarPesos, ancho, alto);
    archivo.close();
    return true;
}

#endif
