/*
 * imageN.H
 */

#ifndef image_H_
#define image_H_

#include <string>
#include <iostream>
#include "pixel.h"
using namespace std;

enum function {
	z,
	exp_z,
	ln_z,
	exp_add_ln,
	negative
};

class image {
 public:
    /******************** CONSTRUCTORES ************************/
    image();
    image(const int &, const int &, const int &);
    image(const image &);
    image(istream *);

    /******************** DESTRUCTOR ************************/
    ~image();


    /************************METODOS************************/
    /* GETTERS AND SETTERS */
    void set_image( int &,  int &,  int &); // setea parametros imagen
    void get_image( int &,  int &,  int &); // obtiene parametros imagen

    void set_pixel_color(const int &, const int &, const int &); //setea el valor de un pixel
    int get_pixel_color(const int , const int ); // obtiene el valor de un pixel

    void set_rows(const int &); // setea el numero de filas
    int& get_rows();  // obtiene el numero de filas
    void set_columns(const int &); //setea el numero de columnas
    int& get_columns(); // obtiene el numero de columnas
    void set_greys(const int &); //setea la cantidad de grises
    int& get_greys(); // obtiene la cantidad de grises



    /* SOBRECARGA OPERADORES */
    void operator=(const image&); // sobre carga operador=
    image operator*(const int &); // sobre carga operador *


    /* OTROS */
    void exp_z(const image&); // calcula la exponencial de los elementos de la matriz
    void export_to_file(ostream *); //imprime la imagen en un archivo
 	void transformation(const image&, const function &);
 	void id_z(const image&);
 	void ln_z(const image&);
 	void add_exp_ln(const image&);
 	void negate_image(const image& );

 private :
 	string comment;
    int rows; // numero de filas
    int columns; // numero de columnas
    int greys; // numero de grises
    pixel ** pixel_val;


};
#endif /* image_H_ */
