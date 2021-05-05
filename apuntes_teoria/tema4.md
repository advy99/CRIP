# Tema 4: Cifrado asimétrico

Buscar funciones que sean facil de calcular la clave, y dificil encontrar el original.


No tiene porque ser inyectiva

Llave publica: forma de calcular la imagen de la función
Llave privada: forma de calcular la preimagen (imagen inversa)


## Diffie-Hellman

EXPLICADO EN DIAPOSITIVAS

Se basa en que es dificil (muy lento) calcular el logaritmo discreto

Llave publica: Primo escogido mutuamente entre A y B, y el exponente k es escogido aleatoriamente, de forma que tenemos un generador en Z_p, \alpha^k


A envia a B, alpha^{x_A} mod p , por un canal inseguro

Se podría aplicar paso enano paso gigante, y es de orden casi exponencial, es muy lento, por lo que es imposible obtener que es.

B envia a A alpha^{x_b} mod p

Ambos comparten alpha^{x_a x_b} = (alpha^{x_a}) ^ {x_b} = (alpha^{x_b}) ^ {x_a}

Esto ya que ambos conocen pueden utilizarlo como clave para cualquier otro cifrado que ya hemos visto


Esto tiene algunos problemas:

### Ataque pasivo

Calcular el logaritmo, complejidad e^{\sqrt{k * log k}}, vamos, casi imposible de obtener

### Ataque activo

Man in the middle

El man in the middle utiliza sus claves, A -> Man in the middle -> B, y cuando B devuelve su clave, lo mismo pero al reves. (mirar diapositivas)

Para resolver esto, se utilizan servidores seguros, es ahi donde se comparten las llaves, para asegurar que no hay man in the middle

## ElGammal

Como diffie-hellman, pero este si que cifra cosas, diffie-hellman solo comparte llaves.

Tiene una llave publica, que se consigue con un primo p, alpha que es el grupo multiplicativo que genera Z_p \{0}, e y, donde y = a^x mod p

Cada vez que se manda un mensaje se manda de forma distinta, ya que tiene una componente aleatoria, la k se escoge de forma aleatoria.

MIRAR DIAPOSITIVVAS

Todas las operaciones del cifrado son mod p, asi que tenemos que tener cuidado que nuestro mensaje sea menor que p, o trocearlo

El mensaje cifrado es el doble de tamaño que el mensaje original.

Para descifrar, calculo s \cdot r^{-1} = s \cdot r^{p - 1 - x}, todo esto en mod p

Para mirar porque funciona, diapositivas, basicamente es lo que vimos en el tema 1.


## Firma ElGammal

La idea es comprobar que un mensaje lo ha mandado la persona que lo firma

MIRAR DIAPOSITIVAS


firma(m) = (r,s)

r = alpha ^ k mod p
s = (m - x * r) * k^{-1} mod p-1

Para verificar la firma tienen que coincidir
y ^ r * r^s mod p y alpha^m mo p


## RSA: Rivest, Shamir y Adleman

Se basa en el teorema de euler (recordar tema 1)

Por euler, si m y n son primos relativos, m^\phi(n) mod n = 1.

Seleccionamos dos primos grandes y distantes entre si (p y q), y calculamos su producto, n.

El n va a ser publico (es imposible calcular los factores p y q, es muy costoso)

Tambien soy el unico que conoce phi(n)

La llave publica es (n, e), y la llave privada es d.


Para cifrar un mensaje:

m -> m^e mod n = c

Aunque todo el mundo sepa e, no es posible calcular la raiz e-esima, sin conocer p y q, así que es seguro

Descifrado:
c -> c^d mod n

Esto funciona ya que son inversos, y sabemos que gdc(e, phi(n)) = 1

(mirar diapositivas para más explicación matematica)

Como tengo d, que es la clave privada, es facil descifrar


Si el mensaje no es primo con n, los divisores serían p y q, así que igualmente nos da igual. La probabilidad de que no sea primo con n ~= 1/p + 1/q, que es muy muy pequeña.


