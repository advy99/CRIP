#include <iostream>
#include <iomanip>

#include "cryptopp/modes.h"
#include "cryptopp/mars.h"
#include "cryptopp/filters.h"
#include "cryptopp/osrng.h"

int main(int argc, char* argv[]) {

	if ( argc < 2 ) {
		std::cerr << "ERROR: Introduce como argumento la cadena a cifrar" << std::endl;
		exit(-1);
	}

	// declaramos generador de numeros aleatorios
	CryptoPP::AutoSeededRandomPool generador_aleatorio;

	// utilizaremos las longitudes de clave y bloque por defecto
	CryptoPP::SecByteBlock clave(CryptoPP::MARS::DEFAULT_KEYLENGTH);
	CryptoPP::SecByteBlock vector_inicializacion(CryptoPP::MARS::BLOCKSIZE);

	// generamos la clave y el vector de inicialización aleatorios
	generador_aleatorio.GenerateBlock(clave, clave.size());
	generador_aleatorio.GenerateBlock(vector_inicializacion, vector_inicializacion.size());


	std::string texto_a_cifrar = "";

	for ( unsigned i = 1; i < argc; i++) {
		texto_a_cifrar += std::string(argv[i]) + " ";
	}

	std::string texto_cifrado;
	std::string texto_descifrado;

	// mostramos el tamaño del texto introducido
	std::cout << "Texto introducido: (" << texto_a_cifrar.size() << " bytes)" << std::endl;
	std::cout << texto_a_cifrar;
	std::cout << std::endl << std::endl;

	// creamos la instancia de MARS para encriptar y el modo de operación, en este caso CBC
	CryptoPP::MARS::Encryption encriptacion_mars(clave, clave.size());

	// inicializamos el modo de operación con el algoritmo MARS y el vector de inicialización que hemos generado
	CryptoPP::CBC_Mode_ExternalCipher::Encryption encriptado_cbc( encriptacion_mars, vector_inicializacion );

	// creamos un flujo entre la instancia de CBC y el texto cifrado
	CryptoPP::StreamTransformationFilter stfEncryptor(encriptado_cbc, new CryptoPP::StringSink( texto_cifrado ) );
	stfEncryptor.Put( reinterpret_cast<const unsigned char*>( texto_a_cifrar.c_str() ), texto_a_cifrar.length() );
	stfEncryptor.MessageEnd();

	//
	// Dump Cipher Text
	//
	std::cout << "Cipher Text (" << texto_cifrado.size() << " bytes)" << std::endl;

	for( int i = 0; i < texto_cifrado.size(); i++ ) {
		std::cout << "0x" << std::hex << (0xFF & static_cast<CryptoPP::byte>(texto_cifrado[i])) << " ";
	}

	std::cout << std::endl << std::endl;

	// desciframos
	CryptoPP::MARS::Decryption desencriptado_mars(clave, clave.size());

	CryptoPP::CBC_Mode_ExternalCipher::Decryption desencriptado_cbc( desencriptado_mars, vector_inicializacion );

	CryptoPP::StreamTransformationFilter stfDecryptor(desencriptado_cbc, new CryptoPP::StringSink( texto_descifrado ) );
	stfDecryptor.Put( reinterpret_cast<const unsigned char*>( texto_cifrado.c_str() ), texto_cifrado.size() );
	stfDecryptor.MessageEnd();

	// mostramos el resultado
	std::cout << "Decrypted Text: " << std::endl;
	std::cout << texto_descifrado;
	std::cout << std::endl << std::endl;

	return 0;
}
