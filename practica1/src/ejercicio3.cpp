#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <bit>
#include <vector>

#include "funciones.hpp"

int main ( int argc, char ** argv) {

	if ( argc != 4 ) {
		std::cerr << "ERROR: Se necesitan tres parametro: base, exponente, modulo" << std::endl;
		exit(-1);
	}

	mp::cpp_int base(argv[1]);
	mp::cpp_int exponente(argv[2]);
	mp::cpp_int modulo(argv[3]);

	std::cout << base << " elevado a " << exponente << " modulo " << modulo << " es " << pow_mod(base, exponente, modulo) << std::endl;

	std::cout << "Comprobacion (utilizando powm): " << base << " elevado a " << exponente << " modulo " << modulo << " es " << powm(base, exponente, modulo) << std::endl;


}
