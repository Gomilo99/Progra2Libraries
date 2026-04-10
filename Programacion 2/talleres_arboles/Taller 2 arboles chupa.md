---
creado: 08/04/2026
modificado: 08/04/2026
---
## CHUPA – Criterio Hiper Universal de Padecimiento Académico
El CHUPA es la secuela espiritual de la MUP, pero peor. ¿Por qué peor? Porque combina dos dolores en uno solo, en este caso, la universidad, según la retorcida lógica del profe, será modelada como un **árbol N-ario** donde cada nodo representa a un jefe de operaciones (o estudiante, porque ya a estas alturas todo es lo mismo). Cada nodo tiene un valor que mide la eficiencia local. Está conformada por:
1. **La Máxima Suma Independiente de Nodos**
	- Un **conjunto independiente** es un grupo de nodos tal que **ningún nodo del conjunto es padre o hijo de otro dentro del mismo conjunto.**
	- La tarea es escoger el conjunto independiente cuya suma de **eficiencias locales** (valores asociados a cada nodo) sea lo más grande posible.
	- En términos narrativos: no puedes premiar a un jefe y a sus subordinados al mismo tiempo, pero sí puedes premiar a varios “hermanos” (nodos con el mismo padre), porque ellos **no están directamente conectados** entre sí.
2. **El Balance Par-Impar de las Hojas**
	- Los nodos hoja representan sucursales, oficinas, o estudiantes que ya se rindieron y no tienen a quién mandar.
	- Si están en **niveles pares** (0, 2, 4, …) contribuyen positivamente a la estabilidad.
	- Si están en **niveles impares** (1, 3, 5, …) se considera que generan caos, burocracia y formularios extra.
Se define matemáticamente como:
- La Máxima Suma Independiente de un árbol T es: $$MSI = max(\sum_{u\in S}val(u)), \text{ S es independiente}$$
- El Balance de hojas es: $$Balance(T) = \sharp \text{hojas en niveles pares} - \sharp\text{hojas en niveles impares}$$
- Finalmente, el CHUPA se define como: $$CHUPA = MSI(T) × Balance(T)$$
3. **Formato de Entrada**: Un número t indicando cuántos casos de prueba hay.
	Para cada caso:
	1. Una línea con un número n: cantidad de nodos del árbol.
	2. Una línea con n enteros, donde el i-ésimo representa la eficiencia local del nodo i.
	3. n - 1 líneas, cada una con dos enteros u v, indicando que v es hijo de u. Se garantiza que el nodo 1 es la raíz.
4. Ejemplo de Entrada
	2
	5
	3 2 1 10 4
	1 2
	1 3
	2 4
	2 5
	4
	5 1 2 6
	1 2
	1 3
	3 4
5. **Formato de Salida**
	Por cada caso, imprimir en una sola línea el valor del CHUPA calculado.
6. Ejemplo de Salida
	17
	0