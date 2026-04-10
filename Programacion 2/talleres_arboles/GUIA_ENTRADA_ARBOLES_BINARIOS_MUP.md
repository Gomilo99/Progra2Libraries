# Guia practica: leer entrada y procesar arboles binarios (inorden + pre/post)

## 1. Formato de entrada esperado

Este tipo de problema suele venir asi:

1. Un entero `t` (cantidad de casos).
2. Por cada caso, un entero `n` (cantidad de grupos/arboles).
3. Por cada grupo:
   - Una linea con `INORDEN ...`
   - Una linea con `PREORDEN ...` o `POSTORDEN ...`
   - Una linea con nodos de prueba (consultas)

Ejemplo de un grupo:

- `INORDEN juan camila santiago mariana pedro`
- `PREORDEN santiago camila juan mariana pedro`
- `juan mariana pedro`

## 2. Patron robusto de lectura en C++98

Regla de oro cuando mezclas `>>` con `getline`:

1. Lee enteros con `cin >> x`.
2. Haz `cin.ignore(numeric_limits<streamsize>::max(), '\n')`.
3. Luego usa `getline` para lineas completas.

Patron minimo:

```cpp
int t;
cin >> t;
cin.ignore(numeric_limits<streamsize>::max(), '\n');

for (int caso = 0; caso < t; ++caso) {
    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int g = 0; g < n; ++g) {
        string linea1, linea2, lineaPrueba;
        getline(cin, linea1);
        getline(cin, linea2);
        getline(cin, lineaPrueba);
        // procesar...
    }
}
```

## 3. Como tokenizar y separar etiqueta de datos

Usa `istringstream`:

```cpp
vector<string> tokenizar(const string& linea) {
    vector<string> v;
    istringstream iss(linea);
    string tok;
    while (iss >> tok) v.push_back(tok);
    return v;
}
```

Interpretacion:

1. `tokens[0]` = tipo de recorrido (`INORDEN`, `PREORDEN`, `POSTORDEN`).
2. Desde `tokens[1]` en adelante = nodos.

## 4. Flujo logico del programa MUP

1. Parsear dos lineas de recorridos.
2. Detectar cual es inorden y cual es pre/post.
3. Reconstruir arbol con `ArbolBin(inOrden, otroRecorrido, esPreOrden)`.
4. Parsear linea de prueba.
5. Para cada sujeto de prueba y cada integrante:
   - calcular nodos intermedios del camino
   - calcular diferencia de niveles
   - acumular `camino * diferencia`
6. Quedarse con el grupo de mayor puntaje.

## 5. Errores comunes y como evitarlos

1. **Desfase de entrada**: leer 2 lineas cuando el formato trae 3.
   - Solucion: por grupo leer exactamente 3 `getline`.

2. **Mezcla de `>>` y `getline` sin ignore**.
   - Solucion: usar `cin.ignore(...)` tras cada entero.

3. **Recorridos con tamanos distintos**.
   - Solucion: validar y lanzar error temprano.

4. **Etiquetas invalidas**.
   - Solucion: aceptar solo `INORDEN`, `PREORDEN`, `POSTORDEN`.

5. **Consultas con nodos fuera del arbol**.
   - Solucion: si profundidad es `-1`, ignorar o reportar segun enunciado.

## 6. Escalabilidad: cuando hay cientos o miles de parametros

Si el juez mete entradas grandes, no cambies por `list` solo por tamano.

Recomendado:

1. Mantener `vector<string>` para datos secuenciales.
2. Agregar cache de profundidad por nodo (`map<string, int>`).
3. Agregar cache de camino por par (`map<string, map<string, int> >` o clave combinada).
4. Evitar recalculos repetidos de LCA en doble ciclo.

## 7. Posibles adaptaciones segun problema

1. **Salida distinta**: imprimir puntaje por grupo en vez de solo el indice ganador.
2. **Empates**: definir politica (primer grupo, ultimo, todos).
3. **Nombres duplicados**: si el enunciado los permite, esta tecnica de reconstruccion clasica ya no es unica.
4. **Arbol no binario**: migrar a `ArbolN` y cambiar logica de camino/profundidad.
5. **Otra metrica**: reemplazar formula de acumulacion y reutilizar parser.

## 8. Checklist de examen

1. Confirmar formato exacto de cada bloque de entrada.
2. Verificar si hay una o varias lineas por grupo de consulta.
3. Probar con caso minimo (1 caso, 1 grupo, 1 nodo).
4. Probar caso con PREORDEN y otro con POSTORDEN.
5. Revisar que no haya saltos de linea extra en output final.
