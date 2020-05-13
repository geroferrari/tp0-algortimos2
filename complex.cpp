/*
 * complex.cpp
 *
 *  Created on: 10 may. 2020
 *      Author: gerof
 */

#include "complex.h"

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

complex complex:: sumar (const complex &r){
	return complex (real+r.real , imaginario+r.imaginario);
}

complex complex:: sumar (double f){
	return complex (real+f, imaginario);
}

complex& complex ::operator= (const complex & b){
	real = b.real;
	imaginario= b.imaginario;
return *this;
}


