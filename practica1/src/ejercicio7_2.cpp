#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <vector>
#include "funciones.hpp"

int main(int argc, char ** argv) {

	if ( argc <= 2 ) {
		std::cout << "Error: Ejecutar con un parametro <n>" << std::endl;
		std::cout << "\t Este programa devuelve la factorización de n utilizando el método de rho de Pollard" << std::endl;
		exit(-1);
	}

	mp::cpp_int n(argv[1]);
	mp::cpp_int q(argv[2]);
	n = n * q;

	if ( n % 2 == 0) {
		n++;
		std::cout << "AVISO: para aplicar la factorización de rho de pollard el número tiene que ser impar, usaré: " << n << std::endl;
	}

	mp::cpp_int factorizacion = factorizacion_rho_pollard(n, 1);

	// como hace gap
	mp::cpp_int i = 2;
	while (factorizacion == -1 && i != 9000) {
		factorizacion = factorizacion_rho_pollard(n, i);
		i++;
	}

	if ( factorizacion != -1 ){
		std::cout << "Un factor no trivial de " << n << " es " << factorizacion << std::endl;
	} else {
		std::cout << "No se ha encontrado un factor no trivial de " << n << std::endl;

	}

}
