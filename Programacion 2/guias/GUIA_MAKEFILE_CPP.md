# Guía de Makefile para C++ (teoría + práctica)

[Volver al README principal](../../README.md)

## 1) ¿Para qué sirve un Makefile?

- Reduce comandos repetitivos.
- Compila solo lo necesario.
- Estandariza flujo de build y ejecución.
- Facilita evaluación y automatización.

## 2) Conceptos clave

- **Target**: objetivo (`all`, `clean`, `run`, binarios).
- **Prerequisites**: dependencias (archivos requeridos).
- **Recipe**: comandos de shell para construir.
- **Variables**: `CXX`, `CXXFLAGS`, etc.

Formato:
```make
objetivo: dependencias
	comando
```

> Importante: el comando usa tabulación real, no espacios.

## 3) Variables típicas

- `CXX`: compilador (`g++`).
- `CXXFLAGS`: flags de compilación.
- `INCLUDES`: rutas de includes (`-Iinclude`).
- `SRC_DIR`, `BIN_DIR`: rutas del proyecto.
- `OUTPUT_MODE`: define si el binario se nombra por ejercicio (`ex`) o con un nombre fijo (`fixed`).
- `FIXED_OUTPUT_NAME`: define el nombre del binario cuando usas modo fijo.
- `BUILD_SCOPE`: define si `make` compila solo `EX` (`one`) o todos los `.cpp` (`all`).

## 4) Flujo recomendado

1. `make` o `make all`: compila.
2. `make run EX=archivo`: ejecuta ejercicio específico.
3. `make run-file EX=archivo IN=in.txt OUT=out.txt`: ejecuta con archivos.
4. `make clean`: limpia binarios.

## 5) Archivo Makefile genérico

Se provee en:
- `Programacion/Makefile.generic`

Uso ejemplo:
```bash
make -f Makefile.generic EX=02_sorted_intersect
make -f Makefile.generic run EX=02_sorted_intersect
```

## 6) Archivo Makefile aplicado al proyecto

Se provee en:
- `Programacion/Makefile`

### Selector de nombre del ejecutable

Dentro del Makefile existe esta línea:

```make
OUTPUT_MODE := ex
```

Y también esta:

```make
FIXED_OUTPUT_NAME := lpc
```

Y esta otra:

```make
BUILD_SCOPE := one
```

Ese es el único elemento que debes cambiar manualmente según el contexto:

- `OUTPUT_MODE := ex`: mantiene el comportamiento normal y genera un ejecutable con el nombre del archivo indicado en `EX`.
- `OUTPUT_MODE := fixed`: genera un ejecutable fijo con el nombre indicado en `FIXED_OUTPUT_NAME`.
- `BUILD_SCOPE := one`: `make` y `make all` compilan solo el archivo indicado en `EX`.
- `BUILD_SCOPE := all`: `make` y `make all` compilan todos los archivos `.cpp` de la carpeta de talleres.

Ejemplo:

```make
EX ?= 09_longest_zigzag
BUILD_SCOPE := one
OUTPUT_MODE := fixed
FIXED_OUTPUT_NAME := lpc
```

Con esa configuración, al ejecutar `make one`, `make run` o `make run-file`, el Makefile compilará `talleres/09_longest_zigzag.cpp` y generará:

- `bin/lpc.exe` en Windows
- `bin/lpc` en Linux/macOS

Si más adelante el nombre fijo exigido cambia, por ejemplo a `arboles`, solo editas:

```make
OUTPUT_MODE := fixed
FIXED_OUTPUT_NAME := arboles
```

Y el binario generado será:

- `bin/arboles.exe` en Windows
- `bin/arboles` en Linux/macOS

Importante:

- La variable `EX` sigue indicando qué archivo `.cpp` se compila.
- Si `BUILD_SCOPE := one`, `make` y `make all` compilan solo el archivo indicado en `EX`.
- Si `BUILD_SCOPE := all`, `make` y `make all` compilan todos los `.cpp` y cada uno conserva su propio nombre de salida.
- En modo `fixed`, el ejecutable toma el nombre definido en `FIXED_OUTPUT_NAME`.
- En modo `ex`, el ejecutable toma el nombre del archivo indicado en `EX`.
- El modo `fixed` está pensado para entrega de talleres. El modo `all` está pensado para práctica.

Comandos útiles:

### Compilar todos los ejercicios
```bash
# primero edita BUILD_SCOPE := all en el Makefile
make all
```

### Ejecutar uno
```bash
make run EX=09_longest_zigzag
```

Si el taller exige nombre fijo:

```bash
# primero edita BUILD_SCOPE := one, OUTPUT_MODE := fixed y FIXED_OUTPUT_NAME := lpc en el Makefile
make run EX=09_longest_zigzag
```

### Ejecutar con archivo de entrada y salida
```bash
make run-file EX=09_longest_zigzag IN=caso.txt OUT=resultado.txt
```

En modo taller:

```bash
# primero edita BUILD_SCOPE := one, OUTPUT_MODE := fixed y FIXED_OUTPUT_NAME := lpc en el Makefile
make run-file EX=09_longest_zigzag IN=caso.txt OUT=resultado.txt
```

Si estás practicando y quieres compilar todo:

```make
BUILD_SCOPE := all
OUTPUT_MODE := ex
```

Con eso, `make` compilará todos los ejercicios hacia `bin/`.

### Listar ejecutables disponibles
```bash
make list
```

### Limpiar
```bash
make clean
```

## 7) PowerShell (Windows)

Si tienes `make` instalado (MinGW, MSYS2, WSL), los comandos son iguales:
```powershell
make all
make run EX=09_longest_zigzag
make run-file EX=09_longest_zigzag IN=caso.txt OUT=resultado.txt
```

Si no tienes `make`, instala:
- MSYS2 + `mingw-w64-make`, o
- usa WSL.

## 8) Buenas prácticas

- Mantén binarios fuera de `src` (`bin/`).
- Activa warnings (`-Wall -Wextra -Wpedantic`).
- Usa estándar fijo (`-std=c++98`).
- Separa código reusable en `include/`.
- Si una evaluación exige un nombre fijo como `lpc` o `arboles`, usa `FIXED_OUTPUT_NAME` dentro del mismo Makefile en vez de mantener dos archivos distintos.
- Usa `BUILD_SCOPE := all` solo para práctica; para entrega conviene volver a `BUILD_SCOPE := one`.
