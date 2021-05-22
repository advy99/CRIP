#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <fstream>

#include <vector>
#include "funciones.hpp"
#include "funciones_p1.hpp"
#include <boost/integer/mod_inverse.hpp>

#include <chrono>


int main(int argc, char ** argv) {

	if ( argc != 3 ) {
		std::cout << "Error: Ejecutar con dos parametros: <salida_llave_publica> <salida_llave_privada>" << std::endl;
		exit(-1);
	}

	auto claves =  generar_claves_RSA_aleatorias();

	std::ofstream salida_clave_publica;
	salida_clave_publica.open(argv[1]);

	salida_clave_publica << claves.first.first << std::endl << claves.first.second << std::endl;

	std::ofstream salida_clave_privada;
	salida_clave_privada.open(argv[2]);
	salida_clave_privada << claves.second << std::endl;


	return 0;
}
