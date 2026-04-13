---
alias:
tags:
  - estudio
  - algoritmos
creado: 30/03/2026
modificado: 12/04/2026
tipo: Concepto
base:
  - "[[A-Algoritmos]]"
  - "[[04-Recursos]]"
---
## Vínculos
- Clase: [[Algoritmos 2 Clase 6]]
- Definición de clases: [[Clases Grafos Algoritmos]]
- Ejercicios: [[Ejercicios Grafos]]
## Resumen
En este documento se presentan y explican ejercicios hechos en clase y en casa del tema Estructuras Multienlazadas (Grafos), vease [[Algoritmos 2 Clase 6]]. En algunos ejercicios se utiliza inteligencia artificial para mejorar las soluciones y explicaciones de los ejercicios. A continuación la definición de las clases y la representación en memoria.

| Problema                         | Algoritmo Recomendado   | Nota Técnica                                |
| -------------------------------- | ----------------------- | ------------------------------------------- |
| **Camino más corto (no pesado)** | Búsqueda en anchura     | BFS                                         |
| **Detección de Ciclos**          | Búsqueda en profundidad | DFS                                         |
| **Conectividad**                 | BFS o DFS               | Si el recorrido visita todos los nodos.     |
| **Orden Topológico**             | DFS modificado          | Útil para dependencias de tareas.           |
| **Laberintos**                   | DFS                     | Explora hasta el fondo antes de retroceder. |


![[Clases Grafos Algoritmos]]
## Mapeado de un grafo (en especial en programación)
- **Definición**: El mapeo es la técnica de asociar un `Element` (ej. un String "Caracas") con un índice entero único entre $1$ y $N$.
- **Implementación**: Generalmente se usa una **Tabla de Hash** o un Diccionario (un map de C++) dentro de la clase `Grafo`.
- **Utilidad**: Permite que el arreglo de `visitados` sea de acceso  usando el índice obtenido del mapeo.
>Se sobreentiende que en algoritmos los grafos ya están mapeados

## Implementación de Métodos Críticos

### BFS (Búsqueda en anchura)
![[algoritmos2_ejercicios_grafos_img2.png|right]]Funciona de manera parecida a un recorrido por niveles, donde se van buscando todos los vertices adyacentes al nodo, se marca como visitado y después se va iterando los vertices en busca de los demás elementos no-visitados.
**Características**:
1. Obtiene la componente conexa de V. (Grafo no dirigido)
2. Obtiene los nodos alcanzables. (Grafos dirigido)
3. Obtiene el camino más corto en arcos.
4. Es O(n + m)
5. Puede quedarse sin recorrer vértices no alcanzables por V.
```Pseudocodigo
func BFS(Grafo<Element>: g, Element: v): Lista<Element>
	Var
		Cola<Element>: colaAux
		array[1..N]of bool: visitados
		Lista<Elemen>: recorrido, vecinos
		int: n, i, w
	Begin
		colaAux.construir()
		recorrido.construir()
		vecinos.construir()
		n <- g.getNVertices()
		for i<-1 to N do
			visitados[i] <- false
		endfor
		colaAux.encolar(v)
		visitados[v] <- true
		
		while ¬colaAux.esVacia() do
			vecinos <- g.getVecinos(colaAux.getFrente())
			while ¬vecinos.esVacia() do
				w <- vecinos.consultar(1)
				if ¬visitados[w] then
					colaAux.encolar(w)
					visitados[w] <- true
				endif
				vecinos.eliminar(1)
			endwhile
			recorrido.insertar(colaAux.getFrente(), recorrido.getLong() +1)
			colaAux.desencolar()
		endwhile
		return recorrido
endfunc
```
### DFS (Búsqueda en profundidad)
![[algoritmos2_ejercicios_grafos_img1.png|right]] La búsqueda en profundidad va buscando los vértices accesibles desde el nodo inicial de manera recursiva. Cuando encuentra un nodo no-visitado lo marca como visitado y busca recursivamente los arcos con vertices no-visitados también hasta que no encuentre ninguno más.
$$Visitados=
\begin{array}{c|cccc}
  & A & B & C & D & E & F \\ \hline
