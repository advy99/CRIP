# Tema 2: Cifrado en flujo

## 24/04/21

Ejemplo:

Mensaje  1011
Llave    1010

XOR     ------

Cifrado: 0001


Como se descrifra:

Cifrado  0001
llave    1010

XOR ----------

Mensaje  1011


Es imposible usar llaves de un solo uso, y encima aleatorioas.

Lo que haremos será generar una llave pseudoaleatoria

Antes de eso:

## Dos modos de operacion

### Sincrono

Comunicacion sencilla:

Tenemos un generador de llaves, que cuando entra un mensaje, se cifra con dicha llave.

De descodifica con la llave, al generador le entra el mensaje cifrado y saca el mensaje descrifrado.

Basicamente, misma llave de cifrado/descrifrado

### Asincrono

Un generador de clave da un bit de clave, a cada entrada da una salida, y además la salida se usa para generar la llave

Se descodifica dando la entrada cifrada al generador, para que así descifra el mensaje.

Tambien se llama autosincronizante, porque la llave al estar en el mensaje se auto sincroniza los generadores de clave

Como ventaja es que no es necesario que ambos generadores esten en el mismo estado para descrifrar, como en el simetrico

Mirar apuntes de miranda pagina 68 (tabla con primera columna i, y la primera fila, i, c(1), ..., c(4), k_i, m_i, c_i)


## Como generamos secuencias de bits "aleatorias"? y que entendemos por "aleatorias"?

Seccion secuencias pseudoaleatorias en los apuntes de Jesus Garcia Miranda

Golomb propuso unos postulados para comprobar lo "aleatorio" que es una secuencia

Son los siguientes:

- |numero de unos - numero de ceros| <= 1 (mismo numero de 0s y 1s a no ser que sea impar)
- numero de rachas de longitud n es el doble que las de longitud (n + 1) (siempre que sea posible, te puedes encontrar que te encuentres que no te coja la longitud del mensaje otra racha mas, ej, 4 rachas de 1, 2 rachas de 2, 1 de 3, 1 de 1)

Una racha sería

b_i b_{i+1} ... b_{i + j} b_{i + j + 1}

b_i = b_{i + j} != b_{i + k}
b_{i + 1} = .... = b_{ i + j}


EN UN PERIODO (es decir, es circular)

Ej: 00110 -> 11 es una racha de 2, 00 y el ultimo 0 hacen una racha de 3


Rachass de ceros los llamaremos huecos (gaps)
Rachas de unos los llamaremos bloques


Ademas, el numero de bloques de longitud n tiene que ser igual que el numero de huecos de longitud n, o que se diferencien en 1. Esta condicion ya la implica el primer postulado

- Correlación constante, equivalente a distancia de Hamming (n. bits distintos) constante por desplazamientos circulares.

Ej.
00110, desplazo circualarmente a la derecha
00011, este con el original ,distancia 2
10001, distancia con el original de 4
....
llegare a un punto que sera el mismo de arriba

Este caso no lo cumpliría, ni este ni el 2o postulado

IDEA PARA IMPLEMETAR: Para hacer el tercer postulado, hacer desplazamiento con rotaciones y con XOR mirar peso hamming del resultado


## 07/04/2021

## Generadores de secuencias aleatorias

### Aritmetica modular

x_0 semilla, x_{i + 1} \cong a \cdot x_i + b (mod c)

No son apropiadas para cifrado en flujo

Vamos a utilizar una mezcla de dos cosas


## FSR (registros de desplazamiento con retroalimentación)

Vamos a usar un registro con un estado, y al aplicar una funcion nos generará el siguiente bit

```
---f(c1,  c2, ..., c_L) ->--
      |	|         |     |
      |	|         |     |
-<--c_1, c_2, ..., c_L--<--
```

Esta funcion f es una serie de operaciones con los c, por ejemplo puede ser, con L = 4:

((c_1 AND c_2) OR (NOT c_3)) XOR c_4


|Lógica  |  Z_2 |
|--------|------|
|a AND b |  a * b|
|a XOR   |  a + b|
|NOT a   |  1 + a|
|a OR b  |  a + b + a * b|


Las operaciones como los productos, no son lineales, así que los FSR que utilizan estas operaciones los llamaremos NLFSR.

Vamos a hacer un ejemplo con el anterior.

((c_1 AND c_2) OR (NOT c_3)) XOR c_4


Es equivalente a :

1 + c_3 + c_4 + c_1 \cdot c_2 \cdot c_3

La semilla será de la forma: c_1 c_2 c_3 c_4 para producir c_5

Vamos a empezar con : 1001

c_5 = 1 + 0 + 1 + 0 = 1 + 1 = 0

el resultado sería 10010

Ahora, para la siguiente, la semilla sería 0010

c_6 = 1 + 1 + 0 + 0 = 0

El resultado sería 100100 (la nueva semilla es 0100)

c_7 =  1 +  0 + 0 + 0 = 1

