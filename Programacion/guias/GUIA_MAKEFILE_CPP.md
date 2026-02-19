# Guía de Makefile para C++ (teoría + práctica)

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

Comandos útiles:

### Compilar todos los ejercicios
```bash
make all
```

### Ejecutar uno
```bash
make run EX=09_longest_zigzag
```

### Ejecutar con archivo de entrada y salida
```bash
make run-file EX=09_longest_zigzag IN=caso.txt OUT=resultado.txt
```

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
- Usa estándar fijo (`-std=c++17`).
- Separa código reusable en `include/`.
