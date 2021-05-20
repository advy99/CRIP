#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <vector>
#include "funciones.hpp"
#include "funciones_p1.hpp"

#include <chrono>


int main(int argc, char ** argv) {

	if ( argc != 4 ) {
		std::cout << "Error: Ejecutar con dos parametros: <n> <u_inicial> <secuencia_bits> " << std::endl;
		std::cout << "\t N es un número primo, u_inicial el vector de inicialización inicial (un número en nuestro caso), y la secuencia de bits una secuencia de 0's y 1's que será el mensaje" << std::endl;
		exit(-1);
	}

	mp::cpp_int n = mp::cpp_int(argv[1]);
	mp::cpp_int u = mp::cpp_int(argv[2]);

	std::string secuencia_bits = std::string(argv[3]);

	std::vector<bool> mensaje;
	mensaje.resize(secuencia_bits.size());

	for(unsigned i = 0; i < secuencia_bits.size(); i++) {
		// si está puesto a uno, lo ponemos true, si no false
		mensaje[i] = secuencia_bits[i] - '0' == 1;
	}

	mp::cpp_int resultado_resumen = funcion_resumen(n, u, mensaje);

	std::cout << "Resultado: " << resultado_resumen << std::endl;

	return 0;
}
