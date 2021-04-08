
#include "funciones.hpp"

#include <iostream>
#include <boost/dynamic_bitset.hpp>


int main ( int argc, char ** argv) {

	if ( argc != 4) {
		std::cerr << "ERROR: Numero de argumentos erroneos.\n"
					 << "\t Uso: " << argv[0] << " <coeficientes polinomio> <semilla> <longitud salida>" << std::endl;
		exit(-1);
	}

	std::string coeficientes_p = std::string(argv[1]);
	std::string semilla = std::string(argv[2]);
	long long longitud_salida = atoll(argv[3]);

	if ( coeficientes_p.size() != semilla.size()) {
		std::cerr << "ERROR: La longitud del string de coeficientes y de la semilla ha de ser la misma" << std::endl;
		exit(-2);
	}

	boost::dynamic_bitset<> coeficientes_bits(coeficientes_p);
	boost::dynamic_bitset<> semilla_bits(semilla);

	auto resultado = LFSR(coeficientes_bits, semilla_bits, longitud_salida);


	std::cout << "Resultado: " << std::endl;
	std::cout << resultado << std::endl;

}
