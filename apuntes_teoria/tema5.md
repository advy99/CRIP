# Tema 5: Firmas y autenticación

MIRAR DIAPOSITIVAS Y APUNTES DE JESUS

## FIrmas:

- Unicas : Solo puede ser generada por firmante
- Verificables por todo el mundo : Facilmente verificables por todos
- No repudiables : el firmante no puede negar que ha firmado algo con su firma
- Viables : faciles de hacer

Cosas necesarias para la firma :

- Conjunto de posibles mensajes
- COnjunto de posibles firmas
- Conjunto de posibles claves
- funcion de firma M -> F
- funcion cer: MxF ->


Ejemplos:

- FIrma ElGammal
- Firma RSA
- Firma de Rabin


### DSS o DSA

Idea es cifrar en algo grande, pero que la firma sea más pequeña

Se escogen dos primos, uno grande y uno pequeño, y la idea es que la firma este modulo el pequeño

Escojo un q a la Miller-Rabin, 160 bits de tamaño mas o menos
p = c \ cdot q  + 1, con c par aleatorio, para que sea entre 512 y 1024 bits, si con c no es primo, pruebo con c+2, y así hasta que p sea primo


Ya tengo p y q, ahora necesito un \alpha que tenga ord(\alpha) = q \in Z_p

Lo consigo aleatorio:

g aleatorio; g^{{p - 1} / q} = g^c,
si g^c no es cong 1 mod p, \alpha = g^{{p - 1} / q} = g^c != 1


\alpha^q \cong g^{{p - 1} / q}^q = g^{p - 1} = 1 (Por fermat)

Si es congruente, escocjo otro g aleatorio


#### COmo se firma

Como ElGammal, pero las cuentas son hibridas mod p y mod q


### MAC

Codigo de autentificación de mensajes

Se añade al mensaje una coletilla, para detectar si se ha modificado

### Funciones resumen

- Facil de calcular
- Unidireccional
- Difusión: efecto cascada, si cambio un unico bit, se propague ese cambio y afecte a gran parte de la funcion resumen
- Resistencia debil a colisiones
- Resistencia fuerte a colisiones

#### Construccion Merkle-Damgard

MIRAR DIAPOSITIVAS

### HMAC

MAC con funciones resumen
