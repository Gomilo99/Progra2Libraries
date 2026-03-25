### TDA Cola de Prioridad

Dominio = {ColaPrioridad, Bolean, Elemento, Entero}

### SINTAXIS:

| Nombre                  | Entrada                     | Salida        |
| ----------------------- | --------------------------- | ------------- |
| crear                   |                             | ColaPrioridad |
| encolar                 | ColaPrioridad, Element, int | ColaPrioridad |
| desencolar              | ColaPrioridad               | ColaPrioridad |
| esVacio                 | ColaPrioridad               | bool          |
| Peek                    | ColaPrioridad               | Elemento      |
| Size                    | ColaPrioridad               | int           |

### SEMANTICA
#### Definición Algebraica
$\forall c \in ColaPrioridad \land \forall e \in Element \land \forall p \in int$ entonces:  

$Ax_1$: esVacio(crear()) = true
$Ax_2$: esVacio(encolar(C, e, p)) = false
$Ax_3$: Size(encolar(C, e, p)) = 1 + Size(C)
$Ax_4$: Peek(encolar(crear(), e, p)) = e
$Ax_5$: si $p_1 \leq p_2$ entonces Peek(encolar(encolar(C, e_1, p_1), e_2, p_2)) = e_1

#### Definicion Operacional:

pre{}
	crear()
post{c <- vacio}

pre{}
	encolar(Element, int)
post{Size(c) +1}

pre{esVacia(c) = false}
	desencolar()
post{Size(c) -1}

pre{esVacia(c) = false}
	Peek(c)
post{ $e$ con menor valor de prioridad numérica}

### Implementación
**Función de Abstracción**: 
	$Rep \rightarrow ColaPrioridad$ 
    $r \rightarrow \quad r.e[i].prioridad \leqslant r.e[i+1].prioridad \leqslant...\leqslant r.e[r.size].prioridad$  
**Invariante**:
	0 <= r.size <= n
#### Declaración
```
tipo
    Elemento = ? 
    apuntador a Nodo: PtrNodo
    
    Nodo = registro
        Elemento: info
        entero: prioridad
        PtrNodo: siguiente
    fregistro

    ColaPrioridad = registro
        PtrNodo: primero, ultimo
        entero: tamaño
    fregistro
```
#### Funciones y procedimientos
```
func crear(): ColaPrioridad
    var
        ColaPrioridad: C
    inicio
        C.primero ← nulo
        C.ultimo ← nulo
        C.tamano ← 0
        retornar(C)
ffunc

proc encolar(ref ColaPrioridad: C; Elemento: e; entero: p)
    var 
    pointer to Nodo: nuevo, act, ant
    inicio
        Crear(nuevo)
        nuevo↑.info ← e
        nuevo↑.prioridad ← p
        nuevo↑.siguiente ← nulo

        if (C.primero = nulo)
            C.primero ← nuevo
            C.ultimo ← nuevo
        else
            if (p < C.primero↑.prioridad)
                nuevo↑.siguiente ← C.primero
                C.primero ← nuevo
            else
                if (C.ultimo↑.prioridad <= p)
                    C.ultimo↑.siguiente ← nuevo
                    C.ultimo ← nuevo
                else
                    act ← C.primero
                    while (act != nulo y act↑.prioridad <= p) hacer
                        ant ← act
                        act ← act↑.siguiente
                    fwhile
                    nuevo↑.siguiente ← act
                    ant↑.siguiente ← nuevo
                fif
            fif
        fif
        C.tamaño ← C.tamaño + 1
fproc

func desencolar(ref ColaPrioridad: C): Elemento
    var 
        pointer to Nodo: aux
        Elemento: e
    inicio
        if(C.primero = nulo)
            e ← C.primero↑.info
            C.primero ← nulo
            C.ultimo ← nulo
            retornar(e)
        fif
        aux ← C.primero
        e ← aux↑.info
        C.primero ← C.primero↑.siguiente
        free(aux)
        C.tamaño ← C.tamaño - 1
        return(e)
ffunc

func peek(ColaPrioridad: C): Elemento
    Var
    
    inicio
        return(C.primero↑.info)
ffunc

func esVacio(ColaPrioridad: C): Boolean
    Var

    inicio
        return(C.primero = nulo)
ffunc

func Size(ColaPrioridad: C): entero
    Var

    inicio
        return(C.tamaño)
ffunc
```