#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
#include <iostream>
#include <bit>
#include <vector>
#include <ctime>
#include <set>
#include <chrono>

#include "funciones.hpp"

int main ( int argc, char ** argv) {

	if ( argc != 2 ) {
		std::cerr << "ERROR: Se necesita un parametro" << std::endl;
		exit(-1);
	}

	mp::cpp_int num(argv[1]);

	std::chrono::high_resolution_clock::time_point t_ini = std::chrono::high_resolution_clock::now();
	bool resultado = es_primo(num);
	std::chrono::high_resolution_clock::time_point t_fin = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> duracion = std::chrono::duration_cast<std::chrono::duration<double>>(t_fin - t_ini);


	std::chrono::high_resolution_clock::time_point t_ini_b = std::chrono::high_resolution_clock::now();
	auto c_boost = mp::miller_rabin_test(num, 10);
	std::chrono::high_resolution_clock::time_point t_fin_b = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> duracion_b = std::chrono::duration_cast<std::chrono::duration<double>>(t_fin_b - t_ini_b);


	if ( resultado ) {
		std::cout << num << " es primo" << std::endl;
	} else {
		std::cout << num << " no es primo" << std::endl;
	}

	std::cout << "El siguiente primo es " << siguiente_primo(num) << std::endl << std::endl;


	std::cout << "Comprobación usando boost: " << std::endl;
	if ( c_boost ) {
		std::cout << num << " es primo" << std::endl;
	} else {
		std::cout << num << " no es primo" << std::endl;
	}


	std::cout << "Tiempo de ejecucion de mi algoritmo: " << duracion.count() << " segundos " << std::endl;
	std::cout << "Tiempo de ejecucion de boost: " << duracion_b.count() << " segundos " << std::endl;

}
