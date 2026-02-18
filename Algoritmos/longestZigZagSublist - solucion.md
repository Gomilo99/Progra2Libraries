# Solución - longestZigZagSublist (Parcial 2-2025 mod1, Ejercicio 2)

## Enunciado
Dada una lista enlazada de números enteros, crear:
`func longestZigZagSublist(Lista<int>: target): int`
que devuelva la longitud de la sublista contigua más larga en patrón zigzag (alterna subir y bajar).

Ejemplo:
Entrada: `[1, 3, 2, 4, 3, 5, 5, 2]`
Salida: `6`

## Idea
- Se comparan ternas consecutivas `(ant2, ant1, actual)`.
- Hay zigzag si ocurre uno de estos dos patrones:
  - `ant2 < ant1 ^ ant1 > actual`
  - `ant2 > ant1 ^ ant1 < actual`
- `counter` cuenta cuántas ternas consecutivas válidas llevamos.
- Longitud de la sublista zigzag asociada a `counter` es `counter + 2`.

## Solución en LPC
```Pseudocodigo
func longestZigZagSublist(Lista<int>: target): int
	Var
		int: counter, actual, ant2, ant1, maxCounter
	Begin
		if target.getLong() < 3 then
			return target.getLong()
		endif

		maxCounter <─ 0
		counter <─ 0

		ant2 <─ target.consultar(1)
		target.eliminar(1)
		ant1 <─ target.consultar(1)
		target.eliminar(1)

		while ¬target.esVacia() do
			actual <─ target.consultar(1)
			target.eliminar(1)

			if (ant2 < ant1 ^ ant1 > actual) v (ant2 > ant1 ^ ant1 < actual) then
				counter <─ counter + 1
			else
				if maxCounter < counter then
					maxCounter <─ counter
				endif
				counter <─ 0
			endif

			ant2 <─ ant1
			ant1 <─ actual
		endwhile

		if maxCounter < counter then
			maxCounter <─ counter
		endif

		if maxCounter = 0 then
			return 1
		endif

		return maxCounter + 2
endfunc
```

## Corrida en frío
Entrada: `L = [1, 3, 2, 4, 3, 5, 5, 2]`

Inicial:
- `ant2 = 1`, `ant1 = 3`, `counter = 0`, `maxCounter = 0`

1) `actual = 2`
- `(1 < 3 ^ 3 > 2)` verdadero
- `counter = 1`
- Actualizar: `ant2 = 3`, `ant1 = 2`

2) `actual = 4`
- `(3 > 2 ^ 2 < 4)` verdadero
- `counter = 2`
- Actualizar: `ant2 = 2`, `ant1 = 4`

3) `actual = 3`
- `(2 < 4 ^ 4 > 3)` verdadero
- `counter = 3`
- Actualizar: `ant2 = 4`, `ant1 = 3`

4) `actual = 5`
- `(4 > 3 ^ 3 < 5)` verdadero
- `counter = 4`
- Actualizar: `ant2 = 3`, `ant1 = 5`

5) `actual = 5`
- `(3 < 5 ^ 5 > 5)` falso y `(3 > 5 ^ 5 < 5)` falso
- `maxCounter = 4`, `counter = 0`
- Actualizar: `ant2 = 5`, `ant1 = 5`

6) `actual = 2`
- `(5 < 5 ^ 5 > 2)` falso y `(5 > 5 ^ 5 < 2)` falso
- `counter` sigue `0`

Fin:
- `maxCounter = 4`
- Respuesta: `maxCounter + 2 = 6`

Salida final: `6`

## Complejidad
- Tiempo: `O(n)`
- Espacio extra: `O(1)`
- No usa apuntadores.