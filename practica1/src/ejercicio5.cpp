#include <boost/multiprecision/cpp_int.hpp>

#include <iostream>
#include "funciones.hpp"


int main ( int argc, char ** argv ) {

	if ( argc != 4 ) {
		std::cerr << "ERROR: Se necesitan tres parametros:"
					 << "\tUso: " << argv[0] << " <base> <valor> <primo>" << std::endl
					 << "\t Este programa calcula el exponente al que elevar la base para que de el valor en Z_primo" << std::endl;

		exit(-1);
	}

	mp::cpp_int a(argv[1]);
	mp::cpp_int c(argv[2]);
	mp::cpp_int primo(argv[3]);

	if ( !es_primo(primo) ) {
		primo = siguiente_primo(primo);
		std::cerr << "AVISO: El numero primo dado no es primo, utilizando el siguiente primo: " << primo << std::endl;
	}

	mp::cpp_int val_log = logaritmo_discreto(a, c, primo);

	if ( val_log == -1 ) {
		std::cerr << "No existe b tal que " << a << " ^b = " << c << " en Z_"<< primo << std::endl;
	} else {
		std::cerr << a << " ^ " << val_log << " = " << c << " en Z_"<< primo << std::endl;
	}

}
