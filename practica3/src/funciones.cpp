#include "funciones.hpp"
#include <random>


// ejercicio 1

std::vector<mp::cpp_int> crear_secuencia_super_creciente(const unsigned longitud, const unsigned margen) {
	std::random_device rd;
	std::mt19937 generador(rd());

	std::vector<mp::cpp_int> resultado;
	resultado.resize(longitud);

	int suma_anteriores = 0;

	for ( unsigned i = 0; i < longitud; i++) {
		std::uniform_int_distribution<> dist(suma_anteriores + 1, suma_anteriores + margen);

		mp::cpp_int generado = dist(generador);
		resultado[i] = generado;
		suma_anteriores += static_cast<int>(generado);

	}

	return resultado;

}

bool comprobar_super_creciente(const std::vector<mp::cpp_int> & secuencia) {
	mp::cpp_int suma_anteriores = 0;
	bool resultado = true;

	unsigned i = 0;
	while (i < secuencia.size() && resultado ){
		resultado = suma_anteriores < secuencia[i];

		suma_anteriores += secuencia[i];

		i++;
	}

	return resultado;
}

std::pair<std::vector<mp::cpp_int>, std::tuple<std::vector<mp::cpp_int>, mp::cpp_int, mp::cpp_int> > generar_llaves(const unsigned longitud_llaves) {
	std::vector<mp::cpp_int> secuencia = crear_secuencia_super_creciente(longitud_llaves);

	mp::cpp_int n = 0;

	for (unsigned i = 0; i < secuencia.size(); i++) {
		n += secuencia[i];
	}

	// para que n sea mayor estricto que la suma
	n++;

	mp::cpp_int u = 2;

	while( mp::gcd(n, u) != 1 ) {
		u++;
	}

	std::vector<mp::cpp_int> llave_publica;
	llave_publica.resize(secuencia.size());

	for ( unsigned i = 0; i < secuencia.size(); i++) {
		// hacemos + n % n por si sale negativo, llevarlo a los positivos
		llave_publica[i] = ( (u * secuencia[i]) + n) % n;
	}


	return std::make_pair( llave_publica, std::make_tuple(secuencia, n, u) );

}
