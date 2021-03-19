#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <vector>
#include "funciones.hpp"

int main(int argc, char ** argv) {

	if ( argc != 2 ) {
		std::cout << "Error: Ejecutar con un parametro <n>" << std::endl;
		std::cout << "\t Este programa devuelve la factorización de n utilizando el método de Fermat" << std::endl;
		exit(-1);
	}

	mp::cpp_int n(argv[1]);

	if ( n % 2 == 0) {
		n++;
		std::cout << "AVISO: para aplicar la factorización a la Fermat el número tiene que ser impar, usaré: " << n << std::endl;
	}

	std::pair<mp::cpp_int, mp::cpp_int> factorizacion = factorizacion_fermat(n);

	std::cout << n << " lo podemos expresar como (" << factorizacion.first << " + " << factorizacion.second << ") * (" << factorizacion.first << " - " << factorizacion.second << ")"  << std::endl;
	std::cout << "Comprobacion: " << (factorizacion.first + factorizacion.second) * (factorizacion.first - factorizacion.second) << std::endl;

}
