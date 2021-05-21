#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <vector>
#include "funciones.hpp"
#include "funciones_p1.hpp"
#include <boost/integer/mod_inverse.hpp>

#include <chrono>


int main(int argc, char ** argv) {

	if ( argc != 4 ) {
		std::cout << "Error: Ejecutar con un parametro: <numero> <numero> <numero_RSA>" << std::endl;
		exit(-1);
	}

	mp::cpp_int primera_entrada = mp::cpp_int(argv[1]);
	mp::cpp_int segunda_entrada = mp::cpp_int(argv[2]);
	mp::cpp_int numero_RSA = mp::cpp_int(argv[3]);



	mp::cpp_int p = siguiente_primo(primera_entrada);
	mp::cpp_int q = siguiente_primo(segunda_entrada);

	mp::cpp_int n = p * q;

	mp::cpp_int e = 2;

	mp::cpp_int phi_n = (p - 1) * (q - 1);

	// escogemos un e que sea primo relativo a phi_n
	while ( mp::gcd(e, phi_n) != 1 ) {
		e++;
	}

	std::cout << "p = " << p << std::endl;
	std::cout << "q = " << q << std::endl;
	std::cout << "n = " << n << std::endl;
	std::cout << "phi_n = " << phi_n << std::endl;
	std::cout << "e = " << e << std::endl;


	// ya tenemos la clave publica (n, e)

	// sabemos que d  tiene que ser el inverso de e modulo n
	mp::cpp_int d = inverso_a(e, phi_n);

	std::cout << "d = " << d << std::endl;

	// Ya tenemos la d

	// con RSA, sabemos que si queremos cifrar un mensaje m,
	// el mensaje cifrado c = m^e
	// mientras que para descifrar un mensaje cifrado c,
	// c^d = m

	mp::cpp_int m = mp::powm(numero_RSA, d, n);

	std::cout << "El mensaje es : " << m << std::endl;
	std::cout << "Comprobación: " << std::endl;
	std::cout << "Mensaje cifrado con el resultado^e (ciframos con RSA el mensaje) = " << mp::powm(m, e, n) << std::endl;
	std::cout << "Mensaje cifrado original: " << numero_RSA << std::endl;

	return 0;
}
