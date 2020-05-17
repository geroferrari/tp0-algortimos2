/*
 * complex.cpp
 *
 *  Created on: 10 may. 2020
 *      Author: gerof
 */
#include <iostream>
#include <cmath>
#include "complex.h"

using namespace std;

complex ::complex (){
	real=0.0;
	imaginario=0.0;
}

complex ::complex (const complex & c){
	real=c.real;
	imaginario=c.imaginario;
}

complex ::complex (double a, double b){
	real=a;
	imaginario=b;
}

complex:: ~complex(){
	real = 0;
	imaginario =0;
}

double complex::getReal(){
	return real;
}

double complex::getImag(){
	return imaginario;
}

void complex::setReal(double xx){
	real=xx;
}

void complex::setImag(double yy){
	imaginario=yy;
}


complex complex:: operator*(int c){
	return complex (real * c, imaginario *c );
}

complex complex:: operator*(double &c){
	return complex (real * c, imaginario *c );
}



complex complex:: operator*( complex &c){
	return complex (real * c.real, imaginario *c.imaginario );
}

// a=b+c
// destino.Exp(origen)

complex complex::operator+(const complex &c){
	return complex(real + c.real , imaginario + c.imaginario );
}
complex complex::operator-(const complex &c){
	return complex(real - c.real , imaginario - c.imaginario);
}

double complex::C_abs(){
	return  (double)sqrt(real * real + imaginario * imaginario);
}

complex& complex ::operator= (const complex & c){
	real = c.real;
	imaginario= c.imaginario;
return *this;
}



