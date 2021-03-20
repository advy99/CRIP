#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <vector>
#include "funciones.hpp"

int main(int argc, char ** argv) {

	if ( argc != 3 ) {
		std::cout << "Error: Ejecutar con dos parámetros <a> y <b>" << std::endl;
		exit(-1);
	}

	mp::cpp_int a(argv[1]);
	mp::cpp_int b(argv[2]);

	std::vector<mp::cpp_int> mcd = algoritmo_extendido_euclides(a, b);

	std::cout << "El máximo comun divisor de " << a << " y " << b << " es " << mcd[0] << std::endl;
	std::cout << "u: " << mcd[1] << std::endl;
	std::cout << "v: " << mcd[2] << std::endl;

	std::cout << "Comprobación usando boost: " << mp::gcd(a, b) << std::endl;

}
