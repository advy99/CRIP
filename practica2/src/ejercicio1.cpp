
#include "funciones.hpp"

#include <iostream>
#include <boost/dynamic_bitset.hpp>


int main ( int argc, char ** argv) {

	if ( argc != 2) {
		std::cerr << "ERROR: Se necesita un parámetro.\n"
					 << "\t Uso: " << argv[0] << " <secuencia_bits>" << std::endl;
		exit(-1);
	}

	// para ejemplo: 000100110101111 si cumple todos
	// 0011101 si cumple todos


	std::string bits_entrada = std::string(argv[1]);

	boost::dynamic_bitset<> bitset(bits_entrada);

	bool cumple_primer_postulado = cumple_primer_postulado_golomb(bitset);
	bool cumple_segundo_postulado = cumple_segundo_postulado_golomb(bitset);
	bool cumple_tercer_postulado = cumple_tercer_postulado_golomb(bitset);

	bool cumple_postulados = cumple_postulados_golomb(bitset);

	std::cout << "La secuencia de bits: " << bits_entrada;

	if ( !cumple_postulados ) {
		std::cout << " NO ";
	}

	std::cout << " cumple los postulados de Golomb" << std::endl;

	if ( cumple_primer_postulado ) {
		std::cout << "Cumple el primer postulado" << std::endl;
	}

	if ( cumple_segundo_postulado ) {
		std::cout << "Cumple el segundo postulado" << std::endl;
	}

	if ( cumple_tercer_postulado ) {
		std::cout << "Cumple el tercer postulado" << std::endl;
	}

}
