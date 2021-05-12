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

## Problemas de MARS

## Prueba de MARS
