# Estructura del Repositorio

Esta página describe la organización de carpetas y archivos del repositorio **Progra2Libraries**.

---

## Árbol de directorios

```
Progra2Libraries/
│
├── Algoritmos/
│   ├── Algoritmos 2 Clase 1.md   # POO: objeto, clase, abstracción, encapsulamiento
│   ├── Algoritmos 2 Clase 2.md   # Encapsulamiento y modificadores de acceso
│   ├── Algoritmos 2 Clase 3.md   # Relaciones: asociación, herencia, polimorfismo
│   ├── Algoritmos 2 Clase 4.md   # Árboles N-arios/binarios y recorridos
│   ├── Algoritmos 2 Clase 5.md   # ABB, AVL y rotaciones de balanceo
│   ├── Algoritmos 2 Clase 6.md   # Grafos: conectividad, representación y recorridos
│   ├── Clases LPC Algoritmos.md  # Material de apoyo: Listas, Pilas y Colas
│   ├── Clases Arboles Algoritmos.md
│   ├── Clases Grafos Algoritmos.md
│   ├── Ejercicios LPC.md
│   ├── Ejercicios Arboles.md
│   ├── Ejercicios Grafos.md
│   ├── Ejercicio POO-Portafolio.md
│   ├── Reglas de Pseudocodigo Algoritmos.md
│   ├── TDA ColaPrioridad.md
│   └── TDA Hamburguesa.md
│
├── PDF/
│   ├── Algoritmos 2 Clase 1-6.pdf   # Diapositivas de clases
│   ├── Clases LPC / Arboles / Grafos Algoritmos.pdf
│   ├── Ejercicios LPC / Arboles / Grafos / POO.pdf
│   ├── Guia Ejercicios Arboles / Grafos.pdf
│   ├── Reglas de Pseudocodigo Algoritmos.pdf
│   ├── GUIA_ENTRADA_ESTANDAR_CPP.pdf
│   ├── GUIA_MAKEFILE_C.pdf
│   ├── GUIA_MAKEFILE_CPP.pdf
│   ├── GUIA_REDIRECCION_STDIN_STDOUT.pdf
│   ├── GUIA_STL_CPP.pdf
│   ├── Parciales/                   # Banco de parciales históricos
│   └── Talleres/                    # Banco de talleres históricos
│
├── Programacion 2/
│   ├── Makefile                     # Sistema de compilación principal
│   ├── Makefile.generic
│   ├── include/                     # Librerías C++ genéricas (.hpp)
│   │   ├── Nodo.hpp
│   │   ├── Lista.hpp
│   │   ├── Cola.hpp
│   │   ├── Pila.hpp
│   │   ├── ArbolBin.hpp
│   │   ├── ArbolN.hpp
│   │   ├── Grafos.hpp
│   │   ├── AlgoritmosGrafos.hpp
│   │   ├── VisualizacionGrafos.hpp
│   │   ├── Ejercicios.hpp
│   │   └── Personaje.hpp
│   ├── guias/                       # Guías de programación en Markdown
│   │   ├── GUIA_ENTRADA_ESTANDAR_CPP.md
│   │   ├── GUIA_MAKEFILE_CPP.md
│   │   ├── GUIA_REDIRECCION_STDIN_STDOUT.md
│   │   └── GUIA_STL_CPP.md
│   ├── ejercicios_lpc/
│   │   ├── 90_test_clases.cpp
│   │   └── 91_test_ejercicios.cpp
│   ├── ejercicios_arboles/
│   │   ├── 90_test_clases_arboles.cpp
│   │   └── 91_test_ejercicios_arboles.cpp
│   ├── talleres_lpc/                # Soluciones taller LPC + casos de prueba
│   ├── talleres_arboles/            # Soluciones taller Árboles + casos de prueba
│   ├── talleres_grafos/             # Soluciones taller Grafos + casos de prueba
│   └── practica laboratorio/
│
└── Programacion1/
    ├── nodo.h
    ├── lista.h / lista.c
    ├── cola.h / cola.c
    ├── pila.h / pila.c
    ├── ejemplo_uso.c
    ├── prueba_estructuras.c
    ├── Makefile
    └── README.md
```

---

## Descripción de secciones

### `Algoritmos/`
Apuntes teóricos de la materia en formato Markdown, organizados por clase y tema. Los gráficos se realizaron con **Excalidraw** mediante la aplicación [Obsidian](https://obsidian.md/).

### `PDF/`
Material de apoyo en PDF: diapositivas de clases, enunciados de ejercicios, guías de programación, banco de parciales y talleres históricos.

### `Programacion 2/`
Contiene las librerías C++ genéricas, las guías de programación en Markdown, los ejercicios de prueba de librerías y las soluciones de talleres con sus casos de prueba.

### `Programacion1/`
Implementación de las mismas estructuras (Lista, Cola, Pila) pero en lenguaje **C**, para la materia de Programación 1.
