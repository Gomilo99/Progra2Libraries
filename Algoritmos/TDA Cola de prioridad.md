---
alias:
tags:
  - algoritmos
  - estudio
creado: 24/03/2026
modificado: 24/03/2026
tipo: Concepto
base:
  - "[[A-Algoritmos]]"
  - "[[04-Recursos]]"
---
## Concepto
Es como una lista, como una cola, pero con prioridad :)
En una cola, el primero en entrar es el primero en salir (FIFO). En la cola de prioridad, el primero en entrar con la prioridad más alta es el primero en salir.
## Creación de TDA
### Dominio
Element = universo de elementos almacenables
Prioridad = int
ColaPrioridad = {c | c es una secuencia finita de pares (e, p), con e in Element y p in Prioridad}
### Sintaxis

| Nombre                  | Entrada                     | Salida        |
| ----------------------- | --------------------------- | ------------- |
| crearCola               |                             | ColaPrioridad |
| encolar                 | ColaPrioridad, Element, int | ColaPrioridad |
| desencolar              | ColaPrioridad               | ColaPrioridad |
| consultar               | ColaPrioridad               | Element       |
| esVacio                 | ColaPrioridad               | bool          |
| vaciar                  | ColaPrioridad               | ColaPrioridad |
| obtenerTamaño           | ColaPrioridad               | int           |
| obtenerPrioridadMasAlta | ColaPrioridad               | int           |
| obtenerPrioridad        | ColaPrioridad, Element      | int           |
### Semántica
#### Definición Algebraica
$\forall c \in ColaPrioridad, \forall e \in Element, \forall p \in int$ entonces:

$Ax_1$: esVacio(crearCola()) = verdadero

$Ax_2$: esVacio(vaciar(c)) = verdadero

$Ax_3$: obtenerTamaño(crearCola()) = 0

$Ax_4$: obtenerTamaño(encolar(c, e, p)) = obtenerTamaño(c) + 1

$Ax_5$: si esVacio(c) = verdadero, entonces consultar(encolar(c, e, p)) = e

$Ax_6$: si esVacio(c) = falso y p > obtenerPrioridadMasAlta(c),
entonces consultar(encolar(c, e, p)) = e

$Ax_7$: si esVacio(c) = falso y p <= obtenerPrioridadMasAlta(c),
entonces consultar(encolar(c, e, p)) = consultar(c)

$Ax_8$: si esVacio(c) = falso, entonces
obtenerTamaño(desencolar(c)) = obtenerTamaño(c) - 1

#### Definición Operacional
pre{}
	crearCola()
post{c <- vacio ^ obtenerTamano(c) = 0}

pre{}
	encolar(c, e, p)
post{obtenerTamano(c) aumenta en 1 y c queda ordenada por prioridad no creciente}

pre{esVacio(c) = falso}
	desencolar(c)
post{obtenerTamano(c) disminuye en 1 y se elimina el elemento de mayor prioridad}

pre{esVacio(c) = falso}
	consultar(c)
post{retorna el elemento con mayor prioridad}

### Implementación
**Función de Abstracción**: 
	$Rep \rightarrow ColaPrioridad$
	$r \rightarrow [r.primero.info, r.primero.siguiente.info, ..., r.ultimo.info]$

	con orden por prioridad:
	$r[i].prioridad >= r[i+1].prioridad$ para todo indice valido.

**Invariante**:
	0 <= r.size

	(r.size = 0) -> (r.primero = NULL ^ r.ultimo = NULL)

	(r.size > 0) -> (r.primero != NULL ^ r.ultimo != NULL ^ r.ultimo->siguiente = NULL)

	La secuencia enlazada esta ordenada por prioridad no creciente.

#### Declaración
```
Tipo
	Papa = ?

	Elemento = registro
		Papa: elem
		int: prioridad
	fregistro

	Nodo = registro
		Elemento: info
		pointer to Nodo: siguiente
	fregistro

	ColaPrioridad = registro
		pointer to Nodo: primero
		pointer to Nodo: ultimo
		int: size
	fregistro
```
#### Funciones y procedimientos
```
func crearCola(): ColaPrioridad
	Var
		ColaPrioridad: c
	Begin
		c.primero <- NULL
		c.ultimo <- NULL
		c.size <- 0
		return c
endfunc

func esVacio(ColaPrioridad: c): bool
	Begin
		return c.size = 0
endfunc

proc encolar(Ref ColaPrioridad: c, Papa: e, int: p)
	Var
		Elemento: caja
		pointer to Nodo: nuevo, actual
	Begin
		caja.elem <- e
		caja.prioridad <- p

		nuevo <- new(Nodo)
		nuevo->info <- caja
		nuevo->siguiente <- NULL

		if esVacio(c) then
			c.primero <- nuevo
			c.ultimo <- nuevo
			c.size <- c.size + 1
			return
		endif

		if p > c.primero->info.prioridad then
			nuevo->siguiente <- c.primero
			c.primero <- nuevo
			c.size <- c.size + 1
			return
		endif

		actual <- c.primero
		while actual->siguiente != NULL ^ actual->siguiente->info.prioridad >= p do
			actual <- actual->siguiente
		endwhile

		nuevo->siguiente <- actual->siguiente
		actual->siguiente <- nuevo

		if nuevo->siguiente = NULL then
			c.ultimo <- nuevo
		endif

		c.size <- c.size + 1
endproc

proc desencolar(Ref ColaPrioridad: c)
	Var
		pointer to Nodo: borrar
	Begin
		if esVacio(c) then
			return
		endif

		borrar <- c.primero
		c.primero <- c.primero->siguiente
		delete(borrar)
		c.size <- c.size - 1

		if c.primero = NULL then
			c.ultimo <- NULL
		endif
endproc

func consultar(ColaPrioridad: c): Papa
	Begin
		return c.primero->info.elem
endfunc

func obtenerPrioridadMasAlta(ColaPrioridad: c): int
	Begin
		return c.primero->info.prioridad
endfunc

func obtenerTamano(ColaPrioridad: c): int
	Begin
		return c.size
endfunc

proc vaciar(Ref ColaPrioridad: c)
	Var
		pointer to Nodo: aux
	Begin
		while c.primero != NULL do
			aux <- c.primero
			c.primero <- c.primero->siguiente
			delete(aux)
		endwhile

		c.ultimo <- NULL
		c.size <- 0
endproc

func obtenerPrioridad(ColaPrioridad: c, Papa: e): int
	Var
		pointer to Nodo: actual
	Begin
		actual <- c.primero
		while actual != NULL do
			if actual->info.elem = e then
				return actual->info.prioridad
			endif
			actual <- actual->siguiente
		endwhile

		return -1
endfunc

```

## Log
- 24/03/2026: Se reviso y corrigio la funcion `encolar` (casos borde, orden por prioridad, actualizacion de `ultimo` y `size`).
- 24/03/2026: Se agregaron operaciones faltantes del TDA: `desencolar`, `consultar`, `vaciar`, `obtenerPrioridadMasAlta`, `obtenerTamano` y `obtenerPrioridad`.
- 24/03/2026: Se normalizo la especificacion formal en dominio, sintaxis, semantica algebraica, semantica operacional, funcion de abstraccion e invariante.