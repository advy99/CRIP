#include "funciones.hpp"
#include <random>


// ejercicio 1

std::vector<int> crear_secuencia_super_creciente(const unsigned longitud, const unsigned margen) {
	std::random_device rd;
	std::mt19937 generador(rd());

	std::vector<int> resultado;
	resultado.resize(longitud);

	int suma_anteriores = 0;

	for ( unsigned i = 0; i < longitud; i++) {
		std::uniform_int_distribution<int> dist(suma_anteriores + 1, suma_anteriores + margen);

		int generado = dist(generador);
		resultado[i] = generado;
		suma_anteriores += generado;

	}

	return resultado;

}

bool comprobar_super_creciente(const std::vector<int> & secuencia) {
	int suma_anteriores = 0;
	bool resultado = true;

	unsigned i = 0;
	while (i < secuencia.size() && resultado ){
		resultado = suma_anteriores < secuencia[i];

		suma_anteriores += secuencia[i];

		i++;
	}

	return resultado;
}

std::pair<std::vector<> > funcion_mochila(const std::vector<int> & secuencia_numeros) {

}
