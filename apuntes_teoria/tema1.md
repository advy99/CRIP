# Tema 1 - Introducción y revisión histórica.


## Repaso ALEM - 24/02/2021

Repasar capítulo 2 (en especial para el tema 1) y capítulo 3 (en especial para cifrado en flujo)

$a, b \in Z$, d un máximo común divisor de a y b

- $d | a$ y $d | b$ (d divide a a y d divide a b)
- Si c \in Z con c | a y c | b, entonces c | d

a | b si existe c con b = a \cdot c

Ej: mcd (6, 10) = 2

Podemos restar el más grande al más pequeño manteniendo el mcd (algoritmo de Euclides):
mcd (6, 10) = mcd(10, 6) = mcd(4, 6) = mcd (6, 4) = mcd(2, 4) =  mcd(4, 2) = mcd(0, 2) = 2

Este algoritmo tiene complejidad (log_2(max(a, b)))


Identidad de Bezout

d = mcd (a, b) existen u, v \in Z tal qued = u \cdot a + v \cdot b

Si a y b son primos relativos, 1 = u \cdot a + v \cdot b entonces trabajamos en Z_b (restos de dividir por b = {0, 1, ..., b - 1})

n \cong  m mod b si b | n - m

Si estamos en Z_b, 1 = u \cdot a + v \cdot b  =  u \cdot a + 0 -> 1 = u cdot a -> u = a^-1


## 03/03/2021

u \in N\{0}  	Z_N = Z/n = {0, 1, ..., n-1}


En Z_n, n + 1 = 1

a \in Z_n y a != 0, a tiene inversi sii mcd(a,n) = 1

Uso identidad de Bezout, 1 = u a + v n = 1 = u a + 0 -> a^-1 = u

U(Z_n) = {a \in Z_n\{0} | mod (a,n ) = 1}

| U(Z_n) | = \phi(n) funcion cociente de Euler

p es primo -> \phi(p) = p - 1 (todos son primos relativos de p, si p es primo, ya que no tiene multiplos en comun)

Z_p es un cuerpo


\phi(p^n) = p^n - p^{n-1}      si a \in Z_{p^n}  -> mcd(a, p^n) = 1 o p^{algo}

Si m y n son primos relativos \phi(n m) = \phi(n) \phi(m)

Esto sucede por el teorema chino de los restos:

Si mcd(m,n) = 1

Z_{m n} -> Z_n x Z_m         biyectiva (inyectiva y sobreyectiva)
a -> (a mod n, a mod m)      isomorfismo (soporta suma y producto)

U(Z_{m n}) = U(Z_n) x U(Z_m) -> \phi(m n) = \phi(n) \phi(m)


El sistema

x \cong a mod n
x \cong b mod m

tiene solucion única modulo n \cdot m


Ejemplo:

Z_6 -> Z_2 x Z_3
n -> (n mod 2, n mod 3)

f(0) = (0, 0)
f(1) = (1, 1)
f(2) = (0, 2)
f(3) = (1, 0)
f(4) = (0, 1)
f(5) = (1, 2)

Tanto en Z_6 como en Z_2 x Z_3 hay 6 elementos


Quiero saber f^{-1}(1, 2):

x \cong 1 mod 2
x \cong 2 mod 3

De la primera ecuación -> x = 1 + 2 <algo>
De la segunda ecuacion -> 1 + 2 algo \cong 2 mod 3

Si nos ponemos mod 3

1 + 2 algo = 2, 2 algo = 1

algo = 2^{-1} \cdot 1 = 2


Si Z normal

algo = 2 + 3 otracosa

De la primera ecuación -> x = 1 + 2 (2 + 3 \cdot otracosa) = 1 + 3 + 6otracosa


x = 5 + 6 \cdot otracosa

Si nos fijamos, f(5) = (1,2), y obtenemos que x = 5 + 6 \cdot otracosa, es decir, es 5 + un multiplo de 6

\phi(6) = \phi(2) \phi(3) = 1 \cdot 2 = 2 -> U(Z_6) = {1,  5} = {1, -1}


<m> es el grupo de m

m \in Z_n\{0}     <m> = {m^n | n \in N}  Si m y n son primos relativos podemos utilizar Z

Cogemos exponenetes hasta que se repita la secuencia (encontramos un 1)

1 -> 1^2 = 1 FIN en Z_6  <1> = {1}

