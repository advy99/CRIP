#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <vector>
#include "funciones.hpp"
#include "funciones_p1.hpp"
#include <boost/integer/mod_inverse.hpp>

#include <chrono>

// Ejecucion ejercicio 6
// ➜ ./bin/ejercicio6 50000000385000000551 5 10000000074000000101
// p = 5000000029
//
// q = 10000000019
// 50000000385000000551 = 5000000029 * 10000000019
// Comprobación:
// n   = 50000000385000000551
// p*q = 50000000385000000551


// Similitudes con Miller-Rabin:
// Basicamente toma la idea de encontrar un z != 1, que z^2 sea 1,
// al igual que en miller Rabin, estamos buscando las raices en Z_n
// Por el mismo motivo que miller rabin este algoritmo no es determinista

// Con respecto al ejercicio 3, estamos haciendo lo mismo , buscando las raices
// de Z_n, solo que en este caso ya sabemos que x^2 = y^2, luego (x + y)(x - y) = 0 en Z_n,
// luego gcd(x - y, n) y gcd(x - (n - y), n) p y q, una factorización de n.

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

	std::cout << "p = " << p << std::endl;
	std::cout << "q = " << q << std::endl;

	std::cout << n << " = " << p  << " * " << q << std::endl;

	std::cout << "Comprobación:" << std::endl;
	std::cout << "n   = " << n << std::endl;
	std::cout << "p*q = " << p * q << std::endl;

	return 0;
}
