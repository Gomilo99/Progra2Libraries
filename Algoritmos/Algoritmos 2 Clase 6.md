---
alias:
  - Grafos
tags:
  - algoritmos
  - clase
creado: 30/03/2026
modificado: 31/03/2026
tipo: Concepto
base:
  - "[[A-Algoritmos]]"
  - "[[04-Recursos]]"
---
## Vínculos
- Clase: [[Algoritmos 2 Clase 6]]
- Definición de clases: [[Clases Grafos Algoritmos]]
- Ejercicios: [[Ejercicios Grafos]]
## Estructuras Multienlazadas (Grafos)
Un grafo es una estructura matemática del tipo $$G=(V,A,\varPhi)$$![[algoritmos2_clase6_grafos_img1.png|right]] Donde:
- $V$ es el conjunto de Vértices
- $A$ es el conjunto de Arcos
- $\varPhi$ es una función de costos
$$\begin{aligned}
\Phi: A (N,N) \rightarrow \mathbb{R} \\ 
V=[A,B,C] \\ 
A=[(A,B),(A,C),(A,D),(C,B)]
\end{aligned}$$
### Conectividad
Conceptos clave para entender la relación entre los vértices:
- **Grafo Conexo**: Existe al menos un camino entre cualquier par de vértices (en grafos no dirigidos).
- **Grafo Fuertemente Conexo**: En un grafo dirigido, existe un camino de $u$ a $v$ y de $v$ a $u$ para todo par de vértices.
- **Grado de un Vértice**:
    - **Grado de entrada ($d_{in}$)**: Número de arcos que llegan al vértice.
    - **Grado de salida ($d_{out}$)**: Número de arcos que salen del vértice.
    - En grafos no dirigidos, simplemente es el número de arcos incidentes.
### Tipos de Grafos
- **Dirigidos**: donde los arcos (las conexiones) tienen una dirección única. 
![[algoritmos2_clase6_grafos_img2.png]]
- **No Dirigidos**: donde los arcos actúan como autopistas de ida y vuelta, no tienen una dirección única, es bidireccional.
![[algoritmos2_clase6_grafos_img3.png]]
>NOTA: trabajaremos con grafos simples, es decir, no se admiten los arcos (a,a)
>![[algoritmos2_clase6_grafos_img4.png]]

#### Subtipos de grafos:
- **Planar**: se puede dibujar en $\mathbb{R}^2$ sin cruzar arcos.
- ![[algoritmos2_clase6_grafos_img5.png|right]]**Bipartitos**: se pueden obtener dos conjuntos de vértices A y B en los que los arcos no tocan elementos del mismo conjunto. 
	- El conjunto de vértices se divide en dos subcojuntos $V_1$ y $V_2$.
	- Un grafo es bipartito si y solo si no posee ciclos de longitud impar.
	- Se puede colorear utilizando solo dos colores, de modo que ningún vértice adyacente tenga el mismo color.
	- Todos los árboles son grafos bipartitos
### Caminos y circuitos
#### Caminos
- **Camino elemental**: no repite nodos
- **Camino Simple**: no repite arcos.
>Todo camino elemental es *simple* pero no al revés.
![[algoritmos2_clase6_grafos_img6.png]]
#### Circuitos ó ciclos
Es un camino que parte de un nodo A y llega al mismo nodo A
$C(A, A) = (A, B, C, A)$ 

### Caminos Especiales
- **Camino Euleriano**: camino que atraviesa todos los *arcos* una sola vez
- **Camino Hamiltoniano**: camino que atraviesa todos los *vértices* una sola vez
### Algoritmos Clásicos (no evaluado en principio)
Si la función de costos  es relevante, se utilizan algoritmos específicos:
1. **Caminos Mínimos (Shortest Path)**:
    - **Dijkstra**: Encuentra el camino más corto desde un origen a todos los demás (pesos no negativos).
    - **Bellman-Ford**: Permite pesos negativos.
2. **Árbol de Recubrimiento Mínimo (MST)**:
    - **Kruskal**: Basado en arcos (usa _Union-Find_).
    - **Prim**: Basado en vértices (similar a Dijkstra).
## Representaciones en Memoria
### Matriz de Adyacencia:
![[algoritmos2_clase6_grafos_img7.png|left]]
**En memoria**: $O(n^2)$; $n=|v|$
$$
\begin{array}{c|cccc}
  & A & B & C & D & E & F & G\\ \hline
A & 0 & 1 & 0 & 0 & 0 & 0 & 0\\
B & 0 & 0 & 0 & 1 & 0 & 1 & 1\\
C & 0 & 1 & 0 & 0 & 0 & 0 & 0 \\
D & 0 & 0 & 0 & 0 & 0 & 0 & 1\\
E & 0 & 0 & 0 & 0 & 0 & 0 & 0\\
F & 0 & 0 & 0 & 0 & 1 & 0 & 0 \\
G & 0 & 0 & 0 & 0 & 0 & 0 & 0 \\
\end{array}
$$

### Lista de adyacencia
Funciona con dos listas, una lista de los nodos vertices (nodos conectados linealmente) donde cada vértices tiene una lista de apuntadores a otros vértices (una lista de adyacencia).
- Es útil en grafos no densos
- **En memoria**: $O(n+m)$ donde $n=|V| \quad m=|A|$
![[algoritmos2_clase6_grafos_img8.png]]
### Aplicaciones Prácticas
- **Redes de computadoras**: Enrutamiento de paquetes
- **Redes Sociales**: Sugerencias de amistad (amigos de amigos).
- **Mapas y GPS**: Cálculos de rutas óptimas (Google Maps).
- **Compiladores**: Análisis de dependencias entre módulos.
### Definición de Clases
![[Clases Grafos Algoritmos#Clases Nodos]]
![[Clases Grafos Algoritmos#Clase Grafo]]

