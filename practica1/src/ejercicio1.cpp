#include <boost/multiprecision/cpp_int.hpp>
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
	std::vector<mp::cpp_int> mcd = algoritmo_extendido_euclides(a, b);
	std::chrono::high_resolution_clock::time_point t_fin = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> duracion = std::chrono::duration_cast<std::chrono::duration<double>>(t_fin - t_ini);


	std::cout << "El máximo comun divisor de " << a << " y " << b << " es " << mcd[0] << std::endl;
	std::cout << "u: " << mcd[1] << std::endl;
	std::cout << "v: " << mcd[2] << std::endl;

	std::chrono::high_resolution_clock::time_point t_ini_b = std::chrono::high_resolution_clock::now();
	mp::cpp_int gcd_boost = mp::gcd(a, b);
	std::chrono::high_resolution_clock::time_point t_fin_b = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> duracion_b = std::chrono::duration_cast<std::chrono::duration<double>>(t_fin_b - t_ini_b);


	std::cout << "Comprobación usando boost: " << gcd_boost << std::endl;

	std::cout << "Tiempo de ejecucion de mi algoritmo: " << duracion.count() << " segundos " << std::endl;
	std::cout << "Tiempo de ejecucion del algoritmo de boost: " << duracion_b.count() << " segundos " << std::endl;



}
