---
alias:
tags:
  - algoritmos
  - estudio
creado: 26/02/2026
modificado: 27/02/2026
tipo: Concepto
base:
  - "[[A-Algoritmos]]"
---
## Árboles Binarios
### Clase NodoBin
```pseudo
Class NodoBin<Element>
	Attributes
		Private:
			Element: info
			pointer to NodoBin<Element>: hijoIzq, hijoDer
	Methods:
		Public:
			#getters
			...
			#setters
			...
```
### Clase ÁrbolBin
```pseudo
Class ArbolBin<Element>
	Attributes
		Private:
			pointer to NodoBin<Element>: pRaiz
			int: peso
	Methods:
		Private:
			proc preOrden(pointer to NodoBin<Element>: ptr, ref Lista<Element>: result)
			proc postOrden(pointer to NodoBin<Element>: ptr, ref Lista<Element>: result)
			proc inOrden(pointer to NodoBin<Element>: ptr, ref Lista<Element>: result)
			proc porNiveles(pointer to NodoBin<Element>: ptr, ref Lista<Element>: result)
		Public:
			proc construir()
			proc construir(ref ArbolBin<Element>: a)
			func getRaiz(): Element //O(1)
			func getPeso(): int //O(1)
			func esNulo(): bool //O(1)
			func esHoja(): bool //O(1)
			func getHijoIzq(): ArbolBin<Element>
			func getHijoDer(): ArbolBin<Element>
			func preOrden(): Lista<Element> //O(n)
			func inOrden(): Lista<Element> //O(n)
			func postOrden(): Lista<Element> //O(n)
			func porNiveles(): Lista<Element> //O(n)
			func getHojas(): Lista<Element> //O(n)
			proc vaciar() //O(n)
			proc destruir() //O(n)
			*proc insertarNodo(Element: padre, e)
			*proc eliminarNodo(Element: padre, e)
endClass
```

## Árboles N-arios
**Representación HijoIzquierdo - HermanoDerecho**
![[algoritmos2_clase_4_arboles_img8.png]]

### Clase NodoN
```pseudo
Class NodoN<Element>
	Attributes
		Private:
			Element: info
			pointer to NodoBin<Element>: hijoIzq, HnoDer
	Methods
		Public:
			#getters
			...
			#setters
			...
```
### Clase ArbolN
```pseudo
Class ArbolN<Element>
	Attributes
		Private:
			pointer to NodoBin<Element>: pRaiz
			int: peso
	Methods:
		Private:
			proc preOrden(pointer to NodoN<Element>: ptr, ref Lista<Element>: result)
			proc postOrden(pointer to NodoN<Element>: ptr, ref Lista<Element>: result)
			proc inOrden(pointer to NodoN<Element>: ptr, ref Lista<Element>: result)
			proc porNiveles(pointer to NodoN<Element>: ptr, ref Lista<Element>: result)
		Public:
			proc construir()
			proc construir(ref ArbolN<Element>: a)
			func getRaiz(): Element //O(1)
			func getPeso(): int //O(1)
			func esNulo(): bool //O(1)
			func esHoja(): bool //O(1)
			func getHijos(): Lista<ArbolN<Element>>
			func preOrden(): Lista<Element> //O(n)
			func inOrden(): Lista<Element> //O(n)
			func postOrden(): Lista<Element> //O(n)
			func porNiveles(): Lista<Element> //O(n)
			func getHojas(): Lista<Element> //O(n)
			proc vaciar() //O(n)
			proc destruir() //O(n)
			*proc insertarNodo(Element: padre, e)
			*proc eliminarNodo(Element: padre, e)
endClass
```
>* referencia a métodos que no están definidos para algoritmos y pesudoformal. Se implementan es en programación 2, C++.