-1 -> (-1)^0, (-1)^1, (-1)^2 = 1		FIN <-1> = {1, -1}


U(Z_n) grupo con el producto

Si a, b = U(Z_n), (a \cdot b)^-1 = b^-1 \cdot a^-1

a^0 = 1, a, a^2, ..., a^k, ..., a^n    si a^k = a^n, como k < n, k + l = n

a^k = a^n = a ^{k + l} = a^k + a^l, cancelamos los a^k (estamos en un grupo), entonces
1 = a^l


Ejemplo

Z_5

<2> = {1, 2, 4, 3}
<2> = {2^0, 2^1, 2^2, 2^3} <- 2^4 ya es 1 y se repite

2^4 = 1 = 2 * 2 ^3 = 2 *3 -> 2^{-1} = 3

2^{-2} = 2 \cdot 2^{-2} = 2^4 \cdot 2^{-2} = 2^{4-2} = 2^2 = 4

2^k = 2^{k mod 4} -> 2^k = 2^{4 \cdot c + r} = (2^n)^c \cdot 2^r = 2^r


<3> = {1, 3, 4, 2} -> 3^4 = 1
<4> = <-1> = {1, -1} -> 4^2 = 1; 4^4 = 1^2 = 1
1^4 = 1

En general a \in Z_p con a != 0 (unidad)

f: Z_p -> Z_p
   x   -> a \cdot x

es inyectiva?

f(x) = f(y) x = y?

entonces

a\ctot x = a \cdot y

si multiplicamos por a^-1

x = y

f^-1(y) = a^-1 \cdot y = f(a^-1 y) = a(a^-1 y) = y -> sobreyectiva

\mul_{x\in Z_p con x!=0} {x} = \mul_{x \in Z_p} {a x} = a ^ {p -1} \mul_{x \in X_p} {x}

1 = a^(p-1)

Teorema pequeño de Fermat

Si p es primo, si estamos en mod p, a^{p - 1} = 1 si a != 0


Euler:

\mul_{x\in U(Z_m)} {x} = \mul_{x\in U(Z_m)} { a x} = a ^{U(m)} \cdot \mul_{x\in U(Z_m)}


En mod m ->

1 = a^{\phi(m)} si a \in U(Z_m) (mcd(a, m) = 1)


Gracias a esto existe RSA



### Test de Miller-Rabin (test de primalidad)

Este test tiene una tasa de acierto del 75%, cada ejecucion del test es independiente, si se ejecuta multiples veces y las pasa todas, la probabilidad de que sea primo es muy alta

Ideas:
- Z_p si p es primo es un cuerpo -> x^2 - 1 = 0 tiene dos raices (1, -1)
- Si a != 0 -> a^{p-1} = 1 en Z_p

Si p es par y distinto de 2, hemos terminado: p no es primo

Este test no funciona para primos por debajo de 5

p - 1 = 2 ^ n \cdot s con s impar (en binario, el bit menos significativo es 0)

a aleatorio (base o semilla) con a != 0

{a ^ s, (a^s)^2 = a^{2 s} = (a^{2 s})^2 = ...., a^{2^m \cdot s} = a^{p-1} } = L

Caso a - Si 1 \not \in L, p no es primo
Caso b - Si 1 \in L, a^{2^k s} = 1 , a^{2^{k-1} s}^2 = a^{2^k s} = 1, entonces
- a^{2^{k-1} s} = -1   b.1
- a^{2^{k-1} s} != -1  b.2

SI b.1 -> Una vez encuentre un 1, podemos parar, ya que 1^2 sigue siendo 1, y siempre elevamos al cuadrado : probablemente primo por la segunda idea

Caso b.2 -> Si en la posicion anterior es un -1, x != -1, con x^2 = 1 -> x^2 = 0 en Z_p

(x-1)(x+1) = 0 en Z_p, y ademas (x-1) != 0 y x+1 != 0 entonces (x-1)(x+1) = algo \cdot p

p NO es primo por la primera idea

mcd(x-1, p) | p -> divisor propio de p
mcd(x+1, p) | p



Millen y Rabin: posiblemente primo -> error < 1/4

Tomando 10 a distintos, error de 1/4^10 muy pequeño


Ejemplo:

p = 21

p - 1 = 20 = 2^2 \cdot 5
a = 6 (aleatorio)

