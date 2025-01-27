# Notas presentación MARS

## Antecedentes

Uso generalizado de DES, desarrollado por IBM y aprobado por la NSA en 1977. Comienza a tener problemas por la poca longitud de clave (56 bits), tamaño de los bloques (64 bits), y las S-box no son publicas lo que hacía que no fuera un sistema transparente para el que cifraba el contenido (con esto la NSA evito una backdoor que dejaron oculta, basada en criptoanálisis diferencial ), y más tarde se llego a conocer que la NSA tenía backdoors sobre DES gracias a que el tamaño de clave tan pequeño les permitia romper el cifrado por fuerza bruta.
Propuestas como Triple-DES para suplir esos problemas.



## AES process

Propuesto por NIST (Instituto Nacional de Estándares y Tecnologı́a de EEUU) para sustituir a DES en 1997.

Pretendía que la nueva solución fuera más segura, utilizando un mayor tamaño de bloque y de claves, además de que fuera publica y de dominio publico, para que todo el mundo pudiera implementarlo, ver errores, y evitar acusaciones de puertas traseras como en DES.

Tambien se buscaba eficiencia tanto en hardware como en software, ya que DES tenia implementación hardware, dejando muchas carencias (era muy lento) en la parte software.  




## Sobre MARS

Propuesta del AES (Advanced Encryption Standard) Process de IBM

Influenciado por DES (IBM también desarrollo DES), parte del equipo de DES, como Don Coppersmith.

Cuanta con tamaño de bloque de 128 bits, y claves de tamaño variable, desde 128 hasta 448 bits.


## Redes de feistel de tipo 3
Se usa una red de feistel de tipo 3.

Se divide en 4 partes el texto plano, y basicamente la primera parte pasa a la ultima de la siguiente iteracion sin modificar, las otras tres partes se le hace un XOR con la parte anterior y la salida de la función de feistel con la primera parte y la función de ronda correspondiente dividida en tres partes

## Como funciona MARS

Tres partes:

1. Mezcla directa, 8 rondas donde se hacen transformaciones lineales sobre la entrada
2. Se aplica la red de feistel de tipo 3 con 16 rondas
3. Deshacer mezcla directa: 8 rondas donde se deshacen las transformaciones lineales del punto 1.

### Mezcla directa

A cada parte del mensaje se le aplica la clave que utilizaremos con suma, no con XOR.

La S-box se divide en dos: S0 y S1, cada una de 256 palabras de 32 bits, de cara a que sea más sencilla de manejar

Basicamente, seguir el flujo del diagrama, se van haciendo rotaciones a la derecha de 8 con cada A. Importante, en el diagrama salen 4 de las 8 rondas, por eso dice que se aplica dos veces. Los desplazamientos solo se hacen sobre A, así que cada vez que cambian de hilo donde están los desplazamientos sería una ronda distinta.

También hay que tener en cuenta que añaden ciertas operaciones pseudo-aleatorias, para añadir aleatoriedad al algoritmo.

### Núcleo criptográfico

Si son las 8 primeras rondas, trabajamos con foward mode, si son las otras 8, con backward mode, de esta forma ensuciamos mas

Basicamente es una red de feistel de tipo 3 con la que utilizamos una funcion E de expansion de llaves

### Deshacer mezcla

Seguir diagrama, lo mismo que antes, pero inverso

### S-box

S-box pseudoaleatoria, utilizando funcion hash SHA-1 haciendo OR con i y tres constantes que podemos escoger.


## Problemas de MARS

Primera imagen de XKCD: No vale inventarse una forma de ensuciar todo y presentarla como algo innovador, porque eso añade complejidad a la hora del cifrado, y por muy seguro que sea, tiene que ser facil de implementar, si de por si va a estar publico

Segunda imagen de XKCD: Explicar los problemas que tuvo Debian con SSL al eliminar una linea de codigo para evitar un warning de Valgrind. Se cargaron el de numeros pseudo-aleatorios, y por lo tanto, un monton de gente tenia las mismas claves. Moraleja: las claves son lo más importante en un sistema criptográfico, lo demás es publico y accesible, y esto se le criticó mucho a MARS, ya que solo utilizaba las llaves en la red de Feistel (a excepción de la suma/resta inicial/final).

Estructura muy compleja, de cara a obtener las claves expandidas.

Implementación muy mala a nivel de hardware por culpa de la latencia que obtiene, sobre todo en comparación con otras propuestas, no es viable para hardware poco potente y microordenadores. Aunque en principio IBM decia que tenia buenos resultados, pero solo a nivel software, y comparando DES con MARS solo en los mejores procesadorese de la epoca

## Prueba de MARS
