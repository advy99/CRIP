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
