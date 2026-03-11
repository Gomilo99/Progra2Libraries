# Libreria simple de listas, pilas y colas en C

Este material esta pensado para una materia inicial de estructuras de datos. La idea es mostrar una implementacion sencilla, corta y facil de leer.

## Archivos principales

- nodo.h: define el nodo basico que usa la lista enlazada.
- lista.h y lista.c: API y codigo de la lista simplemente enlazada.
- pila.h y pila.c: pila construida sobre la lista.
- cola.h y cola.c: cola construida sobre la lista.
- ejemplo_uso.c: programa corto con un caso practico.
- prueba_estructuras.c: pruebas basicas con assert.
- Makefile: automatiza compilacion, ejecucion y limpieza.
- GUIA_MAKEFILE_C.md: explicacion paso a paso de como funciona un Makefile en C.

## Como esta hecha la lista

La lista es simplemente enlazada. Cada nodo guarda:

- un entero llamado dato
- un puntero al siguiente nodo

La estructura Lista guarda:

- cabeza: el primer nodo
- tamanio: cantidad de elementos

Operaciones incluidas:

- inicializar
- insertar al inicio
- insertar al final
- insertar en una posicion
- obtener un dato por posicion
- eliminar por posicion
- buscar un dato
- imprimir
- destruir y liberar memoria

## Como se construyen pila y cola

La pila y la cola reutilizan la lista.

- Pila: inserta y elimina al inicio. Eso representa el tope.
- Cola: inserta al final y elimina al inicio. Eso representa frente y fondo.

Esta decision evita repetir logica de memoria y recorrido.

## Por que separar .h y .c

Se separan por una razon de orden y de mantenimiento.

- El archivo .h declara que funciones y estructuras existen.
- El archivo .c define como funcionan internamente.

Ventajas de separar:

- otros archivos pueden usar la libreria con solo incluir el .h
- si cambia la implementacion, el programa que la usa casi no cambia
- el codigo queda mas limpio y modular
- permite compilar por partes

En otras palabras: el .h es la interfaz y el .c es la implementacion.

## Explicacion rapida del codigo

### lista.c

- crear_nodo: reserva memoria para un nodo nuevo.
- lista_inicializar: deja la lista vacia.
- lista_insertar_inicio: agrega en la cabeza.
- lista_insertar_final: recorre hasta el ultimo nodo y agrega ahi.
- lista_insertar_en_posicion: avanza hasta la posicion correcta y enlaza el nuevo nodo.
- lista_obtener: recorre hasta una posicion y devuelve el dato.
- lista_eliminar_en_posicion: reconecta punteros, libera memoria y reduce el tamanio.
- lista_buscar: compara dato por dato hasta encontrarlo.
- lista_destruir: elimina todo nodo restante.

### pila.c

- pila_apilar usa lista_insertar_inicio.
- pila_desapilar usa lista_eliminar_en_posicion en la posicion 0.
- pila_cima usa lista_obtener en la posicion 0.

La idea es que el ultimo en entrar sea el primero en salir.

### cola.c

- cola_encolar usa lista_insertar_final.
- cola_desencolar elimina la posicion 0.
- cola_frente obtiene la posicion 0.

La idea es que el primero en entrar sea el primero en salir.

## Como usar el Makefile

Un Makefile sirve para no escribir el comando de compilacion completo cada vez.

Reglas importantes de este Makefile:

- all: compila el ejemplo y las pruebas.
- run-ejemplo: compila y ejecuta el ejemplo.
- run-pruebas: compila y ejecuta las pruebas.
- clean: borra archivos generados.

Ejemplos de uso en terminal:

make
make run-ejemplo
make run-pruebas
make clean

En Windows necesitas tener gcc y make disponibles, por ejemplo con MinGW o MSYS2.

## Ejemplo util incluido

El archivo ejemplo_uso.c representa una situacion simple:

- Lista: codigos de productos cargados.
- Pila: historial de acciones para deshacer.
- Cola: turnos de clientes en espera.

No es un sistema real completo, pero sirve para ver donde encaja cada estructura.

## Archivo de prueba

El archivo prueba_estructuras.c usa assert para verificar:

- inserciones y borrados de la lista
- comportamiento LIFO de la pila
- comportamiento FIFO de la cola

Si una prueba falla, el programa se detiene. Si todo sale bien, imprime un mensaje final.

## Compilacion manual sin Makefile

Si quieres compilar a mano, un ejemplo seria:

gcc -Wall -Wextra -Werror -std=c11 lista.c pila.c cola.c ejemplo_uso.c -o ejemplo_uso

Y para pruebas:

gcc -Wall -Wextra -Werror -std=c11 lista.c pila.c cola.c prueba_estructuras.c -o prueba_estructuras

## Ideas para extender la libreria

- usar float, char o estructuras en vez de int
- agregar lista doblemente enlazada
- guardar puntero al ultimo nodo para acelerar la cola
- separar pruebas en varios archivos