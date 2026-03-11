# Guia de Makefile para C

Esta guia explica que es un Makefile, como se lee y como se aplica a programas pequenos en C como esta libreria de listas, pilas y colas.

## 1. Que es un Makefile

Un Makefile es un archivo de texto con instrucciones para compilar un programa.

Su objetivo principal es evitar que tengas que escribir siempre comandos largos como estos:

```bash
gcc -Wall -Wextra -Werror -std=c11 -c lista.c
gcc -Wall -Wextra -Werror -std=c11 -c pila.c
gcc -Wall -Wextra -Werror -std=c11 -c cola.c
gcc -Wall -Wextra -Werror -std=c11 -c ejemplo_uso.c
gcc -Wall -Wextra -Werror -std=c11 -o ejemplo_uso.exe ejemplo_uso.o lista.o pila.o cola.o
```

Con make, en cambio, puedes escribir solo:

```bash
make
```

o tambien:

```bash
make run-pruebas
```

## 2. Para que sirve en C

En C normalmente un programa se divide en varios archivos.

Por ejemplo, en este proyecto tenemos:

- lista.c
- pila.c
- cola.c
- ejemplo_uso.c
- prueba_estructuras.c

Si compilaras todo manualmente cada vez, perderias tiempo y cometerias errores facilmente.

Make resuelve eso porque:

- compila solo lo necesario
- recuerda dependencias entre archivos
- permite crear comandos cortos y claros
- mantiene ordenado el proceso de construccion

## 3. Estructura basica de un Makefile

La forma general es esta:

```make
objetivo: dependencias
	comando
```

Ejemplo:

```make
programa: main.o util.o
	gcc -o programa main.o util.o
```

Esto significa:

- para construir programa, antes necesito main.o y util.o
- cuando esos archivos existan, ejecuto el comando gcc -o programa main.o util.o

Importante: la linea del comando debe empezar con una tabulacion real.

## 4. El Makefile de este proyecto

El archivo [Programacion1/Makefile](Programacion1/Makefile) contiene estas ideas principales.

### Variables

```make
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
OBJETOS = lista.o pila.o cola.o
```

Esto sirve para no repetir texto.

- CC es el compilador
- CFLAGS son las banderas de compilacion
- OBJETOS es la lista de archivos objeto comunes

Entonces en vez de escribir muchas veces todo el comando, reutilizamos variables.

## 5. Que significan las banderas del compilador

En este proyecto usamos:

```make
-Wall -Wextra -Werror -std=c11
```

Significado:

- -Wall: activa advertencias comunes
- -Wextra: activa advertencias adicionales
- -Werror: trata advertencias como errores
- -std=c11: compila usando el estandar C11

Esto es muy util en clases porque obliga a escribir codigo mas limpio.

## 6. Objetivo principal: all

```make
all: ejemplo_uso$(EXE) prueba_estructuras$(EXE)
```

Este objetivo dice que cuando escribes make, se construyen dos programas:

- ejemplo_uso
- prueba_estructuras

En Windows se agrega la extension .exe.

## 7. Como se construye un ejecutable

```make
ejemplo_uso$(EXE): ejemplo_uso.o $(OBJETOS)
	$(CC) $(CFLAGS) -o $@ $^
```

Esto significa:

- para crear ejemplo_uso necesito ejemplo_uso.o, lista.o, pila.o y cola.o
- despues enlazo todo con gcc

Los simbolos especiales significan:

- $@: el nombre del objetivo actual
- $^: todas las dependencias

Si expandimos esa linea, seria algo parecido a:

```bash
gcc -Wall -Wextra -Werror -std=c11 -o ejemplo_uso.exe ejemplo_uso.o lista.o pila.o cola.o
```

## 8. Como se construye un archivo .o

Ejemplo:

```make
lista.o: lista.c lista.h nodo.h
	$(CC) $(CFLAGS) -c lista.c
```

Esto significa:

- lista.o depende de lista.c, lista.h y nodo.h
- si cualquiera de esos cambia, make recompila lista.o

La opcion -c le dice a gcc que compile pero no enlace todavia.

Resultado:

- entrada: lista.c
- salida: lista.o

## 9. Por que se ponen los .h como dependencias

Mira este caso:

```make
pila.o: pila.c pila.h lista.h nodo.h
```

Aunque el archivo compilado directamente sea pila.c, tambien agregamos los .h relacionados.

Eso es importante porque si cambias una declaracion en un .h, make entiende que pila.o debe reconstruirse.

Sin esa dependencia, podrias quedar con binarios viejos y errores raros.

## 10. Objetivos utiles para clase

### Ejecutar ejemplo

