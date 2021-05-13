Antonio David Villegas Yeguas

Descifrando ElGammal

Clave publica: (113, 3, 17)

Mensaje cifrado: (105, 88)

Tenemos r y s = 105 y 88 respectivamente

Tenemos alpha = 3

Podemos calcular

r = alpha^k

105 = 3^k

k = 92

Comprobacion al ejecutar el ejercicio 5 del logaritmo discreto
./bin/ejercicio5 3 105 113
3 ^ 92 = 105 en Z_113
Comprobacion: 105
Tiempo de ejecucion de mi algoritmo: 3.8178e-05 segundos

Ahora sabemos que

s = m \cdot y^k

Luego 87 = m * 17^92
87 = m * 2

El inverso de 2 mod 113 = 57

87 * 57 mod 113= m

m = 100

Comprobandolo por python

>>> r = pow(3, 92, 113)
105
>>> s = (100 * pow(17, 92, 113) ) % 113
87

Vemos que sale igual


Rompiendolo de otra forma:

17 = alpha ^ x
x = 5


m = s * r^{-x}
m = 87 * 105^-5

>>> (87 * pow(105, -5, 113)) % 113
100

Como vemos ambas comprobaciones dan igual


M vale 100
