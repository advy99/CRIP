#include "funciones.hpp"

boost::dynamic_bitset<> desplazar_rotacion_izq(const boost::dynamic_bitset<> bitset, const int n) {
	return (bitset << n) | (bitset >> (bitset.size() - n));
}

boost::dynamic_bitset<> desplazar_rotacion_der(const boost::dynamic_bitset<> bitset, const int n) {
	return (bitset >> n) | (bitset << (bitset.size() - n));
}


bool cumple_primer_postulado_golomb(const boost::dynamic_bitset<> & bitset_original) {
	bool resultado = false;

	boost::dynamic_bitset<> bitset = bitset_original;

	// primer postulado: mismo numero de 0's y 1's, o como mucho una diferencia
	// de uno
	mp::cpp_int num1 = bitset.count();
	bitset.flip();
	mp::cpp_int num0 = bitset.count();

	resultado = mp::abs(num1 - num0) <= 1;

	return resultado;

}


bool cumple_segundo_postulado_golomb(const boost::dynamic_bitset<> & bitset_original) {
	bool resultado = true;

	boost::dynamic_bitset<> bitset = bitset_original;

	while ( bitset[0] == bitset[bitset.size() - 1] ) {
		bitset = desplazar_rotacion_der(bitset, 1);
	}

	// segundo postulado
	std::vector<int> tam_rachas;

	unsigned tam_racha_actual = 1;
	bool valor_racha_actual = bitset[0];

	for ( unsigned i = 1; i < bitset.size(); i++){
		if ( valor_racha_actual != bitset[i]) {
			// se rompe la racha
			// lo metemos en el correspondiente vector de rachas
			if (tam_rachas.size() < tam_racha_actual) {
				tam_rachas.resize(tam_racha_actual );
			}

			tam_rachas[tam_racha_actual - 1]++;

			tam_racha_actual = 1;
			valor_racha_actual = bitset[i];
		} else {
			tam_racha_actual++;
		}

	}

	//tenemos en cuenta la racha final
	tam_rachas[tam_racha_actual - 1]++;


	unsigned i = 0;

	// nos quedamos en el antepenultimo comprobando con el penultimo,
	while ( resultado && i < tam_rachas.size() - 2) {
		resultado = tam_rachas[i] == 2 * tam_rachas[i + 1];
		i++;
	}

	if ( resultado ) {
		// en el caso del final, puede ser que
		resultado = tam_rachas[tam_rachas.size() - 2] == tam_rachas[tam_rachas.size() - 1] ||
						tam_rachas[tam_rachas.size() - 1] == 1 ;
	}


	return resultado;
}


bool cumple_tercer_postulado_golomb(const  boost::dynamic_bitset<> & bitset_original) {
	bool resultado = true;

	boost::dynamic_bitset<> bitset = bitset_original;

	unsigned num_rotacion = 1;
	unsigned peso_hamming_original = bitset.count();

	// para cada rotacion, mientras siga cumpliendo el postulado, calculamos
	// la distancia de hamming
	while( resultado && num_rotacion < bitset.size()) {
		resultado = (bitset ^ desplazar_rotacion_der(bitset,num_rotacion)).count() == peso_hamming_original;
		num_rotacion++;
	}

	return resultado;
}



// ejercicio 1
bool cumple_postulados_golomb(const boost::dynamic_bitset<> & bitset_original) {
	bool resultado = cumple_primer_postulado_golomb(bitset_original);

	// si se cumple el primer postulado, comprobamos el segundo
	if ( resultado ) {
		resultado = cumple_segundo_postulado_golomb(bitset_original);
	}

	// si cumple el primer y segundo postulado, compruebo el tercero
	if ( resultado ) {
		resultado = cumple_segundo_postulado_golomb(bitset_original);
	}


	return resultado;

}


bool aplicar_polinomio_LFSR(const boost::dynamic_bitset<> & polinomio, const boost::dynamic_bitset<> & semilla) {
	// al dar el polinomio caracteristico siempre tenemos el + 1 del final
	// así que comenzamos como verdadero
	bool resultado = false;

	for ( unsigned i = 0; i < polinomio.size(); i++ ) {
		resultado = resultado ^ (polinomio[i] & semilla[i]);
	}

	return resultado;

}

// ejercicio2

boost::dynamic_bitset<> LFSR(const boost::dynamic_bitset<> & polinomio,
									  const boost::dynamic_bitset<> & semilla,
									  const unsigned long long longitud) {

	boost::dynamic_bitset<> resultado(longitud);

	// inicializamos el resultado:
	// no hamos un =, ya que al hacer resize en un bitset, el de indice 0 es el
	// ultimo elemento, no el primero
	for ( unsigned i = 0; i < semilla.size(); i++) {
		resultado[resultado.size() - 1 - i] = semilla[semilla.size() - 1 - i];
	}

	boost::dynamic_bitset<> semilla_actual = semilla;

	for ( unsigned i = semilla.size(); i < longitud; i++) {
		resultado[resultado.size() - 1 - i] = aplicar_polinomio_LFSR(polinomio, semilla_actual);
		// una vez calculado el resultado con el polinomio, actualizamos a la nueva semilla
		// perdemos el valor menos significativo
		semilla_actual <<= 1;

		// en el más significativo insertamos el nuevo valor
		semilla_actual[0] = resultado[resultado.size() - 1 - i];
	}

	return resultado;

}
