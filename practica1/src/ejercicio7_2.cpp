#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <vector>
#include "funciones.hpp"
#include <chrono>

int main(int argc, char ** argv) {

	if ( argc != 2 ) {
		std::cout << "Error: Ejecutar con un parametro <n>" << std::endl;
		std::cout << "\t Este programa devuelve la factorización de n utilizando el método de rho de Pollard" << std::endl;
		exit(-1);
	}

	mp::cpp_int n(argv[1]);

	if ( n % 2 == 0) {
		n++;
		std::cout << "AVISO: para aplicar la factorización de rho de pollard el número tiene que ser impar, usaré: " << n << std::endl;
	}

	std::chrono::high_resolution_clock::time_point t_ini = std::chrono::high_resolution_clock::now();
	mp::cpp_int factorizacion = factorizacion_rho_pollard(n, 1);
	std::chrono::high_resolution_clock::time_point t_fin = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> duracion = std::chrono::duration_cast<std::chrono::duration<double>>(t_fin - t_ini);


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

	std::cout << "Tiempo de ejecucion de mi algoritmo: " << duracion.count() << " segundos " << std::endl;


}
