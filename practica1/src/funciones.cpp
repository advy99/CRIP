#include "funciones.hpp"
#include <map>

// ejercicio 1

std::vector<mp::cpp_int> algoritmo_extendido_euclides(mp::cpp_int a, mp::cpp_int b) {

	std::vector<mp::cpp_int> resultado;

	if ( a == 0 && b == 0) {
		resultado.clear();
	} else {
		std::vector<mp::cpp_int> s = {1, 0};
		std::vector<mp::cpp_int> t = {0, 1};
		std::vector<mp::cpp_int> a_b = {a, b};


		mp::cpp_int q;

		while ( a_b[1] != 0 ) {
			q = a_b[0] / a_b[1];

			a_b = {a_b[1], a_b[0] - a_b[1] * q};
			s = {s[1], s[0] - s[1] * q};
			t = {t[1], t[0] - t[1] * q};

		}

		resultado = {a_b[0], s[0], t[0]};

	}

	return resultado;
}


// ejercicio 2



mp::cpp_int inverso_a(mp::cpp_int a, mp::cpp_int b) {

	mp::cpp_int resultado;

	if ( a == 0 && b == 0) {
		resultado = -1;
	} else {
		std::vector<mp::cpp_int> s = {1, 0};
		std::vector<mp::cpp_int> a_b = {a, b};


		mp::cpp_int q;

		while ( a_b[1] != 0 ) {
			q = a_b[0] / a_b[1];

			a_b = {a_b[1], a_b[0] - a_b[1] * q};
			s = {s[1], s[0] - s[1] * q};
		}

		if ( a_b[0] != 1 ) {
			resultado = -1;
		} else {
			// aplicamos el modulo para que salga positivo
			resultado = ((s[0] % b) + b) % b;
		}
	}

	return resultado;
}



// ejercicio 3


mp::cpp_int pow_mod(mp::cpp_int base, mp::cpp_int exponente,
					 	  const mp::cpp_int modulo) {

	mp::cpp_int resultado = 1;

	while ( exponente > 0) {
		if ( (exponente & 1) == 1) {
			resultado = (resultado * base) % modulo;
		}

		exponente = exponente >> 1;

		base = (base * base) % modulo;

	}

	return resultado;
}


// ejercicio 4

bool test_miller_rabin(mp::cpp_int numero) {
	bool resultado = false;

	if ( numero <= 5 ) {
		resultado = numero == 2 || numero == 3 || numero == 5;
	} else {
		// es par
		if ( (numero & 1 ) == 0 ) {
			resultado = false;
		} else {

			mp::cpp_int s = numero - 1;
			mp::cpp_int exponente_n = 0;


			while ( s % 2 == 0 ) {
				exponente_n++;
				s >>= 1;
			}


			std::srand(std::time(nullptr));
			mp::cpp_int a;
			a = (2 + mp::cpp_int(std::rand()) % (numero - 1) ); // para que sea 2 < a < p-1
			mp::cpp_int nuevo_elemento;

			a = mp::powm(a, s, numero);

			// si a^s es 1 o -1, posiblemente sea primo, no tenemos que seguir
			resultado = a == 1 || a == numero - 1;
			bool continuar = true && !resultado;

			// si no se cumple, aplicamos el algoritmo
			// notar que es i < exponente_n, no <=, si el penultimo no es -1, no tenemos
			// que comprobar el ultimo
			for ( mp::cpp_int i = 1; i < exponente_n && continuar; i++ ) {
				a = mp::powm(a, 2, numero);

				// si a = -1, (en mod numero , pues numero - 1)
				if ( a == numero - 1 ) {
					resultado = true;
					continuar = false;
				}

				// hay mas de dos raices
				if ( a == 1) {
					resultado = false;
					continuar = false;
				}
			}

		}
	}

	return resultado;
}


bool es_primo(mp::cpp_int numero, int num_veces) {
	bool resultado = true;

	int i = 0;
	while (i < num_veces && resultado) {
		resultado = resultado && test_miller_rabin(numero);
		i++;
	}

	return resultado;

}

