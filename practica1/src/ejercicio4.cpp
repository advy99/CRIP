#include <boost/multiprecision/cpp_int.hpp>

#include <iostream>
#include <bit>
#include <vector>
#include <ctime>
#include <set>

namespace mp = boost::multiprecision;

bool test_miller_rabin(mp::cpp_int numero) {
	bool resultado = false;

	if ( numero <= 5 ) {
		resultado = numero == 2 || numero == 3 || numero == 5;
	} else {
		// es par
		if ( (numero & 1 ) == 0 ) {
			resultado = false;
		} else {

			mp::cpp_int s = numero - 1;
			mp::cpp_int exponente_n = 0;


			while ( s % 2 == 0 ) {
				exponente_n++;
				s >>= 1;
			}


			std::srand(std::time(nullptr));
			mp::cpp_int a;
			a = (2 + mp::cpp_int(std::rand()) % (numero - 1) ); // para que sea 2 < a < p-1
			mp::cpp_int nuevo_elemento;

			a = mp::powm(a, s, numero);

			if ( a == 1 || a == numero - 1) {
				return true;
			}

			for ( mp::cpp_int i = 1; i < exponente_n; i++ ) {
				//nuevo_elemento = mp::powm(a, s * mp::powm(mp::cpp_int(2), i, numero), numero);
				a = mp::powm(a, 2, numero);

				// si a = -1, (en mod numero , pues numero - 1)
				if ( a == numero - 1 ) {
					return true;
				}

				if ( a == 1) {
					return false;
				}
			}

		}

		return false;
	}
	
	return resultado;
}


bool es_primo(mp::cpp_int numero, int num_veces = 10) {
	bool resultado = true;

	int i = 0;
	while (i < num_veces && resultado) {
		resultado = resultado && test_miller_rabin(numero);
		i++;
	}

	return resultado;

}

mp::cpp_int siguiente_primo(mp::cpp_int numero) {
	if ( numero % 2 == 0 ) {
		numero += 1;
	}

	do {
		numero += 2;
	} while (!es_primo(numero));

	return numero;

}


int main ( int argc, char ** argv) {

	if ( argc != 2 ) {
		std::cerr << "ERROR: Se necesita un parametro" << std::endl;
		exit(-1);
	}

	mp::cpp_int num(argv[1]);


	if ( es_primo(num) ) {
		std::cout << num << " es primo" << std::endl;
	} else {
		std::cout << num << " no es primo" << std::endl;
	}

	std::cout << "El siguiente primo es " << siguiente_primo(num) << std::endl;


}

