/*
 * imageN.H

 */

#ifndef image_H_
#define image_H_

#include <cmath>
#include <string>
#include "pixel.h"


enum function {
	z,
	exp_z,
	ln_z
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



    /* SOBRECARGA OPERADORES */
    void operator=(const image&); // sobre carga operador=
    image operator*(const int &); // sobre carga operador *


    /* OTROS */
    void exp_z(const image&); // calcula la exponencial de los elementos de la matriz
    void export_to_file(ostream *); //imprime la imagen en un archivo
 	void transformation(const image&, const function &);
 	void id_z(const image&);
 	void ln_z(const image&);

    /*funcion para rotar la imagen
    void rotateimage(int theta, image& old_image);
     bool inBounds(int , int );
    void negateimage(image& old_image);
	*/

 private :
 	string comment;
    int rows; // numero de filas
    int columns; // numero de columnas
    int greys; // numero de grises
    pixel ** pixel_val;


};
#endif /* image_H_ */