& 1 & 1 & 1 & 1 & 1 & 1 & 
\end{array}
$$
$$Recorrido=[C, A, B, E, D, F]$$
Cuando se recorre, los arcos se pueden clasificar. Esto es vital para detectar ciclos:
1. **Arcos de Árbol**: Arcos que pertenecen al bosque de expansión (cuando visitas un nodo por primera vez).
2. **Arcos de Retroceso (Back Edges)**: Arcos que van de un nodo a un ancestro en el árbol DFS. **¡Si existen, el grafo tiene ciclos!**
3. **Arcos de Avance (Forward Edges)**: Arcos que van de un nodo a un descendiente ya visitado.
4. **Arcos de Cruce (Cross Edges)**: Arcos entre ramas diferentes del árbol.
```Pseudocodigo
func DFS(Grafo<Element>: g, Element: v): Lista<Element>
	Var
		array[1..N] of bool: visitados
		Lista<Element>: recorrido, vecinos
		int: i, n
	Begin
		recorrido.construir()
		vecinos.construir()
		n <- g.getNVertices()
		for i <- 1 to n do
			visitados[i] <- false
		endfor
		DFS(g, v, visitados, recorrido)
		return recorrido
endfunc
proc DFS(ref Grafo<Element>: g, Element: v, ref array[1..N] of bool: visitados, ref Lista<Element>: recorrido)
	Var
		Lista<Element>: vecinos
		Element: w
	Begin
		recorrido.insertar(v, recorrido.getLong() +1)
		visitados[v] <- true
		vecinos <- g.getVecinos(v)
		while ¬vecinos.esVacia() do
			w <- vecinos.consultar(1)
			if ¬visitados[w] then
				DFS(g, w, visitados, recorrido)
			endif
			vecinos.eliminar(1)
		endwhile
endproc
```
## Implementación de Métodos de Clase
### Eliminar Vértice
```
proc Grafo<Element>::eliminarVertice(Element: v)
	Var
		pointer to NodoVertice<Element>: ptr, target
	Begin
		*instance.eliminarArcosDeEntrada(v)
		*instance.eliminarArcosDeSalida(v)
		
		ptr <- instance.g
		if ptr->getInfo() = v then
			target <- ptr
			instance.g <- pre->getNext()
		else
			while ptr->getNext()->getInfo() != v do
				ptr <- ptr->getNext()
			endwhile
			
			target <- ptr->getNext()
			ptr->setNext(target->getNext())
		endif
		
		free(target)
endproc

proc Grafo<Element>::eliminarArcosDeEntrada(Element: v)
	Var
		pointer to NodoVertice<Element>: ptrV
		pointer to NodoArco<Element>: ptrA
	Begin
		ptrV <- instance.g
		while preV do
			ptrA <- ptrV->getListaAdy()
			if ptrA->getInfo->getInfo() = v then
				target <- ptrA
				ptrV.setListaAdy(target->getNext())
			else
				while ptrA->getNext()->getInfo()->getInfo() != v do
					ptrA <- ptrA->getNext()
				endhwile
				target <- ptrA->getNext()
				ptrA->setNext(target->getNext())
			endif
			
			free(target)
			ptrV <- ptrV->getNext()
		endwhile
endproc
proc Grafo<Element>::eliminarArcosDeSalida(Element: v)
	Var
		pointer to NodoVertice<Element>: ptrV
		pointer to NodoArco<Element>: ptrArco, aux
	Begin
		ptrV <- instance.g
		while ptrV->getInfo() != v do
			ptrV <- ptrV->getInfo()
		endwhile
		
		ptrArco <- ptrV->getListaAdy()
		while ¬ptrArco do
			aux <- ptrArco
			ptrArco <- ptrArco->getNext()
			free(aux)
		endwhile
endproc
```
## Guia Ejercicios
### Fáciles
#### Representación de un grafo (Lista de Adyacencia)
Dado un número de nodos **n** y na lista de aristas (vertices), construya la representación de un grafo utilizando lista de adyacencia. El programa debe mostrar los vecinos de cada nodo.
Implemente la función: `func construirGrafo(int: n, Lista<Par<int, int>>): Lista<Lista<int>>`
>La solución **no** debe utilizar apuntadores. O(n + m)
```Pseudocodigo
func construirGrafo(int: n, Lista<Par<int,int>>: aristas): Lista<Lista<int>>
	Var
		Lista<Lista<int>>: result
		array[1..N] of Lista<int>: buffer // Arreglo de un tipo genérico
		Par<int, int>: verticeActual
		int: i, v, w
	Begin
		result.construir()
		// 1. Inicializamos el vector buffer (en progra se deberia crear una lista auxiliar, construirla y luego enviarla)
		for i <- 1 to n do
			buffer[i].construir()
		endfor

		// 2. Procesamos los m vértices usando el índice del arreglo
		while ¬aristas.esVacia() do
			verticeAct <- atistas.consultar(1)
			v <- verticeAct.getPrimero()
			w <- verticeAct.getSegundo()

			buffer[v].insertar(w, 1)
			buffer[w].insertar(v, 1)

			aristas.eliminar(1)
		endwhile
		
		// 3. Volcamos el arreglo en la lista final con un for
		for i <- 1 to n do
			result.insertar(buffer[i], result.getLong() +1)
		endfor

		return result
endfunc
```
#### Verificación de existencia de vertices
Dado un grafo representado mediante matriz de adyacencia y dos nodos u y v, determine si existe una arista directa entre dichos nodos.
``func existeArista(matriz: Matriz<int>, u: int, v: int): bool``
>La solución **no** debe utilizar apuntadores. O(1)
```Pseudocodigo

```
## Ejercicios Parciales y en clase
Hay ejercicios de la guia de ejercicios que se encuentran aqui, especialmente los de dificultad dificil. 
### Detección de ciclos (Grafo Dirigido)
![[Pasted image 20260411152636.png]]
Se desea determinar si un grafo no dirigido tiene ciclos/circuitos en alguna parte, es decir, que en algún punto del grafo un nodo puede regresar a un nodo ya visitado antes. 

