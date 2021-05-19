#include <iostream>
#include <fstream>
#include <iomanip>

#include "cryptopp/modes.h"
#include "cryptopp/mars.h"
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

	if ( string_clave.size() != CryptoPP::MARS::DEFAULT_KEYLENGTH) {
		std::cerr << "ERROR: La clave tiene que ser de longitud " << CryptoPP::MARS::DEFAULT_KEYLENGTH << std::endl;
		exit(-2);
	}

	if ( string_vector_inicializacion.size() != CryptoPP::MARS::BLOCKSIZE) {
		std::cerr << "ERROR: El vector de inicialización tiene que ser de longitud " << CryptoPP::MARS::BLOCKSIZE << std::endl;
		exit(-3);
	}


	// utilizaremos las longitudes de clave y bloque por defecto
	CryptoPP::SecByteBlock clave(reinterpret_cast<const unsigned char*>(string_clave.c_str()), CryptoPP::MARS::DEFAULT_KEYLENGTH);
	CryptoPP::SecByteBlock vector_inicializacion(reinterpret_cast<const unsigned char*>(string_vector_inicializacion.c_str()), CryptoPP::MARS::BLOCKSIZE);

	std::ifstream fichero_entrada( argv[1], std::ios::binary );
	std::ofstream salida( argv[2], std::ios::binary );

	std::vector<unsigned char> buffer_entrada(std::istreambuf_iterator<char>(fichero_entrada), {});


	// creamos la instancia de MARS para encriptar y el modo de operación, en este caso CBC
	CryptoPP::MARS::Decryption desencriptado_mars(clave, clave.size());

	CryptoPP::CBC_Mode_ExternalCipher::Decryption desencriptado_cbc( desencriptado_mars, vector_inicializacion );

	auto tiempo_inicio = std::chrono::high_resolution_clock::now();

	CryptoPP::StreamTransformationFilter stfDecryptor(desencriptado_cbc, new CryptoPP::FileSink( salida ) );
	stfDecryptor.Put( reinterpret_cast<const unsigned char*>( buffer_entrada.data() ), buffer_entrada.size() );
	stfDecryptor.MessageEnd();


	auto tiempo_fin = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> t_ejecucion = std::chrono::duration_cast<std::chrono::microseconds>(tiempo_fin - tiempo_inicio);


	std::cout << "Fichero " << argv[1] << " desenciptado con MARS en " << argv[2] << std::endl;
	std::cout << "Se han tardado " << t_ejecucion.count() << " en desencriptar" << std::endl;

	return 0;
}
