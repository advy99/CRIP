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
			// para que borre los que vemos al final (que en realidad están al principio)
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


boost::dynamic_bitset<> generador_geffe(const std::pair<boost::dynamic_bitset<>, boost::dynamic_bitset<> > & lfsr1,
													 const std::pair<boost::dynamic_bitset<>, boost::dynamic_bitset<> > & lfsr2,
												 	 const std::pair<boost::dynamic_bitset<>, boost::dynamic_bitset<> > & lfsr3,
												 	 const int longitud) {

	// calculamos los tres lfsr por separado, pero de la misma longitud
	auto resultado_lfsr_1 = LFSR(lfsr1.first, lfsr1.second, longitud);
	auto resultado_lfsr_2 = LFSR(lfsr2.first, lfsr2.second, longitud);
	auto resultado_lfsr_3 = LFSR(lfsr3.first, lfsr3.second, longitud);

	boost::dynamic_bitset<> resultado;
	resultado.resize(longitud);

	// aplicamos la funcion del generador de Geffe para obtener el resultado
	for ( int i = 0; i < longitud; i++) {
		resultado[i] = (resultado_lfsr_1[i] & resultado_lfsr_2[i]) ^ (resultado_lfsr_2[i] & resultado_lfsr_3[i]) ^ resultado_lfsr_3[i];
	}

	return resultado;

}



boost::dynamic_bitset<> cadena_a_bitset(const std::string & cadena) {
	const int num_bits_char = sizeof(cadena[0]) * 8;
	boost::dynamic_bitset<> cadena_bitset;
	cadena_bitset.resize(cadena.size() * num_bits_char);

	for (unsigned i = 0; i < cadena.size(); ++i) {
		char c = cadena[i];
		for (int j = 7; j >= 0 && c; --j) {
			if (c & 0x1) {
				cadena_bitset.set(8 * i + j);
			}
			c >>= 1;
		}
	}
	return cadena_bitset;
}

std::string bitset_a_cadena(const boost::dynamic_bitset<> & bitset) {
	std::string resultado;
	unsigned k = 0;
	while ( k < bitset.size()) {
		boost::dynamic_bitset<> caracter_bitset;
		for (int i = 7; i >= 0; --i) {
			caracter_bitset.push_back(bitset[k + i]);
		}
		resultado.push_back(caracter_bitset.to_ulong());
		k += 8;
	}

	return resultado;
}



std::pair<int, boost::dynamic_bitset<> > algoritmo_berlekamp_massey(const boost::dynamic_bitset<> & bitset) {

	boost::dynamic_bitset<> f;
	boost::dynamic_bitset<> g;

	// secuencias con todo 0
	f.resize(bitset.size());
	g.resize(bitset.size());

	// ponemos la primera posicion con 1
	g[0] = true;
	f[0] = true;

	// buscamos la k
	int k = 0;
	while (!bitset[k] && k < static_cast<int>(bitset.size()) ) {
		k++;
	}

	if ( k < static_cast<int>(bitset.size()) - 1 ) {
		f[k + 1] = true;
	}

	std::cout << k << std::endl;
	std::cout << bitset << std::endl;

	std::cout << "r \t l \t a \t b \t\t f \t g \t\t d \t 2l > r" << std::endl;


	int l = k + 1;
	int a = k;
	int b = 0;
	int r = k + 1;

	while ( r < static_cast<int>(bitset.size()) ) {

		std:: cout << r << "\t";
		std:: cout << l << "\t";
		std:: cout << a << "\t";
		std:: cout << b << "\t";
		std::cout << f << "\t";
		std::cout << g << "\t";

		int d = 0;
		for (int i = 0; i <= l; i++) {
			d = d ^ (f[i] & bitset[i + r - l]);
		}

		std::cout << d << "\t";

		if (d == 0) {
			b++;
			std::cout << std::endl;
		} else {

			if ( 2 * l > r ) {
				std::cout << "1" << std::endl;
				int indice;

				for (int i = 0; i <= l; i++) {
					indice = i + b - a;
					bool valor = indice >= 0 && indice < static_cast<int>(g.size());
					if (valor) {
						valor = g[indice];
					}

					f[i] = f[i] ^ valor;
				}

				b++;

			} else {
				std::cout << "0" << std::endl;
				boost::dynamic_bitset<> aux = f;
				int indice;

				for ( int i = 0; i < r + l; i++) {
					indice = i + a - b;

					bool valor = indice >= 0 && indice < static_cast<int>(aux.size());
					if (valor) {
						valor = aux[indice];
					}

					f[i] = valor ^ g[i];
				}

				l = r - l + 1;
				g = aux;
				a = b;
				b = r - l + 1;
			}
		}

		r++;
	}

	boost::dynamic_bitset<> f_x;
	f_x.resize(l);

	for ( int i = 0; i < l; i++) {
		f_x[i] = f[i];
	}

	return std::make_pair(l, f_x);
}