Normalmente se utiliza una versión mejorada, ya que con el teorema chino de los restos y el teorema pequeño de fermat, es facil que si es congruente con p y con q, es congruente con p*q, que es n, cosa que es un problema ya que tendríamos n. x^mcm(p-1, q-1), es multiplo con p * q,  así que ya tengo n,  y no necesito el teorema de euler. Si e es primo relatico con mcd(p-1, q-1) es un problema grande, ya que es más facil obtener una clave privada d.

En lugar de usar phi(n), se usa un mcm(p, q)

Tambien existe una serie de mensajes que no se pueden cifrar, m^e = m, esto quiere decir x^e - x = 0, tanto mod p como mod q, si sabemos la soluciones, sabemos cuantos mensajes no podremos cifrar. (Ejemplo en dispositivas, es facil calcularlas)

Detalles en apuntes de jesus miranda

## Firma RSA

Firmar es simple, para firmar un mensaje m:

f = m^d mod n

Y enviamos la pareja (m, f)

Para comprobar veracidad

f^e = (m^d)^e = m mod n

De esta forma, con e, que es parte de la clave publica, se puede comprobar que he firmado con d.


## La función de Rabin

Esta funcion es elevar al cuadrado

Romper esta funcion es de orden n!

Si tenemos una función
f: Z_n -> Z_n, f^{-1}(y) tiene cuatro elementos
    x  -> x^2

Si se que f(a) = f(b) -> a^2 = b^2, con a != +-b

Entonces se que

a^2 - b^2 = (a - b) (a + b) = 0 mod n

y a - b != 0 y a + b != 0

Entonces se que a + b y a - b, no pueden ser primos relativos

mcd(a-b, n) != 1, entonces tieen que ser p o q, y me he cargado el sistema. Esto es muy dificil porque calcular raices sin saber p y q risas.


Este sistema es fuerte porque nadie sabe como romper n. Solo se puede utilizar para firmar

## La firma de Rabin

Las dos barritas || es concatenación

Tenemos una función resumen h, y sabemos n = p * q, conociendo todo. queremos firmar m

1 - Escogemos u aleatoria, de forma que h(m||u) sea un cuadrado modulo n (la concatenación a voleo para que sea cuadrado mod n, tenemos 1/4 de posibilidades de acertar)

2- Calculamos una raiz cuadrada r

3 - Enviamos (m, u, r)

Verificación, r^2 = h(m||u) mod n

Esto funciona porque no se puede calcular la raiz, a no ser que se tenga p y q, que yo si la tengo.


## Generación de llaves

Como consigo alpha primitivo mod p??

Es sencillo, pero computacionalmente dificil.

Esoty siempre en mod p

alpha^{p-1} = 1
alpha^{k} != 1 para k < p - 1

Idea 1: Si alpha^k = 1, alpha^2k = 1, alpha^{n*k} = 1
Idea 2: ord(alpha) = k, alpha^k = 1, entonces k | p - 1 ; si el orden  de alpha (menor elemento que al elevar da 1) = k,  entonces k divide a p - 1

ord(alpha) = |<alpha>|

Lo que estoy buscando para que alpha sea primitivo:

alpha^k != 1 para k divisor propio maximal de p - 1

Tendria que romper p - 1 en producto de primos y

p - 1 = p_1^e_1 \cdot .... \cdot p_t^e_t  ; k = p / p_i divisores maximales de p - 1

Solo tengo que comprobar con la mitad, ejemplo:

p = 7; p - 1 = 2 * 3; k \in {2, 3}

Problema obvio: Romper p - 1 (es un poco más facil que romper p, pero sigue siendo dificil)

Solución: Hacer trampas; Crear p "a medida"

Busco p primo con (p - 1) / 2  primo. Esto lo hacemos para que romper p - 1 solo tenga dos posibles valores, 2 y (p - 1) / 2

p - 1 = 2 * (p - 1) / 2 divisores maximales = {2, (p - 1) / 2}

Tengo que comprobar que alpha^2 != 1 y que alpha^{(p - 1) / 2} != 1

esto quiere decir que alpha != +=1
Entonces alpha^{(p-1) /2 }  = -1

Segun el criterio de euler, alpha^{(p-1) /2 } = simbolo jacobi de alpha sobre p. SI buscamos aleatorio un alpha, te da la mitad de las posibildiades, se busca a voleo con miller-rabin

(recordamos que todo esto mod p)