6^5 en Z_21 = 6, 6^2 = 15,      6^4 = 15^2 = 15
6^5              6^{2 \cdot 5}  6^{2^2 \cdot 5} = 6 ^ {p-1}

L = {6, 15, 15} \not \int 1 -> 21 no es primo



Ejemplo:

p = 41

p - 1 = 40 = 2^3 \cdot 5
a = 6 (aleatorio)

6^5 en Z_41 = 27, 6^{2 \cdot 5}  = 27^2 = 32,      6^{2^2 \cdot 5} = 32^2 = 40 = -1 FIN

41 es probablemente primo


si a = 21

21 ^ 5 = 9, 21^{2 \cdot 5} = 9^2 = -1 FIN

41 es posiblemente primo



Ejemplo:

p = 33

p - 1 = 32 = 2^5 \cdot 1 -> s = 1

a = 7

7^1 en Z_33 = 7, 7^2 = 16, 7^{2^2 \cdot 1} = 16^2 =  25, 7^{2^3} = 25^2 = 31, 7^{2^4} = 31^2 = 4   -> FIN, como no ha salido un -1, el siguiente no puede salir 1, entonces no es primo, no hace falta calcular el siguiente de la lista

Si lo hacemos: 7^{2^5} = 4^2 = 16 != 1 NO ES PRIMO

Si encuentras un ciclo, como siempre encuentro un cuadrado, podemos parar




LOGARITMO DISCRETO

a \in Z_n    a^b = c, dado c, como calculo b?

b = log_a(c)

n = p primo


Paso enano, paso gigante

Tomamos un s tal que s^2 >= p-1
Supongamos que tal b existe, a^b = c
b = t \cdot s - r      

b <= p-1 eso me dice:
- 1 <= t <= s
- 0 <= r <= s - 1


a^b = c -> a^{t \cdot s - r} = c -> a^{t \cdot s} \cdot a^{-r} = c

a^{t \cdot s} = c \cdot a^r:
- {a^{1 s}, a^{2 s} , ..., a^{s s} } = L
- {c a^0, ...., c a^{s-1}} = l


Si L interseccion l == 0, no existe el log_a(c)


Ejemplo:

Z_11, log_7(2)

b tal que 7^b = 2?

sqrt(10) = 4 = s

L = {7^{t \cdot 4}} = {3, 9, 5,4 } 1 <= t <= 4

l = {2 \cdot 7^r} = { 2, 3, 10, 4}, 0 <= r <= 3

Como coinciden el 3, t = 1, r = 1,

b = t \cdot s - r = 1 \cdot 4 - 2 = 2


7^3 = 2 en Z_11

Comprobacion 7^2 = 49 = 5, 7*5 = 7^3 = 35 = 2


## 04/03/2021

Idea:

a \cdot b = b    y existe a^-1 -> a^{-1} \cdot a \cdot b = a^{-1} \cdot 0 = 0 -> b = 0

Si pasa esto, tiene más de dos raices, entonces no es un cuerto, ejemplo

En Z_8:

x^2 - 1 = 0

f(x) = x^2 - 1

f(0) = 7
f(1) = 0 -> f(-1) = f(7) = 0
f(2) = 3
f(3) = 0 -> f(-3) = f(5) = 0

Tenemos más de dos raices, luego Z_8 no es un cuerpo

se tambien que

3^2 = 1 -> 3^2 - 1 = 0 = (3 - 1) ( 3 + 1) = 4 * 2


Luego mcd(2, 8) | 8
      mcd(4, 8) | 8

		8 = 2 * 4


Con 5, que es la otra raiz

5 ^ 2 - 1 = 0 = (5 - 1) (5 + 1) = 4 * 6 = 0

mcd(4, 8) | 8
mcd(6, 8) | 8

8 = 2 * 4


Solucion generica, repaso Teorema chino de los restos:

x \cong a mod n
x \cong b mod m

tal que mcd(n, m) = 1 (son primos relativos)

x = a + k \cdot n
a + k \cdot n \cong b mod m   -> k \cdot n \cong b - a mod m

Como mcd(n, m) = 1, existe n^{-1} mod m

k = n^{-1}(b - a) mod m

k = n^{-1} (b - 1) + l \cdo m

Sustituimos arriba:

x = a + (n^{-1} (b - a) + l \cdot m) \cdot n = a + n^{-1} (b - a) \cdot n + l \cdot m \cdot n

