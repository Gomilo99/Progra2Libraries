# Cómo Compilar y Ejecutar

Esta página explica cómo compilar y ejecutar los programas del repositorio usando el `Makefile` incluido en `Programacion 2/`.

---

## Requisitos

- **Compilador:** `g++` (C++11 o superior)
- **Sistema operativo:** Linux / macOS (o WSL en Windows)
- **make** instalado en el sistema

---

## Estructura del Makefile

El archivo principal es `Programacion 2/Makefile`. Usa un `Makefile.generic` reutilizable que permite compilar cualquier archivo `.cpp` sin modificar las rutas en la terminal.

**Variables configurables** (se pueden cambiar dentro del Makefile o pasar por línea de comandos):

| Variable | Descripción | Valor por defecto |
|----------|-------------|-------------------|
| `SRC_DIR` | Subcarpeta con los fuentes | `ejercicios_lpc` |
| `EX` | Nombre del archivo sin extensión | `90_test_clases` |
| `IN` | Archivo de entrada (stdin) | — |
| `OUT` | Archivo de salida (stdout) | — |

---

## Comandos disponibles

### Ver la ayuda

```bash
make help
```

### Compilar el ejercicio por defecto

```bash
make
```

Compila el archivo definido en las variables por defecto del Makefile.

### Compilar un archivo específico

```bash
make one SRC_DIR=<carpeta> EX=<nombre_sin_extension>
```

**Ejemplos:**

```bash
# Taller de grafos
make one SRC_DIR=talleres_grafos EX=2-2025_ordenMundial

# Test de librerías LPC
make one SRC_DIR=ejercicios_lpc EX=90_test_clases

# Taller de árboles
make one SRC_DIR=talleres_arboles EX=1-2026_rutaDefensa
```

### Compilar y ejecutar con stdin interactivo

```bash
make run SRC_DIR=<carpeta> EX=<nombre>
```

El programa queda a la espera de entrada por teclado (stdin).

### Compilar y ejecutar con archivos de entrada/salida

```bash
make run-file SRC_DIR=<carpeta> EX=<nombre> IN=<ruta_entrada> OUT=<ruta_salida>
```

**Ejemplo completo:**

```bash
make run-file \
  SRC_DIR=talleres_grafos \
  EX=1-2026_ultimaOla \
  IN=talleres_grafos/in_1-2026_caso_mediano.txt \
  OUT=talleres_grafos/out_1-2026_caso_mediano.txt
```

### Limpiar ejecutables generados

```bash
make clean
```

---

## Comparar con la salida esperada

Una vez generada la salida, puedes compararla con la esperada usando `diff`:

```bash
diff mi_salida.txt out_1-2026_caso_mediano.txt
```

Si no hay diferencias, el comando no imprime nada (salida vacía = correcto).

---

## Modificar las rutas sin tocar la terminal

Si prefieres no pasar variables por línea de comandos cada vez, edita directamente las variables al inicio del `Makefile`:

```makefile
SRC_DIR = talleres_lpc
EX      = 1-2026_asamblea
IN      = talleres_lpc/in_1-2026_caso_pequeno.txt
OUT     = talleres_lpc/out_1-2026_caso_pequeno.txt
```

Luego simplemente ejecuta `make` o `make run-file`.

---

## Compilación manual (sin make)

Si no tienes `make`, puedes compilar directamente con `g++`:

```bash
# Desde Programacion 2/
g++ -std=c++11 -I include talleres_lpc/1-2026_asamblea.cpp -o programa

# Ejecutar con archivo de entrada
./programa < talleres_lpc/in_1-2026_caso_pequeno.txt
```

---

Para más detalles sobre el Makefile, consulta la guía [`GUIA_MAKEFILE_CPP.md`](https://github.com/Gomilo99/Progra2Libraries/blob/main/Programacion%202/guias/GUIA_MAKEFILE_CPP.md).
