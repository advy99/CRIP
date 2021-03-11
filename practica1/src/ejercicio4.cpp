#include <boost/multiprecision/cpp_int.hpp>

#include <iostream>
#include <bit>
#include <vector>
#include <ctime>
#include <set>

#include "funciones.hpp"

int main ( int argc, char ** argv) {

	if ( argc != 2 ) {
		std::cerr << "ERROR: Se necesita un parametro" << std::endl;
		exit(-1);
	}

	mp::cpp_int num(argv[1]);


	if ( es_primo(num) ) {
		std::cout << num << " es primo" << std::endl;
	} else {
		std::cout << num << " no es primo" << std::endl;
	}

	std::cout << "El siguiente primo es " << siguiente_primo(num) << std::endl;


}
