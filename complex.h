/*
 * complex.h
 *
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
	complex(const double &, const double &);
	complex(const complex &);

	/*DESTRUCTOR */
	~complex() ;

	/*FUNCIONES */
	double get_real();
	double get_imag() ;

	void set_real(const double &);
	void set_imag(const double &);

	double c_abs();
	double c_arg();
	void c_exp(const complex &);
	void ln(complex);

	complex operator*(const double &);
	complex operator*(const complex &);
	complex operator*(const int &);
	complex operator+(const complex &);
	complex operator-(const complex &);
	complex& operator = (const complex &);


};

#endif
