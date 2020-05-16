/*
 * imageN.H
 *
 *  Created on: 10 may. 2020
 *      Author: gerof
 */

#ifndef image_H_
#define image_H_

#include <cmath>
#include "pixel.h"

#define SIDE 2;


class image {
 public:
	/*constructores */
    image();
    image(const int ,const int , const int );
    image(const image& old_image);
    image(istream *is);

    /*destructores */
    ~image();

    /*setear parametros imagen*/
    void setimage(int num_row, int num_col, int grey_scale);

    /*obtener parametros imagen */
    void getimage(int &num_row, int &num_col, int &grey_scale);

    /* sobre carga operador = */
    void operator=(const image&);

    /*funcion para rotar la imagen
    void rotateimage(int theta, image& old_image);
     */

    /*setear el valor del pixel */
    void setPixelColor(int row, int col, int value);


    /* obtener valor de un pixel */
    int getPixelColor(int row, int col);




    bool inBounds(int row, int col);

    /*
    void negateimage(image& old_image);
	*/

    int getRows();
    int getColumns();
    int getGreys();


    void setRows(int &);

    void setColumns(int &);

    void setGreys(int &);



 private :
    int rows; // number of rows
    int columns; // number of columns
    int greys; // number of gray levels
    pixel ** pixel_val;


};
#endif /* image_H_ */
