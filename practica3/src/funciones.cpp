#include "funciones.hpp"
#include "funciones_p1.hpp"
#include <boost/random.hpp>


// ejercicio 1

std::vector<mp::cpp_int> crear_secuencia_super_creciente(const unsigned longitud, const mp::cpp_int & margen) {
	boost::random::mt19937 mt;

	std::vector<mp::cpp_int> resultado;
	resultado.resize(longitud);

	mp::cpp_int suma_anteriores = 0;

	for ( unsigned i = 0; i < longitud; i++) {
		boost::random::uniform_int_distribution<mp::cpp_int> ui( suma_anteriores + 1, suma_anteriores + margen);

		mp::cpp_int generado = ui(mt);
		resultado[i] = generado;
		suma_anteriores += generado;

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
	n = siguiente_primo(n);
	boost::random::mt19937 mt;
   boost::random::uniform_int_distribution<mp::cpp_int> ui( mp::cpp_int(2), mp::cpp_int(n - 2));
	mp::cpp_int u = ui(mt);

	// esto debería ser cierto, pero por comprobar
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


mp::cpp_int cifrar_secuencia_bits(const std::vector<bool> & bits, const std::vector<mp::cpp_int> & clave_publica) {
	mp::cpp_int resultado = 0;

	for ( unsigned i = 0; i < bits.size(); i++) {
		resultado += bits[i] * clave_publica[i];
	}

	return resultado;
}

std::vector<bool> descifrar(const mp::cpp_int & numero, const std::tuple<std::vector<mp::cpp_int>, mp::cpp_int, mp::cpp_int> & llave_privada) {
	std::vector<mp::cpp_int> secuencia_clave_privada = std::get<0>(llave_privada);
	mp::cpp_int n = std::get<1>(llave_privada);
	mp::cpp_int u = std::get<2>(llave_privada);


	// calculamos el inverso de u mod n
	mp::cpp_int inverso_u_mod_n = inverso_a(u, n);
	mp::cpp_int inverso_numero_dado = ( (inverso_u_mod_n * numero) + n) % n;

	std::vector<bool> resultado;
	resultado.resize(secuencia_clave_privada.size(), false);

	mp::cpp_int suma_actual = 0;

	int i = resultado.size() - 1;

	while ( suma_actual != inverso_numero_dado && i >= 0) {
		if (suma_actual + secuencia_clave_privada[i] <= inverso_numero_dado) {
			resultado[i] = true;
			suma_actual += secuencia_clave_privada[i];
		}

		i--;
	}

	return resultado;

}


// ejercicio 2
// precondicion: (p - 1) / 2 también es primo
mp::cpp_int encontrar_elemento_primitivo(const mp::cpp_int & primo) {

	mp::cpp_int alfa = 2;

	while ( simbolo_jacobi(alfa, primo) != -1 ) {
		alfa++;
	}

	return alfa;
}
