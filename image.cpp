#include <iostream>

#include "image.h"
#include "complex.h"
#include "pixel.h"
#include <cmath>
using namespace std;


/******************** CONSTRUCTORES ************************/
/* constructor por defecto - inicializa los valores en 0 */
image::image(){
	comment = '\0';
	rows = 0;
    columns = 0;
    greys = 0;
    pixel_val = 0;
}

/*constructor a partir del tamaño y cantidad de colores, inicializa
 * la matriz con valor 0
 */
image::image(const int &num_row, const int &num_col, const int &grey_scale){
    comment = '\0';
	rows = num_row;
    columns = num_col;
    greys = grey_scale;

    pixel_val = new pixel* [rows];
    for(int i = 0; i < rows; i++){
        pixel_val[i] = new pixel [columns];
        for(int j = 0; j < columns; j++){
            (pixel_val[i][j]).setColor(0);
        cout << (pixel_val[i][j]).getColor() << '\t';
        }
    }
}
/* constructor a partir de lo recibido por linea de comando */
image::image(istream *is){
	char hashtag;
	(*is) >> hashtag;
	 if (hashtag == '#'){
		 getline(*is,comment);
		 (*is) >> columns;
	 }
	 else{
		 comment = '\0';
		 columns = hashtag;
	 }
	 (*is) >> rows >> greys; //guardo los valores de columna, fila y grises
	 pixel_val = new pixel* [rows];  // pide memoria para las filas

	 /*variables auxiliares */
	 int color;
	 double x = (double) 2/(columns-1);
	 double y = (double) 2/(rows-1);
	 complex x_position(x,0.0);
	 complex y_position(0.0,y);
	 complex init_position(-1, 1);
	 complex init_position_n(-1, 1);

	 for(int r = 0; r < rows; r++){
		 pixel_val[r] = new pixel [columns]; //pido memoria para las columnas
		 init_position_n = init_position - (y_position*r);
		 for (int c = 0; c < columns; c++) {
			 *is >> color;
			 pixel_val[r][c].setColor(color);
			 pixel_val[r][c].setPosition(init_position_n + (x_position*c));
		 }
		 pixel_val[r][0].setPosition(init_position_n);
	 }
}

/* constructor por copia */
image::image(const image& old_image)
{
    rows = old_image.rows;
    columns = old_image.columns;
    greys = old_image.greys;
    pixel_val = new pixel* [rows];

	for(int r = 0; r < rows; r++){
		pixel_val[r] = new pixel [columns];

		for (int c = 0; c < columns; c++) {
			 pixel_val[r][c].setColor(0);
			 pixel_val[r][c].setPosition(old_image.pixel_val[r][c].getPosition());
		 }
	 }
}


/******************** DESTRUCTOR ************************/
image::~image()
{
	comment = "\n";
    rows = 0;
    columns = 0;
    greys = 0;
    for(int i = 0; i < rows; i++)
        delete[] pixel_val [rows];
    delete[] pixel_val;
    pixel_val = NULL;
}


void image::transformation(const image & origen, const function &factor){
	if (factor == 0){
		this->id_z(origen);
	}
	else if (factor == 1){
		this->exp_z(origen);
	}
	else if (factor == 2){
		this->ln_z(origen);
	}
	else if(factor == 3){
		this->add_exp_ln(origen);

	} else if (factor == 4){
		this->negateimage();
	}
	else{
		cerr << "Invalid Transformation function" << endl;
		exit(1);
	}

}


void image::add_exp_ln(const image& old_image){
     rows = old_image.rows;
     columns = old_image.columns;
     greys = old_image.greys;

     image aux(old_image);

     this->exp_z(old_image);
	 aux.ln_z(old_image);

	 pixel_val = new pixel* [rows];

		for(int r = 0; r < rows; r++){
			pixel_val[r] = new pixel [columns];

			for (int c = 0; c < columns; c++) {
			pixel_val[r][c].setColor(pixel_val[r][c].getColor() + aux.pixel_val[r][c].getColor());
			 }
		 }

}

void image::id_z(const image& old_image)
{
    rows = old_image.rows;
    columns = old_image.columns;
    greys = old_image.greys;
    pixel_val = new pixel* [rows];

	for(int r = 0; r < rows; r++){
		pixel_val[r] = new pixel [columns];

		for (int c = 0; c < columns; c++) {
			 pixel_val[r][c].setColor(old_image.pixel_val[r][c].getColor());
			 pixel_val[r][c].setPosition(old_image.pixel_val[r][c].getPosition());
		 }
	 }
}

