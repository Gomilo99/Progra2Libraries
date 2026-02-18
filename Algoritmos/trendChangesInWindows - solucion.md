# Solución - trendChangesInWindows HECHA A MANO
**Ejercicio 3**
Dada una lista de números enteros, escriba la función:
``func trendChangesInWindows(List<int>: target, int k): Lista<int>``
Que reciba un entero k y devuelva una nueva lista donde cada posición indique cuántas veces la secuencia de números dentro de la ventana cambia de tendencia, es decir, de creciente a decreciente o de decreciente a creciente.
Ejemplo:
Entrada: [1, 3, 2, 4, 3, 5], k = 4
Salida: [2, 2, 2]
>NO DEBE USAR APUNTADORES EN SU SOLUCIÓN. Su solución debe ser a lo sumo O(n)

```
func trendChangesInWindow(List<int>: target, int: k): Lista<int>
	Var
		Lista<int>: result
		Cola<int>: window
		int: i, actual, counter, primeroVentana
		bool: crec, decre
	Begin
		result.construir()
		window.construir()
		crec <─ false
		decre <─ false
		counter <─ 0

		//Calcular la primera ventana
		for i <─ 1 to k do
			actual <─ target.consultar(1)
			target.eliminar(1)

			if window.getLong() >= 1 then

				//Condición de aumento del contador
				if window.getUltimo() < actual then
					crec <─ true
					if crec = decre then
						decre <─ false
						counter <─ counter +1
					endif
				else
					if window.getUltimo() > actual then
						decre <─ true
						if crec = decre then
							crec <─ false
							counter <─ counter +1
						endif
					endif
				endif
			endif
			window.encolar(actual)
		endfor
		result.insertar(counter, 1)
		
		while ¬target.esVacia() do
			primeroVentana <─ window.getFrente()
			window.desencolar()
			if primeroVentana < window.getFrente() then
				crec <─ true
				if crec = decre then
					decre <─ false
					counter <─ counter -1
				endif
			else
				if primeroVentana > window.getFrente() then
					decre <─ true
					if crec = decre then
						crec <─ false
						counter <─ counter -1
					endif
				endif
			endif

			actual <─ target.consultar(1)
			target.eliminar(1)
			if window.getUltimo() < actual then
				crec <─ true
				if crec = decre then
					decre <─ false
					counter <─ counter +1
				endif
			else
				if window.getUltimo() > actual then
					decre <─ true
					if crec = decre then
						crec <─ false
						counter <─ counter +1
					endif
				endif
			endif

			window.encolar(actual)
			result.insertar(counter, result.getLong() +1)
		endwhile
		
		return result
endfunc
```
# Solución - trendChangesInWindows (versión examen) Chat GPT 5.3 codex
## Supuestos aceptados
- La lista `target` no está vacía.
- `k` es válido para la lista de entrada.
- Los valores de entrada son válidos y no exceden límites.

Bajo estos supuestos no se agregan validaciones extra de borde.

```Pseudocodigo
func trendChangesInWindows(Lista<int>: target, int: k): Lista<int>
	Var
		Lista<int>: result
		Cola<int>: window, signos, cambios
		int: i, actual, anterior, signoActual, signoAnterior, cambio, counter
	Begin
		result.construir()
		window.construir()
		signos.construir()
		cambios.construir()
		counter <─ 0

		// Primera ventana de tamaño k
		for i <─ 1 to k do
			actual <─ target.consultar(1)
			target.eliminar(1)

			if i = 1 then
				anterior <─ actual
			else
				signoActual <─ 0
				if anterior < actual then
					signoActual <─ 1
				endif
				if anterior > actual then
					signoActual <─ -1
				endif

				if signos.getLong() > 0 then
					signoAnterior <─ signos.getUltimo()
					cambio <─ 0
					if (signoAnterior = 1 ^ signoActual = -1) v (signoAnterior = -1 ^ signoActual = 1) then
						cambio <─ 1
						counter <─ counter + 1
					endif
					cambios.encolar(cambio)
				endif

				signos.encolar(signoActual)
				anterior <─ actual
			endif

			window.encolar(actual)
		endfor

		result.insertar(counter, result.getLong() + 1)

		// Ventanas restantes
		while ¬target.esVacia() do
			window.desencolar()
			signos.desencolar()

			if cambios.getFrente() = 1 then
				counter <─ counter - 1
			endif
			cambios.desencolar()

			actual <─ target.consultar(1)
			target.eliminar(1)

			signoActual <─ 0
			if window.getUltimo() < actual then
				signoActual <─ 1
			endif
			if window.getUltimo() > actual then
				signoActual <─ -1
			endif

			signoAnterior <─ signos.getUltimo()
			cambio <─ 0
			if (signoAnterior = 1 ^ signoActual = -1) v (signoAnterior = -1 ^ signoActual = 1) then
				cambio <─ 1
				counter <─ counter + 1
			endif

			cambios.encolar(cambio)
			signos.encolar(signoActual)
			window.encolar(actual)

			result.insertar(counter, result.getLong() + 1)
		endwhile

		return result
endfunc
```

## Idea clave
- `signos` guarda la tendencia entre pares consecutivos de la ventana (`1`, `-1`, `0`).
- `cambios` guarda si entre dos signos consecutivos hubo cambio real (`1`) o no (`0`).
- Al mover la ventana: se resta el cambio que sale y se suma el cambio que entra.
- Cada elemento entra y sale una sola vez: complejidad `O(n)`.

## Versión corta (parcial)

```Pseudocodigo
func trendChangesInWindows(Lista<int>: target, int: k): Lista<int>
	Var
		Lista<int>: result
		Cola<int>: window, signos
		int: i, actual, anterior, signoActual, s1, s2, counter
	Begin
		result.construir()
		window.construir()
		signos.construir()
		counter <─ 0

		// Primera ventana
		for i <─ 1 to k do
			actual <─ target.consultar(1)
			target.eliminar(1)

			if i = 1 then
				anterior <─ actual
			else
				signoActual <─ 0
				if anterior < actual then
					signoActual <─ 1
				endif
				if anterior > actual then
					signoActual <─ -1
				endif

				if signos.getLong() > 0 then
					s1 <─ signos.getUltimo()
					if (s1 = 1 ^ signoActual = -1) v (s1 = -1 ^ signoActual = 1) then
						counter <─ counter + 1
					endif
				endif

				signos.encolar(signoActual)
				anterior <─ actual
			endif

			window.encolar(actual)
		endfor

		result.insertar(counter, result.getLong() + 1)

		// Ventanas restantes
		while ¬target.esVacia() do
			// Quitar aporte saliente
			if signos.getLong() >= 2 then
				s1 <─ signos.getFrente()
				signos.desencolar()
				s2 <─ signos.getFrente()
				if (s1 = 1 ^ s2 = -1) v (s1 = -1 ^ s2 = 1) then
					counter <─ counter - 1
				endif
			endif

			window.desencolar()

			// Agregar nuevo elemento y aporte entrante
			actual <─ target.consultar(1)
			target.eliminar(1)

			signoActual <─ 0
			if window.getUltimo() < actual then
				signoActual <─ 1
			endif
			if window.getUltimo() > actual then
				signoActual <─ -1
			endif

			if signos.getLong() > 0 then
				s1 <─ signos.getUltimo()
				if (s1 = 1 ^ signoActual = -1) v (s1 = -1 ^ signoActual = 1) then
					counter <─ counter + 1
				endif
			endif

			signos.encolar(signoActual)
			window.encolar(actual)
			result.insertar(counter, result.getLong() + 1)
		endwhile

		return result
endfunc
```