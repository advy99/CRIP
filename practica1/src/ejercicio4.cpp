#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
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

	std::cout << "El siguiente primo es " << siguiente_primo(num) << std::endl << std::endl;


	std::cout << "Comprobación usando boost: " << std::endl;
	if ( mp::miller_rabin_test(num, 10) ) {
		std::cout << num << " es primo" << std::endl;
	} else {
		std::cout << num << " no es primo" << std::endl;
	}


}
