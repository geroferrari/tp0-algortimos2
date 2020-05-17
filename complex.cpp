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

//double complex::getAbs(){
//    double
//}


void complex::setReal(double xx){
	real=xx;
}

void complex::setImag(double yy){
	imaginario=yy;
}


complex complex:: operator*(double c){
	return complex (real * c, imaginario *c );
}

complex complex::operator+(const complex &d){
	return complex(real + d.real , imaginario + d.imaginario );
}
complex complex::operator-(const complex &e){
	return complex(real - e.real , imaginario - e.imaginario);
}


complex& complex ::operator= (const complex & b){
	real = b.real;
	imaginario= b.imaginario;
return *this;
}



