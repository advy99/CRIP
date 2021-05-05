# Tema 3: Cifrado por bloques

Algunos cifrados por bloques también permiten cifrado en flujo

De los más famosos son DES y AES

## 14/04/2021

## Redes de Feistel

El mensaje se parte en bloques y se cifra.

La idea es que los bloques se cifren en conjunto, para si consiguen obtener un bloque, saber que ha sido comprometido.

Se basan en hacer un proceso de codificación de forma que la persona con la que te comunicas repita el proceso y obtenga el resultado. ( como el XOR, que si lo aplico dos veces obtengo el inicio)

La idea es que tanto el emisor como el receptor recorran la red de feistel para cifrar/descrifrar el mensaje

TExto --RED--> cifrado --RED--> Texto


La dureza de la red está en la f (funcion de cada paso) (mirar diapositivas para ver como es la red)

En cada ronda se aplica la funcion. Cuantas mas rondas tenga el sistema, mas seguro, pero más lento

Paso por ejemplo con DES, DES original funcionaba, pero cuando se consiguo romper salio triple DES con mas rondas.

El mensaje se parte en L0 y R0,

Cifrado:

L1 = R0 / R1 = L0 XOR f(R0, K1)
L2 = R1 / R2 = L1 XOR f(R1, K2)
...


La idea es que teno una K, que es una clave, para cifrar cada ronda, de forma que en cada ronda tengo una clave distinta. SI tengo 15 rondas, por ejemplo, hago expansion de llaves, y cifro con 15 claves distintas obtenidas a partir de K (es igual de seguro mandar 15 llaves, que mandar una y hacer expansion de llaves para la misma llave).


Se puede demostrar que puedo recuperar el mensaje original, si introduzco las claves K ordenadas del reves en la misma red


DES va de como hago las llaves

En el ultimo paso no se hace el inteercambio, no merece la pena


## Modos de operacion

Depende de para que usemos el cifrado por bloques tenemos que hacer los bloques

### ECB

Sistema mas simple de cifrado por bloques

Si tu mensaje no tiene la longitud de un múltiplo del tamaño de los bloques (quedan bloques vacios o inacabados), se hace un padding, se introducen ceros, bloques originales, etc, para rellenar

Esto es lo peor que se puede hacer, la idea es utilizar la salida de un bloque para el siguiete bloque, de forma que si hay un error, se amplifique

Este sistema se utiliza para sistemas con poca potencia, en la que se busca rapidez

### CBC

Encademaniento de bloques cifrados

Utiliza un vector de inicializcionm y se utiliza la misma llave compartida( key, aunque luego internamente se utilicen otras)

Funciona :

Mensaje -> XOR con vector de inicializacion -> cifro con key -> la salida cifrada, es el vector de inicializacion para el siguiente bloque, y así voy cifrando bloques

Se desencripta al reves:

Mensaje cifrado -> Aplica la clave -> XOR con vector inicializacion original, y tenemos el texto

El vector d einicializacion del siguiente bloque es el mensaje cifrado del bloque anterior

### CFB

MIRAR DIBUJOS EN PDF

Bascamente como si estuviera haciendo cifrado en flujo,

COmienzo con un vecor de inicializacion, que encripto con la clave, le hago un XOR con el mensaje y eso es el mensaje cifrado

El siguietne bloque usa como vector de inicializacion el cifrado anterior

COmo diferencia, lo que se cifra con la clabe es el vector de inicializacion

### OFB

Igua que el anterior, pero el vector de inicializacion no es el texto cifrado, si no el vector de inicializacion anterior cifrado con la clave (sin hacer el XOR con el texto plano)

Se decodifica igual

### CRT

Es como el ECB, pero en lugar de meter el texto plano y dar la salida, se introduce basura con un contador, de forma que se puede hacer en paralelo


## AES

AES surgio a partir de un concurso de protocolos de cifrado.

IBM contaba con Lucifer, aunque la NSA  le propuso un cambio: una llave más pequeña y una S-caja más fuerte, este alforitmos sería el Data Encryption Standard (DES).

DES se basaba en una red de feistel, y "reino" durante 20 años.


COnfusion de datos

Difusion de la confusión

El secreto esta solo en la llave: todo el mundo conoce el protocolo


### Idea

Dividir el mensaje en bloques para tener una matriz (si el mensaje no rellena la matriz, hacer padding, por ejemplo, ceros + al final el numero de bloques)

Cada bloque será de 4x4 bytes, es decir, 16 bytes

Primer paso: hacer XOR del bloque con la llave

XOR porque es facil, rápido, y no necesita acarreos.

Para cada ronda utilizaras una clave distinta.

Para crear la llave de cada ronda se utiliza expansion de llaves, de cara a generar nuevas llaves.

### Expansion de llaves

COgo la ultima columna de la matriz 4x4 de la llave, y aplico la operacion triangulo (la veremos más adelante), y hago un XOR con la constante de ronda, y luego un XOR con la primera columna de la llave anterior. Esto me dará la nueva primera columna. El resto de columnas es simplemente la columna actual de la ronda anterior XOR la columna anterior.


### Las rondas

Cada ronda tiene sus pasos

#### Confusion

Operacion triangulo que aplicamos byte a byte, a cada elemento de la matriz

#### Difusión

Permutaciones ciclicas de las filas segunda, tercera y cuarta fila, y una, dos y tress veces respectivamente

Permutaciones de las columnas, con una transformación lineal (con inversa)

#### Añadimos la llave

Al resultado le hacemos un XOR con la llave de ronda.

En la ultima ronda no hace falta la difusión, ya que es una operacion inversible.

### Seguradad vs eficiencia

Si añadimos mas rondas, es mas lento, y menos rondas es mas rápido

Normalmente se utilizan

Tam clave:

128 bytes -> 10 (9 con las intermedias)
192 bytes -> 12 (11 con las intermedias)
256 bytes -> 13 (12 con las intermedias)

(la ultima ronda sin la difución)


### Decodificacion:

Todas las operaciones tienen inversos, incluidas las llaves de ronda.


### ADVERTENCIA

No usas modo de operacion que no utilice la clave anterior en la siguiente ronda

### Ultimo detalle de algebra:

Utilizaremos un polinomio de grado 8 irreducible(para que tenga inverso)

AES usa : x^8 + x^4 + x^3 + x + 1

Todo polinomio menor que 8 va a tener inverso en un cuerpo de este polinomio

Uso una lista, en la que pongo (x+1)^pos . Basicamente relleno la tabla de forma que tenga todos los elementos (254 posiciones) se repetirá, y utilizando logaritmos busco el indice de un elemento en la tabla, para no tener que calcularlo, buscamos los bytes en la tabla. AES tiene una lista de 255 bytes que me sirve para saber el logaritmo en base x+1 de cualquier bytes. Para multiplicar dos bytes , me voy  a la tabla, sumo indices, y hago modulo tamaño de la tabla. Dividir (calcular inversos) es 255 - indice que ocupa.

### La operacion triangulo

Aplicas f(g(a))

g(a) = a^-1

y luego f(a)

f(a) es una transofrmacion afin en Z_2 ^ 8, que tiene inverso.

La clave de ronda es multiplicar por x la columna anterior.

El mezclado de columnas , si tenemos una columna de 4, lo podemos representar como un polinomio de grado 3 (o menor). Podemos multiplicar por una constante, y hacer mod x^4 + 1.

En resumen, multiplicar por una matriz 4x4: (MIRAR DIAPOSITIVAS)

2 1 1 3
3 2 1 1
1 3 2 1
1 1 3 2