mp::cpp_int siguiente_primo(mp::cpp_int numero) {
	if ( numero % 2 == 0 ) {
		numero += 1;
	}

	do {
		numero += 2;
	} while (!es_primo(numero));

	return numero;

}



// ejercicio 5


mp::cpp_int babylonian_sqrt(mp::cpp_int n) {
	mp::cpp_int x = n;
	mp::cpp_int y = 1;

	while ( x > y) {
		x = (x + y ) / 2;
		y = n / x;
	}

	return x;
}

mp::cpp_int logaritmo_discreto(mp::cpp_int base, mp::cpp_int valor, mp::cpp_int modulo) {

	mp::cpp_int resultado = -1;

	if ( !es_primo(modulo) ) {
		std::cerr << "ERROR: El módulo ha de ser primo" << std::endl;
	} else {
		mp::cpp_int s = babylonian_sqrt(modulo - 1);
		std::multimap<mp::cpp_int, mp::cpp_int> l;
		std::multimap<mp::cpp_int, mp::cpp_int> L;

		mp::cpp_int t;
		mp::cpp_int r;

		// para asegurarnos que es la parte superior
		s += 1;

		mp::cpp_int valor_l = valor;
		mp::cpp_int valor_L = mp::powm(base, s, modulo);
		mp::cpp_int base_elevado_s = valor_L;

		l.insert(std::make_pair(valor_l, 0));
		L.insert(std::make_pair(valor_L, 1));

		auto it_l = l.find(valor_L);
		auto it_L = L.find(valor_l);


		bool encontrado_l = it_l != l.end();
		bool encontrado_L = it_L != L.end();


		// el primero lo acabamos de insertar
		mp::cpp_int i = 1;
		while ( i <= s - 1 && !encontrado_l && !encontrado_L){
			// aprovechamos los valores anteriores
			valor_l = (base * valor_l) % modulo;
			valor_L = (valor_L * base_elevado_s) % modulo;

			l.insert(std::make_pair(valor_l, i));
			L.insert(std::make_pair(valor_L, i + 1));

			// buscamos si el nuevo valor de L esta en l o viceversa
			it_l = l.find(valor_L);
			it_L = L.find(valor_l);

			encontrado_l = it_l != l.end();
			encontrado_L = it_L != L.end();

			i++;
		}

		if ( encontrado_l ) {
			t = i;
			r = it_l->second;
			resultado = t * s - r;
		}

		if ( encontrado_L) {
			t = it_L->second;
			r = i - 1;
			resultado = t * s - r;
		}

	}

	return resultado;
}


// ejercicio 6


// https://en.wikipedia.org/wiki/Jacobi_symbol
mp::cpp_int simbolo_jacobi ( mp::cpp_int a, mp::cpp_int n) {

	mp::cpp_int resultado = -1;

	if (n > 0 && n % 2 == 1) {

		a = a % n;
		mp::cpp_int t = 1;
		mp::cpp_int r;

		while ( a != 0) {
			// voy sacando todos los 2 de a
			while( a % 2 == 0 ) {
				a = a / 2;
				r = n % 8;

				if ( r == 3 || r == 5) {
					t = -t;
				}
			}

			// intercambio los valores, ya que he llegado a un punto en el que no puedo
			// sacar mas 2
			mp::cpp_int tmp = a;
			a = n;
			n = tmp;

			if ( a % 4 == 3 && n % 4 == 3 ) {
				t = -t;
			}
			a = a % n;

		}

		if ( n == 1 ) {
			resultado = t;
		} else {
			resultado = 0;
		}

	}

	return resultado;

}


