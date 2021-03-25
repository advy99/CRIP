#include "funciones.hpp"

boost::dynamic_bitset<> desplazar_rotacion_izq(const boost::dynamic_bitset<> bitset, const int n) {
	return (bitset << n) | (bitset >> (bitset.size() - n));
}

boost::dynamic_bitset<> desplazar_rotacion_der(const boost::dynamic_bitset<> bitset, const int n) {
	return (bitset >> n) | (bitset << (bitset.size() - n));
}


// ejercicio 1
bool cumple_postulados_golomb(boost::dynamic_bitset<> bitset) {
	bool resultado = false;

	boost::dynamic_bitset<> bitset_negado = bitset.flip();

	// primer postulado: mismo numero de 0's y 1's, o como mucho una diferencia
	// de uno
	mp::cpp_int num0 = bitset_negado.count();
	mp::cpp_int num1 = bitset.count();

	resultado = mp::abs(num1 - num0) <= 1;

	// si se cumple el primer postulado, comprobamos el segundo
	if ( resultado ) {

		while ( bitset[0] == bitset[bitset.size()] ) {
			bitset = desplazar_rotacion_der(bitset, 1);
		}

		// segundo postulado
		std::vector<int> tam_rachas;

		int tam_racha_actual = 1;
		bool valor_racha_actual = bitset[0];

		for ( boost::dynamic_bitset<>::size_type i = 1; i < bitset.size(); i++){
			if ( valor_racha_actual != bitset[i]) {
				// se rompe la racha
				// lo metemos en el correspondiente vector de rachas
				if (tam_rachas.size() < tam_racha_actual) {
					tam_rachas.resize(tam_racha_actual, 0 );
				}

				tam_rachas[tam_racha_actual]++;

				tam_racha_actual = 1;
				valor_racha_actual = bitset[i];
			} else {
				tam_racha_actual++;
			}

		}


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



	}

	// si cumple el primer y segundo postulado, compruebo el tercero
	if ( resultado ) {
		unsigned num_rotacion = 0;
		unsigned peso_hamming_original = bitset.count();

		while( resultado && num_rotacion < bitset.size()) {
			resultado = (bitset ^ desplazar_rotacion_der(bitset,1)).count() == peso_hamming_original;
		}
	}


	return resultado;

}
