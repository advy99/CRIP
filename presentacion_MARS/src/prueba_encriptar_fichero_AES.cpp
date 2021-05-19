#include <iostream>
#include <fstream>
#include <iomanip>

#include "cryptopp/modes.h"
#include "cryptopp/aes.h"
#include "cryptopp/filters.h"
#include "cryptopp/files.h"
#include "cryptopp/osrng.h"

int main(int argc, char* argv[]) {

	if ( argc != 5 ) {
		std::cerr << "ERROR: Numero de parametros erroneo" << std::endl;
		std::cerr << "\tUso: <fichero_entrada> <ruta_salida> <clave> <vector_inicializacion>" << std::endl;

		exit(-1);
	}

	std::string string_clave = std::string(argv[3]);
	std::string string_vector_inicializacion = std::string(argv[4]);

	if ( string_clave.size() != CryptoPP::AES::DEFAULT_KEYLENGTH) {
		std::cerr << "ERROR: La clave tiene que ser de longitud " << CryptoPP::AES::DEFAULT_KEYLENGTH << std::endl;
		exit(-2);
	}

	if ( string_vector_inicializacion.size() != CryptoPP::AES::BLOCKSIZE) {
		std::cerr << "ERROR: El vector de inicialización tiene que ser de longitud " << CryptoPP::AES::BLOCKSIZE << std::endl;
		exit(-3);
	}


	// utilizaremos las longitudes de clave y bloque por defecto
	CryptoPP::SecByteBlock clave(reinterpret_cast<const unsigned char*>(string_clave.c_str()), CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::SecByteBlock vector_inicializacion(reinterpret_cast<const unsigned char*>(string_vector_inicializacion.c_str()), CryptoPP::AES::BLOCKSIZE);

	std::ifstream fichero_entrada( argv[1], std::ios::binary );
	std::ofstream salida( argv[2], std::ios::binary );

	std::vector<unsigned char> buffer_entrada(std::istreambuf_iterator<char>(fichero_entrada), {});


	// creamos la instancia de AES para encriptar y el modo de operación, en este caso CBC
	CryptoPP::AES::Encryption encriptacion_aes(clave, clave.size());

	// inicializamos el modo de operación con el algoritmo AES y el vector de inicialización que hemos generado
	CryptoPP::CBC_Mode_ExternalCipher::Encryption encriptado_cbc( encriptacion_aes, vector_inicializacion );


	auto tiempo_inicio = std::chrono::high_resolution_clock::now();

	// creamos un flujo entre la instancia de CBC y el texto cifrado
	CryptoPP::StreamTransformationFilter stfEncryptor(encriptado_cbc, new CryptoPP::FileSink( salida ) );
	stfEncryptor.Put( reinterpret_cast<const unsigned char*>( buffer_entrada.data() ), buffer_entrada.size() );
	stfEncryptor.MessageEnd();

	auto tiempo_fin = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> t_ejecucion = std::chrono::duration_cast<std::chrono::microseconds>(tiempo_fin - tiempo_inicio);

	std::cout << "Fichero " << argv[1] << " cifrado con AES en " << argv[2] << std::endl;
	std::cout << "Se han tardado " << t_ejecucion.count() << " en encriptar" << std::endl;

	return 0;
}
