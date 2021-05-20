#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <vector>
#include "funciones.hpp"
#include "funciones_p1.hpp"

#include <chrono>


int main(int argc, char ** argv) {

	if ( argc != 2 ) {
		std::cout << "Error: Ejecutar con un parametro: <numero> " << std::endl;
		exit(-1);
	}

	mp::cpp_int numero = mp::cpp_int(argv[1]);

	mp::cpp_int primo_mayor_numero = numero;

	do {
		primo_mayor_numero = siguiente_primo(primo_mayor_numero);
	} while( !es_primo((primo_mayor_numero - 1) / 2) );

	std::cout << "Utilizaré el primo: " << primo_mayor_numero << std::endl;

	mp::cpp_int elemento_primitivo = encontrar_elemento_primitivo(primo_mayor_numero);

	std::cout << "Un elemento primitivo de Z_" << primo_mayor_numero << " es " << elemento_primitivo << std::endl;


	return 0;
}