Siendo a + n^{-1} (b - a) \cdot n  -> la solucion particular (doy "vueltas" en el anillo con +  l \cdot m \cdot n )


Comprobación:

En Z_n

x = a + 0 + 0 = a
x = a + n^{-1}(b - a) \cdot n + 0 = a + n^{-1} \cdot n (b-a) = a + b - a = b






### Exponenciación modular:

Objetivo: calcular a^n mod m

Ideas: escribir n en "binario" (base 2)  -> n = \sum {b_i \cdot 2^i}

Trabajaremos en Z_m

a^n = a^{\sum{b_i \cdot 2^i}} = \mul {a^{b_i \cdot 2^i}} = \mul{a^{2^i}}^b_i

p = 1
a -> a^2 -> a^{2^2} ->... a^{2^i}

Para cada uno, si b_i = 0, no hago nada, si b_i = 1 actualizo p = p * a^{2^i} mod m


## 10/03/2021

### Calculo de raices cuadradas (módulo p primo)

a \in Z_p (o grupo finito)

<a> = {a^k / k > 0} <= grupo generado por a en Z_p^* (Z_p sin el 0)

Existe un k con a^k = 1 en Z_p

Definimos el orden:

ord(a) = min(k > 0 / a^k = 1) // cuando se repite

Si a^k = 1, entonces ord(a) | k

Demostracion

k = c \cdot ord(c \cdot a) + r -> 0 <= r <= ord(a)

a^r = a^{k - c \cdot ord{a}} = a^k \cdot (a^{ord(a)})^{-c} = 1

a^k = 1 y (a^{ord(a)})^{-c} = -1, no puede ser -1
a la fuerza r = 0 y ord(a) | k
FIN DE LA SEMOSTRACION

Ningun divisor del orden va a ser 1:
ord(a) = k si y solo si a^d != 1 para d | k y a^k = 1

Si ord(a) = p - 1 , <a> = Z_p*
a se dice que es primitivo o un generador de Z_p*

Existen \phi(p-1)

Problema: Dado un a \in Z_p , existe b tal que b^2 = a ?

Z_5 = {0, 1, 2, 3, 4, 5} -^2-> Z_5

0 ->0
1 -> 1
2 -> 4
3 -> 4
4 -> 1

2 no tiene raiz cuadrada en Z_5

Si existe ese b, diremos que a es un \textbg{residuo cuadrático}

a sobre p (\frac{a}{p}) =

- 0 si p | a (a = 0 en Z_p)
- 1 si a es residuo cuadratico
- -1 si no lo es

2 sobre 5 (\frac{2}{5}) = -1
4 sobre 5 (\frac{4}{5}) = -1

#### Criterio de Euler

Si a != 0 en Z_p

a sobre p = a^{\frac{p - 1}{2}} mod p

Observación, p - 1 es par ( p != 2)

por fermat -> a^{p - 1} = 1 -> (a^{\frac{p - 1}{2}})^2 = a^{p - 1} = 1

a^{\frac{p - 1}{2}} es una raiz cuadrada de 1:
- 1
- -1

Tengo que probar que (\frac{a}{p}) = 1 si y solo si a^{\frac{p - 1}{2}} \cong 1 mod p

Necesidad (esto es cierto): \fract{a}{p} = 1 , ¿a^{\frac{p - 1}{2}} \cong 1 mod p?

Existe b con b^2 = a

a^{\frac{p - 1}{2}} = (b^2)^{\fract{p - 1}{2}} = b^{p - 1} = 1 // este ultimo igual por fermat

Suficiencia: Sea \alpha primitivo:

<\alpha> = Z_p* , a \in Z_p* , Existe i con \alpha^i = a // conocer el i es paso enano paso giganta

a^{\frac{p - 1}{2}} = 1 ( hipotesis) -> (\alpha^i)^{\fract{p - 1}{2} \cdot i} = 1
ord(a) = p - 1 -> p - 1 | \fract{p - 1}{2} \cdot i
(p - 1) \cdot k = \fract{p - 1}{2} \cdot i  -> (p - 1) \cdot i = 2 \cdot k \cdot (p - 1)

i = 2 \cdot k

\alpha^{2 b} = \alpha^i = a -> \alpha^k = b
||
(\alpha^k)^2

FIN DEMOSTRACION (y constructivo, aunque no util en la práctica, paso enano paso gigante demasiado lento)


