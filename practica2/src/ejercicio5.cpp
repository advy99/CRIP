
#include "funciones.hpp"

#include <iostream>
#include <boost/dynamic_bitset.hpp>

// IMPORTANTE: Se trata del ejemplo que hace Jesus en su implementación, pero invertido,
// al utilizar el más significativo a la derecha
// Ejemplo de ejecución:
// ./bin/ejercicio5 11001000111101
// K: 0
// r        l       a       b               f       g               d       2l > r
// 1       1       0       0       00000000000011  00000000000001  1       1
// 2       1       0       1       00000000000010  00000000000001  1       0
// 3       2       1       1       00000000000101  00000000000010  1       1
// 4       2       1       2       00000000000111  00000000000010  1       0
// 5       3       2       2       00000000001100  00000000000111  0
// 6       3       2       3       00000000001100  00000000000111  1       0
// 7       4       3       3       00000000011111  00000000001100  1       1
// 8       4       3       4       00000000010011  00000000001100  0
// 9       4       3       5       00000000010011  00000000001100  0
// 10      4       3       6       00000000010011  00000000001100  0
// 11      4       3       7       00000000010011  00000000001100  0
// 12      4       3       8       00000000010011  00000000001100  0
// 13      4       3       9       00000000010011  00000000001100  0
// Complejidad lineal: 4
// El polinomio que lo genera es:
// 0011 = 1  + x_4 + x_3
//
// Para comprobarlo, vamos a lanzar el LSFR.
// Resultado LFSR:
// 11001000111101
// Cadena original:
// 11001000111101

// para las pruebas de suma de secuencias y multiplicación de secuencias, utilizaremos
// los ejemplos de Jesus en sus apuntes.
// Con el ejercicio 2, obtendremos el periodo de las secuencias que pone como ejemplo
// polinomio 1 + x + x^2
// ./bin/ejercicio2 11 11
// Resultado:
// 011
// El periodo tiene longitud 3
// Además, para la cadena resultante se cumplen los postulados de Golomb
//
// polinomio 1 + x + x^3
//  ./bin/ejercicio2 101 111
// Resultado:
// 0010111
//
// El periodo tiene longitud 7
// Además, para la cadena resultante se cumplen los postulados de Golomb
//
// Como vemos tienen longitud 3 y 7, así que las generamos hasta longitud 21, y las sumamos
//
// 011011011011011011011 // esta cadena tiene complejidad lineal 2
// 001011100101110010111 // esta cadena tiene complejidad lineal 3
// ---------------------
// 010000111110101001100
// que como vemos tiene periodo 21
// si lo ejecutamos, vemos que tiene complejidad lineal 5, como vimos, en este caso
// la complejidad lineal es la suma de la complejidad de cada cadena

// en el caso del producto:
// 011011011011011011011 // esta cadena tiene complejidad lineal 2
// 001011100101110010111 // esta cadena tiene complejidad lineal 3
// ---------------------
// 001011000001010010011
// la complejidad lineal es 6, y como vismo, en este caso se multiplican cada
// complejidad lineal


int main ( int argc, char ** argv) {

	if ( argc != 2 ) {
		std::cerr << "ERROR: Numero de argumentos erroneos.\n"
					 << "\t Uso: " << argv[0] << " <secuencia_bits>" << std::endl;
		exit(-1);
	}

	std::string secuencia = std::string(argv[1]);
	boost::dynamic_bitset<> secuencia_bits(secuencia);

	auto resultado = algoritmo_berlekamp_massey(secuencia_bits);


	std::cout << "Complejidad lineal: " << resultado.first << std::endl;


	auto f_x = resultado.second;

	// en principio segun el algoritmo habría que invertir f, pero en mi implementación
	// los polinomios se utilizan ya invertidos

	std::cout << "El polinomio que lo genera es: " << std::endl;
	std::cout << f_x << " = 1 ";


	for ( unsigned i = 0; i < f_x.size(); i++) {
		if (f_x[i]) {
			std::cout << " + x_" << f_x.size() - i;
		}
	}

	std::cout << std::endl << std::endl;

	std::cout << "Para comprobarlo, vamos a lanzar el LSFR. " << std::endl;

	auto semilla = secuencia_bits;

	while (semilla.size() != f_x.size()) {
		semilla.pop_back();
	}

	auto resultado_lfsr = LFSR(f_x, semilla, secuencia_bits.size());
	std::cout << "Resultado LFSR:" << std::endl;
	std::cout << resultado_lfsr << std::endl;
	std::cout << "Cadena original:" << std::endl;
	std::cout << secuencia_bits << std::endl;


}