El resultado: 1001001

si nos damos cuenta, los ultimos 4 bits son el estado inicial, luego se repite, ademas con periodo corto, el periodo es 3

Lo ideal sería:

- Dada una semilla de longitud L acercarme a periodo 2^{L} (periodo máximo)
- Que la salida cumpla los postulados de Golomb
- Que el periodo no dependa de la semilla

## LFSR (FSR lineales)

f(c_1, ..., c_L) = a_L \cdot c_1 + ... + a_1 \cdot c_L \ a_i \in Z_2
una aplicación lineal

Ejemplo

f(c_1, c_2, c_3, c_4) = c_1 + c_4

Semilla: 1001 (siempre no nula, si no sería todo 0)

La secuancia sería: 1001, 10010, 100100, 1001000, 10010001, ..., 100100011110101|1001 (marca con } donde se repite)

Vemos como tenemos un periodo de 15, que = 2^{4} - 1 (le quitamos la semilla nula, 0), es el máximo posible

Si nos damos cuenta, cualquier semilla de longitud 4 va a estar en el ejemplo anterior, porque es de periodo máximo


f LFSR se le asocia un polinomio **(de conexión)**

En este caso el polinomio seríá:

p_{f}(x) = 1 + a_1 \cdot x + ... + a_L \cdot x^{L}   | en algunos libros a_L + a_{L-1} \cdot x + ... + a_1 \cdot x^{L - 1} + x^{L} = x^L \cdot p_{L}(1/x)

Si tengo mi secuencia s_0, s_1, ..., s_n, ...  con la semilla de s_0 ... s_{L-1}

s_L = a_L \cdot s_0 + a_{L-1} \cdot s_1 + ... + a_1 \cdot s_{L-1}

s_{L + K} = a_L \cdot s_K + a_{L-1} \cdot S_{k + 1} + ... + a_1 \cdot s_{L + K - 1}


Si tengo una matriz

0 1 0 ... 0   |  s_0
0 0 1 ... 0   |  .
...........   |  .
c_L ..... c_1 | s_{L-1}

Si las multiplico tengo

S_1
.
.
S_L

Si lo multiplicamos,

p_{F}(x) = det(x M - Id)
Polinomio característico: det(M - x ID)

La relacion es que el polinomio caracteristico es el simetrico (el simetrico que aparece en algunos libros)

Ejemplo para

f(c_1, c_2, c_3, c_4) = c_1 + c_4

p_{f}(x) = 1 + x + x^4

Z_2[x]_{p_{f}(x)}

<x> = <1, x, x^2, x^3, 1 + x (x^4), x+x^2 (x^5), x^2 + x^3 (x^6), 1 + x + x^3 (x^7), ....> Sabemos que estan todos por el orden:

ord(x) | 15 = 2^4 - 1, así que tiene que ser un numero que divida a 15, y tenemos como minimo 7, así que estan todos

Este polinomio es primitivo, por lo que el orden es el más grande posible, e independiente de la semilla


Ejemplo:

x^3 + x + 1

Para sacar la f, escribimos el polinomio en la ultima fila de la matriz, de mayor a menor orden, eso multiplicado por la matriz columna de c.

f = (1 1 1 0) * (c_1 c_2 c_3 c_4)

s_1 = 0001
f = c_2 + c_3


s_1
----
   s_7
  ----
0001110
 ----
  s_3

Vemos como pasamos de s_1 (0001) -> s_3(0011) -> s_7(0111) -> s_14 (1110), como en las diapositivas

MIRAR EN LAS DIAPOSITIVAS

f() = c_1 + c_2 + c_3
s_10 = 1010

101001


Si el polinomio no es primitivo, tendrá varios ciclos, si es primitivo, solo un ciclo de periodo máximo (independientemente de la semilla, como hemos visto antes)

Al ser lineal, es muy facil romer un LFSR.

Si yo conozco 2L trozos de una secuencia, la puedo romper, planteando un sistema de L ecuaciones con L incognitas (MIRAR PDF PRADO)



Ejemplo:

10010001  -> 2L = 8, L = 4

La semilla es 1001

// uso x y z t , en lugar de a_4, a_3, a_2, a_1

s_4 = 0 = x \cdot s_0 + y \cdot s_1 +  z \cdot s_2 + t \cdot s_3 = x + t -> x + t = 0
s_5 = 0 = x \cdot s_1 + y \cdot s_2 +  z \cdot s_3 + t \cdot s_4 = z -> z = 0
s_6 = 0 = x \cdot s_2 + y \cdot s_3 +  z \cdot s_4 + t \cdot s_5 = y -> y = 0
s_7 = 1 = x \cdot s_3 + y \cdot s_4 +  z \cdot s_5 + t \cdot s_6 = x -> x = 1


sabemos que z = 0, y = 0, x = 1, y con x + t = 0, t = 1

