#include <boost/multiprecision/cpp_int.hpp>

#include <iostream>
#include "funciones.hpp"
#include <chrono>


int main(int argc, char ** argv) {
	if ( argc != 4 ) {
		std::cerr << "ERROR: Se necesitan tres parametros:"
					 << "\tUso: " << argv[0] << " <a> <p> <q> " << std::endl
					 << "\t Este programa calcula la raiz cuadrada modular de a y p" << std::endl;

		exit(-1);
	}

	mp::cpp_int a(argv[1]);
	mp::cpp_int p (argv[2]);
	mp::cpp_int q (argv[3]);

	if ( !es_primo(p) ){
		p = siguiente_primo(p);
		std::cout << "Aviso: El número " << argv[2] << " no es primo, utilizaré el siguiente primo: " << p << std::endl;
	}

	if ( !es_primo(q) ){
		q = siguiente_primo(q);
		std::cout << "Aviso: El número " << argv[3] << "  no es primo, utilizaré el siguiente primo: " << q << std::endl;
	}

	std::chrono::high_resolution_clock::time_point t_ini = std::chrono::high_resolution_clock::now();
	std::set<mp::cpp_int> resultado = raices_cuadradas_p_q(a, p, q);
	std::chrono::high_resolution_clock::time_point t_fin = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> duracion = std::chrono::duration_cast<std::chrono::duration<double>>(t_fin - t_ini);

	std::cout << "Las raices cuadradas de " << a << " mod " << p * q << " son :" << std::endl;

	for ( auto it = resultado.begin(); it != resultado.end(); ++it) {
		std::cout << (*it);
		std::cout << "\t Comprobacion (usando powm): " << (*it) << "^2 mod " << p*q << " = " << mp::powm(*it, 2, p*q) << std::endl;
	}

	std::cout << "Tiempo de ejecucion de mi algoritmo: " << duracion.count() << " segundos " << std::endl;

}
