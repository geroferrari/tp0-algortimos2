/*
 * imageN.H
 *
 *  Created on: 10 may. 2020
 *      Author: gerof
 */

#ifndef image_H_
#define image_H_

#include <cmath>


class image {
 public:
	/*constructores */
    image();
    image(int num_row, int num_col, int gray_level);
    image(const image& old_image);

    /*destructores */
    ~image();

    /*setear parametros imagen*/
    void setimage(int num_row, int num_col, int max_val);

    /*obtener parametros imagen */
    void getimage(int &num_row, int &num_col, int &max_val);

    /* sobre carga operador = */
    void operator=(const image&);

    /*funcion para rotar la imagen */
    void rotateimage(int theta, image& old_image);

    /*setear el valor del pixel */
    void setPixelVal(int row, int col, int value);

    /* obtener valor de un pixel */
    int getPixelVal(int row, int col);


    bool inBounds(int row, int col);
    void negateimage(image& old_image);

 private :
    int rows; // number of rows
    int columns; // number of columns
    int greys; // number of gray levels
    int **pixel_val;

};
#endif /* image_H_ */