#### Alternativa "rapida"

Dado a \in Z_p a != 0, \frac{a}{p} (a sobre p) = 1, ¿b, b^2 = a?

Truco y retruco
Tomo n aleatorio tal que, n sobre p (\frac{n}{p}) = -1, este n se escoge de forma aleatoria, tiene probabilidad 1/2 de que pase

Escribimos p - 1 = 2^{u} \cdot s // s impar
r = a^{\frac{s + 1}{2}}; r^2 = a^s \cdot a -> a^{-1} \cdot r^2 = a^s

(a^{-1} \cdot r^2)^{2^{u - 1}} = (a^s)^{2^{u - 1}} = a^{2^{u - 1} \cdot s} = a^{\fract{p - 1}{2}} = 1 = a sobre p (\frac{a}{p})

a^{-1} \cdot r^2 es solucion de x^{2^{u-1}} - 1 = 0

Idea: buscar todas las soluciones de x^{2^{u-1}} - 1 = 0

Ayuda: b = n^s (n era \fract{n}{p} = -1)

b^{2^u} = u^{s \cdot 2^u} = n^{p - 1} = 1 (Fermat)
b^{2^{n - 1}} = n^{\fract{n - 1}{2}} = -1 (criterio de euler)

Con estas dos: b solucion de x^{2^{u-1}} - 1 = 0

B = {1, b, b^2, ..., b^k, ..., b^{2^u - 1}, ..} =>  b^k != 1, k < s^u <===== *1

b^{k^{2^u}} = (b^{2^u})^k = 1^k = 1


*1 aqui estan todas las soluciones de x^{2^{u}} - 1 = 0

Retruco:

<i> todas las raices 4 = 2^2

i^2 = -1  => <-1> todas las raices 2 = 2^1

Tomo b^2:
B^2 = {1, b^2, b^4, b^6, ..., b^{2^u - 4}, b^{2^u - 2}} <- todas las potencias pares del conjunto original B

Esto son todas las soluciones de x^{2^{u-1}} - 1 = 0


(b^{2 k})^{2^{u - 1}} = (b^{2^u})^k = 1^k = 1

a^{-1} r^2 \in B^2 => a^{-1} r^2 = b^{2k} para algun k

Despejando

a = r^2 b^{-2k} = (r b^{-k})^2  FIN

Salida: r b^-k

b^{2^u} = 1 -> b^{-1} = 1 b^{-k} = b^{2^u} b^{-k} = b^{2^u - k}


Para buscar el n rápido:

#### Propiedad del simbolo de Legendre

(\frac{a}{p}) ( a sobre p) = a^{\fract{p - 1}{2}} mod p

(\frac{a}{p}) (a sobre p) = \fract{a mod p}{p}

(\frac{a b}{p}) ( a b sobre p) = (\frac{a}{p}) (\frac{b}{p})

(\frac{a^2}{p}) = 1 si a != 0 en Z_p

(\frac{-1}{p}) = (-1)^{\fract{p - 1}{2}}:
	- 1 si p \cong 1 mod 4
	- -1 si p \cong 3 mod 4

(\frac{2}{p}) = (-1)^{\fract{p^2 - 1}{8}}:
	- 1 si p \cong +- 1 mod 8
	- -1 si p \cong +- 3 mod 8

Ley de reciprocidad cuadrática

(\frac{q}{p}) ( q sobre p) = (-1)^{\fract{(p - 1)(q - 1)}{4}} \cdot (\fract{p}{q}) // el ultimo es p sobre q

(\frac{q}{p}) ( q sobre p) = :
	- -(\frac{p}{q}) ( p sobre q) p = q \cong 3 mod 4
	- (\frac{p}{q}) ( p sobre q) En otro caso

Problema: y si p no es primo??

Jacobi dio la solución:

a sobre n = \mul{(\fract{a}{p_i})^{e_i}} si n = p_1^{e_i} ... p_k^{e_k}

Ejemplo:

19 sobre 31

A 19 no le puedo sacar potencia de dos, me fijo en la ultima ley

(\fract{19}{31}) = - (\fract{31}{19}) = - (\fract{12}{19}) = // al hacer modulo 19

= - (\fract{2^2 3}{19}) = - (\fract{2^2}{19}) (\fract{3}{19}) = ->  (\fract{2^2}{19}) = 1

