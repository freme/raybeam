// image.cc

#include "image.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Image::Image()
{}

Image::Image(int width, int height)
{
    nx=width;
    ny=height;

    // alloc mem 4 raster
    raster = new rgb*[nx];
    for (int i = 0; i < nx; i++)
        raster[i] = new rgb[ny];
}

Image::Image(int width, int height, rgb background)
{
    nx=width;
    ny=height;

    // alloc mem 4 raster
    raster = new rgb*[nx];
    for (int i = 0; i < nx; i++)
    {
        raster[i] = new rgb[ny];
        for (int j = 0; j < ny; j++)
            raster[i][j] = background;
    }
}

bool Image::set(int x, int y, const rgb& color)
{
    // check out of bounds err
    if (0 > x || x > nx) return false;
    if (0 > y || x > ny) return false;

    raster[x][y] = color;
    return true;
}

void Image::gammaCorrect(float gamma)
{
    rgb tmp;
    float power = 1.0 / gamma;
    for (int i = 0; i < nx; i++)
        for (int j = 0; j < ny; j++)
        {
            tmp = raster[i][j];
            raster[i][j] = rgb(pow(tmp.r(), power),
                               pow(tmp.g(), power),
                               pow(tmp.b(), power));
        }
}

void Image::writePPM(ostream& out)
{
    // PPM header
    out << "P6\n";
    out << nx << ' ' << ny << '\n';
    out << "255\n";

    int i, j;
    unsigned int ired, igreen, iblue;
    unsigned char red, green, blue;

    // output clamped values, range [0...255]
    // PPM start in the upper left of the picture
    // A raster of Height rows, in order from top to bottom. 
    // Each row consists of Width pixels, in order from left to right.
    // the outer(first loop has to be the height
    // so the inner(second) loop has to be the width
    for (i = ny-1; i >= 0; i--)
        for (j = 0; j < nx; j++)
        {
            raster[j][i].clamp();
            ired = (unsigned int) (255*raster[j][i].r());
            igreen = (unsigned int) (255*raster[j][i].g());
            iblue = (unsigned int) (255*raster[j][i].b());
            red = (unsigned char) (ired);
            green = (unsigned char) (igreen);
            blue = (unsigned char) (iblue);
            out.put(red);
            out.put(green);
            out.put(blue);
        }
}

// read in a binary PPM
void Image::readPPM(string file_name)
{
    // open file
    ifstream in;
    in.open(file_name.c_str());
    if (!in.is_open())
    {
        cerr << " Error:\t couldn't open file\'" << file_name << "\'.\n";
        exit(-1);
    }

    char ch, type;
    char red, green, blue;
    int i, j, cols, rows, num;

    // read header
    in.get(ch);
    in.get(type);
    in >> cols >> rows >> num;

    nx = cols;
    ny = rows;

    // alloc raster
    raster = new rgb*[nx]; // array of pointers;
    for (i=0; i < nx; i++)
        raster[i] = new rgb[ny];

    // consume newline
    in.get(ch);

    // write pixel-values to raster
    for (i = ny-1; i >= 0; i--)
        for (j = 0; j < nx; j++)
        {
            in.get(red);
            in.get(green);
            in.get(blue);
            raster[j][i] = rgb((float)((unsigned char)red)/255.0,
                               (float)((unsigned char)green)/255.0,
                               (float)((unsigned char)blue)/255.0);
        }
}

