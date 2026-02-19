# Guía: pasar archivos por entrada estándar y guardar salida

## 1) Concepto

- `stdin` (entrada estándar): datos que consume el programa.
- `stdout` (salida estándar): resultados normales del programa.
- `stderr` (salida de error): mensajes de error.

En revisión automática, normalmente se usa:
- entrada desde archivo,
- salida a archivo.

## 2) Linux / macOS (bash, zsh)

## Compilar
```bash
g++ -std=c++17 -O2 -Wall -Wextra -Iinclude ejercicios/02_sorted_intersect.cpp -o bin/02_sorted_intersect
```

## Ejecutar leyendo de archivo y escribiendo a archivo
```bash
./bin/02_sorted_intersect < in.txt > out.txt
```

## Guardar también errores
```bash
./bin/02_sorted_intersect < in.txt > out.txt 2> err.txt
```

## Unir stdout y stderr en un solo archivo
```bash
./bin/02_sorted_intersect < in.txt > all.txt 2>&1
```

## 3) Windows PowerShell

## Compilar
```powershell
g++ -std=c++17 -O2 -Wall -Wextra -Iinclude ejercicios\02_sorted_intersect.cpp -o bin\02_sorted_intersect.exe
```

## Ejecutar con redirección
```powershell
Get-Content in.txt | .\bin\02_sorted_intersect.exe | Set-Content out.txt
```

Alternativa (si redirección `<` está disponible en tu entorno):
```powershell
.\bin\02_sorted_intersect.exe < in.txt > out.txt
```

## Guardar errores por separado
```powershell
.\bin\02_sorted_intersect.exe < in.txt > out.txt 2> err.txt
```

## 4) Recomendaciones para revisión automática

- Evita imprimir textos decorativos.
- Imprime solo formato esperado.
- Asegura salto de línea final.
- Usa `stderr` para debug, no `stdout`.

## 5) Plantilla mínima de uso

```bash
# Linux
./programa < entrada.txt > salida.txt
```

```powershell
# PowerShell
Get-Content entrada.txt | .\programa.exe | Set-Content salida.txt
```
