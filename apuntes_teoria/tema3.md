# Tema 2: Cifrado por bloques

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
