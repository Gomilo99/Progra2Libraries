# Guía de entrada estándar en C++ (incluyendo casos difíciles)

## 1) Reglas básicas de extracción

- `std::cin >> x`:
  - Lee tokens separados por espacios/saltos de línea.
  - Sirve para números y palabras simples.
  - No lee espacios internos en strings.

- `std::getline(std::cin, s)`:
  - Lee la línea completa (incluye espacios).
  - Ideal para textos largos o líneas mixtas.

## 2) Mezclar `>>` y `getline` sin errores

Problema típico:
- Lees un número con `cin >> n`.
- Luego llamas `getline` y recibes cadena vacía.

Solución:
```cpp
int n;
std::cin >> n;
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
std::string linea;
std::getline(std::cin, linea);
```

## 3) Lectura de líneas con comas, comillas y espacios

### Caso A: línea completa cruda
```cpp
std::string linea;
std::getline(std::cin, linea);
```

Ejemplo leído correctamente:
`"hola, mundo", 123, "a b c"`

### Caso B: parsear CSV simple (sin escapes complejos)

```cpp
std::vector<std::string> splitCSVSimple(const std::string& s) {
    std::vector<std::string> out;
    std::string current;
    bool inQuotes = false;

    for (char ch : s) {
        if (ch == '"') {
            inQuotes = !inQuotes;
        } else if (ch == ',' && !inQuotes) {
            out.push_back(current);
            current.clear();
        } else {
            current.push_back(ch);
        }
    }
    out.push_back(current);
    return out;
}
```

## 4) Parsear números de una línea

```cpp
std::string linea;
std::getline(std::cin, linea);
std::stringstream ss(linea);
int x;
while (ss >> x) {
    // procesar x
}
```

## 5) Leer todo el archivo de entrada estándar

```cpp
std::string contenido(
    (std::istreambuf_iterator<char>(std::cin)),
    std::istreambuf_iterator<char>()
);
```

## 6) Buenas prácticas para evaluaciones con archivo por stdin

- No mezclar prompts (`"Ingrese..."`) con salida evaluable.
- Validar formato y reportar errores a `std::cerr`.
- Mantener salida limpia en `std::cout`.
- Si hay formatos mixtos, leer por línea (`getline`) y parsear después.

## 7) Patrón robusto recomendado

1. Leer líneas completas (`getline`).
2. Validar si la línea está vacía.
3. Parsear con `stringstream` o parser propio.
4. Emitir resultados en formato fijo.

Este patrón evita la mayoría de errores con espacios, comas y comillas.
