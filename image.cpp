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
        }
    }
}

/* constructor a partir de lo recibido por linea de comando */
image::image(istream *is){
	string hashtag;
	/* primero se verifica si la imagen posee comentario */
	(*is) >> hashtag;
	if (hashtag[0] == '#'){
		 getline(*is,comment); // si tiene comentario se lo guarda
		 comment = hashtag + comment;
		 (*is) >> columns; // obtiene el tamaño de las columnas
	}
	 else{
		 comment = '\0'; // si no tiene comentario guarda un "\0"
		 columns = stoi(hashtag); //si no tiene comentarios, lo que leyó antes era el tamaño de las columnas
	 }

	 (*is) >> rows >> greys; //guarda el valor de las  filas y de la escala grises
	 pixel_val = new pixel* [rows];  // pide memoria para las filas

	 /*variables auxiliares */
	 int color;
	 /* se definen los saltos entre posiciones */
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
	/* copio los valores de la imagen pasada en la nueva imagen */
	comment = old_image.comment;
    rows = old_image.rows;
    columns = old_image.columns;
    greys = old_image.greys;

    pixel_val = new pixel* [rows]; // pide memoria para filas

	for(int r = 0; r < rows; r++){
		pixel_val[r] = new pixel [columns]; // pide memoria para columnas

		for (int c = 0; c < columns; c++) {
			 pixel_val[r][c].setColor(0); // se crea con todos los valores en 0 (color negro )
			 pixel_val[r][c].setPosition(old_image.pixel_val[r][c].getPosition()); //se copian las posiciones de la imagen de origen
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

/*  a partir del factor que elige el usuario, se elige que funcion se va a utilizar */
void image::transformation(const image & origen, const function &factor){
	if (factor == 0){ // en la posicion 0 esta la variable z
		this->id_z(origen);
	}
	else if (factor == 1){ // en la posicion 1 esta la variable exp_z
		this->exp_z(origen);
	}
	else if (factor == 2){ // en la posicion 2 esta la variable ln_z
		this->ln_z(origen);
	}
	else if(factor == 3){ // en la posicion 3 esta la variable add_exp_ln
		this->add_exp_ln(origen);

	} else if (factor == 4){ //en la posicion 4 esta la variable negate
		this->negateimage();
	}
	else{
		cerr << "Invalid Transformation function" << endl;
		exit(1);
	}

}




/* funcion que calcula la multiplicacion de la imagen original por la matriz identidad */
void image::id_z(const image& old_image)
{
	/* se copian los valores de la imagen original */
    rows = old_image.rows;
    columns = old_image.columns;
    greys = old_image.greys;

    pixel_val = new pixel* [rows]; // se pide memoria para las filas

	for(int r = 0; r < rows; r++){
		pixel_val[r] = new pixel [columns]; //se pide memoria para las columnas

		for (int c = 0; c < columns; c++) {
			 pixel_val[r][c].setColor(old_image.pixel_val[r][c].getColor()); // se copia el color de cada pixel de la imagen original
		 }
	 }
}

/* se calcula el exponente complejo de cada posicion de los pixels de la imagen */
void image::exp_z(const image & origen)
{
	/* variables auxiliares */
    complex new_value;
    double minimum;

   /* se inicializa el valor minimo con el que se correlaciona la distancia a una posicion */
    if (rows < columns){
    	minimum = sqrt(2)/(rows-1);
    }
    else{
    	minimum = sqrt(2)/(columns-1);
    }

    /* recorre la matriz de salida */
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
        	new_value.C_exp(pixel_val[i][j].getPosition()); //calculo la exponencial compleja de cada posicion de la matriz de salida
            if(abs(new_value.getReal()) <= 1.0 && abs(new_value.getImag()) <= 1.0)
            { //se corrobora que el valor obtenido entre en las dimensiones de la imagen
            	double minimum_distance = minimum;
            	double distance = 0;
            	int f=-1,h=-1; // se inicializan negativos para no acceder a un lugar probable

            	if (new_value.getReal() >= 0 && new_value.getImag() > 0){ //chequea si el pixel esta en el primer cuadrante de la imagen
            		for(int r = 0; r < origen.rows/2 && (minimum_distance >= minimum); r++){
            			for (int c=origen.columns/2; c < origen.columns && (minimum_distance >= minimum) ; c++){
            				// se recorre el cuadrante hasta que  se llegue al limite o la minima distancia
            				// sea menor a la distancia seteada
            				distance = (new_value - origen.pixel_val[r][c].getPosition()).C_abs();
            				if(minimum_distance > distance){
            					minimum_distance = distance; //si es menor, se actualiza la minima distancia
            					f=r; //se guarda la posicion de dicha distancia
            					h=c;
            				}
            			}
            		}
            	}
            	/* se realiza el mismo procedimiento  en el 4to cuadrante */
            	else if (new_value.getReal() >= 0 && new_value.getImag() <= 0){

            		for(int r = origen.rows/2; r < origen.rows && (minimum_distance >= minimum); r++){
            			for (int c=origen.columns/2; c < origen.columns && (minimum_distance >= minimum); c++){
            				distance = (new_value - origen.pixel_val[r][c].getPosition()).C_abs();
            				if(minimum_distance > distance){
            					minimum_distance = distance;
            					f=r;
            					h=c;
            				}
            			}
            		}
            	}
            	/* si se encontro distancia minima, se guarda el color de esa posicion */
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
    	minimum = sqrt(2)/(rows-1);
    }
    else{
    	minimum = sqrt(2)/(columns-1);
    }

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
        	new_value.ln(pixel_val[i][j].getPosition());
            if(abs(new_value.getReal()) <= 1.0 && abs(new_value.getImag()) <= 1.0)
            {
            	double minimum_distance = minimum;
            	double distance = 0;
            	int f=-1,h=-1;
            	if (new_value.getReal() < 0 && new_value.getImag() > 0){
            				cout << "1" << endl;
            		for(int r = 0; r < origen.rows/2 && (minimum_distance >= minimum); r++){
            			for (int c=0; c < origen.columns/2  && (minimum_distance >= minimum); c++){
            				distance = (new_value - origen.pixel_val[r][c].getPosition()).C_abs();
            				if(minimum_distance > distance ){
            					minimum_distance = distance;
            					f=r;
            					h=c;

            				}
            			}
            		}
            	}
            	if (new_value.getReal() >= 0 && new_value.getImag() > 0){
    				cout << "2" << endl;

            		for(int r = 0; r < origen.rows/2 && (minimum_distance >= minimum); r++){
            			for (int c=origen.columns/2; c < origen.columns && (minimum_distance >= minimum); c++){

            				distance = (new_value - origen.pixel_val[r][c].getPosition()).C_abs();
            				if(minimum_distance > distance ){
            					minimum_distance = distance;
            					f=r;
            					h=c;

            				}
            			}
            		}
            	}
            	if (new_value.getReal() < 0 && new_value.getImag() <= 0){
    				cout << "3" << endl;

            		for(int r = origen.rows/2; r < origen.rows && (minimum_distance >= minimum); r++){
            			for (int c=0; c < origen.columns/2  && (minimum_distance >= minimum); c++){

            				distance = (new_value - origen.pixel_val[r][c].getPosition()).C_abs();
            				if(minimum_distance > distance){
            					minimum_distance = distance;
            					f=r;
            					h=c;

            				}
            			}
            		}
            	}
            	if (new_value.getReal() >= 0 && new_value.getImag() <= 0){
    				cout << "4" << endl;

            		for(int r = origen.rows/2; r < origen.rows && (minimum_distance >= minimum); r++){
            			for (int c=origen.columns/2; c < origen.columns  && (minimum_distance >= minimum); c++){

            				distance = (new_value - origen.pixel_val[r][c].getPosition()).C_abs();
            				if(minimum_distance > distance ){
            					minimum_distance = distance;
            					f=r;
            					h=c;

            				}
            			}
            		}
            	}
            	if (f >= 0 && h >= 0) {
            		pixel_val[i][j].setColor(origen.pixel_val[f][h].getColor());
            	}
            }

        }
    }

}

void image::add_exp_ln(const image& old_image){
     rows = old_image.rows;
     columns = old_image.columns;
     greys = old_image.greys;

     image aux(old_image);

     this->exp_z(old_image);
	 aux.ln_z(old_image);

		for(int r = 0; r < rows; r++){
			for (int c = 0; c < columns; c++) {
			pixel_val[r][c].setColor(pixel_val[r][c].getColor() + aux.pixel_val[r][c].getColor());
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
	(*os) << comment <<endl;
	(*os) << columns << " " << rows << endl;
	(*os) << greys << endl;

	for(int i = 0; i < rows; i++){
          for(int j = 0; j < columns; j++){
        	  (*os) << pixel_val[i][j].getColor() << " ";
          }
          (*os) << endl;
    }

}


/******************* GETTERS AND SETTERS*********************/

/* se setean las variables de la imagen */
void image::setimage( int &num_rows,  int &num_cols,  int &grey_scale){
    rows = num_rows;
    columns = num_cols;
    greys = grey_scale;
}

/* se obtienen los valores de la imagen */
void image::getimage(int &num_rows,  int &num_cols,  int &grey_scale){
    num_rows = rows;
    num_cols = columns;
    grey_scale = greys;
}

/* se setea la cantidad de filas */
void image::setRows(const int &num_rows){
		rows = num_rows;
}
/* se obtiene la cantidad de filas */
int& image::getRows(){
	return rows;
}


/* se setea la cantidad de columnas */
void image::setColumns(const int &num_columns){
	columns = num_columns;
}
/* se obtiene la cantidad de columnas */
int& image::getColumns(){
	return columns;
}

/* se setea la cantidad de grises */
void image::setGreys(const int &grey_scale){
	 greys = grey_scale;
}
/* se obtiene la cantidad de grises */
int& image::getGreys(){
	return greys;
}


int image::getPixelColor(const int num_row, const int num_col)
{
	if ((rows < num_row) || (columns < num_col)){
		cerr << "error: very long rows or columns" <<endl;
		exit(1);
	}

    return pixel_val[num_row][num_col].getColor();
}






