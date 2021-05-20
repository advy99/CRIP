#ifndef FUNCIONES_P3_HPP
#define FUNCIONES_P3_HPP

#include <boost/dynamic_bitset.hpp>
#include <iostream>
#include <vector>

#include <boost/multiprecision/cpp_int.hpp>

namespace mp = boost::multiprecision;


// ejercicio 1
std::vector<mp::cpp_int> crear_secuencia_super_creciente(const unsigned longitud, const mp::cpp_int & margen = 20);
bool comprobar_super_creciente(const std::vector<mp::cpp_int> & secuencia);

std::pair<std::vector<mp::cpp_int>, std::tuple<std::vector<mp::cpp_int>, mp::cpp_int, mp::cpp_int> > generar_llaves(const unsigned longitud_llaves);

mp::cpp_int cifrar_secuencia_bits(const std::vector<bool> & bits, const std::vector<mp::cpp_int> & clave_publica);
std::vector<bool> descifrar(const mp::cpp_int & numero, const std::tuple<std::vector<mp::cpp_int>, mp::cpp_int, mp::cpp_int> & llave_privada);


// ejercicio 2
// precondicion: (p - 1) / 2 también es primo
// coger un alfa hasta que el simbolo de jacobi valga -1
mp::cpp_int encontrar_elemento_primitivo(const mp::cpp_int & primo);

// ejercicio 3 en su main

#endif