void image::exp_z(const image & origen)
{
    complex new_value;
	double minimum;
    if (rows < columns){
    	minimum = sqrt(2)*1.0/(rows-1);
    }
    else{
    	minimum = sqrt(2)*1.0/(columns-1);
    }

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
        	new_value.C_exp(pixel_val[i][j].getPosition());
            if(abs(new_value.getReal()) <= 1.0 && abs(new_value.getImag()) <= 1.0)
            {	
			
				double real_part = new_value.getReal();
				double imag_part = new_value.getImag();
				double distance1, distance2;

				int f=-1,h=-1;
				int first_real, last_real, mid_real, first_imag, last_imag, mid_imag;

				first_imag = 0;
				last_imag = rows - 1;
				mid_imag = (first_imag + last_imag)/2;
				while(first_imag<=last_imag)
				{
					if(origen.pixel_val[mid_imag][0].getPosition().getImag() > imag_part)
					{
						first_imag = mid_imag + 1;
					}
					else if (origen.pixel_val[mid_imag][0].getPosition().getImag() == imag_part)
					{
						f = mid_imag;
						break;
					}
					else
					{
						last_imag = mid_imag - 1;
					}
					mid_imag = (first_imag + last_imag)/2;
				}
				if(first_imag>last_imag)
				{
					if (first_imag > (rows-1))
					{
						first_imag = first_imag - 1;
					}
					distance1 = abs(origen.pixel_val[first_imag][0].getPosition().getImag() - imag_part);
					distance2 = abs(origen.pixel_val[last_imag][0].getPosition().getImag() - imag_part);
					if(distance1<=distance2)
					{
						f = first_imag;
					}
					else
					{
						f = last_imag;
					}
					
				}

				first_real = 0;
				last_real = columns - 1;
				mid_real = (first_real + last_real)/2;
				while(first_real<=last_real)
				{
					if(origen.pixel_val[0][mid_real].getPosition().getReal() < real_part)
					{
						first_real = mid_real + 1;
					}
					else if (origen.pixel_val[0][mid_real].getPosition().getReal() == real_part)
					{
						h = mid_real;
						break;
					}
					else
					{
						last_real = mid_real - 1;
					}
					mid_real = (first_real + last_real)/2;
				}
				if(first_real>last_real)
				{
					distance1 = abs(origen.pixel_val[0][first_real].getPosition().getReal() - real_part);
					distance2 = abs(origen.pixel_val[0][last_real].getPosition().getReal() - real_part);
					if(distance1<=distance2)
					{
						h = first_real;
					}
					else
					{
						h = last_real;
					}
					
				}

				if (f >= 0 && h >= 0) {
            	 	pixel_val[i][j].setColor(origen.pixel_val[f][h].getColor());
            	}

            }
        }
    }

}




void image::ln_z(const image & origen)
{
    double minimum;
    complex new_value;
    if (rows > columns){
    	minimum = 2.0/(rows-1);
    }
    else{
    	minimum = 2.0/(columns-1);
    }

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
        	new_value.ln(pixel_val[i][j].getPosition());
            if(abs(new_value.getReal()) <= 1.0 && abs(new_value.getImag()) <= 1.0)
            {	
				double real_part = new_value.getReal();
				double imag_part = new_value.getImag();
				double distance1, distance2;

				//cout << real_part << endl;
				//cout << imag_part << endl;

				int f=-1,h=-1;
				int first_real, last_real, mid_real, first_imag, last_imag, mid_imag;

				first_imag = 0;
				last_imag = rows - 1;
				mid_imag = (first_imag + last_imag)/2;
				while(first_imag<=last_imag)
				{
					//cout << mid_imag << endl;
					if(origen.pixel_val[mid_imag][0].getPosition().getImag() > imag_part)
					{
						first_imag = mid_imag + 1;
					}
					else if (origen.pixel_val[mid_imag][0].getPosition().getImag() == imag_part)
					{
						f = mid_imag;
						break;
					}
					else
					{
						last_imag = mid_imag - 1;
					}
					mid_imag = (first_imag + last_imag)/2;
				}
				if(first_imag>last_imag)
				{
					if (first_imag > (rows-1))
					{
						first_imag = first_imag - 1;
					}
					distance1 = abs(origen.pixel_val[first_imag][0].getPosition().getImag() - imag_part);
					distance2 = abs(origen.pixel_val[last_imag][0].getPosition().getImag() - imag_part);
					if(distance1<=distance2)
					{
						f = first_imag;
					}
					else
					{
						f = last_imag;
					}
					
				}

				first_real = 0;
				last_real = columns - 1;
				mid_real = (first_real + last_real)/2;
				while(first_real<=last_real)
				{
					if(origen.pixel_val[0][mid_real].getPosition().getReal() < real_part)
					{
						first_real = mid_real + 1;
					}
					else if (origen.pixel_val[0][mid_real].getPosition().getReal() == real_part)
					{
						h = mid_real;
						break;
					}
					else
					{
						last_real = mid_real - 1;
					}
					mid_real = (first_real + last_real)/2;
				}
				if(first_real>last_real)
				{
					distance1 = abs(origen.pixel_val[0][first_real].getPosition().getReal() - real_part);
					distance2 = abs(origen.pixel_val[0][last_real].getPosition().getReal() - real_part);
					if(distance1<=distance2)
					{
						h = first_real;
					}
					else
					{
						h = last_real;
					}
					
				}

				if (f >= 0 && h >= 0) {
					//cout << f << ' ' << h << endl;
            	 	pixel_val[i][j].setColor(origen.pixel_val[f][h].getColor());
            	}


            }
        }
    }

}


