#include <boost/multiprecision/cpp_int.hpp>

#include <iostream>
#include "funciones.hpp"


int main(int argc, char ** argv) {
	if ( argc != 3 ) {
		std::cerr << "ERROR: Se necesitan dos parametros:"
					 << "\tUso: " << argv[0] << " <a> <p> " << std::endl
					 << "\t Este programa calcula la raiz cuadrada modular de a y p" << std::endl;

		exit(-1);
	}

	mp::cpp_int a(argv[1]);
	mp::cpp_int p (argv[2]);

	mp::cpp_int resultado = raiz_cuadrada_mod(a, p);

	if ( resultado != -1 ){
		std::cout << "La raiz cuadrada de " << a << " modulo " << p << " es : " << resultado << std::endl;
	} else {
		std::cout << a << " no tiene raiz cuadrada modulo " << p << std::endl;
	}

}
