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
	complex(double , double );
	complex(const complex &);

	/*DESTRUCTOR */
	~complex() ;

	/*FUNCIONES */
	double getReal();
	double getImag() ;

	//double getAbs();

	void setReal(double);
	void setImag(double);

	complex operator*(double);
	complex operator+(const complex &);
	complex operator-(const complex &);
	complex& operator = (const complex &);


};

#endif
