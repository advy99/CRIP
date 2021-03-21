#include <boost/multiprecision/cpp_int.hpp>

#include <iostream>
#include "funciones.hpp"
#include <chrono>

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

	if ( c > primo ) {
		std::cout << "Aviso: " << c << " no está en Z_" << primo << ", utilizaré " << c << " mod " << primo << " = ";
		c = c % primo;
		std::cout << c << std::endl;
	}

	std::chrono::high_resolution_clock::time_point t_ini = std::chrono::high_resolution_clock::now();
	mp::cpp_int val_log = logaritmo_discreto(a, c, primo);
	std::chrono::high_resolution_clock::time_point t_fin = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> duracion = std::chrono::duration_cast<std::chrono::duration<double>>(t_fin - t_ini);


	if ( val_log == -1 ) {
		std::cerr << "No existe b tal que " << a << " ^b = " << c << " en Z_"<< primo << std::endl;
	} else {
		std::cout << a << " ^ " << val_log << " = " << c << " en Z_"<< primo << std::endl;
		std::cout << "Comprobacion: " << mp::powm(a, val_log, primo) << std::endl;
	}

	std::cout << "Tiempo de ejecucion de mi algoritmo: " << duracion.count() << " segundos " << std::endl;


}
