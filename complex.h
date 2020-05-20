/*
 * complex.h
 *
 *  Created on: 10 may. 2020
 *      Author: gerof
 */

#ifndef complex_INCLUDED
#define complex_INCLUDED
#include <iostream>
using namespace std;



class complex {
private:
	double real;
	double imaginario;

public:
	/*CONSTRUCTORES */
	complex();
	complex(const double &, const double &);
	complex(const complex &);

	/*DESTRUCTOR */
	~complex() ;

	/*FUNCIONES */
	double getReal();
	double getImag() ;

	void setReal(const double &);
	void setImag(const double &);

	double C_abs();
	double C_arg();
	void C_exp(const complex &);
	void ln(complex);

	complex operator*(const double &);
	complex operator*(const complex &);
	complex operator*(const int &);
	complex operator+(const complex &);
	complex operator-(const complex &);
	complex& operator = (const complex &);


};

#endif
