/*
 * complex.h
 *
 */

#ifndef complex_INCLUDED
#define complex_INCLUDED

#include <iostream>
using namespace std;

class complex {

public:
	/***************** CONSTRUCTORES  *****************/
	complex(); // constructor por defecto
	complex(const double &, const double &);
	complex(const complex &); //constructor por copia

	/********************* DESTRUCTOR  ****************/
	~complex() ;

	/****************** GETTERS AND SETTERS ***************/
	double getReal();  //devuelve parte real
	void setReal(const double &); //setea parte real
	double getImag() ; //devuelve parte compleja
	void setImag(const double &); //setea parte compleja

	/******************* FUNCIONES MATEMATICAS ********************/
	double C_abs(); // devuelve el modulo del complejo
	double C_arg(); // devuelve el argumento del complejo
	void C_exp(const complex &); // calcula la exponencial compleja
	void ln(complex); // calcula el ln complejo

	/********************** SOBRECARGA DE OPERADORES ***************/
	complex operator*(const double &);
	complex operator*(const complex &);
	complex operator*(const int &);
	complex operator+(const complex &);
	complex operator-(const complex &);
	complex& operator = (const complex &);

private:
	double real;
	double imaginario;
};

#endif
