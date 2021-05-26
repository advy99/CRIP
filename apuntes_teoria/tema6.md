# Protocolos criptográficos

## Definicion

En realidad son algoritmos

Previamente establecido

Mutuamente suscrito

Sin ambigüedad

Completo


## Protocolo del lanzamiento de moneda

1. A elige dos primos grandes p y q. Calcula su podructo y lo envia a B
2. B elige un numero al azar u entre 1 y (n-1) / 2, calcula v = u^2 mod n y lo envia a A. Usamos (n - 1) / 2 para asegurarse que solo se tratan dos de la raices, no las cuatro
3. A calcula las cuatro raices de v mod n, y puede porque conoce a p y q. Elige una menor que n / 2 (solo tener en cuenta las dos menores) y la envia a B.
4. Si A escoge u' (una de las dos raices, la otra es u), B puede calcular p y q, ya que gcd(u - u', n) | n (tenemos sus factores). Si A escoge u, como B solo tiene u, y no u' u', no puede hacer nada.



## Protocolo de secreto compartido

Se pretende distribuir un secreto s en n particiones, de forma que sean necesarias t de ellas para poder recuperarlo.

1. Se elige un prmo p mayor que s y mayor que n.
2. Se eligen t - 1 elementos de Z_p, a_1, a_2, ..., a_{t-1} con a_{t - 1} != 0
3. Se toma el polinomio p(x) = s + a_1 x + ... +a{t - 1} x^{t - 1}
4. Se eligen n elementos distintos x_1, x_2, ... x_n en X_p \ {0}
5. Se calcula y_1 = P(x_1), ..., y_t = P(x_n)
6. A cada participante se le da la pareja de numeros (x_i, y_i)

Basicamente se hace un polinomio de grado t, de forma que si tengo t coeficientes (se juntan t personas), puedo resolver el sistema y obtener el polinomio.

## Protocolos de conocimiento cero

A quiere convencer a B que tiene una información, pero A no quiere desvelar esa informacion.

B desarfia a A con preguntas que solo puede responder si posee la información, pero con probabilidad de 1/2 de hacer trampa.

Si respondes n veces bien, la probabilidad de que no tenga la información es 1/2^n.

### Protocolo de Chaum, Evertse y Van de Graff

A quiere convencer a B que conoce la clave privada x de ElGammal, (p, alpha, y) (recordar que y = alpha ^ x)

1. A elige un valor aleatorio r, calcula beta = alpha^r (mod p) y envia este valor a B.
2. B elige un bit de c y lo envia a A
3. A calcula z = r + c x (mod p - 1)
4. B acepta la prueba si alpha^z = Beta \cdot y^c (mod p)


A puede decidir haber mandado Beta, o beta * y^{-1}, haciendo trampas, pero esto solo funciona segun si B elige bit 0 o 1, nunca con ambos, así que la posibilidad de acertar mintiendo es 1/2, si se hacen n pruebas, 1/2^n.

Si A conoce x, siempre acertará

### Protocolo de Fiat-Shamir

A quiere convencer a B de que posee la raiz cuadrada s de ID modulo n = p*q

1. A genera un aleatorio r y envia a B t = r^2
2. B elige un bit b al azar y se lo envia a A.
3. A calcula u = r * s^b y lo envia a B
4. B compruba que u^2 = t * ID^b

En este caso, de nuevo, A puede o mandar t, o t*ID^{-1}, y de nuevo, tiene posibilidad 1/2 de acertar, dependiendo del bit que escoja B, de nuevo, en n pruebas, la posibilidad e ganar mintiendo es 1/2^n


Si A conoce s, siempre acertará
