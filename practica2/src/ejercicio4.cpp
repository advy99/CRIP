
#include "funciones.hpp"

#include <iostream>
#include <boost/dynamic_bitset.hpp>


int main ( int argc, char ** argv) {

	if ( argc != 8 ) {
		std::cerr << "ERROR: Numero de argumentos erroneos.\n"
					 << "\t Uso: " << argv[0] << " <p1> <semilla1> <p2> <semilla2> <p3> <semilla3> <longitud>" << std::endl;
		exit(-1);
	}

	std::string coeficientes_p1 = std::string(argv[1]);
	std::string semilla1 = std::string(argv[2]);
	std::string coeficientes_p2 = std::string(argv[3]);
	std::string semilla2 = std::string(argv[4]);
	std::string coeficientes_p3 = std::string(argv[5]);
	std::string semilla3 = std::string(argv[6]);

	int longitud = atoi(argv[7]);

	if ( coeficientes_p1.size() != semilla1.size() || coeficientes_p2.size() != semilla2.size() || coeficientes_p3.size() != semilla3.size()) {
		std::cerr << "ERROR: La longitud del string de coeficientes y de la semilla ha de ser la misma en cada pareja" << std::endl;
		exit(-2);
	}

	std::pair<boost::dynamic_bitset<>, boost::dynamic_bitset<> > lfsr1;
	std::pair<boost::dynamic_bitset<>, boost::dynamic_bitset<> > lfsr2;
	std::pair<boost::dynamic_bitset<>, boost::dynamic_bitset<> > lfsr3;

	lfsr1 = std::make_pair(boost::dynamic_bitset<>(coeficientes_p1), boost::dynamic_bitset<>(semilla1));
	lfsr2 = std::make_pair(boost::dynamic_bitset<>(coeficientes_p2), boost::dynamic_bitset<>(semilla2));
	lfsr3 = std::make_pair(boost::dynamic_bitset<>(coeficientes_p3), boost::dynamic_bitset<>(semilla3));

	auto resultado = generador_geffe(lfsr1, lfsr2, lfsr3, longitud);


	std::cout << "Resultado: " << std::endl;
	std::cout << resultado << std::endl;

}
