/*
 * complex.h
 *
 *  Created on: 10 may. 2020
 *      Author: gerof
 */

#ifndef complex_INCLUDED
#define complex_INCLUDED

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

	void setReal(double);
	void setImag(double);

	complex sumar (const complex &);
	complex sumar (double);
	complex& operator = (const complex &);
};

#endif
