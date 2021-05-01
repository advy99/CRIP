
#include "funciones.hpp"

#include <iostream>
#include <boost/dynamic_bitset.hpp>

//
// El periodo del generador de Geffe es el mcm(2^{L_1} - 1, 2^{L_2} - 1, 2^{L_3} - 1), luego
// si queremos un periodo de p1p2p3, tenemos que buscar tres LFSRs cuyos periodos sean primos relativos
//
// Como podemos comprobar con el ejercicio 2:
// ./bin/ejercicio2 1100 0110
// Resultado:
// 110
// El periodo tiene longitud 3
// Además, para la cadena resultante se cumplen los postulados de Golomb
//
// ./bin/ejercicio2 1100 0111
// Resultado:
// 0111
// El periodo tiene longitud 4
//
// ./bin/ejercicio2 0100101 0110101
// Resultado:
// 10101
// El periodo tiene longitud 5
// Además, para la cadena resultante se cumplen los postulados de Golomb
//
//
// estos numeros son primos relativos, luego el periodo tiene que ser 3 * 4 * 5 = 60
//
// 																			    111111111011011111111111011011111111111011011111111111011011
// 111111111011011111111111011011111111111011011111111111011011 111111111011011111111111011011111111111011011111111111011011
//
// Cadena de 180, partida en 3
// 111111111011011111111111011011111111111011011111111111011011 111111111011011111111111011011111111111011011111111111011011 111111111011011111111111011011111111111011011111111111011011
// 111111111011011111111111011011111111111011011111111111011011																				  111111111011011111111111011011111111111011011111111111011011
//  																				 111111111011011111111111011011111111111011011111111111011011



int main ( int argc, char ** argv) {

	if ( argc != 9 ) {
		std::cerr << "ERROR: Numero de argumentos erroneos.\n"
					 << "\t Uso: " << argv[0] << " <p1> <semilla1> <p2> <semilla2> <p3> <semilla3> <longitud> <cadena bits a cifrar>" << std::endl;
		exit(-1);
	}

	std::string coeficientes_p1 = std::string(argv[1]);
	std::string semilla1 = std::string(argv[2]);
	std::string coeficientes_p2 = std::string(argv[3]);
	std::string semilla2 = std::string(argv[4]);
	std::string coeficientes_p3 = std::string(argv[5]);
	std::string semilla3 = std::string(argv[6]);
	int longitud = atoi(argv[7]);
	std::string cadena_cifrar = std::string(argv[8]);

	if ( coeficientes_p1.size() != semilla1.size() || coeficientes_p2.size() != semilla2.size() || coeficientes_p3.size() != semilla3.size()) {
		std::cerr << "ERROR: La longitud del string de coeficientes y de la semilla ha de ser la misma en cada pareja" << std::endl;
		exit(-2);
	}

	std::pair<boost::dynamic_bitset<>, boost::dynamic_bitset<> > lfsr1;
	std::pair<boost::dynamic_bitset<>, boost::dynamic_bitset<> > lfsr2;
	std::pair<boost::dynamic_bitset<>, boost::dynamic_bitset<> > lfsr3;

	lfsr1 = std::make_pair(boost::dynamic_bitset<>(coeficientes_p1), boost::dynamic_bitset<>(semilla1));
	lfsr2 = std::make_pair(boost::dynamic_bitset<>(coeficientes_p2), boost::dynamic_bitset<>(semilla2));
	lfsr3 = std::make_pair(boost::dynamic_bitset<>(coeficientes_p3), boost::dynamic_bitset<>(semilla3));

	auto resultado = generador_geffe(lfsr1, lfsr2, lfsr3, longitud);


	std::cout << "Resultado: " << std::endl;
	std::cout << resultado << std::endl << std::endl;


	// cifrar una cadena:

	boost::dynamic_bitset<> cadena_entrada(cadena_cifrar);

	auto clave_cifrado = generador_geffe(lfsr1, lfsr2, lfsr3, cadena_cifrar.size());

	auto entrada_cifrada = cadena_entrada ^ clave_cifrado;

	std::cout << "Cadena a cifrar:" << std::endl << cadena_entrada << std::endl;
	std::cout << "Clave genrada con los LFSR dados:" << std::endl << clave_cifrado << std::endl;
	std::cout << "Cadena cifrada con la clave:" << std::endl << entrada_cifrada << std::endl;


	// parte 2, cifrar una cadena
	std::string cadena;
	std::string cadena_cifrada;

	std::cout << std::endl << "Introduce una cadena: " ;
	std::getline(std::cin, cadena);

	const int num_bits_char = sizeof(cadena[0]) * 8;

	boost::dynamic_bitset<> clave = generador_geffe(lfsr1, lfsr2, lfsr3, cadena.size() * num_bits_char);

	// paso la cadena a un bitset
	boost::dynamic_bitset<> cadena_bitset = cadena_a_bitset(cadena);

	// cifro la cadena haciendo xor con la clave
	boost::dynamic_bitset<> cadena_cifrada_bitset = cadena_bitset ^ clave;

	// paso el bitset cifrado a string, para tener la cadena cifrada
	cadena_cifrada = bitset_a_cadena(cadena_cifrada_bitset);

	std::cout << "Cadena cifrada: " << cadena_cifrada << std::endl;

	boost::dynamic_bitset<> bitset_cadena_a_descifrar = cadena_a_bitset(cadena_cifrada);

	boost::dynamic_bitset<> bitset_descifrado = bitset_cadena_a_descifrar ^ clave;

	std::string descifrado = bitset_a_cadena(bitset_descifrado);

	std::cout << "Cadena descifrada: " << descifrado << std::endl;

}
