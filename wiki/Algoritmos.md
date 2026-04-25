# Algoritmos — Apuntes de Clase

Esta sección recopila los apuntes teóricos de la materia **Algoritmos 2**, organizados por clase y tema. Los archivos están en la carpeta `Algoritmos/` del repositorio.

> Los diagramas y gráficos se elaboraron con **Excalidraw** dentro de la aplicación [Obsidian](https://obsidian.md/).

---

## Clases teóricas principales

### Clase 1 — Programación Orientada a Objetos (POO)
**Archivo:** [`Algoritmos 2 Clase 1.md`](https://github.com/Gomilo99/Progra2Libraries/blob/main/Algoritmos/Algoritmos%202%20Clase%201.md)

- Concepto de **objeto**: ente real o abstracto con características y funcionalidades.
- Análisis Orientado a Objetos: identificación de objetos desde la descripción del problema.
- Diseño Orientado a Objetos: diagramas de clase UML (modelo estático).
- Principios fundamentales: **abstracción**, **encapsulamiento**, **modularidad**, **jerarquía**.

### Clase 2 — Encapsulamiento y Modificadores de Acceso
**Archivo:** [`Algoritmos 2 Clase 2.md`](https://github.com/Gomilo99/Progra2Libraries/blob/main/Algoritmos/Algoritmos%202%20Clase%202.md)

- Modificadores `public`, `private`, `protected`.
- Interfaz de clase: métodos de acceso (getters/setters) y constructores.
- Métodos especiales: destructor, constructor de copia, operador de asignación.

### Clase 3 — Relaciones entre Clases
**Archivo:** [`Algoritmos 2 Clase 3.md`](https://github.com/Gomilo99/Progra2Libraries/blob/main/Algoritmos/Algoritmos%202%20Clase%203.md)

| Relación | Descripción |
|----------|-------------|
| Asociación | Un objeto "usa" a otro |
| Agregación | Relación "tiene un" con ciclo de vida independiente |
| Composición | Relación "tiene un" con ciclo de vida dependiente |
| Herencia | Relación "es un"; subclase extiende superclase |
| Polimorfismo | Comportamiento distinto según el tipo real del objeto |

### Clase 4 — Estructuras Jerárquicas: Árboles
**Archivo:** [`Algoritmos 2 Clase 4.md`](https://github.com/Gomilo99/Progra2Libraries/blob/main/Algoritmos/Algoritmos%202%20Clase%204.md)

- Árboles N-arios y binarios.
- Terminología: raíz, hoja, nivel, altura, peso.
- Recorridos:
  - **Preorden**: raíz → izquierda → derecha
  - **Inorden**: izquierda → raíz → derecha
  - **Postorden**: izquierda → derecha → raíz
  - **Nivelorden** (BFS): por niveles de arriba a abajo

### Clase 5 — ABB y AVL
**Archivo:** [`Algoritmos 2 Clase 5.md`](https://github.com/Gomilo99/Progra2Libraries/blob/main/Algoritmos/Algoritmos%202%20Clase%205.md)

- **Árbol Binario de Búsqueda (ABB)**: inserción, eliminación y búsqueda en O(h).
- **Degeneración**: caso peor del ABB con inserción en orden.
- **Árbol AVL**: ABB balanceado; factor de balance FB = altura(izq) − altura(der).
- **Rotaciones de balanceo**: simple izquierda (II), simple derecha (DD), doble izquierda-derecha (ID), doble derecha-izquierda (DI).

> ⚠️ Los ejercicios de balanceo AVL están **incompletos** en este repositorio.

### Clase 6 — Grafos
**Archivo:** [`Algoritmos 2 Clase 6.md`](https://github.com/Gomilo99/Progra2Libraries/blob/main/Algoritmos/Algoritmos%202%20Clase%206.md)

- Definición: conjunto de **vértices** y **arcos** (dirigidos o no, con o sin peso).
- Conectividad: caminos, ciclos, componentes conexas.
- Representaciones: **matriz de adyacencia** y **lista de adyacencia**.
- Recorridos: **BFS** (anchura) y **DFS** (profundidad).
- Algoritmos de camino mínimo: **Dijkstra**.
- Árbol de expansión mínima: **Prim** y **Kruskal**.

---

## Material de apoyo por tema

| Archivo | Contenido |
|---------|-----------|
| [`Clases LPC Algoritmos.md`](https://github.com/Gomilo99/Progra2Libraries/blob/main/Algoritmos/Clases%20LPC%20Algoritmos.md) | Resumen de listas, pilas y colas |
| [`Clases Arboles Algoritmos.md`](https://github.com/Gomilo99/Progra2Libraries/blob/main/Algoritmos/Clases%20Arboles%20Algoritmos.md) | Resumen de árboles |
| [`Clases Grafos Algoritmos.md`](https://github.com/Gomilo99/Progra2Libraries/blob/main/Algoritmos/Clases%20Grafos%20Algoritmos.md) | Resumen de grafos |
| [`Ejercicios LPC.md`](https://github.com/Gomilo99/Progra2Libraries/blob/main/Algoritmos/Ejercicios%20LPC.md) | Ejercicios resueltos de LPC |
| [`Ejercicios Arboles.md`](https://github.com/Gomilo99/Progra2Libraries/blob/main/Algoritmos/Ejercicios%20Arboles.md) | Ejercicios resueltos de árboles |
| [`Ejercicios Grafos.md`](https://github.com/Gomilo99/Progra2Libraries/blob/main/Algoritmos/Ejercicios%20Grafos.md) | Ejercicios resueltos de grafos |
| [`Reglas de Pseudocodigo Algoritmos.md`](https://github.com/Gomilo99/Progra2Libraries/blob/main/Algoritmos/Reglas%20de%20Pseudocodigo%20Algoritmos.md) | Convenciones de pseudocódigo usadas en clase |
| [`TDA ColaPrioridad.md`](https://github.com/Gomilo99/Progra2Libraries/blob/main/Algoritmos/TDA%20ColaPrioridad.md) | TDA Cola de Prioridad |
| [`TDA Hamburguesa.md`](https://github.com/Gomilo99/Progra2Libraries/blob/main/Algoritmos/TDA%20Hamburguesa.md) | Ejemplo TDA con POO |
| [`Ejercicio POO-Portafolio.md`](https://github.com/Gomilo99/Progra2Libraries/blob/main/Algoritmos/Ejercicio%20POO-Portafolio.md) | Ejercicio de portafolio con POO |
