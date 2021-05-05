Antonio David Villegas Yeguas


LFSR de 4 celdas:

10000 00101 01000 11000 11001 00111

Sabemos cuales son los dos caracteres centrales: AM (00001 01101)


Si tengo el mensaje cifrado, con un XOR saco la clave



AM    cifrado: 01000 11000
AM no cifrado: 00001 01101
Hacemos XOR  : 01001 10101  // esto es parte de la semilla

Los coeficientes serán: x, y, z, t

Sabemos que

0100: x ^ 0 + y ^ 1 + z ^ 0 + t ^ 0 = 1 // con esto sabemos que y = 1
1001: x ^ 1 + y ^ 0 + z ^ 0 + t ^ 1 = 1 -> x + t = 1
0011 :x ^ 0 + y ^ 0 + z ^ 1 + t ^ 1 = 0 -> z + t = 0
0110 :x ^ 0 + y ^ 1 + z ^ 1 + t ^ 0 = 1 -> y + t = 1 -> 1 + t = 1 -> t = 0

x + t = 1 -> x + 0 = 1; x = 1
z + t = 0 -> z + 0 = 1; z = 0

La clave es 1100


Ahora seguimos adelante:

01001 10101
1100         // da un 1, lo que esperabamos

01001 10101
 1100        // da un 1, lo que esperabamos

01001 10101
  110 0      // da un 0, lo que esperabamos

01001 10101
   11 00    // da un 1, lo que esperabamos

01001 10101
    1 100    // da un 1, lo que esperabamos

01001 10101
	   1100    // da un 1, lo que esperabamos

// seguimos sacando la clave aplicando los coeficientes

01001 10101 1
	    1100   

01001 10101 11
	     110 0   

01001 10101 111
	      110 0  

01001 10101 1110
	       1 100  

01001 10101 1110 0
	         1100  

01001 10101 1110 00
	          110 0  

01001 10101 1110 001
	           11 00  

01001 10101 11100 010
	            11 00  

01001 10101 11100 0100
	             1 100  

01001 10101 11100 01001
	               1100


Cogemos hasta el periodo (vemos que se repite 0100 en el ultimo bloque)

Mensaje cifrado: 10000 00101 01000 11000 11001 00111
clave:           10101 11100 01001 10101 11100 01001
					  00101 11001 00001 01101 00101 01110

El mensaje es: 5 25 1 13 5 14

El mensaje es: EXAMEN
