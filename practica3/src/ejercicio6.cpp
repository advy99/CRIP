#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <vector>
#include "funciones.hpp"
#include "funciones_p1.hpp"
#include <boost/integer/mod_inverse.hpp>

#include <chrono>


int main(int argc, char ** argv) {

	if ( argc != 4 ) {
		std::cout << "Error: Ejecutar con un parametro: <n> <e> <d>" << std::endl;
		exit(-1);
	}

	mp::cpp_int n = mp::cpp_int(argv[1]);
	mp::cpp_int e = mp::cpp_int(argv[2]);
	mp::cpp_int d = mp::cpp_int(argv[3]);


	auto p_q = obtener_p_q_RSA(n, e, d);

	mp::cpp_int p = p_q.first;
	mp::cpp_int q = p_q.second;

	std::cout << n << " = " << p  << " * " << q << std::endl;

	std::cout << "Comprobación:" << std::endl;
	std::cout << "n = " << n << std::endl;
	std::cout << "p*q = " << p * q << std::endl;

	return 0;
}