Los árboles son, por definición, grafos sin ciclos.
`func tieneCiclo(Grafo<int>: g): bool`
```Pseudocodigo
func tieneCiclo(Grafo<int>: g): bool
	Var
		array[1..N] oof bool: visitado
		int: i
		bool: result
	Begin
		for i <- 1 to g.getNNodos() do
			visitados[i] <- false
		endfor
		
		i <- 1
		while ¬result ^ i < g.getNNodos() do
			if ¬visitados[i] then
				DFSCiclos(g, i, visitados, result, -1)
			endif
			i <- i+1
		endwhile
		return result
endfunc

proc DFSCiclo(ref Grafo<int>: g, int: v, ref array[1..N] of bool: visitados, ref bool: result, int: padre)
	Var
		Lista<int>: vecinos
	Begin
		if ¬result then
			visitados[v] <- true
			vecinos <- g.getVecinos(v)
			while ¬vecinos.esVacia() ^ ¬result do
				w <- vecinos.consultar(1)
				result <- w != padre ^ visitados[w]
				if ¬visitados[w] then
					DFSCiclo(g, w, visitados, result, v)
				endif
				vecinos.eliminar(1)
			endwhile
		endif
endProc
```
### Ordenamiento Topológico
Dado un DAG "==Directed Acyclical Graph==" de tareas. Devolver el orden de ejecución de estas.
![[Pasted image 20260411170216.png]] 
Result: (T1, T2, T3, T4, T5, T7, T11, T6, T8, T9, T10)
>Usa BFS

