---
creado: 14/02/2026
modificado: 15/02/2026
alias:
tags:
  - algoritmos
  - estudio
tipo: Concepto
base:
  - "[[A-Algoritmos]]"
---
# Portafolio financiero
> Ejercicio 3 de parcial POO 1-2022 "La Secta"

Implemente la clase “Portafolio”. Se sabe que un portafolio financiero es un conjunto de activos que conforman la propiedad de un inversionista. Cada activo del portafolio tiene un nombre, un precio actual y una cantidad (número entero). Para crear un portafolio simple, basta con pasarle los activos que lo van a conformar. El capital total que representa el Portafolio puede calcularse fácilmente como la suma de los precios de todos sus activos multiplicada por su cantidad correspondiente, o sea:
$$
Capital = \sum_{i}^{n}P_iC_i
$$
Donde es el precio del activo i, y es la cantidad del activo i en el portafolio. Por otra parte, 𝑃 es importante asignar 𝑖 𝐶𝑖pesos a cada activo, por lo que, para ello, existe la siguiente fórmula:
$$
peso_i = \frac{P_1C_i}{Capital}
$$
Lo que se traduce como: “El peso del activo i es igual a su precio por su cantidad entre el capital total. Entonces, se solicita que usted cree el prototipo de la clase Portafolio que sea capaz de modelar este problema. A su vez, debe implementar la clase Activo. E implementar para la clase Portafolio: un constructor que reciba un arreglo de activos y arme el portafolio con sus respectivos pesos y capital. Un método que permita obtener el activo con mayor peso, otro método que dado el nombre de un activo devuelva su peso (en caso del activo no estar devolver -1) y los respectivos métodos obtener y modificar por cada uno de sus atributos. 
>**Nota**: asuma que existe la función “compararCadena(cadena: cadena1, cadena2): logico” que devuelve verdadero si las cadenas son iguales.

## Resolución del ejercicio

**Declaración de clases**
```Pseudocodigo
Class Activo
    Attributes:
        Private:
            string: nombre
            float: precio
    Methods:
        Public:
            proc Construir()
            proc Construir(string: nombre, float: precio)

            //Getters
            func getPrecio():float
            func getNombre():string
            //Setters
            proc setPrecio(float: precio)
            proc setNombre(string: nom)
endClass
```
```Pseudocodigo
Class Portafolio
    Attributes:
        Private:
            array[1..N] of float: pesos
            array[1..N] of int: cantidades
            array[1..N] of Activos: listActivos
            int: nActivos
            float: capital
    Methods:
        Public:
            proc Construir()
            proc Construir(array[1..N] of Activos: activos, int: nAct, array[1..N] of int: cant)

            //Getters
            func getActivos():array[1..N] of Activos
            func getPesos():array[1..N] of float
            func getCantidades():array[1..N] of int
            func getNAct():int
            func getCapital():float
            //Setters
            proc setCapital(float: capital)
            proc setActivos(array[1..N] of Activos: activos, array[1..N] of int: cant, int: nAct)
            proc setCantidades(array[1..N] of int: cant)

            func getMayorPesoActivo():Activo
            func getPesoActivo(string: nomAct):float
```
**Implementación de Métodos**
```Pseudocodigo
proc Portafolio::Construir(array[1..N] of Activos: activos, int: nAct, array[1..N] of int: cant)
    Var
        int: i
    Begin
        instance.listaActivos <─ activos
        instance.cantidades <─ cant
        instance.nActivos <─ nAct
        //Calcular capital
        instance.capital <─ 0
        for i<─1 to nAct do
            instance.capital <─ instance.capital + activos[i].getPrecio() * cant[i]
        endfor
        for i<─1 to nAct do
            instance.pesos[i] <─ (activos[i].getPrecio() * cant[i]) / instance.capital
        endfor
endproc

func Portafolio::getActivoMayorPeso():Activo
    Var
        int: i, mayorI
        float: mayor
    Begin
        mayor <─ -inf //En pseudo se puede usar menos infinito e infinito, en programacion se utilizarían librerías
        for i<─1 to instance.nActivos do
            if instance.pesos[i] >= mayot then
                mayor <─ instance.pesos[i]
                mayorI <─ i
            endif
        endfor

        return instance.listaActivos[mayorI]
endfunc

func Portafolio::getPesoActivo(string: nombre):float
    Var
        float: peso
        int: i
        bool: found
    Begin
        found <─ false
        peso <─ -1
        i <─ 1
        while ¬found ^ i <= instance.nActivos do
            found <─ compararCadena(nombre, instance.listaActivos[i].getNombre())
            if found then
                peso <─ instance.pesos[i]
            endif
            i <─ i+1
        endwhile

        return peso
endfunc
```
