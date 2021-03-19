#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <vector>
#include "funciones.hpp"

int main(int argc, char ** argv) {

	if ( argc <= 2 ) {
		std::cout << "Error: Ejecutar con un parametro <n> <grado0> <grado1> <grado2>" << std::endl;
		std::cout << "\t Este programa devuelve la factorización de n utilizando el método de rho de Pollard, con el polinomio pseudoaleatorio dado" << std::endl;
		std::cout << "\t El polinomio pseudoaleatorio dado se introduce por grados, por ejemplo , para introducir x^2 + 1, la secuencia sería 1, 0, 1" << std::endl;
		exit(-1);
	}

	mp::cpp_int n(argv[1]);

	std::vector<mp::cpp_int> g;

	for ( int i = 2; i < argc; i++) {
		g.push_back(mp::cpp_int(argv[i]));
	}

	std::cout << "Polinomio pseudoaleatorio introducido: " << std::endl;
	for (int i = g.size() - 1; i >= 1; i--) {
		if (g[i] != 0) {
			std::cout << g[i] << " * x^" << i << " + ";
		}
	}

	std::cout << g[0] << std::endl;


	if ( n % 2 == 0) {
		n++;
		std::cout << "AVISO: para aplicar la factorización a la Fermat el número tiene que ser impar, usaré: " << n << std::endl;
	}

	mp::cpp_int factorizacion = factorizacion_rho_pollard(n, g);


	std::cout << factorizacion << std::endl;

}
