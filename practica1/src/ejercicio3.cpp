#include <boost/multiprecision/cpp_int.hpp>


#include <iostream>
#include <bit>
#include <vector>

using boost::multiprecision::cpp_int;

cpp_int pow_mod(cpp_int base, cpp_int exponente, 
					 const cpp_int modulo) {
	
	cpp_int resultado = 1;
	
	while ( exponente > 0) {
		if ( (exponente & 1) == 1) {
			resultado = (resultado * base) % modulo;
		}

		exponente = exponente >> 1;

		base = (base * base) % modulo;

	}

	return resultado;
}

int main ( int argc, char ** argv) {

	if ( argc != 4 ) {
		std::cerr << "ERROR: Se necesitan tres parametro: base, exponente, modulo" << std::endl;
		exit(-1);
	}

	cpp_int base(argv[1]);
	cpp_int exponente(argv[2]);
	cpp_int modulo(argv[3]);

	std::cout << base << " elevado a " << exponente << " modulo " << modulo << " es " << pow_mod(base, exponente, modulo) << std::endl; 

	std::cout << "Boost: " << base << " elevado a " << exponente << " modulo " << modulo << " es " << powm(base, exponente, modulo) << std::endl; 


}