```make
run-ejemplo: ejemplo_uso$(EXE)
	./ejemplo_uso$(EXE)
```

Hace dos cosas:

- verifica que el ejecutable exista
- lo ejecuta

Entonces puedes escribir:

```bash
make run-ejemplo
```

### Ejecutar pruebas

```make
run-pruebas: prueba_estructuras$(EXE)
	./prueba_estructuras$(EXE)
```

Sirve para compilar y correr pruebas de una vez:

```bash
make run-pruebas
```

### Limpiar archivos generados

```make
clean:
	powershell -NoProfile -Command "Remove-Item -Force -ErrorAction SilentlyContinue *.o, *.exe"
```

Este objetivo borra archivos temporales y ejecutables generados en Windows.

Se usa asi:

```bash
make clean
```

## 11. Que son los objetivos .PHONY

```make
.PHONY: all clean run-ejemplo run-pruebas
```

Esto le dice a make que esos nombres no son archivos reales sino acciones.

Por ejemplo, clean no crea un archivo llamado clean. Solo ejecuta una tarea.

Si no usas .PHONY, make a veces puede confundirse si existe un archivo con el mismo nombre.

## 12. Flujo normal de trabajo para ejemplos sencillos

En un proyecto chico como este, el flujo recomendado es:

1. escribes o modificas codigo en un .c o .h
2. ejecutas make
3. si quieres ver el ejemplo, ejecutas make run-ejemplo
4. si quieres validar comportamiento, ejecutas make run-pruebas
5. si quieres empezar limpio, ejecutas make clean

## 13. Ejemplo minimo de Makefile para principiantes

Si solo tuvieras dos archivos, main.c y suma.c, un Makefile muy sencillo podria ser este:

```make
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: programa

programa: main.o suma.o
	$(CC) $(CFLAGS) -o programa main.o suma.o

main.o: main.c suma.h
	$(CC) $(CFLAGS) -c main.c

suma.o: suma.c suma.h
	$(CC) $(CFLAGS) -c suma.c

clean:
	rm -f *.o programa

.PHONY: all clean
```

Ese es el modelo mental que luego se amplia a proyectos mas grandes.

## 14. Diferencia entre compilar y enlazar

Este punto suele confundir mucho al inicio.

### Compilar

Transforma cada archivo .c en un archivo .o.

Ejemplo:

```bash
gcc -c lista.c
```

### Enlazar

Une varios archivos .o para formar el programa final.

Ejemplo:

```bash
gcc -o ejemplo_uso.exe ejemplo_uso.o lista.o pila.o cola.o
```

Makefile organiza estas dos etapas automaticamente.

## 15. Que pasa si modifico un solo archivo

Supongamos que cambias solo lista.c.

Cuando ejecutes make:

- make recompila lista.o
- luego vuelve a enlazar los ejecutables que dependan de lista.o
- no recompila innecesariamente lo que no cambio

Esa es una de las mayores ventajas de usar make.

## 16. Errores comunes en Makefile

### Usar espacios en vez de tab

Los comandos deben empezar con tab. Si usas espacios, make suele fallar.

### Olvidar dependencias

Si no incluyes un .h como dependencia, make puede no recompilar cuando deberia.

### Poner nombres incorrectos

Si escribes mal un archivo, make no podra encontrarlo.

### Mezclar rutas o comandos segun el sistema operativo

En Windows a veces el comando de limpieza cambia respecto de Linux. Por eso en este proyecto se dejo clean usando PowerShell.

## 17. Como adaptar este Makefile a otros ejercicios

Si haces otro ejercicio en C con varios modulos, puedes copiar esta idea:

1. defines CC y CFLAGS
2. agrupas los .o comunes en una variable
3. haces un objetivo principal all
4. escribes una regla por cada ejecutable
5. escribes una regla por cada archivo .o
6. agregas clean y .PHONY

## 18. Resumen corto

Piensa un Makefile asi:

- objetivo: que quiero construir
- dependencias: que necesita antes
- comando: como se construye

En este proyecto, make automatiza la compilacion de una libreria simple de estructuras de datos y sus programas de ejemplo y prueba.

## 19. Comandos utiles para este proyecto

Desde la carpeta Programacion1:

```bash
make
make run-ejemplo
make run-pruebas
make clean
```

## 20. Recomendacion docente

Si estas empezando, no memorices el Makefile completo de una vez.

Aprende primero estas tres ideas:

- un .c normalmente se convierte en .o
- varios .o se unen para crear el ejecutable
- make hace eso solo si las dependencias estan bien escritas

Cuando esa idea queda clara, el resto del archivo empieza a tener sentido muy rapido.