= - (\fract{3}{19}) = - - (\fract{19}{3}) = (\fract{1}{3}) = 1

Luego existe b con b^2 = 19 en Z_31


Aleatoriamente  (\fract{11}{31}) = -1; n = 11; a = 19

r = a^{\fract{s + 1}{2}}
r = a^8 = 9
31 - 1 = 30 = 2 \cdot 15 ; u = 1; s = 15
b = n^s = 11^15 = -1 = 30
a^{-1} r^2 = 18 \cdot r^2 = 1

B^2 = {bla bla bla} NO LO HAGO ->
De aqui a^{-1} r^2 = 18 \cdot r^2 = 1

r^2 = a; devuelvo r = 9



## 11/03/21

### Raices módulo p * q

Si tengo
r, r^2 \cong a mod p
s, s^2 \cong a mod q

De estas dos puedo encontrar un

x \cong r mod p
x \cong s mod q

si lo resuelvo:

x^2 \cong r^2 \cong a mod p
x^2 \cong s^2 \cong a mod q

x mod p \cdot q

tambien vale el sistema con signos negativos, por ejemplo:

x \cong -r mod p
x \cong s mod q

o

x \cong r mod p
x \cong -s mod q

o

x \cong -r mod p
x \cong -s mod q


Son las soluciones cambiadas de signo


### Metodo de Newton-Raphson

