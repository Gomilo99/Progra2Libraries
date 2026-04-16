# Progra2Libraries

Repositorio de estudio y práctica para Algoritmos y Programación 1/2.

## Índice rápido

- [Estructura general](#estructura-general)
- [Guías de Programación 2](#guías-de-programación-2)
- [Librerías principales](#librerías-principales)
- [Talleres y parciales resueltos](#talleres-y-parciales-resueltos)
- [Cómo compilar y ejecutar](#cómo-compilar-y-ejecutar)

## Estructura general

- [Algoritmos/](Algoritmos/): apuntes teóricos, clases y ejercicios en pseudocódigo.
- [PDF/](PDF/): material de apoyo en PDF.
- [Programacion 2/](Programacion%202/): librerías C++ y ejercicios/talleres.
- [Programacion1/](Programacion1/): librerías y prácticas en C.

## Guías de Programación 2

Rutas principales dentro de [Programacion 2/guias/](Programacion%202/guias/):

- [GUIA_ENTRADA_ESTANDAR_CPP.md](Programacion%202/guias/GUIA_ENTRADA_ESTANDAR_CPP.md)
- [GUIA_MAKEFILE_CPP.md](Programacion%202/guias/GUIA_MAKEFILE_CPP.md)
- [GUIA_REDIRECCION_STDIN_STDOUT.md](Programacion%202/guias/GUIA_REDIRECCION_STDIN_STDOUT.md)
- [GUIA_STL_CPP.md](Programacion%202/guias/GUIA_STL_CPP.md)

## Librerías principales

Ubicación: [Programacion 2/include/](Programacion%202/include/)

- [Lista.hpp](Programacion%202/include/Lista.hpp)
- [Cola.hpp](Programacion%202/include/Cola.hpp)
- [Pila.hpp](Programacion%202/include/Pila.hpp)
- [ArbolBin.hpp](Programacion%202/include/ArbolBin.hpp)
- [ArbolN.hpp](Programacion%202/include/ArbolN.hpp)
- [Grafos.hpp](Programacion%202/include/Grafos.hpp)
- [Ejercicios.hpp](Programacion%202/include/Ejercicios.hpp)

## Talleres y parciales resueltos

### LPC (Listas, Pilas, Colas)

- Carpeta: [Programacion 2/talleres_lpc/](Programacion%202/talleres_lpc/)
- Casos trabajados:
	- [1-2024_puma.cpp](Programacion%202/talleres_lpc/1-2024_puma.cpp)
	- [1-2025_semana_santa.cpp](Programacion%202/talleres_lpc/1-2025_semana_santa.cpp)
	- [1-2026_asamblea.cpp](Programacion%202/talleres_lpc/1-2026_asamblea.cpp)
	- [2-2025_ultima_copa.cpp](Programacion%202/talleres_lpc/2-2025_ultima_copa.cpp)

### Árboles

- Carpeta: [Programacion 2/talleres_arboles/](Programacion%202/talleres_arboles/)
- Casos trabajados:
	- [1-2025_mup.cpp](Programacion%202/talleres_arboles/1-2025_mup.cpp)
	- [1-2026_rutaDefensa.cpp](Programacion%202/talleres_arboles/1-2026_rutaDefensa.cpp)
	- [1-2026_rutaDefensa_mejorado.cpp](Programacion%202/talleres_arboles/1-2026_rutaDefensa_mejorado.cpp)
	- [1-2026_rutaDefensa_orden_n.cpp](Programacion%202/talleres_arboles/1-2026_rutaDefensa_orden_n.cpp)
	- [2-2025_chupa.cpp](Programacion%202/talleres_arboles/2-2025_chupa.cpp)
	- [2-2025_chupa_pedagogico.cpp](Programacion%202/talleres_arboles/2-2025_chupa_pedagogico.cpp)

### Grafos

- Carpeta: [Programacion 2/talleres_grafos/](Programacion%202/talleres_grafos/)
- Estado actual:
	- [2-2025_ordenMundial.cpp](Programacion%202/talleres_grafos/2-2025_ordenMundial.cpp): plantilla de construcción del grafo desde entrada estándar (fase base).

### Pruebas de librerías y ejercicios

- LPC:
	- [90_test_clases.cpp](Programacion%202/ejercicios_lpc/90_test_clases.cpp)
	- [91_test_ejercicios.cpp](Programacion%202/ejercicios_lpc/91_test_ejercicios.cpp)
- Árboles:
	- [90_test_clases_arboles.cpp](Programacion%202/ejercicios_arboles/90_test_clases_arboles.cpp)
	- [91_test_ejercicios_arboles.cpp](Programacion%202/ejercicios_arboles/91_test_ejercicios_arboles.cpp)

## Cómo compilar y ejecutar

Archivo base: [Programacion 2/Makefile](Programacion%202/Makefile)

Ejemplos:

```bash
# Compilar un taller puntual
make one SRC_DIR=talleres_grafos EX=2-2025_ordenMundial

# Ejecutar con stdin directo
make run SRC_DIR=talleres_grafos EX=2-2025_ordenMundial

# Ejecutar con archivo de entrada/salida
make run-file SRC_DIR=talleres_grafos EX=2-2025_ordenMundial IN=talleres_grafos/in_2-2025.txt OUT=talleres_grafos/out_2-2025.txt
```

Para más detalle, revisa [GUIA_MAKEFILE_CPP.md](Programacion%202/guias/GUIA_MAKEFILE_CPP.md).
