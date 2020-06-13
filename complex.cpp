/*
 * complex.cpp
 *
 */
#include <cmath>
#include "complex.h"



complex ::complex (){
	real=0.0;
	imaginario=0.0;
}

complex ::complex (const complex & c){
	real=c.real;
	imaginario=c.imaginario;
}

complex ::complex (const double& a, const double& b){
	real=a;
	imaginario=b;
}

complex:: ~complex(){
	real = 0;
	imaginario =0;
}

double complex::get_real(){
	return real;
}

double complex::get_imag(){
	return imaginario;
}

void complex::set_real(const double & xx){
	real=xx;
}

void complex::set_imag(const double & yy){
	imaginario=yy;
}


complex complex:: operator*(const int & c){
	return  complex (real *c, imaginario *c );
}

complex complex:: operator*(const double &c){
	return complex (real * c, imaginario *c );
}



complex complex:: operator*(const complex &c){
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

double complex::c_abs(){
	return  sqrt(real * real + imaginario * imaginario);
}

double complex::c_arg(){
	if (real > 0) {
		return atan(imaginario/real);
	}
	else if (real < 0){
		if(imaginario >=0){
			return (atan(imaginario/real) + M_PI);
		}
		else if (imaginario <0){
			return (atan(imaginario/real) - M_PI);
		}
	}
	else if (real == 0) {
		if(imaginario == 0){
			return 0.0;
		}
		else if (imaginario > 0){
			return (M_PI/2);
		}
		else if (imaginario < 0) {
			return  (-M_PI/2);
		}
	  }
	return 0;
}

void complex::c_exp(const complex & c){
	real = exp(c.real)*cos(c.imaginario);
	imaginario = exp(c.real)*sin(c.imaginario);
}

void complex::ln(complex c){
	real = log(c.c_abs());
	imaginario = c.c_arg();
}

complex& complex ::operator= (const complex & c){
	real = c.real;
	imaginario= c.imaginario;
return *this;
}



