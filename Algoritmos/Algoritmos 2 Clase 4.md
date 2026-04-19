---
alias:
  - Estructuras Jerarquicas
  - Arboles Binarios y N arios
tags:
  - algoritmos
  - clase
creado: 26/02/2026
modificado: 30/03/2026
tipo: Concepto
base:
  - "[[A-Algoritmos]]"
  - "[[04-Recursos]]"
---
## 🌳Estructuras Jerárquicas (Árboles)
>[!aabstract] Resumen:
>En esta clase se explora la jerarquía de datos, desde la raiz a las hojas, y cómo los recorridos definen la forma en que procesamos la información.

**¿Por qué existe los árboles?** Un árbol es un grafo que no posee circuitos.
Tienen diversos utilidades:
- Representación de organigramas
- Directorios del Sistema Operativo (OS)
- DOM (Document Object Model)
- Árboles genealógicos
- Índices

Todos siguen una jerarquía: ***Un elemento depende de otro superior***
Se compone de:
>[!multi-column]
>
>>[!info] Glosario rápido
>> - **Raíz**: Nodo superior (sin padres).
>> - **Hojas**: Nodos finales (sin hijos).
>> - **Grado**: Cantidad de hijos de un nodo.
>> - **Hijos**: nodos que derivan de un nodo padre, pueden tener hermanos y otros hijos. Funcionan en un nivel inferior a su padre.
>> - **Nodo interior**: nodos con padre e hijo(s)
>
>>[!tip] Altura vs Nivel
>> - **Nivel**: Distancia desde la raíz (Raíz = 0).
>> - **Altura**: Camino más largo hacia una hoja

 ![[algoritmos2_clase_4_arboles_img1.png]]
- **Grado de un nodo**: número de hijos del nodo
	- $G(A) = 5$; 
	- $G(B)=2$; 
	- $G(C)=0$
- **Grado del Árbol**: $max( G(x_i) ) \quad x_i \text{ es un nodo del árbol}$ 
- **Nivel de un Nodo**: Distancia desde la raíz hasta el Nodo
	- $Nivel(A) = 0$
	- $Nivel(D) = 1$
- **Altura**: longitud del camino desde un nodo hasta una hoja
- **Altura del Árbol**: altura de la raíz hasta el ultimo nodo

Algunos tipos comunes de árboles: ![[algoritmos2_clase_4_arboles_img2.png|right]]
- Árbol nulo: árbol sin nodos
- **Árbol trivial (o hoja)**: árbol con un sólo nodo.
**Árbol degenerado**: árbol cuyos enlaces son lineales. Es equivalente a una lista enlazada. 
> [!warning] El Problema de la Degeneración > Cuando insertamos datos ordenados (ej. `[1, 2, 3, 4]`), el árbol se convierte en una **lista enlazada**. > - **Consecuencia**: La búsqueda pasa de $O(\log n)$ a $O(n)$.
## Arboles N-arios
Un árbol donde un nodo puede tener muchos hijos.
**Definición Recursiva**: Un árbol N-ario es un *nodo + lista de subarboles*
![[algoritmos2_clase_4_arboles_img3.png]]
**Ejemplo**: ![[algoritmos2_clase_4_arboles_img4.png|right]]
- Hijos de A = [B, C, D]
- Hijos de B = [E, F, G, H]
- Hermanos de B = [C, D]
- Hijos de C = [I]
- Hijos de D = [J, K]
- Hijos de J = [L]
- Hermanos de E = [F, G, H]
- Hermanos de J = [K]

## Recorridos
>USA EJEMPLO ANTERIOR.
>En los ejercicios se reemplaza procesar por el procedimiento pertinente que se desee hacer.

**PreOrden**:
1. Procesar Raíz
2. Procesar hijos en PreOrden (y hermanos)
$$PreOrden = [A, B, E, F, G, H, C, I, D, J, L , K]$$

**PostOrden**:
1. Procesar hijos en PostOrden (y hermanos)
2. Procesar raíz
$$PostOrden = [E,F,G,H,B,I,C,L,J,K,D,A]$$

**InOrden**:
1. Procesar primer hijo
2. Procesar raíz
3. Procesar resto de hijos en InOrden
$$InOrden = [E,B,F,G,H,A,I,C,L,J,D,K]$$
## Árboles Binario
>Tienen los mismo recorridos

Tiene un máximo de 2 hijos: *izquierdo* y *derecho*
### Tipos de Árboles Binarios 
- **Completo**: todos los nodos tienen 2 hijos
- **Lleno**: todas las hojas están al mismo nivel. 
 ![[algoritmos2_clase_4_arboles_img5.png|right]]
- **Árbol Binario de Búsqueda** 
	- **Definición**: 
		- Todo número menor va a la izquierda
		- Todo número mayor o igual va a la derecha
	- **Inserción** $O(\log_2(n))$ *no siempre se cumple*
	- **Búsqueda** $O(\log_2(n))$ *no siempre se cumple*
	- **Eliminación** $O(\log_2(n))$ *no siempre se cumple*
	$$A=[5,23,-8,0,9,1,12, -1,-20]$$
	![[algoritmos2_clase_4_arboles_img6.png]]
	
	Hay **lentitud** cuando el árbol tiene esta forma $A=[1,2,3,4,5]$
	![[algoritmos2_clase_4_arboles_img7.png]]
## Vínculos
- Clase: [[Algoritmos 2 Clase 4]] y [[Algoritmos 2 Clase 5]]
- Definición de clases: [[Clases Arboles Algoritmos]]
- Ejercicios: [[Ejercicios Arboles]]