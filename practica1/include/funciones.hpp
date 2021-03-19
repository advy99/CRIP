#ifndef FUNCIONES_HPP
#define FUNCIONES_HPP

#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <vector>

namespace mp = boost::multiprecision;


// ejercicio 1
std::vector<mp::cpp_int> algoritmo_extendido_euclides(mp::cpp_int a, mp::cpp_int b);

// ejercicio 2
mp::cpp_int inverso_a(mp::cpp_int a, mp::cpp_int b);

// ejercicio 3
mp::cpp_int pow_mod(mp::cpp_int base, mp::cpp_int exponente,
					 	  const mp::cpp_int modulo);

// ejercicio 4

bool test_miller_rabin(mp::cpp_int numero);
bool es_primo(mp::cpp_int numero, int num_veces = 10);
mp::cpp_int siguiente_primo(mp::cpp_int numero);


// ejercicio 5

mp::cpp_int babylonian_sqrt(mp::cpp_int n);
mp::cpp_int logaritmo_discreto(mp::cpp_int base, mp::cpp_int valor, mp::cpp_int modulo);


// ejercicio 6

mp::cpp_int simbolo_jacobi(mp::cpp_int a, mp::cpp_int n);
mp::cpp_int raiz_cuadrada_mod(mp::cpp_int a, mp::cpp_int p);

std::set<mp::cpp_int> raices_cuadradas_p_q(mp::cpp_int a, mp::cpp_int p, mp::cpp_int q);



#endif
