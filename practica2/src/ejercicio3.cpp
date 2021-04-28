
#include "funciones.hpp"

#include <iostream>
#include <boost/dynamic_bitset.hpp>

//
//
//

int main ( int argc, char ** argv) {

	if ( argc < 4 ) {
		std::cerr << "ERROR: Numero de argumentos erroneos.\n"
					 << "\t Uso: " << argv[0] << "<semilla> <longitud salida>  <coeficientes polinomio> " << std::endl
					 << "\t Separar los coeficientes por espacios, por ejemplo: " << std::endl
					 << "00 10 11" << std::endl
					 << "Sería el polinomio x^0 y^0 + x^1 y^0 + x^1 y^1";
		exit(-1);
	}

	std::vector<boost::dynamic_bitset<> > polinomio;

	for ( int i = 3; i < argc; i++ ) {
		polinomio.push_back( boost::dynamic_bitset<>(std::string(argv[i])) );
	}

	std::string semilla = std::string(argv[1]);

	boost::dynamic_bitset<> semilla_bits (semilla);
	long long longitud = atoll(argv[2]);

	auto resultado = NLFSR(polinomio, semilla_bits, longitud);

	std::cout << resultado << std::endl;

	return 0;
}
