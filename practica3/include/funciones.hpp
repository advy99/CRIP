#ifndef FUNCIONES_P3_HPP
#define FUNCIONES_P3_HPP

#include <boost/dynamic_bitset.hpp>
#include <iostream>
#include <vector>

#include <boost/multiprecision/cpp_int.hpp>

namespace mp = boost::multiprecision;


// ejercicio 1
std::vector<mp::cpp_int> crear_secuencia_super_creciente(const unsigned longitud, const unsigned margen = 500);
bool comprobar_super_creciente(const std::vector<mp::cpp_int> & secuencia);

std::pair<std::vector<mp::cpp_int>, std::tuple<std::vector<mp::cpp_int>, mp::cpp_int, mp::cpp_int> > funcion_mochila(const unsigned longitud_llaves);



#endif
