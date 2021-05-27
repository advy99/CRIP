#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <vector>
#include "funciones.hpp"
#include "funciones_p1.hpp"

#include <chrono>

// Ejemplo de ejecucion
// ➜ ./bin/ejercicio3 48478872564493742276963 12 37659670402359614687722
// p = 159497098847
// q = 303948303229
// p * q = 48478872564493742276963
//
// n introducido = 48478872564493742276963

int main(int argc, char ** argv) {

	if ( argc != 4 ) {
		std::cout << "Error: Ejecutar con dos parametros: <n> <x> <y> " << std::endl;
		exit(-1);
	}

	mp::cpp_int n = mp::cpp_int(argv[1]);
	mp::cpp_int x = mp::cpp_int(argv[2]);
	mp::cpp_int y = mp::cpp_int(argv[3]);

	if ( mp::powm(x, 2, n) != mp::powm(y, 2, n)) {
		std::cerr << "Error: La funcion de rabin para las dos entradas x e y dadas no tienen la misma salida mod n" << std::endl;
		exit(-2);
	}


	mp::cpp_int p = mp::gcd(x - y, n);
	mp::cpp_int q = mp::gcd(x - (n - y), n);

	std::cout << "p = " << p << std::endl;
	std::cout << "q = " << q << std::endl;

	std::cout << "p * q = " << p * q << std::endl;
	std::cout << "n introducido = " << n << std::endl;

	return 0;
}
