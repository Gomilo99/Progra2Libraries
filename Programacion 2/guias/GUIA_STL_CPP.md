# Guía STL en C++ (nivel inicial)

[Volver al README principal](../../README.md)

## 1) ¿Qué es STL?

STL (Standard Template Library) es la libreria estandar de estructuras y algoritmos de C++.
Te permite usar contenedores listos (como `vector` o `map`) sin implementarlos desde cero.

En este repositorio se usan sobre todo estructuras propias (Lista, Cola, Pila), pero STL te puede ayudar para:

- mapear nombres a IDs
- manejar arreglos dinamicos
- ordenar resultados
- simplificar parseos

## 2) Encabezados mas usados

```cpp
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <string>
#include <sstream>
#include <algorithm>
```

## 3) Contenedores clave

### 3.1 `std::vector<T>`
Arreglo dinamico contiguo en memoria.

Metodos utiles:

- `push_back(x)` agrega al final
- `size()` cantidad de elementos
- `empty()` verifica vacio
- `operator[]` acceso rapido por indice

Ejemplo:

```cpp
vector<int> v;
v.push_back(10);
v.push_back(20);
cout << v[0] << " " << v.size(); // 10 2
```

Complejidad tipica:

- acceso por indice: O(1)
- push_back: O(1) amortizado

### 3.2 `std::map<K, V>`
Diccionario ordenado por clave (arbol balanceado).

Metodos utiles:

- `m[k]` inserta/consulta
- `find(k)` busca sin insertar
- `count(k)` retorna 0 o 1

Ejemplo:

```cpp
map<string, int> id;
id["Alemania"] = 1;
id["Belgica"] = 2;
if (id.count("Alemania")) {
    cout << id["Alemania"]; // 1
}
```

Complejidad tipica:

- insertar / buscar / borrar: O(log n)

### 3.3 `std::set<T>`
Conjunto de elementos unicos (ordenados).

Metodos utiles:

- `insert(x)`
- `count(x)`
- `erase(x)`

### 3.4 `std::queue<T>` y `std::stack<T>`
Implementaciones STL de cola y pila.

En este proyecto ya tienes `Cola.hpp` y `Pila.hpp`, pero vale conocerlas.

## 4) Algoritmos comunes (`<algorithm>`)

- `sort(inicio, fin)` ordena
- `reverse(inicio, fin)` invierte
- `max(a, b)` y `min(a, b)`

Ejemplo:

```cpp
vector<int> a;
a.push_back(4);
a.push_back(1);
a.push_back(3);
sort(a.begin(), a.end()); // [1, 3, 4]
```

## 5) Iteracion basica (C++98)

En C++98 no hay `auto` ni range-for.

```cpp
map<string, int> m;
m["A"] = 1;
m["B"] = 2;

for (map<string, int>::iterator it = m.begin(); it != m.end(); ++it) {
    cout << it->first << " -> " << it->second << "\n";
}
```

## 6) `string` y `stringstream` para entrada

Muy util en talleres con entrada por linea.

```cpp
string linea;
getline(cin, linea);
stringstream ss(linea);
string a, b;
if (ss >> a >> b) {
    // se leyeron dos tokens
}
```

## 7) Consejos practicos para parciales/talleres

- Si no te piden STL explicitamente, puedes usar las TAD del curso.
- Si te piden velocidad de desarrollo, `map` y `vector` ahorran mucho tiempo.
- Para nombres de ciudades/aeropuertos, `map<string, int>` suele ser ideal.
- Evita mezclar salida de debug con salida oficial.

## 8) Errores comunes

- Usar `operator[]` en `map` solo para consultar: puede insertar claves nuevas sin querer.
- Acceder `vector[i]` fuera de rango.
- Olvidar limpiar estructuras entre casos de prueba.

## 9) Mini plantilla util

```cpp
map<string, int> id;
vector<string> nombre;

int getId(const string& s) {
    map<string, int>::iterator it = id.find(s);
    if (it != id.end()) {
        return it->second;
    }

    int nuevo = (int)nombre.size();
    id[s] = nuevo;
    nombre.push_back(s);
    return nuevo;
}
```

Ese patron te permite mapear etiquetas de texto a indices enteros.
