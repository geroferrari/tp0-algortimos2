/*
 * imageN.H

 */

#ifndef image_H_
#define image_H_

#include <cmath>
#include <string>
#include "pixel.h"

/* tipo enumerativo para elegir que funcion se le aplicara a la imagen */
/* la variable global "factor" declarada en el main es de tipo enumerativo "function" */
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
    image(); //constructor por defecto
    image(const int &, const int &, const int &); //constructor a partir del tamaño y cantidad de colores
    image(const image &); //constructor por copia
    image(istream *); //constructor a partir de lo que lee de cmdline

    /******************** DESTRUCTOR ************************/
    ~image();


    /******************* GETTERS AND SETTERS*********************/
    void setimage( int &,  int &,  int &); // setea parametros imagen
    void getimage( int &,  int &,  int &); // obtiene parametros imagen

    void setPixelColor(const int &, const int &, const int &); //setea el valor de un pixel
    int getPixelColor(const int , const int ); // obtiene el valor de un pixel

    void setRows(const int &); // setea el numero de filas
    int& getRows();  // obtiene el numero de filas
    void setColumns(const int &); //setea el numero de columnas
    int& getColumns(); // obtiene el numero de columnas
    void setGreys(const int &); //setea la cantidad de grises
    int& getGreys(); // obtiene la cantidad de grises



    /****************** FUNCIONES MATEMATICAS  **********************/
    void exp_z(const image&); // calcula la exponencial de los elementos de la imagen original
 	void id_z(const image&); // calcula el producto de la imagen original por la identidad
 	void ln_z(const image&); // calcula el logaritmo natural de los elementos de la imagen original
 	void add_exp_ln(const image&); // suma el resultado de aplicar el ln y la exp.

 	/******************* OTROS **************************************/
    void export_to_file(ostream *); //imprime la imagen en un archivo
 	void negateimage(); // invierte los colores de la imagen
 	void transformation(const image&, const function &); //elige que funcion se va a utilizar


 private :
 	string comment; // comentario al inicio de la imagen
    int rows; // numero de filas
    int columns; // numero de columnas
    int greys; // numero de grises
    pixel ** pixel_val;
};

#endif /* image_H_ */
