# Talleres y Casos de Prueba

Esta página documenta los talleres históricos resueltos y los casos de prueba disponibles en el repositorio.

> ⚠️ **Importante:** Los talleres pueden contener errores. No tomar como solución absoluta. Siempre verificar con los casos de prueba disponibles y contrastar con otras fuentes.

---

## Tabla de contenido

- [LPC (Listas, Pilas, Colas)](#lpc-listas-pilas-colas)
- [Árboles](#árboles)
- [Grafos](#grafos)
- [Pruebas de librerías](#pruebas-de-librerías)

---

## LPC (Listas, Pilas, Colas)

**Carpeta:** `Programacion 2/talleres_lpc/`

### Soluciones disponibles

| Archivo | Descripción | Confiabilidad |
|---------|-------------|---------------|
| `1-2024_puma.cpp` | Taller 1 semestre 2024 | Referencial |
| `1-2025_semana_santa.cpp` | Taller 1 semestre 1-2025 | Referencial |
| `1-2026_asamblea.cpp` | Taller 1 semestre 1-2026 | ✅ Solución más confiable |
| `2-2025_ultima_copa.cpp` | Taller 2 semestre 2025 | Referencial |

### Casos de prueba — Taller 1-2026 (Asamblea)

| Archivo entrada | Archivo salida | Tamaño |
|-----------------|----------------|--------|
| `in_1-2026_caso_pequeno.txt` | `out_1-2026_caso_pequeno.txt` | Pequeño |
| `in_1-2026_caso_mediano.txt` | `out_1-2026_caso_mediano.txt` | Mediano |
| `in_1-2026_caso_grande.txt` | `out_1-2026_caso_grande.txt` | Grande |
| `in_1-2026_caso_gigante.txt` | `out_1-2026_caso_gigante.txt` | Gigante |

---

## Árboles

**Carpeta:** `Programacion 2/talleres_arboles/`

### Soluciones disponibles

| Archivo | Descripción | Notas |
|---------|-------------|-------|
| `1-2025_mup.cpp` | Taller 1 semestre 2025 | Referencial |
| `2-2025_chupa.cpp` | Taller 2 semestre 2025 | Referencial |
| `2-2025_chupa_pedagogico.cpp` | Versión pedagógica del anterior | Mayor legibilidad |
| `1-2026_rutaDefensa.cpp` | Taller 1 semestre 1-2026 | ⚠️ Solución base con errores |
| `1-2026_rutaDefensa_mejorado.cpp` | Versión mejorada con IA (mantiene lógica base) | Mejor que la base |
| `1-2026_rutaDefensa_orden_n.cpp` | Versión O(n) con IA | Más eficiente |

> La solución `1-2026_rutaDefensa.cpp` no es completamente correcta, pero se mantiene como base de referencia para comparar con las versiones mejoradas.

### Casos de prueba — Taller 1-2026 (Ruta Defensa)

| Archivo entrada | Archivo salida | Tamaño |
|-----------------|----------------|--------|
| `in_1-2026_caso_dummy.txt` | — | Caso mínimo de prueba |
| `in_1-2026_caso_pequeno.txt` | `out_1-2026_caso_pequeno.txt` | Pequeño |
| `in_1-2026_caso_mediano.txt` | `out_1-2026_caso_mediano.txt` | Mediano |
| `in_1-2026_caso_grande.txt` | `out_1-2026_caso_grande.txt` | Grande |
| `in_1-2026_caso_gigante.txt` | `out_1-2026_caso_gigante.txt` | Gigante |

---

## Grafos

**Carpeta:** `Programacion 2/talleres_grafos/`

### Soluciones disponibles

| Archivo | Descripción | Confiabilidad |
|---------|-------------|---------------|
| `1-2026_ultimaOla.cpp` | Taller 1 semestre 1-2026 | ✅ Solución más confiable |
| `2-2025_ordenMundial.cpp` | Taller 2 semestre 2025 | Referencial |

### Casos de prueba — Taller 1-2026 (Última Ola)

| Archivo entrada | Archivo salida | Tamaño |
|-----------------|----------------|--------|
| `in_1-2026_caso_pequeno.txt` | `out_1-2026_caso_pequeno.txt` | Pequeño |
| `in_1-2026_caso_mediano.txt` | `out_1-2026_caso_mediano.txt` | Mediano |
| `in_1-2026_caso_grande.txt` | `out_1-2026_caso_grande.txt` | Grande |
| `in_1-2026_caso_gigante.txt` | `out_1-2026_caso_gigante.txt` | Gigante |

---

## Pruebas de librerías

Archivos de prueba para validar el correcto funcionamiento de las librerías C++.

**Carpeta LPC:** `Programacion 2/ejercicios_lpc/`

| Archivo | Descripción |
|---------|-------------|
| `90_test_clases.cpp` | Pruebas de `Lista`, `Cola` y `Pila` |
| `91_test_ejercicios.cpp` | Pruebas de funciones en `Ejercicios.hpp` para LPC |

**Carpeta Árboles:** `Programacion 2/ejercicios_arboles/`

| Archivo | Descripción |
|---------|-------------|
| `90_test_clases_arboles.cpp` | Pruebas de `ArbolBin` y `ArbolN` |
| `91_test_ejercicios_arboles.cpp` | Pruebas de funciones en `Ejercicios.hpp` para árboles |

### Cómo ejecutar las pruebas

```bash
# Desde Programacion 2/
make one SRC_DIR=ejercicios_lpc EX=90_test_clases
make run  SRC_DIR=ejercicios_lpc EX=90_test_clases

make one SRC_DIR=ejercicios_arboles EX=90_test_clases_arboles
make run  SRC_DIR=ejercicios_arboles EX=90_test_clases_arboles
```

Para más detalles de compilación, consulta [Cómo Compilar y Ejecutar](Como-Compilar).
