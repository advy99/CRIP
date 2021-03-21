#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <bit>
#include <vector>
#include <chrono>

#include "funciones.hpp"

int main ( int argc, char ** argv) {

	if ( argc != 4 ) {
		std::cerr << "ERROR: Se necesitan tres parametro: base, exponente, modulo" << std::endl;
		exit(-1);
	}

	mp::cpp_int base(argv[1]);
	mp::cpp_int exponente(argv[2]);
	mp::cpp_int modulo(argv[3]);

	std::chrono::high_resolution_clock::time_point t_ini = std::chrono::high_resolution_clock::now();
	mp::cpp_int resultado = pow_mod(base, exponente, modulo);
	std::chrono::high_resolution_clock::time_point t_fin = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> duracion = std::chrono::duration_cast<std::chrono::duration<double>>(t_fin - t_ini);


	std::chrono::high_resolution_clock::time_point t_ini_b = std::chrono::high_resolution_clock::now();
	auto c_boost = mp::powm(base, exponente, modulo);
	std::chrono::high_resolution_clock::time_point t_fin_b = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> duracion_b = std::chrono::duration_cast<std::chrono::duration<double>>(t_fin_b - t_ini_b);

	std::cout << base << " elevado a " << exponente << " modulo " << modulo << " es " << resultado << std::endl;

	std::cout << "Comprobacion (utilizando powm): " << base << " elevado a " << exponente << " modulo " << modulo << " es " << c_boost << std::endl;

	std::cout << "Tiempo de ejecucion de mi algoritmo: " << duracion.count() << " segundos " << std::endl;
	std::cout << "Tiempo de ejecucion de boost: " << duracion_b.count() << " segundos " << std::endl;



}
