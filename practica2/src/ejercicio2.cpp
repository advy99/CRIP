
#include "funciones.hpp"

#include <iostream>
#include <boost/dynamic_bitset.hpp>

// IMPORTANTE: Al escribir los polinomio, se escriben ordenados por grado (primero grado uno, dos, tres, ...)
// al contrario que como se veian en las diapositivas de LFSR
//
// Algunos ejemplos:
// 1 + x^2 + x^5: 01001 (más significativo a la derecha, le tenemos que dar la vuelta)
// ./bin/ejercicio2 01001 01000
// Resultado:
// 0100001010111011000111110011010
// El periodo tiene longitud 31
// Además, para la cadena resultante se cumplen los postulados de Golomb

// 1 + x^6: 100001
// ./bin/ejercicio2 100001 010001
// Resultado:
// 010001100001000001111110101011001101110110100100111000101111001
// El periodo tiene longitud 63
// Además, para la cadena resultante se cumplen los postulados de Golomb


//
// x^10 + x^3 + 1: 0010000001
//  ./bin/ejercicio2 0010000001 1111100101
//
// Resultado:
// 111110010101010011001100101001111101001110000100011011001000101001101111011101010111001100111
// 011101110011101010011101000001111011011100001100010010100101100110100010001011010010111010011
// 000101100000010100100101111101111000110001101110110000111100100111001011000100001101111111001
// 110001101010010100001000010010110111110101110001011100100001111101101010100010111101100111001
// 111100000111001001010110010111100101110000010101101100110000110101101110100010101111110100011
// 100110111001010001101000000110010010001000001001101101001111001101010110000101110110100011000
// 010011111110111000111100000011101101100010100010011001000001101001001111011111000101010110100
// 001010000000101101101111001111000100011111101100011101011010100001100110110000011000000001101
// 101101011101011110000101010010000101100100110000010001001000000100000000010010010011010011010
// 111110011000111110010001110111111000011100000001111111111000111000100111011001010111011110101
// 000111101001010100000101111111101010101011110100001110100100011001011010110011110101100011001
// El periodo tiene longitud 1023
// Además, para la cadena resultante se cumplen los postulados de Golomb


//	x^15 + x + 1: 100000000000001
// ./bin/ejercicio2 100000000000001 010010101011100
// Salida demasiado grande, pero cumple los postulados de golomb


// IMPORTANTE para este hace falat como 4GB de RAM por como esta hecho para calcular cuando cicla
// Esta tarda un poco: x^25 + x^3 + 1: 0010000000000000000000001
// ./bin/ejercicio2 0010000000000000000000001 0100101010111010010101100
// Salida demasiado grande, pero cumple los postulados de golomb



int main ( int argc, char ** argv) {

	if ( argc < 3 ) {
		std::cerr << "ERROR: Numero de argumentos erroneos.\n"
					 << "\t Uso: " << argv[0] << " <coeficientes polinomio> <semilla> [longitud salida]" << std::endl
					 << "\t Si se ejecuta sin longitud de salida se ejecutará hasta llegar a la frecuencia máxima" << std::endl;
		exit(-1);
	}

	std::string coeficientes_p = std::string(argv[1]);

	std::string semilla = std::string(argv[2]);
	signed long long longitud_salida = -1;

	if ( argc == 4) {
		longitud_salida = atoll(argv[3]);
	}

	if ( coeficientes_p.size() != semilla.size()) {
		std::cerr << "ERROR: La longitud del string de coeficientes y de la semilla ha de ser la misma" << std::endl;
		std::cout << "Longitudes dadas: " << coeficientes_p.size() << " y " << semilla.size() << std::endl;
		exit(-2);
	}

	if ( coeficientes_p.size() > (unsigned) longitud_salida) {
		std::cerr << "ERROR: La longitud de la salida tiene que ser mayor o igual a la longitud de la semilla dada" << std::endl;
		exit(-3);
	}

	boost::dynamic_bitset<> coeficientes_bits(coeficientes_p);
	boost::dynamic_bitset<> semilla_bits(semilla);

	auto resultado = LFSR(coeficientes_bits, semilla_bits, longitud_salida);


	std::cout << "Resultado: " << std::endl;
	std::cout << resultado << std::endl;

	if (longitud_salida == -1) {
		std::cout << "El periodo tiene longitud " << resultado.size() << std::endl;
	}

	bool cumple_golomb = cumple_postulados_golomb(resultado);

	if ( cumple_golomb) {
		std::cout << "Además, para la cadena resultante se cumplen los postulados de Golomb" << std::endl;
	}

}
