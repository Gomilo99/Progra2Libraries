# Librerías C++

Todas las librerías se encuentran en `Programacion 2/include/`. Son implementaciones genéricas (templates) que permiten trabajar con cualquier tipo de dato `T`.

---

## Tabla de contenido

- [Nodo.hpp](#nodohpp)
- [Lista.hpp](#listahpp)
- [Cola.hpp](#colahpp)
- [Pila.hpp](#pilahpp)
- [ArbolBin.hpp](#arbolbinhpp)
- [ArbolN.hpp](#arbolnhpp)
- [Grafos.hpp](#grafoshpp)
- [AlgoritmosGrafos.hpp](#algoritmosgrafoshpp)
- [VisualizacionGrafos.hpp](#visualizaciongrafoshpp)
- [Ejercicios.hpp](#ejercicioshpp)
- [Personaje.hpp](#personajehpp)
- [Dependencias entre librerías](#dependencias-entre-librerías)

---

## `Nodo.hpp`

Nodo genérico para estructuras enlazadas (Lista, Cola, Pila).

| Atributo | Tipo | Descripción |
|----------|------|-------------|
| `info` | `T` | Valor almacenado |
| `next` | `Nodo<T>*` | Puntero al siguiente nodo |

**Métodos principales:** `getInfo()`, `setInfo()`, `getNext()`, `setNext()`.

---

## `Lista.hpp`

Lista **simplemente enlazada** genérica.

| Atributo | Descripción |
|----------|-------------|
| `head` | Primer nodo |
| `tail` | Último nodo |
| `length` | Número de elementos |

### Constructores
- `Lista()` — lista vacía
- `Lista(const T& element)` — lista con un elemento inicial
- `Lista(const Lista<T>& other)` — copia

### Métodos principales

| Método | Descripción |
|--------|-------------|
| `insertar(valor, pos)` | Inserta en posición (1-indexado) |
| `eliminar(pos)` | Elimina elemento en posición |
| `consultar(pos)` | Retorna elemento en posición |
| `buscar(valor)` | Retorna posición del valor (0 si no existe) |
| `longitud()` | Retorna número de elementos |
| `vacia()` | `true` si la lista no tiene elementos |
| `vaciar()` | Elimina todos los elementos |
| `imprimir()` | Imprime todos los elementos |

### Ejemplo de uso
```cpp
#include "Lista.hpp"

Lista<int> lista;
lista.insertar(10, 1);
lista.insertar(20, 2);
lista.insertar(15, 2); // inserta entre 10 y 20
lista.imprimir();      // 10 15 20
cout << lista.longitud(); // 3
```

---

## `Cola.hpp`

Cola **FIFO** (First In, First Out) implementada con nodos enlazados.

| Atributo | Descripción |
|----------|-------------|
| `frente` | Primer elemento de la cola |
| `ultimo` | Último elemento de la cola |
| `length` | Número de elementos |

### Métodos principales

| Método | Descripción |
|--------|-------------|
| `encolar(valor)` | Agrega al final |
| `desencolar()` | Elimina y retorna el frente |
| `frente()` / `verFrente()` | Consulta el frente sin eliminar |
| `longitud()` | Retorna número de elementos |
| `vacia()` | `true` si está vacía |
| `vaciar()` | Elimina todos los elementos |
| `imprimir()` | Imprime todos los elementos |

### Ejemplo de uso
```cpp
#include "Cola.hpp"

Cola<string> cola;
cola.encolar("A");
cola.encolar("B");
cola.encolar("C");
cout << cola.desencolar(); // "A"
cout << cola.longitud();   // 2
```

---

## `Pila.hpp`

Pila **LIFO** (Last In, First Out) implementada con nodos enlazados.

| Atributo | Descripción |
|----------|-------------|
| `tope` | Elemento en el tope de la pila |
| `length` | Número de elementos |

### Métodos principales

| Método | Descripción |
|--------|-------------|
| `apilar(valor)` | Agrega al tope |
| `desapilar()` | Elimina y retorna el tope |
| `verTope()` | Consulta el tope sin eliminar |
| `longitud()` | Retorna número de elementos |
| `vacia()` | `true` si está vacía |
| `vaciar()` | Elimina todos los elementos |
| `imprimir()` | Imprime todos los elementos |

### Ejemplo de uso
```cpp
#include "Pila.hpp"

Pila<int> pila;
pila.apilar(1);
pila.apilar(2);
pila.apilar(3);
cout << pila.desapilar(); // 3
cout << pila.verTope();   // 2
```

---

## `ArbolBin.hpp`

Árbol **binario** genérico. Incluye `NodoBin<T>` y `ArbolBin<T>`.

### `NodoBin<T>`

| Atributo | Descripción |
|----------|-------------|
| `info` | Valor almacenado |
| `hijoIzq` | Puntero hijo izquierdo |
| `hijoDer` | Puntero hijo derecho |

### `ArbolBin<T>`

| Atributo | Descripción |
|----------|-------------|
| `nodoRaiz` | Nodo raíz del árbol |
| `peso` | Número de nodos |

#### Construcción
- `ArbolBin()` — árbol vacío
- `ArbolBin(preorden, inorden)` — construye desde recorridos preorden e inorden

#### Recorridos

| Método | Tipo |
|--------|------|
| `preorden()` | Lista con recorrido preorden |
| `inorden()` | Lista con recorrido inorden |
| `postorden()` | Lista con recorrido postorden |
| `nivelorden()` | Lista con recorrido por niveles (BFS) |

#### Consultas

| Método | Descripción |
|--------|-------------|
| `altura()` | Altura del árbol |
| `peso` / `getPeso()` | Número total de nodos |
| `vacio()` | `true` si el árbol está vacío |
| `esHoja(nodo)` | `true` si el nodo es hoja |
| `buscar(valor)` | Busca un valor (retorna puntero al nodo) |

> ⚠️ La implementación AVL está **incompleta**. Los ejercicios de balanceo no están totalmente desarrollados.

---

## `ArbolN.hpp`

Árbol **N-ario** genérico usando representación hijo-izquierdo / hermano-derecho. Incluye `NodoN<T>` y `ArbolN<T>`.

### `NodoN<T>`

| Atributo | Descripción |
|----------|-------------|
| `info` | Valor almacenado |
| `hijoIzq` | Primer hijo |
| `hnoDer` | Siguiente hermano |

### `ArbolN<T>`

#### Recorridos

| Método | Tipo |
|--------|------|
| `preorden()` | Lista con recorrido preorden |
| `postorden()` | Lista con recorrido postorden |
| `nivelorden()` | Lista con recorrido por niveles |

#### Consultas

| Método | Descripción |
|--------|-------------|
| `altura()` | Altura del árbol |
| `peso()` | Número de nodos |
| `nivel(valor)` | Nivel del nodo con ese valor |
| `vacio()` | `true` si el árbol está vacío |

---

## `Grafos.hpp`

Grafo dirigido/no dirigido con pesos, representado mediante **lista de adyacencia**.  
Incluye: `NodoArco<T>`, `NodoVertice<T>` y `Grafo<T>`.

### `Grafo<T>`

#### Operaciones sobre vértices

| Método | Descripción |
|--------|-------------|
| `insertarVertice(valor)` | Agrega un vértice |
| `eliminarVertice(valor)` | Elimina un vértice y sus arcos |
| `existeVertice(valor)` | `true` si el vértice existe |
| `numVertices()` | Número de vértices |

#### Operaciones sobre arcos

| Método | Descripción |
|--------|-------------|
| `insertarArco(origen, destino, peso)` | Agrega un arco dirigido con peso |
| `eliminarArco(origen, destino)` | Elimina un arco |
| `existeArco(origen, destino)` | `true` si el arco existe |
| `numArcos()` | Número total de arcos |

#### Consultas

| Método | Descripción |
|--------|-------------|
| `adyacentes(valor)` | Lista de vértices adyacentes |
| `gradoEntrada(valor)` | Número de arcos que llegan al vértice |
| `gradoSalida(valor)` | Número de arcos que salen del vértice |
| `imprimir()` | Imprime la lista de adyacencia completa |

### Ejemplo de uso
```cpp
#include "Grafos.hpp"
#include "AlgoritmosGrafos.hpp"

Grafo<int> g;
g.insertarVertice(1);
g.insertarVertice(2);
g.insertarVertice(3);
g.insertarArco(1, 2, 5.0f);
g.insertarArco(2, 3, 3.0f);
g.imprimir();
```

---

## `AlgoritmosGrafos.hpp`

Algoritmos clásicos de grafos implementados como funciones libres (o clase utilitaria).

| Algoritmo | Descripción |
|-----------|-------------|
| BFS | Recorrido en anchura |
| DFS | Recorrido en profundidad |
| Dijkstra | Camino más corto desde un vértice fuente |
| Prim / Kruskal | Árbol de expansión mínima |
| Ordenamiento topológico | Para DAGs |
| Detección de ciclos | Determina si el grafo tiene ciclos |
| Componentes conexas | Identificación de componentes |

---

## `VisualizacionGrafos.hpp`

Utilidades para **imprimir** representaciones del grafo en consola (lista de adyacencia, matriz de adyacencia).

---

## `Ejercicios.hpp`

Colección de ejercicios resueltos sobre LPC y estructuras jerárquicas. Las funciones están documentadas individualmente en el archivo.

---

## `Personaje.hpp`

Clase de ejemplo de POO. Representa un personaje con atributos básicos, usada en ejercicios de demostración de herencia y polimorfismo.

---

## Dependencias entre librerías

```
Nodo.hpp
  └── Lista.hpp
        ├── Cola.hpp
        ├── Pila.hpp
        ├── ArbolBin.hpp   (usa Lista y Cola)
        ├── ArbolN.hpp     (usa Lista, Cola y Pila)
        └── Grafos.hpp     (usa Lista)
              └── AlgoritmosGrafos.hpp
              └── VisualizacionGrafos.hpp
```
