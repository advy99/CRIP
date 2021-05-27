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

	if ( argc != 5 ) {
		std::cout << "Error: Ejecutar con tres parametros: <archivo_firmar> <archivo_llave_publica> <archivo_llave_privada> <archivo_almacenar_firma>" << std::endl;
		exit(-1);
	}

	std::ifstream leer_llave_publica;
	leer_llave_publica.open(argv[2]);

	std::ifstream leer_llave_privada;
	leer_llave_privada.open(argv[3]);

	mp::cpp_int n;
	mp::cpp_int d;

	leer_llave_publica >> n;
	leer_llave_privada >> d;

	std::ifstream f(argv[1]);
	std::string mensaje;

	if (f) {
		std::ostringstream ss;
		ss << f.rdbuf();
		mensaje = ss.str();
	}

	mp::cpp_int firma = firmar_mensaje_rsa(mensaje, n, d);

	std::ofstream salida_firma;
	salida_firma.open(argv[4]);

	salida_firma << firma << std::endl;

	return 0;
}
