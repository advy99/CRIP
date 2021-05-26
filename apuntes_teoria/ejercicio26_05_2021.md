Antonio David Villegas Yeguas

Tenemos un mensaje m formado por n bits

Si n = 1, añadimos 1 a la derecha y vamos al paso siguiente.
Si n < 4, añadimos a la derecha la suma (XOR) de los ultimos bits. Este proceso lo repetimos hasta que tengamos 4 bits.
Si n = 4 lo dejamos tal cual.
Si n >= 5 sumamos los dos primeros bits. El resultado final lo colocamos al final y los dos bit sumados los eliminamos, así hasta que n = 4

Sea :

p = 103
q = 17
alpha = 72
y = 8

1. Comprueba los parametros (p, q, alpha, y) pueden ser los parámetros públicos necesarios para un  sistema de firma DSA (salvo en lo referente al tamaño de los números primos).  

Para esto, tenemos que comprobar que alpha^q es uno mod p.
Como vemos esto se cumple:
>>> pow(72, 17, 103)
1

2. Calcula el parámetro x (privado).

Sabemos que y = alpha^x mod p

./bin/ejercicio5 72 8 103
72 ^ 5 = 8 en Z_103

Comprobacion con pow
>>> pow(72, 5, 103)
8

3. Firma el mensaje 10110101110101011011 (nota: puesto que el resumen del mensaje tiene 4 bits, podemos verlo como un número comprendido entre 0 y 15).


10110101110101011011
1101011101010110111
010111010101101110
01110101011011101
1101010110111011
010101101110110
01011011101101
0110111011011
101110110111
11101101111
1011011110
110111101
01111010
1110101
101010
10101
1011


Este numero en decimal es el 11.

k = 10

r = (alpha^k mod p) mod q


>>> pow(72, 10, 103)
64
>>> 64 % 17
13

r = 13

k^{-1} = 12

s = (h + x * r) * k^{-1} mod q

>>> ((11 + 5 * 13) * 12 ) % 17
11

s = 11

La firma es (13, 11)


4. Sea el mensaje 10101. Comprueba si (0,14) es una firma válida.


el resumen es

10101
1011

Es el mismo mensaje que antes.

r = 0
Ahora s  = 15
s^{-1} = 11

u = h * s^{-1} mod q

>>> (11 * 11) % 17
2

u = 2

Calculamos v = r * s^{-1}

v = 0 ya que r = 0

Calculamos r' = ((alpha^u * y^v) mod p) mod q

>>> pow(72, 2, 103)
34
>>> 34 % 17
0

r' = 0

Como r = r' , la firma es valida
