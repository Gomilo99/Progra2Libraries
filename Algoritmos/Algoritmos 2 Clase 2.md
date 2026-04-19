---
alias:
  - Diagrama de clases
tags:
  - algoritmos
  - clase
creado: 12/12/2025
modificado: 30/01/2026
tipo: Concepto
base:
  - "[[A-Algoritmos]]"
  - "[[04-Recursos]]"
---
# Mecanismos de Encapsulamiento
## Modificador de Control de Acceso
Un modificador de control de acceso es un mecanismo que determina el nivel de protección de los atributos y métodos de una clase, esto es:

> Definir quién puede acceder a los mismos.

Existen tres modificadores de control de acceso
- \- **Privado**: Es accesible solamente por los métodos de su clase
- \* **Protegido**: Accesible por los métodos de su propia clase y de sus subclases.
- \+ **Público**: Es accesible por los métodos de su clase y cualquier subclase.
# Interfaz de Clase
Es el conjunto de todos los atributos y operaciones que son visibles al mundo exterior.
De cada objeto se conoce solo su interfaz y solamente mediante la interfaz se puedo tener acceso y modificar el estado de un objeto.
# Mensaje
Un mensaje es una llamada a un método hecha por un objeto emisor hacia otro receptor.
En Orientación a Objetos, cuando un objeto recibe un mensaje, este puede reaccionar de 2 formas:

- Si el mensaje corresponde a un tratamiento definido en la clase del objeto, el protocolo del método correspondiente se ejecuta.
- El objeto rechaza el mensaje, señalando un error.
# Miembros de una clase
- **Atributos:** Los atributos constituyen la estructura interna de los objetos de una clase.
- **Método:** Es una colección de sentencias que ejecutan tareas específicas (Bloques de código/Funciones y Procedimientos). Existen **dos** métodos especiales:
	- **Constructor:** Método especial cuya función es inicializar nuevos objetos de su clase
	- **Constructor copia:** Se invoca para inicializar un nuevo objeto a partir de otro existente (ya instanciado).
	- **Destructor:** Es llamado cuando se destruye un objeto después que se haya usado. Libera la memoria de las estructuras de datos que existan.
``` pseudocodigo
Clase Activo
	Atributo:
		- nombre
		- precio
		- cantidad
	Metodos:
		Constructor(n: cadena, p: real, c: entero)
			nombre ← n
			precio ← p
			cantidad ← c
fin_clase
```
## Miembros Estáticos
Cuando se crea un objeto de una clase este guarda una copia de cada uno de sus atributos. Un atributo declarado como estático es un atributo que almacena información común a todos los objetos, pero no pertenece a ninguno.
Se pueden clasificar cómo:
- **Atributos o Variables de Instancia:** Cuando pertenecen a cada objeto de clase.
- **Atributos o Variables de Clase:** Cuando son estáticos y en consecuencia perteneces solamente a la clase y no a los objetos que se crean de la misma.
Si el valor del atributo es común a todos los miembros de la clase, es conveniente declararlo como estático para evitar copias en cada objeto de la clase.

