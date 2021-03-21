#include <boost/multiprecision/cpp_int.hpp>
#include <boost/integer/mod_inverse.hpp>

#include <iostream>
#include <vector>
#include "funciones.hpp"
#include <chrono>

int main(int argc, char ** argv) {

	if ( argc != 3 ) {
		std::cout << "Error: Ejecutar con dos parámetros <a> y <b>" << std::endl;
		exit(-1);
	}

	mp::cpp_int a(argv[1]);
	mp::cpp_int b(argv[2]);

	std::chrono::high_resolution_clock::time_point t_ini = std::chrono::high_resolution_clock::now();
	mp::cpp_int inverso = inverso_a(a, b);
	std::chrono::high_resolution_clock::time_point t_fin = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> duracion = std::chrono::duration_cast<std::chrono::duration<double>>(t_fin - t_ini);

	std::chrono::high_resolution_clock::time_point t_ini_b = std::chrono::high_resolution_clock::now();
	auto c_boost = boost::integer::mod_inverse(a, b);
	std::chrono::high_resolution_clock::time_point t_fin_b = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> duracion_b = std::chrono::duration_cast<std::chrono::duration<double>>(t_fin_b - t_ini_b);


	if ( inverso != -1) {
		std::cout << "El inverso de " << a << " módulo " << b << " es " << inverso << std::endl;
		std::cout << "Comprobación usando boost: " << c_boost << std::endl;
	} else {
		std::cout << "No existe el inverso de " << a << " módulo " << b << std::endl;
	}

	std::cout << "Tiempo de ejecucion de mi algoritmo: " << duracion.count() << " segundos " << std::endl;
	std::cout << "Tiempo de ejecucion de boost: " << duracion_b.count() << " segundos " << std::endl;


}
