
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
	unsigned long long longitud_salida = atoll(argv[3]);

	if ( coeficientes_p.size() != semilla.size()) {
		std::cerr << "ERROR: La longitud del string de coeficientes y de la semilla ha de ser la misma" << std::endl;
		std::cout << "Longitudes dadas: " << coeficientes_p.size() << " y " << semilla.size() << std::endl;
		exit(-2);
	}

	if ( coeficientes_p.size() > longitud_salida) {
		std::cerr << "ERROR: La longitud de la salida tiene que ser mayor o igual a la longitud de la semilla dada" << std::endl;
		exit(-3);
	}

	boost::dynamic_bitset<> coeficientes_bits(coeficientes_p);
	boost::dynamic_bitset<> semilla_bits(semilla);

	auto resultado = LFSR(coeficientes_bits, semilla_bits, longitud_salida);


	std::cout << "Resultado: " << std::endl;
	std::cout << resultado << std::endl;


	auto resultado_postulados = LFSR(coeficientes_bits, semilla_bits, semilla_bits.size() * semilla_bits.size() - 1);

	bool cumple_golomb = cumple_postulados_golomb(resultado_postulados);

	if ( cumple_golomb) {
		std::cout << "Además, la cadena resultante cumple los postulados de Golomb para la cadena más larga posible:"
					 << std::endl << resultado_postulados << std::endl;
	}

}
