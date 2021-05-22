#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include "funciones.hpp"
#include "funciones_p1.hpp"
#include <boost/integer/mod_inverse.hpp>

#include <chrono>


int main(int argc, char ** argv) {

	if ( argc != 4 ) {
		std::cout << "Error: Ejecutar con tres parametros: <fichero_mensaje> <fichero_firma> <ficher_llave_publica>" << std::endl;
		exit(-1);
	}

	std::ifstream leer_mensaje;
	leer_mensaje.open(argv[1]);

	std::string mensaje;

	if (leer_mensaje) {
		std::ostringstream ss;
		ss << leer_mensaje.rdbuf();
		mensaje = ss.str();
	}

	std::ifstream leer_firma;
	leer_firma.open(argv[2]);

	mp::cpp_int firma;

	leer_firma >> firma;

	std::ifstream leer_llave_publica;
	leer_llave_publica.open(argv[3]);

	mp::cpp_int n;
	mp::cpp_int e;

	leer_llave_publica >> n;
	leer_llave_publica >> e;


	if ( verificar_firma(mensaje, firma, std::make_pair(n, e) ) ) {
		std::cout << "El mensaje almacenado en " << argv[1] << " corresponde con la firma almacenada en " << argv[2] << std::endl;
	} else {
		std::cout << "AVISO: El mensaje almacenado en " << argv[1] << " NO corresponde con la firma almacenada en " << argv[2] << std::endl;
	}


	return 0;
}
