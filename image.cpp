#include "image.h"

/* Crea imagen 0x0 */

image::image(){
   rows = 0;
    columns = 0;
    greys = 0;
    pixel_val = 0;
}


image::image(int num_rows, int num_cols, int gray_levels)
{
    rows = num_rows;
    columns = num_cols;
    greys = gray_levels;
    pixel_val = new int *[rows];

    for(int i = 0; i < rows; i++)
    {
        pixel_val[i] = new int [columns];
        for(int j = 0; j < columns; j++)
            pixel_val[i][j] = 0;
    }
}

/**
 * destroy image
 */
image::~image()
{
    rows = 0;
    columns = 0;
    greys = 0;
    for(int i = 0; i < rows; i++)
        delete pixel_val [rows];
    delete pixel_val;
    pixel_val = 0;
}


image::image(const image& old_image)
{
    rows = old_image.rows;
    columns = old_image.columns;
    greys = old_image.greys;

    pixel_val = new int* [rows];
    for(int i = 0; i < rows; i++)
    {
        pixel_val[i] = new int [columns];
        for(int j = 0; j < columns; j++)
            pixel_val[i][j] = old_image.pixel_val[i][j];
    }
}

/**
 * copies old_image into whatever you = it to
 *
 * @param old_image object image
 */
void image::operator=(const image& old_image)
{
    rows = old_image.rows;
    columns = old_image.columns;
    greys = old_image.greys;

    pixel_val = new int* [rows];
    for(int i = 0; i < rows; i++)
    {
        pixel_val[i] = new int [columns];
        for(int j = 0; j < columns; j++)
            pixel_val[i][j] = old_image.pixel_val[i][j];
    }
}

/**
 * sets the number of rows, columns and graylevels
 *
 */
void image::setimage(int num_rows, int num_cols, int max_val)
{
    rows = num_rows;
    columns = num_cols;
    greys = max_val;
}

/**
 * returns the number of rows, columns and gray levels
 */
void image::getimage(int &num_rows, int &num_cols, int &max_val)
{
    num_rows = rows;
    num_cols = columns;
    max_val = greys;
}

/**
 * returns the gray value of a specific pixel
 */
int image::getPixelVal(int num_row, int num_col)
{
    return pixel_val[num_row][num_col];
}

/**
 * sets the gray value of a specific pixel
 */
void image::setPixelVal(int row, int col, int value)
{
    pixel_val[row][col] = value;
}

/**
 * checks to see if a pixel is within the image, returns true or false
 */
bool image::inBounds(int row, int col)
{
    if(row >= rows || row < 0 || col >=columns || col < 0)
        return false;
    //else
    return true;
}

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
 *
void image::rotateimage(int theta, image& old_image)
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