// apuntes de miranda, pag 188 de 236
mp::cpp_int raiz_cuadrada_mod(mp::cpp_int a, mp::cpp_int p) {

	mp::cpp_int resultado;

	if ( simbolo_jacobi(a, p) != 1) {
		resultado = -1;
	} else {
		// el simbolo de jacobi es 1, a es residuo cuadrático modulo p

		// buscamos el simbolo de jacobi de n sobre p que nos de 1
		mp::cpp_int n = 2;

		while ( simbolo_jacobi(n, p) != -1) {
			n++;
		}

		mp::cpp_int s = p - 1;
		mp::cpp_int u = 0;

		// mientras la descomcomposición se pueda dividir por 2
		while ( s % 2 == 0 ){
			s = s >> 1 ;
			u++;
		}

		// ahora tenemos que p - 1 = 2^u * s

		resultado = mp::powm(a, (s + 1) / 2, p);
		mp::cpp_int b = mp::powm(n, s, p);
		mp::cpp_int j = 0;

		while (j <= u - 2){
			mp::cpp_int inv_a = inverso_a(a, p);
			mp::cpp_int r_cuadrado = mp::powm(resultado, mp::cpp_int(2), p);
			mp::cpp_int exponente = mp::powm(mp::cpp_int(2), u - 2 - j, p);


			if ( mp::powm( (inv_a * r_cuadrado) % p , exponente, p) == p - 1 ) {
				 resultado = (resultado * b) % p;
			}

			b = mp::powm(b, 2, p);

			j++;
		}

		// devuelvo siempre la más pequeña
		if ( resultado > p / 2) {
			resultado = p - resultado;
		}


	}

	return resultado;
}



std::set<mp::cpp_int> raices_cuadradas_p_q(mp::cpp_int a, mp::cpp_int p, mp::cpp_int q) {

	// utilizo un set, así evito repetidas
	std::set<mp::cpp_int> resultado;

	if ( simbolo_jacobi(a, p) != 1 || simbolo_jacobi(a, q) != 1) {
		std::cerr << "ERROR: a tiene que ser residuo cuadrático de p y q" << std::endl;
	} else {

		// si tenemos que
		// x \cong a mod p
		// x \cong a mod q
		// los resultados son de la forma x = a + k * p

		// busco x, x^2 \cong a mod p * q
		mp::cpp_int n = p * q;

		// raices con p
		mp::cpp_int r1_p = raiz_cuadrada_mod(a, p);
		mp::cpp_int r2_p = p - r1_p;

		// raices con q
		mp::cpp_int r1_q = raiz_cuadrada_mod(a, q);
		mp::cpp_int r2_q = q - r1_q;

		// aplico teorema chino de los restos a la primera posibilidad:
		// x \cong r1_p mod p
		// x \cong r1_q mod q

		// de la primea ecuacion, x = r1_p + p * k
		// luego r1_p + p * k \cong r1_q mod q
		// p * k \cong r1_q - r1_p mod q
		// k \cong p^-1 * (r1_q - r1_p) mod q
		// entonces
		// k = p^-1 * (r1_q - r1_p) + q * t
		// x = r1_p + p * (p^-1 * (r1_q - r1_p) + q * t)
		// x = r1_p + p^-1 * (r1_q - r1_p) * p + t * p * q
		// el ultimo sumando lo quito, ya que solo quiero la solucion particular

		// calculo el inverso de p mod q
		mp::cpp_int inv_p = inverso_a(p, q);
		mp::cpp_int sol1 = r1_p + inv_p * (r1_q - r1_p) * p;

		sol1 = sol1 % n;

		// por si sale negativo el modulo
		if ( sol1 < 0) {
			sol1 += n;
		}


		// otra solucion es la misma, pero utilizando la raiz 2 de p por ejemplo
		mp::cpp_int sol2 = r2_p + inv_p * (r1_q - r2_p) * p;

		sol2 = sol2 % n;

		// por si sale negativo el modulo
		if ( sol2 < 0) {
			sol2 += n;
		}

		// las otras soluciones serían cambiando de signo, así que no hace falta calcularlas
		mp::cpp_int sol3 = n - sol1;
		mp::cpp_int sol4 = n - sol2;

		// insertamos todas, las repetidas no se insertarán ya que es un set
		resultado.insert(sol1);
		resultado.insert(sol2);
		resultado.insert(sol3);
		resultado.insert(sol4);


	}

	return resultado;

}
