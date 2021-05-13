#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <vector>
#include "funciones.hpp"
#include <chrono>


int main(int argc, char ** argv) {

	if ( argc != 3 ) {
		std::cout << "Error: Ejecutar con un parametro: <longitud_llave> <mensaje_cifrar>" << std::endl;
		exit(-1);
	}

	unsigned longitud = atoi(argv[1]);
	std::string string_mensaje(argv[2]);

	if ( longitud != string_mensaje.size() ) {
		std::cout << "Error: El mensaje y la longitud de clave tienen que ser iguales." << std::endl
					 << "\t Tamaños dados: " << longitud << " y " << string_mensaje.size() << std::endl;
		exit(-2);
	}

	auto resultado = generar_llaves(longitud);

	std::vector<mp::cpp_int> llave_publica = resultado.first;

	std::cout << "Llave publica: " << std::endl;

	for (unsigned i = 0; i < llave_publica.size(); i++) {
		std::cout << llave_publica[i] << " ";
	}
	std::cout << std::endl;


	auto llave_privada = resultado.second;

	auto secuencia_llave_privada = std::get<0>(llave_privada);
	auto n_llave_privada = std::get<1>(llave_privada);
	auto u_llave_privada = std::get<2>(llave_privada);

	std::cout << "Llave privada: " << std::endl;

	for (unsigned i = 0; i < secuencia_llave_privada.size(); i++) {
		std::cout << secuencia_llave_privada[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "N: " << n_llave_privada << std::endl;
	std::cout << "U: " << u_llave_privada << std::endl;

	std::vector<bool> mensaje_cifrar;

	mensaje_cifrar.resize(string_mensaje.size());

	for(unsigned i = 0; i < string_mensaje.size(); i++) {
		// si está puesto a uno, lo ponemos true, si no false
		mensaje_cifrar[i] = string_mensaje[i] - '0' == 1;
	}

	mp::cpp_int mensaje_cifrado = cifrar_secuencia_bits(mensaje_cifrar, llave_publica);

	std::cout << "Mensaje cifrado: " << mensaje_cifrado << std::endl;

	std::vector<bool> mensaje_descifrado = descifrar(mensaje_cifrado, llave_privada);

	std::cout << "Mensaje descifrado: ";
	for ( unsigned i = 0; i < mensaje_descifrado.size(); i++) {
		std::cout << mensaje_descifrado[i];
	}
	std::cout << std::endl;
	std::cout << "Mensaje       dado: " << string_mensaje << std::endl;


}
