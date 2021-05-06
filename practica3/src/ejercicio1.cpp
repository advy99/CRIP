#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <vector>
#include "funciones.hpp"
#include <chrono>


int main(int argc, char ** argv) {

	if ( argc != 2 ) {
		std::cout << "Error: Ejecutar con un parametro: <longitud_llave>" << std::endl;
		exit(-1);
	}

	int longitud = atoi(argv[1]);

	auto resultado = funcion_mochila(longitud);

	std::vector<mp::cpp_int> llave_publica = resultado.first;

	std::cout << "Llave publica: " << std::endl;

	for (unsigned i = 0; i < llave_publica.size(); i++) {
		std::cout << llave_publica[i] << " ";
	}
	std::cout << std::endl;


	auto llave_privada = resultado.second;

	auto secuencia_llave_privada = std::get<0>(llave_privada);
	auto n_llave_privada = std::get<1>(llave_privada);
	auto u_llave_privada = std::get<2>(llave_privada);

	std::cout << "Llave privada: " << std::endl;

	for (unsigned i = 0; i < secuencia_llave_privada.size(); i++) {
		std::cout << secuencia_llave_privada[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "N: " << n_llave_privada << std::endl;
	std::cout << "U: " << u_llave_privada << std::endl;

}
