#include "funciones.hpp"

boost::dynamic_bitset<> desplazar_rotacion_izq(const boost::dynamic_bitset<> bitset, const int n) {
	return (bitset << n) | (bitset >> (bitset.size() - n));
}

boost::dynamic_bitset<> desplazar_rotacion_der(const boost::dynamic_bitset<> bitset, const int n) {
	return (bitset >> n) | (bitset << (bitset.size() - n));
}

void push_front(boost::dynamic_bitset<> & bitset, const bool value) {
	bitset.push_back(false);
	bitset <<= 1;
	bitset[0] = value;
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
	bool resultado = bitset_original.count() != 0 && bitset_original.count() != bitset_original.size();

	if ( resultado ) {
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

		if ( tam_rachas[tam_rachas.size() - 1] == 1 && tam_rachas[tam_rachas.size() - 2] == 1) {
			tam_rachas.pop_back();
		}

		unsigned i = 0;

		// nos quedamos en el antepenultimo comprobando con el penultimo,
		while ( resultado && i < tam_rachas.size() - 1) {
			resultado = tam_rachas[i] == 2 * tam_rachas[i + 1];
			i++;
		}
	} else {
		resultado = bitset_original.size() == 1;
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
	bool resultado = false;

	for ( unsigned i = 0; i < polinomio.size(); i++ ) {
		resultado = (resultado ^ (polinomio[i] & semilla[i]) );
	}

	return resultado;

}

// ejercicio2

boost::dynamic_bitset<> LFSR(const boost::dynamic_bitset<> & polinomio,
									  const boost::dynamic_bitset<> & semilla,
									  const signed long long longitud) {

	boost::dynamic_bitset<> resultado;
	std::set<boost::dynamic_bitset<> > semillas_usadas;

	bool hasta_repeticion = longitud == -1;
	bool he_encontrado_repeticion = false;

	// inicializamos el resultado:
	resultado = semilla;

	boost::dynamic_bitset<> semilla_actual = semilla;
	semillas_usadas.insert(semilla_actual);

	unsigned i = semilla.size();
	while (i < longitud || (hasta_repeticion && !he_encontrado_repeticion) )  {
		bool valor = aplicar_polinomio_LFSR(polinomio, semilla_actual);

		// como la semilla la desplazamos a la derecha, el resultado tenemos que introducir
		// los valores por el mismo lado
		resultado.push_back(valor);
		resultado <<= 1;
		resultado[0] = valor;


		// una vez calculado el resultado con el polinomio, actualizamos a la nueva semilla
		// perdemos el valor menos significativo
		semilla_actual <<= 1;

		// en el menos significativo insertamos el nuevo valor
		semilla_actual[0] = valor;

		auto resultado = semillas_usadas.insert(semilla_actual);

		if ( !resultado.second ) {
			he_encontrado_repeticion = true;
		}

		i++;
	}


	if ( hasta_repeticion ) {
		for ( unsigned i = 0; i < semilla.size(); i++) {
			resultado >>= 1;
			resultado.pop_back();
		}
	}

	return resultado;

}


// ejercicio 3

bool aplicar_polinomio_NLFSR(const std::vector<boost::dynamic_bitset<> > & polinomio, const boost::dynamic_bitset<> & semilla) {
	// al dar el polinomio caracteristico siempre tenemos el + 1 del final
	// así que comenzamos como verdadero
	bool resultado = false;
	bool resultado_polinomio;

	for ( unsigned i = 0; i < polinomio.size(); i++) {
		resultado_polinomio = true;
		for ( unsigned j = 0; j < polinomio[i].size(); j++ ) {
			resultado_polinomio &= mp::powm(semilla[j], polinomio[i][j], 2 );
		}

		resultado = resultado ^ resultado_polinomio;
	}

	return resultado;

}

boost::dynamic_bitset<> NLFSR(const std::vector<boost::dynamic_bitset<> > & polinomio,
									   const boost::dynamic_bitset<> & semilla,
									   const signed long long longitud) {

	boost::dynamic_bitset<> resultado;

	resultado = semilla;

	boost::dynamic_bitset<> semilla_actual = semilla;

	unsigned i = semilla.size();
	while (i < longitud )  {
		bool valor = aplicar_polinomio_NLFSR(polinomio, semilla_actual);
		resultado.push_back(valor);
		resultado <<= 1;
		resultado[0] = valor;

		// una vez calculado el resultado con el polinomio, actualizamos a la nueva semilla
		semilla_actual <<= 1;

		// en el más significativo insertamos el nuevo valor
		semilla_actual[0] = valor;

		i++;
	}

	return resultado;
}
