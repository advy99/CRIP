#ifndef FUNCIONES_P2_HPP
#define FUNCIONES_P2_HPP

#include <boost/dynamic_bitset.hpp>
#include <iostream>
#include <vector>

#include <boost/multiprecision/cpp_int.hpp>

namespace mp = boost::multiprecision;

boost::dynamic_bitset<> desplazar_rotacion_izq(const boost::dynamic_bitset<> bitset, const int n);
boost::dynamic_bitset<> desplazar_rotacion_der(const boost::dynamic_bitset<> bitset, const int n);

bool cumple_primer_postulado_golomb(const boost::dynamic_bitset<> & bitset);
bool cumple_segundo_postulado_golomb(const boost::dynamic_bitset<> & bitset);
bool cumple_tercer_postulado_golomb(const  boost::dynamic_bitset<> & bitset);


bool cumple_postulados_golomb(const boost::dynamic_bitset<> & bitset);


// ejercicio 2
bool aplicar_polinomio_LFSR(const boost::dynamic_bitset<> & polinomio, const boost::dynamic_bitset<> & semilla_actual);
boost::dynamic_bitset<> LFSR(const boost::dynamic_bitset<> & polinomio, const boost::dynamic_bitset<> & semilla, const signed long long longitud);


// ejercicio 3
bool aplicar_polinomio_NLFSR(const std::vector<boost::dynamic_bitset<> > & polinomio, const boost::dynamic_bitset<> & semilla);

boost::dynamic_bitset<> NLFSR(const std::vector<boost::dynamic_bitset<> > & polinomio,
									   const boost::dynamic_bitset<> & semilla,
									   const signed long long longitud);


// ejercicio 4

boost::dynamic_bitset<> generador_geffe(const std::pair<boost::dynamic_bitset<>, boost::dynamic_bitset<> > & lfsr1,
													 const std::pair<boost::dynamic_bitset<>, boost::dynamic_bitset<> > & lfsr2,
												 	 const std::pair<boost::dynamic_bitset<>, boost::dynamic_bitset<> > & lfsr3,
												 	 const int longitud);


boost::dynamic_bitset<> cadena_a_bitset(const std::string & cadena);

std::string bitset_a_cadena(const boost::dynamic_bitset<> & bitset);

#endif
