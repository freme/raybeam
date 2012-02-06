// image.h

#ifndef _IMAGE_H_
#define _IMAGE_H_ 1

#include <cmath>
#include <string>
#include <fstream>
#include "rgb.h"
// bad idea to use namespace in .h
// using namespace std;

class Image
{
    public:
        Image();
        // init raster to default rgb color
        Image(int width, int height);
        // init raster to background color
        Image(int width, int height, rgb background);
        // return false if x or y are out of bounds, else true
        bool set(int x, int y, const rgb & color);
        void gammaCorrect(float gamma);
        // output PPM
        void writePPM(std::ostream& out);
        void readPPM(std::string file_name);

        int width() { return nx; }
        int height() { return ny; }

        rgb getPixel(int x, int y) {return raster[x][y];}

    private:
        rgb** raster;
        int nx; // width
        int ny; // height
};

#endif // _IMAGE_H_

