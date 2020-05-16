/*
 * pixel.cpp
 *
 *  Created on: 15 may. 2020
 *      Author: gerof
 */
#include <iostream>
#include "image.h"
#include "pixel.h"

using namespace std;

	pixel::pixel(){
		color = 0;
	}

	pixel::pixel(const pixel& p){
		position = p.position;
		color = p.color;
	}

	void pixel::setColor(int pix){
		color = pix;
	}

	int pixel::getColor(){
		return color;
	}


	void pixel::setPosition(complex c){
		position = c;
	}

	complex pixel::getPosition(){
		return position;
	}


	pixel::~pixel(){
		position.~complex();
		color = 0;
	}
