
#include "funciones.hpp"

#include <iostream>
#include <boost/dynamic_bitset.hpp>

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


}