void image::negateimage()
{

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
            pixel_val[i][j].setColor(-(pixel_val[i][j]).getColor() + 255);
    }

}





void image::export_to_file(ostream *os){
	(*os) << "P2" <<endl;
	(*os) << "# " << comment <<endl;
	(*os) << columns << " " << rows << endl;
	(*os) << greys << endl;

	for(int i = 0; i < rows; i++){
          for(int j = 0; j < columns; j++){
        	  (*os) << pixel_val[i][j].getColor() << " ";
          }
          (*os) << endl;
    }

}

void image::setimage( int &num_rows,  int &num_cols,  int &grey_scale)
{
    rows = num_rows;
    columns = num_cols;
    greys = grey_scale;
}

/**
 * returns the number of rows, columns and gray levels
 */
void image::getimage(int &num_rows,  int &num_cols,  int &grey_scale)
{
    num_rows = rows;
    num_cols = columns;
    grey_scale = greys;

}

void image::setRows(const int &num_rows){
		rows = num_rows;
}

void image::setColumns(const int &num_columns){
	columns = num_columns;
}

void image::setGreys(const int &grey_scale){
	 greys = grey_scale;
}


int& image::getRows(){
	return rows;
}

int& image::getColumns(){
	return columns;
}

int& image::getGreys(){
	return greys;
}

/**
 * returns the gray value of a specific pixel
 */

int image::getPixelColor(const int num_row, const int num_col)
{
	if ((rows < num_row) || (columns < num_col)){
		cerr << "error: very long rows or columns" <<endl;
		exit(1);
	}

    return pixel_val[num_row][num_col].getColor();
}
/**
 * sets the gray value of a specific pixel
 *
void image::setPixelColor(int row, int col, int value)
{
    pixel_val[row][col] = value;
}
*/
/**
 * checks to see if a pixel is within the image, returns true or false

bool image::inBounds(int row, int col)
{
    if(row >= rows || row < 0 || col >=columns || col < 0)
        return false;
    //else
    return true;
}
*/






/**
 * negates image
 *
void image::negateimage(image& old_image)
{
    int rows, cols, gray;
     = N;
    cols = M;
    gray = Q;

    image tempimage(N,M,Q);

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
            tempimage.pixelVal[i][j] = -(pixelVal[i][j]) + 255;
    }

    old_image = tempimage;
}
 */

/**
 * based on users input and rotates it around the center of the image
 **/
/*void image::rotateimage(int theta, image& old_image)
    {
        int r0, c0;
        int r1, c1;
        int rows, cols;
        rows = old_image.N;
        cols = old_image.M;
        image tempimage(rows, cols, old_image.Q);

        float rads = (theta * 3.14159265)/180.0;

        r0 = rows / 2;
        c0 = cols / 2;

        for(int r = 0; r < rows; r++)
        {
        for(int c = 0; c < cols; c++)
        {
            r1 = (int) (r0 + ((r - r0) * cos(rads)) - ((c - c0) * sin(rads)));
            c1 = (int) (c0 + ((r - r0) * sin(rads)) + ((c - c0) * cos(rads)));

            if(inBounds(r1,c1))
            {
                tempimage.pixelVal[r1][c1] = old_image.pixelVal[r][c];
            }
        }
        }

        for(int i = 0; i < rows; i++)
        {
        for(int j = 0; j < cols; j++)
        {
            if(tempimage.pixelVal[i][j] == 0)
                tempimage.pixelVal[i][j] = tempimage.pixelVal[i][j+1];
        }
        }
        old_image = tempimage;
    }
   */
