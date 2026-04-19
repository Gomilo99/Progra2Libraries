---
alias:
  - Relaciones entre clases 
tags:
  - algoritmos
  - clase
creado: 21/01/2026
modificado: 28/02/2026
tipo: Concepto
base:
  - "[[A-Algoritmos]]"
  - "[[04-Recursos]]"
---
# Relaciones entre clases 
## Asociación
Es una dependencia semántica entre clases que de otra modo serían dependientes  Es una **relación débil**: El ciclo de vida de ambas clases es independiente.
> Es una relación débil
![[algoritmos2_clase_3_clases_img10.png]]
## Agregación ("Tiene un")
Es una forma de asociación que específica  una relación todo/parte entre un agregado (el todo) y las partes que la componen.
> Es una relación débil

![[algoritmos2_clase_3_clases_img2.png]]
## Composición ("Tiene un")
Es una forma de asociación de agregación con fuerte sentido de posesión y tiempo de vida coincidente con las partes del conjunto.
> Es una relación fuerte
![[algoritmos2_clase_3_clases_img3.png]]
## Herencia ("es un")
Es un mecanismo mediante el cual unos elementos mas específicos incorporan la estructura y el comportamiento definido por otros elementos mas generales.
**Herencia Simple**
![[algoritmos2_clase_3_clases_img4.png]]
**Herencia Múltiple**
func doSomething(Persona: elem) : int
![[algoritmos2_clase_3_clases_img5.png]]
## Polimorfismo
Es la habilidad que tienen diferentes objetos para invocar el método apropiado en respuesta de un mismo mensaje.
![[algoritmos2_clase_3_clases_img6.png]]

``` pseudocodigo
var
	Abstracto: elem
Begin
	elem.construir()
	elem.calcular(5)
```

![[algoritmos2_clase_3_clases_img7.png]]
### Polimorfismo Estático
Ocurre su detección en tiempo de compilación.
- sobrecarga de métodos
- sobrecarga de operadores
### Polimorfismo Dinámico
Ocurre en tiempo de ejecución.
![[algoritmos2_clase_3_clases_img8.png]]
``` Pseudocodigo
func Animal::hablar():string
var
begin
	return ""
ffunc
---
func Perro::hablar():string
var
begin
	return "guau"
ffunc
```
## Clase Abstracta
![[algoritmos2_clase_3_clases_img9.png]]
## Clase de Asociación
![[algoritmos2_clase_3_clases_img1.png]]