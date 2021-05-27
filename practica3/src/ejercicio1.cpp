#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <vector>
#include "funciones.hpp"
#include <chrono>

// Algunos ejemplos:
//
// ➜ ./bin/ejercicio1 13 1010100100011
// Llave publica:
// 92627 32072 68013 67453 90667 56075 23392 2545 61496 26216 44414 16106 24194
// Llave privada:
// 17 20 56 110 206 429 857 1700 3408 6810 13615 27239 54473
// La llave privada generada es una secuencia super-creciente
//
// N: 108943
//
// U: 88758
// Mensaje cifrado: 294152
// Mensaje descifrado: 1010100100011
// Mensaje       dado: 1010100100011

//
// ➜ ./bin/ejercicio1 40 1110110101001110100101010101001010101110
// Llave publica:
// 4473189699524 10423627104734 8713986975589 13461015681038 13776301269429 2779836641716 3576194148362 8629636002410 3881149488714 10484401965341 11051408255332 10708173
// 129628 11498950583906 4407965099339 8077306345835 4759969310634 9519938621268 4416899444203 8833798888406 3044619978479 3599529392504 14394351472445 9460143023574 4297
// 308248815 8594616497630 12716043295736 10070484940296 2795889094346 7575257323762 7955221960087 9960006514964 1330076961455 3905009205137 10532121398187 8930975562495
// 5961076314570 3249612236017 10466182742174 10276345956155 2701379696680
// Llave privada:
// 17 20 56 110 206 429 857 1700 3408 6810 13615 27239 54473 108944 217895 435799 871598 1743196 3486392 6972784 13945552 27891115 55782235 111564470 223128940 446257863
// 892515733 1785031472 3570062945 7140125879 14280251755 28560503508 57121007024 114242014042 228484028100 456968056194 913936112391 1827872224784 3655744449570 73114888
// 99131
//
// La llave privada generada es una secuencia super-creciente
//
// N: 14622977798333
// U: 1983479135070
// Mensaje cifrado: 176821484615854
// Mensaje descifrado: 1110110101001110100101010101001010101110
// Mensaje       dado: 1110110101001110100101010101001010101110


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

	if ( comprobar_super_creciente(secuencia_llave_privada)) {
		std::cout << "La llave privada generada es una secuencia super-creciente" << std::endl;
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