```Pseudocodigo
proc calcularGradosDeEntrada(ref Grafo<int>:g, ref array[1..N] of int: grados)
	Var
		int: i, w
		Lista<int>: sucesores
	Begin
		for i <- 1 to g.getNNodos() do
			sucesores <- g.getSucesores()
			
			while ¬sucesores.esVacia() do
				w <- sucesores.consultar(1)
				grados[w] <- grados[w] +1
				sucesores.eliminar(1)
			endwhile
		endfor
endproc
func ordenarTareas(Grafo<int>: g): Lista<int>
	Var
		array[1..N] of int: gradosDeEntrada
		Cola<int>: colaAux
		Lista<int>: result
		int: i
	Begin
		result.construir()
		colaAux.construir()
		for i <- 1 to g.getNNodos() do
			grafosDeEntrada[i] <- 0
		endfor
		
		calcularGrafosDeEntrada(g, grafosDeEntrada)
		for i <- 1 to g.getNNodos() do
			if gradosDeEntrada[i] = 0 then
				colaAux.encolar(i)
			endif
		endfor
		
		while ¬colaAux.esVacia() do
			v <- colaAux.getFrente()
			result.insertar(v, result.getLong() +1)
			
			sucesores <- g.getSucesores(v)
			while ¬sucesores.esVacia() do
				w <- sucesores.consultar(1)
				colaAux.encolar(w)
				sucesores.eliminar(1)
			endwhile
			colaAux.desencolar()
		endwhile
		
		return result
endfunc
		
endfunc
```
### Es Bipartito
Dado un grafo g conexo, mapeado y no dirigido cree la función para saber si es bipartito. Un grafo bipartito es un grafo donde se pueden extraer dos conjuntos de elementos que no esté conexos entre sí (el conjunto A no está conectado directamente con el conjunto B), no tiene un arco directo. Este problema es el mismo que el de colorear un grafo con dos colores donde los elemento contiguos no tengan el mismo color.
![[Pasted image 20260411174627.png]]
>Se usa BFS

```Pseudocodigo
func esBipartito(Grafo<int>: g): bool
	Var
		Cola<int>: colaAux
		Lista<int>: vecinos
		array[1..N] of int: color
		array[1..N] of bool: visitado
		int: i
	Begin
		for i <- 1 to g.getNNodos() do
			color[i] <- -1
			visitado[i] <- false
		endfor
		colaAux.construir()
		colaAux.encolar(1)
		color[1] <- 1
		
		while ¬colaAux.esVacia() do
			v <- colaAux.getFrente()
			vecinos <- g.getVecinos(v)
			visitado[v] <- true
			
			while ¬vecinos.esVacia() do
				w <- vecinos.consultar(1)
				if visitado[w] ^ (color[w] = color[v]) then
					return false
				endif
				
				color[w] <- (color[v] +1) mod 2
				colaAux.encolar(w)
				vecinos.eliminar(1)
			endwhile
			colaAux.desencolar()
		endwhile
		
		return true
endfunc
```
### Componentes conexas
Dado un grafo previamente mapeado encontrar la cantidad/numero de componentes conexas de un grafo. O(n+m)

Las componentes conexas son el conjunto de elementos que tienen arcos entre si. Si hay una sola componente conexas el grafo es conexo, de lo contrario se podría decir que hay varios "subgrafos"  no conexos/accesibles entre si.
>Se usa DFS


```Pseudocodigo
func getNComponentesConexas(Grafo<int>: g): int
	Var
		array[1..N] of bool: visitado
		int: result, i
	Begin
		for i <- 1 to g.getNNodos() do
			visitado[i] <- false
		endfor
		result <- 0
		
		for i <- 1 to g.getNNodos() do
			if ¬visitado[i] then
				DFSMod(g, i, visitado)
				result <- result +1
			endif
		endfor
		
		return result
endfunc

proc DFSMod(ref Grafo<int>: g, int: v, ref array[1..N] of bool: visitado)
	Var
		Lista<int>: vecinos
	Begin
		vecinos <- g.getVecinos(v)
		while ¬vecinos.esVacia() do
			w <- vecinos.consultar(1)
			if ¬visitado[w] then
				visitado[w] <- true
				DFSMod(g, w, visitado)
			endif
			vecinos.eliminar(1)
		endwhile
endproc
```

