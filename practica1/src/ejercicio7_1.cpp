#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <vector>
#include "funciones.hpp"
#include <chrono>

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

	std::chrono::high_resolution_clock::time_point t_ini = std::chrono::high_resolution_clock::now();
	std::pair<mp::cpp_int, mp::cpp_int> factorizacion = factorizacion_fermat(n);
	std::chrono::high_resolution_clock::time_point t_fin = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> duracion = std::chrono::duration_cast<std::chrono::duration<double>>(t_fin - t_ini);


	std::cout << n << " lo podemos expresar como (" << factorizacion.first << " + " << factorizacion.second << ") * (" << factorizacion.first << " - " << factorizacion.second << ")"  << std::endl;
	std::cout << "Comprobacion: " << (factorizacion.first + factorizacion.second) * (factorizacion.first - factorizacion.second) << std::endl;

	std::cout << "Tiempo de ejecucion de mi algoritmo: " << duracion.count() << " segundos " << std::endl;

}
