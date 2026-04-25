# Progra2Libraries — Wiki

Bienvenido a la wiki del repositorio **Progra2Libraries**, un repositorio de estudio y práctica para las materias de **Algoritmos 2**, **Programación 1** y **Programación 2**.

> ⚠️ Este repositorio se elaboró con ayuda de inteligencia artificial (ChatGPT / Codex) con fines educativos. Las soluciones **no deben tomarse como absolutas**; se recomienda cotejat los resultados, identificar posibles mejoras y contribuir si las encuentras.

---

## 📌 Navegación rápida

| Página | Descripción |
|--------|-------------|
| [Estructura del Repositorio](Estructura-del-Repositorio) | Mapa de carpetas y archivos del proyecto |
| [Librerías C++](Librerias-CPP) | Documentación de las librerías genéricas en C++ (LPC, Árboles, Grafos) |
| [Librerías C](Librerias-C) | Documentación de las librerías de estructuras en C (Programación 1) |
| [Algoritmos — Apuntes](Algoritmos) | Resumen de clases teóricas de Algoritmos 2 |
| [Talleres y Casos de Prueba](Talleres) | Soluciones de talleres históricos y casos de prueba |
| [Guías de Programación](Guias) | Guías de compilación, Makefile, STL y redirección |
| [Cómo Compilar y Ejecutar](Como-Compilar) | Instrucciones paso a paso para compilar con `make` |

---

## 🗂️ Resumen del proyecto

```
Progra2Libraries/
├── Algoritmos/          # Apuntes teóricos en Markdown (POO, LPC, Árboles, Grafos)
├── PDF/                 # Material PDF de clases, ejercicios, guías y parciales
├── Programacion 2/      # Librerías C++, talleres y ejercicios
│   ├── include/         # Cabeceras genéricas (.hpp)
│   ├── guias/           # Guías de programación en Markdown
│   ├── talleres_lpc/    # Soluciones taller LPC
│   ├── talleres_arboles/# Soluciones taller Árboles
│   └── talleres_grafos/ # Soluciones taller Grafos
└── Programacion1/       # Librerías y prácticas en C
```

---

## ⚠️ Limitaciones conocidas

- La clase `ArbolBin` tiene la implementación de AVL **incompleta** (faltan ejercicios de balanceo con rotaciones).
- Las soluciones de parciales de árboles **no registran** los pasos de balanceo AVL.
- Algunos talleres pueden contener errores; las soluciones más confiables son:
  - **LPC**: `1-2026_asamblea.cpp`
  - **Grafos**: `1-2026_ultimaOla.cpp`
  - **Árboles**: la solución de `rutaDefensa` es aproximada; existen dos versiones mejoradas.

---

## 🤝 Contribuciones

¡Las mejoras son bienvenidas! Si encuentras un error o tienes una solución más eficiente, abre un *issue* o un *pull request*. Se recomienda también utilizar cualquier LLM de frontera para validar o mejorar un programa particular.
