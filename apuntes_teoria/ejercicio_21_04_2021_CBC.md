Antonio David Villegas Yeguas


Ejercicio descifrado CBC

Vector de inicialización: 000000


Mensaje cifrado: 010101 101001 000001 111111 010010

Primer bloque: 010101

Multiplicamos el mensaje cifrado por el inverso de 13 mod 64 = 4

010101 = 21

21 * 5 = 105

105 = 1101001, hacemos mod 64 = 101001

A esto le hacemos XOR con el vector de inicializacion:

101001 XOR 000000 = 101001

101001 = 41


Segundo bloque: 101001 = 41

41 * 5 = 205

205 en binario = 11001101

y modulo 64 = 001101

001101 en decimal = 13

001101 XOR 010101 = 11000 (24 en decimal)

Segundo bloque de texto plano = 011000


Tercer bloque: 000001 = 1

1 * 5 = 5

Modulo 64 y en binario: 000101 = 5

000101 XOR 101001 = 101100 (44 en decimal)


Cuarto bloque: 111111 = 63

63 * 5 = 315

315 en binario = 100111011

365 moduo 64 en binario  = 111011
111011 = 59

111011 XOR  000001 = 111010 (58 en decimal)

Quinto bloque: 010010 = 18

18 * 5 = 90
90 en binario = 1011010

90 modulo 64 es = 011010 (26 en decimal)

011010 ^ 111111 = 100101 (37 en binario)

El resultado es:

101001 011000 101100 111010 100101

Lo separamos en bloques de 5:

10100 10110 00101 10011 10101 00101

20 22 5 19 21 5

El mensaje descifrado es:

SUERTE
