---
creado: 26/02/2026
modificado: 26/02/2026
alias:
tags:
  - algoritmos
  - estudio
tipo: Concepto
base:
  - "[[A-Algoritmos]]"
  - "[[04-Recursos]]"
---
# TDA Hamburguesa
### Representación en Lenguaje Pseudoformal
**const** N <- 10000
**tipo**
	Ingrediente = **string**
	Ingredientes = **arreglo**(1..N) **de** ingrediente
	Salsas = **arreglo**(1..N) **de** ingre
	Hamburguesa = **registro**
			**ingrediente** pan
			**ingrediente** proteina
			Ingredientes ingre
			Salsas salsas
			**entero** totalIngre, totalSalsas
			**bool** cruda

### Función de Abstracción
$f_{abs}$ : Rep ->  Hamburguesa
	h -> {h.ingre(j) | 1 <= j <= h.totalIngre
		h.salsas(k) | 1 <= k <= h.totalSalsas
		proteina != NULL
		pan != NULL }
### Invariante de la Representación
(0 $\leq$ h.totalIngre $\leq$ N) $\wedge$
(h.totalIngre > 0 -> $\forall i\forall j$: ((i, j$\in$[1, h.totalIngre]) $\wedge$ (i $\neq$ j)) -> (h.ingre[i] $\neq$ h.ingre[j] ) ) $\wedge$ 
(1 $\leq$ h.totalSalsas $\leq$ N) $\wedge$
(h.totalSalsas > 0 -> $\forall i\forall j$: ((i, j$\in$[1, h.totalSalsas]) $\wedge$ (i $\neq$ j)) -> (h.salsas[i] $\neq$ h.salsas[j] ) ) $\wedge$ 
(pan.encontrarCadena("pan") $=$ 1 ) $\wedge$ (proteina.encontrarCadena("Carne") $\lor$ proteina.encontrarCadena("Pollo"))
## ¿Que tiene una hamburguesa?
Invariante:
- Pan
- Proteína (pollo o carne)
- Ingrediente
- Salsas

## ¿Qué puede hacer una hamburguesa?
Comer() // Eliminas la hamburguesa
Armar() // Crea la hamburguesa con lo básico
Desarmar() // Deja la hamburguesa con lo básico
Cocinarla() //Pasa cruda a falso
Botar(ingrediente: ing) // Eliminas un ingrediente
Regalar() // Se la envias de regalo a michelle
EnviarlaDelivery() //
Cagar() // Eliminas Hamburguesa y retornas pupu
Rellenar(ingrediente: ing, int: pos) // Le pones un ingrediente
existe_ham(): bool // Revisa si existe la hamburguesa (o es hamburguesa valida)
verIngredientes(): **arreglo**(1..N) // Retorna el vector de ingredientes
verSalsas(): **arreglo**(1..N) // Retorna el vector de salsas
pertenece(ingrediente: inge) // revisa si el ingrediente está en la hamburguesa (pan, proteina, salsa u otro TDA Hamburguesa)