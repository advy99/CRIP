#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <vector>

using boost::multiprecision::cpp_int;


cpp_int inverso_a(cpp_int a, cpp_int b) {

	cpp_int resultado;

	if ( a == 0 && b == 0) {
		resultado = -1;
	} else {
		std::vector<cpp_int> s = {1, 0};
		std::vector<cpp_int> a_b = {a, b};


		cpp_int q;

		while ( a_b[1] != 0 ) {
			q = a_b[0] / a_b[1];

			a_b = {a_b[1], a_b[0] - a_b[1] * q};
			s = {s[1], s[0] - s[1] * q};
		}

		if ( a_b[0] != 1 ) {
			resultado = -1;
		} else {
			resultado = s[0] % b;
		}
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
	
	cpp_int inverso = inverso_a(a, b);

	std::cout << "El inverso de " << a << " módulo " << b << " es " << inverso << std::endl;

}
