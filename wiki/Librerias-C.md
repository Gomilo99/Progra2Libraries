# Librerías C (Programación 1)

Las estructuras de datos para **Programación 1** se encuentran en `Programacion1/` e implementan las mismas tres estructuras que las librerías C++, pero en lenguaje **C**.

---

## Archivos

| Archivo | Descripción |
|---------|-------------|
| `nodo.h` | Definición del nodo genérico |
| `lista.h` / `lista.c` | Lista simplemente enlazada |
| `cola.h` / `cola.c` | Cola FIFO |
| `pila.h` / `pila.c` | Pila LIFO |
| `ejemplo_uso.c` | Programa de demostración de las tres estructuras |
| `prueba_estructuras.c` | Casos de prueba de las estructuras |
| `Makefile` | Compilación para los programas de prueba |

---

## Lista (`lista.h` / `lista.c`)

Lista **simplemente enlazada** genérica en C (con `void*` para datos).

### Operaciones principales

| Función | Descripción |
|---------|-------------|
| `crearLista()` | Crea e inicializa una lista vacía |
| `insertarLista(lista, valor, pos)` | Inserta en posición indicada |
| `eliminarLista(lista, pos)` | Elimina el elemento en posición |
| `consultarLista(lista, pos)` | Retorna el elemento en posición |
| `buscarLista(lista, valor)` | Busca un valor, retorna posición |
| `longitudLista(lista)` | Número de elementos |
| `vaciaLista(lista)` | `1` si vacía, `0` si no |
| `vaciarLista(lista)` | Libera todos los nodos |
| `imprimirLista(lista, fn)` | Imprime con función auxiliar |

---

## Cola (`cola.h` / `cola.c`)

Cola **FIFO** en C.

### Operaciones principales

| Función | Descripción |
|---------|-------------|
| `crearCola()` | Crea una cola vacía |
| `encolar(cola, valor)` | Agrega al final |
| `desencolar(cola)` | Elimina y retorna el frente |
| `verFrente(cola)` | Consulta el frente sin eliminar |
| `longitudCola(cola)` | Número de elementos |
| `vaciaCola(cola)` | `1` si vacía |
| `vaciarCola(cola)` | Libera todos los nodos |

---

## Pila (`pila.h` / `pila.c`)

Pila **LIFO** en C.

### Operaciones principales

| Función | Descripción |
|---------|-------------|
| `crearPila()` | Crea una pila vacía |
| `apilar(pila, valor)` | Agrega al tope |
| `desapilar(pila)` | Elimina y retorna el tope |
| `verTope(pila)` | Consulta el tope sin eliminar |
| `longitudPila(pila)` | Número de elementos |
| `vaciaPila(pila)` | `1` si vacía |
| `vaciarPila(pila)` | Libera todos los nodos |

---

## Compilación

Desde la carpeta `Programacion1/`:

```bash
make          # compila todos los programas
make clean    # elimina los ejecutables generados
```

Para más detalles, consulta el [README de Programacion1](https://github.com/Gomilo99/Progra2Libraries/blob/main/Programacion1/README.md).