x_{n+1} = x_n + \fract{f(x_n)}{f'(x_n)}

f(x) = x^2 - n
f'(x) = 2 x

x_{n+1} = x_n - \fract{x_{n}^2 - 1}{2 x_n} =
= \fract{2 x_{x}^2 - x_{n}^2 + n}{2 x_n} = \fract{x_{n}^2 + n}{2 x_n} = \fract{x_n + \fract{n}{x_n}}{2}

## 17/03/21

Ejemplo metodo de Newton-Raphson:

Vamos a calcular las raices cuadradas de 4 en Z_15 = Z_3 x Z_5 (mcd (3, 5) = 1, Teorema chino restos)

4 tiene dos raices en Z_3 y en Z_5 (son cuerpos)

En Z_3 son 2 y -2 (1):

2^2 \cong 4 \cong 1 mod 3
1^2 \cont 1 mod 3

En Z_5 son 2 y -2 (3):
2^2 \cong 4 \cong 1 mod 3
3^2 \cont 4 mod 3


Busco x, x^2 \cong 4 mod 15

1a posibilidad (cong con 2):

x \cong 2 mod 3
x \cong 2 mod 5

Aplico teorema chino de los restos a estas dos formulas

x \cong 2 cong 15 -> ya tengo una raiz

2a posibilidad (cong con -2):

x \cong 1 mod 3 // 1  == -2
x \cong 2 mod 5

x = 1 + 3 k
1 + 3 k \cong 2 mod 5
3 k \cong 1 mod 5

k \cong 2 mod 5

k = 2 + 5 t; x = 1 + 3 (2 + 5 t) = 7 + 10 t

x \cong 7 mod 15 // 7 ^ 2 = 4 en Z_15 -> 7^2 \cong 4 mod 15

Las otras dos serían, cambiando los signos:

x \cong -2 \cong 13 mod 15
x \cong -7 \cong 8 mod 15

Las raices de 4 mod 15 son : 2, 7, 8 ,13

2 != +- 7 -> 2^2 \cong 7^2 mod 15
EN Z_15: 0 = 2^2 - 7^2 = (2 - 7)(2 + 7)
mcd(2 - 7, 15) = 5/15
mcd(2 + 7, 15) = 3/15

Recordamos que Miller-Rabin explotaba dos ideas:

- x^2 - 1 = 0 tiene dos raices en un cuerpo
- a ^{p - 1} \cong 1 mod p si p es primo

La comprobación de la segunda idea sola da lugar al método de Fermat.

Si a^{p - 1} \cong 1 mod p ; a^{\fract{p - 1}{2}} \cong +- 1 mod p

Por el criterio de Euler, a^{\fract{p - 1}{2}} = (\fract{a}{p}) (el símbolo de Jacobi)




### Problema de la factorización: Factorización a la Fermat

¿factorizar n?

Si tiene un factor, será <= que sqrt(n)

Metodo de fermat:

x = sqrt(n) por arriba

x^2 - n ¿n es un cuadrado?

si
x^2 - n = y^2
n = x^2 - y^2 = (x - y)(x + y) // si ninguno de ellos es 1 ya he encontrado la factorizacion

Si no es cuadrado,
x <- x + 1

Vuelvo a comprobar si x^2 - n es cuadrado, así hasta superar n.

Ej: n = 5959

x = 78 -> x^2 - n = 125 -> no es un cuadrado
x = 79 -> x^2 - n = 282 -> no es un cuadrado
x = 80 -> x^2 - n = 441 = 21^2 -> y = 21, los factores son 80 +- 21



### Metodo rho the Pollard

n = p * q, p factor primo menor o igual que sqrt(n)

x_1, ..., x_k "aleatorio"

Si 1 < mcd(|x_i - x_j|, n) < n, entonces p | mcd(|x_i - x_j|, n) y tendría un factor de n

El problema es elegir los aleatorios ->  Lo resuelvo con una funcion:

x_{i + 1} = f(x_i) // f(x) = (x^2 + c) mod n, con c != 0, -2

Esto no es una funcion aleatoria, pero se asemeja a una

Si hacemos esto, se producen ciclos

x_1, x_2 , ..., x_n, ..., x_k

Llega un punto en el que x_n = x_k

x_0 = y_0 = 2
x_i = f(x_i) // hacemos un paso lento
y_i = f(f(y_i)) // y un paso rápido

si mcd(|x_i - y_i|, n) != 1, parabas
si mcd(|x_i - y_i|, n) != n, exito, he encontrado un factor

Si hay fracaso, cambio c y vuelvo a empezar


Ejemplo:

```
gap> n:=8051;f:=x->(x^2+1) mod n;
8051
function( x ) ... end
gap> x:=2; y:=2;
2
2
gap> x:= f(x); y:=f(f(y));
5
26
gap> GcdInt(26-5,n);
1
gap> x:= f(x); y:=f(f(y));
26
7474
gap> GcdInt(last2-last,n);
1
gap> x:= f(x); y:=f(f(y));
677
871
gap> GcdInt(last2-last,n);
97
```

El 97 es un factor, porque el mcd es != 1

### Repaso cuerpos finitos y polinomios irreducibles

Z_2[x] // polinomios con coeficiente en Z_2

Z_2[x] = {b_0 + b_1 x + b_x x^2 + ... + b_k x^k | b_i \in Z_2}

(1 + x)(1 +x) = 1 + x^2 en Z_2[x]
||
1 + 2x + x^2 = 1 + x^2 // 2 es 0 en Z_2, entonces 2x = 0

Z_2[x]_{p(x)} el conjunto de restos de dividir por p(x)

Ejemplo:

p(x) = x^2 + 1


// el grado del resto al dividir es, como muy grande, del grado del polinomio por el que divido
Z_2[x]_{x^2 + 1}  = {0, 1, x, x+1} = // 0 y 1 son de grado 0, y x, x+1 son de grado 1, para porque de grado 2 no pueden ser los restos

=  { a + bx | a, b \in Z_2} \equiv {(a, b) | a, b \in Z_2}
= Z_2 x Z_2

El poliniomio que escojas da igual, lo importante es el grado

+ | 0 | 1 | x | x+1
--|---|---|---|-----
0 | 0 | 1 | x | x+1
1 | 1 | 0 | x + 1 | x
x | x | x + 1 | 0 | 1
x+1 | x + 1 | x | 1 | 0

* | 0 | 1 | x | x+1
--|---|---|---|-----
0 | 0 | 0 | 0 | 0
1 | 0 | 1 | x | x + 1
x | 0 | x | 1 | x + 1
x+1 | 0 | x + 1 | x+1 | 0

El conjunto de restos nunca va a ser un cuerpo, porque hemos encontrado a, b != tal que a b = 0


Ejemplo:

p(x) = x^2 + x + 1

La de la suma es la mismo:

+ | 0 | 1 | x | x+1
--|---|---|---|-----
0 | 0 | 1 | x | x+1
1 | 1 | 0 | x + 1 | x
x | x | x + 1 | 0 | 1
x+1 | x + 1 | x | 1 | 0



* | 0 | 1 | x | x+1
--|---|---|---|-----
0 | 0 | 0 | 0 | 0
1 | 0 | 1 | x | x + 1
x | 0 | x | x + 1 | 1
x+1 | 0 | x + 1 | 1 | x

Z_2[x]_{x^2+x+1} es un cuerpo, porque todo elemento tiene inverso

Como y cuando puedo calcular inversos?


a(x) y b(x) polinomios en Z_x[x]
Existen u(x) y v(x) tales que d(x) = u(x) a(x) + v(x)b(x)
con d(x) = mcd(a(x), b(x))

Puedo calcular el inverso ( a(x)^1 ) en Z_s[x]_{b(x)} cuando d(x) = mcd(a(x), b(x)) = 1, y en ese caso 1 = u(x) a(x) + v(x)b(x) = u(x)a(x); u(x) = a(x)^-1 // v(x)b(x) = 0

Para que todos no nulos tengan inverso, b(x) tiene que ser irreducible.


1 + x + x^2 es irreducible en Z_2[x], ya que no tiene raices en Z_2 (con x = 0 sale 1 y con x = 1 sale 1)

El polinomio utilizado en AES es x^8 + x^4 + x^3 + x + 1 = p(x)

Z_2[x]_{p(x)}  tiene 2^8 elementos


## 24/04/21


Z_2[x]_{p(x)} tiene 2^{gr(gr(x)) - 1} elementos \cong Z_2^{gr(p(x))}

es un cuerpo (finito) si p(x) es irreducible (primo)

a(x), b(x) \in Z_2[x]_{p(x)}

a(x) + b(x) = a(x) + b(x) mod p(x)

a(x) \cdot b(x) = a(x) \cdot b(x) mod p(x)

p(x) irreducible? (es primo) a^{-1}(x) se calcula con Euclides extendido
1 = u(x) a(x) + v(x) p(x), con a(x) != 0 (p(x) \not | a(x))

a^{-1}(x) = u(x)

En AES no se calcula inversos de esta manera ya que es lento, se almacenan en una tabla

p(x) se dice **primitivo** si x genera todo Z_2[x]_{p(x)}^*

<x> = Z_2[x]_{p(x)}^* = {1 = x^0, x, x^2, ..., x^{2^{n} - 1}} con n = gr(p(x))



Ejemplo:

p(x) = x^2 + x + 1 en Z_2[x]

x \in Z_2[x]_{p(x)} (esto tiene 4 elementos contando con el cero)

<x> = {1, x, x+1} = Z_2[x]_{p(x)}^* (sin el cero)

Como vemos, llegamos a x^2, este 2 sale de 2^2 - 2 = 2, que es x^{2^{n} - 1}


Ejemplo:

p(x) = x^3 + x + 1 en Z_2[x] <- es irreducible, no tiene raices en Z_2 y no puedo divirlo en factores de grados menores.

x \in Z_2[x]_{p(x)} (tiene 8 elementos, 2^{gr(p(x)) = 2^3 = 8})

<x> = {1, x, x^2, x + 1, x^2 + x, x^2 + x + 1, x^2 + 1}

// x^5 = x x^4 = x (x^2 + x) = x^3 + x^2 = x + 1 + x^2
// x^6 = x x^5 = x * (x^2 + x + 1) = x^3 + x^2 + x = x + 1 + x^2 + x

 x^7 no hace falta, porque solo hay 7 elementos, saldria 1 y se repitiría

 recordemos que

 ord(x) | |Z_2[x]_{p(x)}^x| = 7


Supongamos que queremos hacer a(x) \cdot b(x) con a(x) y b(x) != 0

a(x) \cdot b(x) = a(x) \cdot b(x) mod p(x)
a(x) \cdot b(x) = x^\alpha \cdot x^\betha = x^{\alpha + \betha mod 7} // en este caso p(x) = 7

(x + 1)(x^2 + x) = x^3 x^4 = x^7 = 1

a(x)^{-1} = (x^\alpha)^{-1} = x^{-\alpha} = x^7 x^{-\alpha} = x^{7 \cdot -\alpha}

primitivo implica irreducible

(x^2 + x)^{-1} = (x^{4})^-1 = x^{-4} = x^{7 - 4} = x^3 = x - 1

Para calcular inversos simplemente puedo buscar posiciones en la lista anterior, y no estar ejecutando bezout, es más rápido así


si lo respresntamos como bits

a(x) + b(x) \equiv XOR

(x^2 + x) + (x+1) = x^2 + 1
110 \XOR 011 = 101

Por eso la tabla con bits nos es tan util
