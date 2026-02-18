# Solución - longestParityAlternatingSublist

## Enunciado
`func longestParityAlternatingSublist(Lista<int>: target): int`

Devuelve la longitud de la sublista contigua más larga donde los números alternan entre par e impar.

Ejemplo:
- Entrada: `[1, 3, 2, 4, 3, 5, 5, 2]`
- Salida: `6`

## Solución LPC (O(n), sin apuntadores)
```Pseudocodigo
func longestParityAlternatingSublist(Lista<int>: target): int
	Var
		int: maxLen, actualLen, ant, actual
	Begin
		if target.esVacia() then
			return 0
		endif

		maxLen <─ 1
		actualLen <─ 1

		ant <─ target.consultar(1)
		target.eliminar(1)

		while ¬target.esVacia() do
			actual <─ target.consultar(1)
			target.eliminar(1)

			if (ant mod 2 = 0 ^ actual mod 2 != 0) v (ant mod 2 != 0 ^ actual mod 2 = 0) then
				actualLen <─ actualLen + 1
			else
				actualLen <─ 1
			endif

			if maxLen < actualLen then
				maxLen <─ actualLen
			endif

			ant <─ actual
		endwhile

		return maxLen
endfunc
```

## Corrida en frío (resumen)
Lista: `[1, 3, 2, 4, 3, 5, 5, 2]`

- `1 -> 3` no alterna (impar-impar): `actualLen = 1`, `maxLen = 1`
- `3 -> 2` alterna: `actualLen = 2`, `maxLen = 2`
- `2 -> 4` no alterna: `actualLen = 1`, `maxLen = 2`
- `4 -> 3` alterna: `actualLen = 2`, `maxLen = 2`
- `3 -> 5` no alterna: `actualLen = 1`, `maxLen = 2`
- `5 -> 5` no alterna: `actualLen = 1`, `maxLen = 2`
- `5 -> 2` alterna: `actualLen = 2`, `maxLen = 2`

Salida para este ejemplo: `2`

## Nota importante
Si tu cátedra espera salida `6` para esa misma entrada, ese enunciado corresponde al ejercicio de **zigzag** (sube-baja), no al de **paridad alternante**.