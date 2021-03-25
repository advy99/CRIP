#ifndef FUNCIONES_P2_HPP
#define FUNCIONES_P2_HPP

#include <boost/dynamic_bitset.hpp>
#include <iostream>
#include <vector>

#include <boost/multiprecision/cpp_int.hpp>

namespace mp = boost::multiprecision;

boost::dynamic_bitset<> desplazar_rotacion_izq(const boost::dynamic_bitset<> bitset, const int n);
boost::dynamic_bitset<> desplazar_rotacion_der(const boost::dynamic_bitset<> bitset, const int n);

bool cumple_postulados_golomb(boost::dynamic_bitset<> bitset);


#endif
