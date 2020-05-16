/*
 * pixel.h
 *
 *  Created on: 15 may. 2020
 *      Author: gerof
 */

#ifndef PIXEL_H_
#define PIXEL_H_
#include <iostream>
#include "complex.h"
using namespace std;

class pixel {
public:
	pixel();
	pixel(const pixel&);

	void setColor(int);
	int getColor();
	void setPosition(complex);
	complex getPosition();


	~pixel();

private:
	complex position;
	int color;



};




#endif /* PIXEL_H_ */
