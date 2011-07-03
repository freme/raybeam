#include "image.h"
#include <ostream>

float rand_FloatRange(float a, float b)
{
    return ((b-a)*((float)rand()/RAND_MAX))+a;
}

int main()
{   int w = 800;
    int h = 600;
    Image pic(w, h, rgb(0, 0, 0));
    rgb col(0.5, 0.5, 0.5);

    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
        {
            col.setRed(rand_FloatRange(0.0, 1.0));
            col.setGreen(rand_FloatRange(0.0, 1.0));
            col.setBlue(rand_FloatRange(0.0, 1.0));
            pic.set(i, j, col);
        }
    
    std::ofstream out;
    out.open("./picture.ppm");
    if (!out.is_open()) exit(-1);

    pic.writePPM(out);

    out.close();
    
    return 0;
}

