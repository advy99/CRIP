#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <vector>
#include "funciones.hpp"

int main(int argc, char ** argv) {

	if ( argc != 3 ) {
		std::cout << "Error: Ejecutar con dos parámetros <a> y <b>" << std::endl;
		exit(-1);
	}

	mp::cpp_int a(argv[1]);
	mp::cpp_int b(argv[2]);

	mp::cpp_int inverso = inverso_a(a, b);

	std::cout << "El inverso de " << a << " módulo " << b << " es " << inverso << std::endl;

}
