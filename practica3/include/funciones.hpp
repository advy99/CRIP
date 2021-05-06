#ifndef FUNCIONES_P3_HPP
#define FUNCIONES_P3_HPP

#include <boost/dynamic_bitset.hpp>
#include <iostream>
#include <vector>

#include <boost/multiprecision/cpp_int.hpp>

namespace mp = boost::multiprecision;


// ejercicio 1
std::vector<int> crear_secuencia_super_creciente(const unsigned longitud, const unsigned margen);
bool comprobar_super_creciente(const std::vector<int> & secuencia);





#endif