Sabemos que f(c_1, c_2, c_3, c_4) = c_1 + c_4 (x y t)
luego p_{f}(x) = x^4 + x + 1
FIN

Si p_{f}(x) es primitivo, entonces la secuencia generada (2^L - 1) cumple los postulados de Golomb

MIRAR TABLA DE LONGITUD DE RACHA EN APUNTES DE JESUS MIRANDA

## 08/04/2021

NLFSR podría ser algo así c_{1}^5 \cdot c_2 + c_3 \cdot c_4^2 + 1 = p

En Z_2 :

x^2 \equiv x
2x = 0

p \equiv p' = c_1 c_2 + c_3 c_4 + 1
p != p'

Todo NLFSR se expresa como la suma de monomios en los que la variable esta elevada a 0 o 1

p'(c_1, c_2, c_3, c_4) = c_1 \cdot c_2 + c_3 \cdot c_4 = [[1, 1, 0, 0], [0, 0, 1, 0]]

Podemos codificar el polinomio en una lista de exponentes

Tenemos que tener en cuenta que al estar en Z_2:
0^0 = 2^0 = 1

Ejemplo:

p'(0, 1, 0 ,1 ) = 0^1 1^1 0^0 1^0 + 0^0 1^0 0^1 1^1

Para representar 1 como la lista, sería todo ceros, por ejemplo [0, 0, 0, 0]


## 14/04/2021

Repaso LFSR : La matriz,  las filas son la semilla desplazada, y la ultima los coeficientes del polinomio

Si el polinomio es irreducible pero no primitivo, varios ciclos de mismo longitud

Si es primitivo longitud de periodo máxima



## Algotitmo de Berlekamp-Massey

L es el tamaño del LFSR

La coplejidad del LFSR es k si tenemos un LFSR de tamaño k que reproduce toda la secuencia.

Complejidad lineal: minimo L que reproduce la secuencia


COn este algoritmo se buscaba resolver un problema del estilo

a(x) X \equiv b(x) mod c(x)

donde X es la incognita, para codigos correctores de secuencas para mandar mensajes con basura

Dio con un algoritmo de complejidad O(n^2), y se dieron cuenta de que tambien servia para codificar

Se dieron cuenta de que tambien vale para LFSR, los problemas eran equivalentes

El algoritmo consiste en:

```
Entrada : secuencia s
	Para i desde 1 hasta l ( longitud de s)
		Simula un LFSR hasta el simbolo i-esisimo. Denota esta secuenca con s'
		En caso contrario, corrijase el LFSR si no coincide con la correspondencia de s
```

La idea es suponer que el LFSR actual funciona para s, calculo el supuesto siguiente valor, y si hay una discrepacia (bit generado es distinto al bit de la secuencia real), la almaceno, la sumo, cambiando el LFSR

La complejidad cuando encuentro una discrepancia, la nueva complejidad (el nuevo LFSR), es el maximo entre la complejidad anterior y  n + 1 - la complejidad anterior.

La salida es el unico posible LFSR más pequeño capaz de reconstruir la secuencia. En caso de que no exista LFSR, devuelve uno de ellos

MIRAR ALGORITMO EN LOS PDF Y EN EL HANDBOOK

## Combinaciones de LFSR para evitar que rompan un mensaje


### Suma de secuencias

La complejidad lineal es <= que la suma de las complejidades

Periodo : m.c.m de los periodos


### Producto de secuencias

Periodo y complejidad igual que en el caso de la suma

### Función no lineal

#### Ejemplo: Generador de Geffe: famoso por lo malo que era

#### Otro ejemplo GSM A5/1: Se sigue usando, aunque se puede romper.

Utiliza tres LFSR, cada LFSR avanza si su bit de mayoria (marcados en naranja en las diapositivas) coincide con la mayoría. Cada LFSR tiene asociado un polinomio primitivo asociado, y se hace un xor con la salida.

Ejemplo del bit de mayoría: Si tengo en dos de ellos un 1 y en el otro un 0, solo avanzan los LFSR de los que tienen 1. Esto se utiliza para dificultar el romperlo, aunque no evita que se vea comprometido.


#### RC4

Se utiliza actualmente en TLS, WPA y otros, aunque se esta empezando a dejar de usar por sus problemas

TIene una caja con una serie de bits, y con operaciones modulares de sus bits, obtener un nuevo bit. Las cajas se llaman s-cajas. Van de  0 a 255 bits, con una llave, de forma que cuando iniciaas la caja se inicia la comunicación y con eso se crifra la conexión.

Ejemplo:

```
for i in 0..255:
	S[i] = i

j = 0
for i in 0..255
	j = (j + S[i] + K[i mod keylength]) mod 256
	intercambia S[i] and S[j]
```

de esta forma, se baraja la caja para dificultar romperla

Una vez hecho esto

```
i = i + 1 mod 256
j = j + S[i] mod 256
intercambia S[i] y S[j]
t = (S[i] + S[j]) mod 256
Devolver S[t]
```
