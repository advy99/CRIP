#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <vector>
#include "funciones.hpp"
#include "funciones_p1.hpp"

#include <chrono>


int main(int argc, char ** argv) {

	if ( argc != 3 ) {
		std::cout << "Error: Ejecutar con dos parametros: <numero> <numero> " << std::endl;
		exit(-1);
	}

	mp::cpp_int numero = mp::cpp_int(argv[1]);
	mp::cpp_int numero_a_invertir = mp::cpp_int(argv[2]);


	mp::cpp_int primo_mayor_numero = numero;

	do {
		primo_mayor_numero = siguiente_primo(primo_mayor_numero);
	} while( !es_primo((primo_mayor_numero - 1) / 2) );

	std::cout << "Utilizaré el primo: " << primo_mayor_numero << std::endl;

	mp::cpp_int elemento_primitivo = encontrar_elemento_primitivo(primo_mayor_numero);

	std::cout << "Un elemento primitivo de Z_" << primo_mayor_numero << " es " << elemento_primitivo << std::endl;

	mp::cpp_int x = logaritmo_discreto(elemento_primitivo, numero_a_invertir, primo_mayor_numero);
	std::cout << "El x tal que " << elemento_primitivo << "^x en Z_" << primo_mayor_numero << " = " << numero_a_invertir << " es " << x << std::endl;

	std::cout << "Comprobación:" << std::endl;

	mp::cpp_int alfa_elevado_x = mp::powm(elemento_primitivo, x, primo_mayor_numero);
	std::cout << "Fecha introducida: " << numero_a_invertir << std::endl;
	std::cout << "Valor calculado con alpha ^ x: " << alfa_elevado_x << std::endl;

	return 0;
}
