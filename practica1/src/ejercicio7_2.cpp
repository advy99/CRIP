#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <vector>
#include "funciones.hpp"

int main(int argc, char ** argv) {

	if ( argc != 2 ) {
		std::cout << "Error: Ejecutar con un parametro <n>" << std::endl;
		std::cout << "\t Este programa devuelve la factorización de n utilizando el método de rho de Pollard" << std::endl;
		exit(-1);
	}

	mp::cpp_int n(argv[1]);

	if ( n % 2 == 0) {
		n++;
		std::cout << "AVISO: para aplicar la factorización a la Fermat el número tiene que ser impar, usaré: " << n << std::endl;
	}

	mp::cpp_int factorizacion = factorizacion_rho_pollard(n);


	std::cout << factorizacion << std::endl;

}
