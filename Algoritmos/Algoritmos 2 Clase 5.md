---
alias:
  - AVL
tags:
  - algoritmos
  - clase
creado: 28/03/2026
modificado: 30/03/2026
tipo: Concepto
base:
  - "[[A-Algoritmos]]"
  - "[[04-Recursos]]"
---
## Vínculos
- Clase: [[Algoritmos 2 Clase 4]] y [[Algoritmos 2 Clase 5]]
- Definición de clases: [[Clases Arboles Algoritmos]]
- Ejercicios: [[Ejercicios Arboles]]
## Árboles Binarios de Búsqueda
**Problema**: El árbol degenerado
![[algoritmos2_clase5_avl_img1.png]]
### Árboles Balanceados
#### Árboles perfectamente balanceados (AVL: Adelson-Velski y Londis)
Sea: $A=<e,A_1,A_2>$ un ABB se dice que es perfectamente balanceado (AVL) si:
- $|peso(A_1)-peso(A_2)| \leq 1$ (condición de equilibrio) (peso = altura)
- $A_1$ y $A_2$ son perfectamente balanceados (AVL)
![[algoritmos2_clase5_avl_img2.png|right]]
#### Inserción en Árboles AVL
Se inserta un nodo manteniendo el ABB (se inserta del lado derecho de un nodo si es mayor, izquierdo si es menor; recursivamente).
Si a la hora de insertar el subárbol izquierdo o derecho tiene mayor longitud que el otro, el nodo raíz (de donde parten los subárboles) se desbalancea, por tanto se tiene que realizar una rotación.
$Ejemplo: [1,2,3]$
![[algoritmos2_clase5_avl_img3.png]] ![[algoritmos2_clase5_avl_img4.png]]
- Si el nodo insertado cae en la parte externa:
	- **Rotación Simple a la Izquierda (RSI)**
	- **Rotación Simple a la Derecha (RSD)**
- Si el nodo insertado cae en la parte interna:
	- **Rotación Doble Izquierda-Derecha (RDID)**
	- **Rotación Doble Derecha-Izquierda (RDDI)**
