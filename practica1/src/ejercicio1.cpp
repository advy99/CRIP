#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <vector>

using boost::multiprecision::cpp_int;


std::vector<cpp_int> algoritmo_extendido_euclides(cpp_int a, cpp_int b) {

	std::vector<cpp_int> resultado;

	if ( a == 0 && b == 0) {
		resultado.clear();
	} else {
		std::vector<cpp_int> s = {1, 0};
		std::vector<cpp_int> t = {0, 1};
		std::vector<cpp_int> a_b = {a, b};


		cpp_int q;

		while ( a_b[1] != 0 ) {
			q = a_b[0] / a_b[1];

			a_b = {a_b[1], a_b[0] - a_b[1] * q};
			s = {s[1], s[0] - s[1] * q};
			t = {t[1], t[0] - t[1] * q};

		}

		resultado = {a_b[0], s[0], t[0]};

	}

	return resultado;
}


int main(int argc, char ** argv) {

	if ( argc != 3 ) {
		std::cout << "Error: Ejecutar con dos parámetros <a> y <b>" << std::endl;
		exit(-1);
	}

	cpp_int a = atoi(argv[1]);
	cpp_int b = atoi(argv[2]);
	
	std::vector<cpp_int> mcd = algoritmo_extendido_euclides(a, b);

	std::cout << "El máximo comun divisor de " << a << " módulo " << b << " es " << mcd[0] << std::endl;
	std::cout << "u: " << mcd[1] << std::endl;
	std::cout << "v: " << mcd[2] << std::endl;

}
