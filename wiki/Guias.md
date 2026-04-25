# Guías de Programación

Esta sección recopila las guías de referencia rápida disponibles en `Programacion 2/guias/`.  
Las versiones PDF equivalentes están en la carpeta `PDF/`.

---

## Índice

- [Entrada estándar en C++](#entrada-estándar-en-c)
- [Makefile para C++](#makefile-para-c)
- [Redirección de stdin/stdout](#redirección-de-stdinstdout)
- [STL de C++](#stl-de-c)

---

## Entrada estándar en C++

**Archivo:** [`GUIA_ENTRADA_ESTANDAR_CPP.md`](https://github.com/Gomilo99/Progra2Libraries/blob/main/Programacion%202/guias/GUIA_ENTRADA_ESTANDAR_CPP.md)  
**PDF:** [`GUIA_ENTRADA_ESTANDAR_CPP.pdf`](https://github.com/Gomilo99/Progra2Libraries/blob/main/PDF/GUIA_ENTRADA_ESTANDAR_CPP.pdf)

Cubre el uso de `cin` para leer distintos tipos de datos:
- Lectura de enteros, flotantes y strings.
- Lectura línea por línea con `getline`.
- Manejo de múltiples valores en una línea.
- Lectura hasta EOF con `while (cin >> var)`.

---

## Makefile para C++

**Archivo:** [`GUIA_MAKEFILE_CPP.md`](https://github.com/Gomilo99/Progra2Libraries/blob/main/Programacion%202/guias/GUIA_MAKEFILE_CPP.md)  
**PDF:** [`GUIA_MAKEFILE_CPP.pdf`](https://github.com/Gomilo99/Progra2Libraries/blob/main/PDF/GUIA_MAKEFILE_CPP.pdf)

Explica el sistema de compilación del repositorio:

- Estructura del `Makefile` genérico.
- Variables configurables: `SRC_DIR`, `EX`, `IN`, `OUT`.
- Targets disponibles:

| Target | Descripción |
|--------|-------------|
| `make` | Compila el ejercicio por defecto |
| `make one SRC_DIR=... EX=...` | Compila un archivo específico |
| `make run SRC_DIR=... EX=...` | Compila y ejecuta con stdin |
| `make run-file SRC_DIR=... EX=... IN=... OUT=...` | Compila y ejecuta con archivos |
| `make clean` | Elimina ejecutables generados |
| `make help` | Muestra ayuda de los targets disponibles |

---

## Redirección de stdin/stdout

**Archivo:** [`GUIA_REDIRECCION_STDIN_STDOUT.md`](https://github.com/Gomilo99/Progra2Libraries/blob/main/Programacion%202/guias/GUIA_REDIRECCION_STDIN_STDOUT.md)  
**PDF:** [`GUIA_REDIRECCION_STDIN_STDOUT.pdf`](https://github.com/Gomilo99/Progra2Libraries/blob/main/PDF/GUIA_REDIRECCION_STDIN_STDOUT.pdf)

Explica cómo redirigir la entrada y salida estándar en la terminal para probar programas:

```bash
# Redirigir entrada desde archivo
./programa < entrada.txt

# Redirigir salida a archivo
./programa > salida.txt

# Redirigir ambas
./programa < entrada.txt > salida.txt

# Comparar salida con salida esperada
diff <(./programa < entrada.txt) salida_esperada.txt
```

---

## STL de C++

**Archivo:** [`GUIA_STL_CPP.md`](https://github.com/Gomilo99/Progra2Libraries/blob/main/Programacion%202/guias/GUIA_STL_CPP.md)  
**PDF:** [`GUIA_STL_CPP.pdf`](https://github.com/Gomilo99/Progra2Libraries/blob/main/PDF/GUIA_STL_CPP.pdf)

Referencia de los contenedores y algoritmos más útiles de la STL:

| Contenedor | Header | Descripción |
|------------|--------|-------------|
| `vector<T>` | `<vector>` | Arreglo dinámico |
| `list<T>` | `<list>` | Lista doblemente enlazada |
| `stack<T>` | `<stack>` | Pila LIFO |
| `queue<T>` | `<queue>` | Cola FIFO |
| `priority_queue<T>` | `<queue>` | Cola de prioridad (max-heap) |
| `map<K,V>` | `<map>` | Diccionario ordenado |
| `unordered_map<K,V>` | `<unordered_map>` | Diccionario hash |
| `set<T>` | `<set>` | Conjunto ordenado |
| `pair<A,B>` | `<utility>` | Par de valores |

Algoritmos comunes (`<algorithm>`): `sort`, `find`, `count`, `min_element`, `max_element`, `reverse`, `accumulate`.
