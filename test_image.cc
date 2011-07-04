#include "image.h"
#include <ostream>

// picture starts in the lower left

void swap(int &x, int &y)
{
    x -= y;
    y += x;         // y gets the original value of x
    x = (y - x);    // x gets the original value of y
}


void draw_line(int startx, int starty, int endx, int endy, rgb& col, Image& pic)
{   
    
    if (startx == endx)
    {
        if (starty > endy) swap(starty, endy);
        for (int i=starty; i <= endy; i++) pic.set(startx, i, col);
        return;
    }

    if (starty == endy)
    {
        if (startx > endx) swap(startx, endx);
        for (int i=startx; i <= endx; i++) pic.set(i, starty,col);
        return;
    }

    if ((startx > endx) && (starty > endy))
    {
        swap(startx, endx);
        swap(starty, endy);
    }

    if ((startx < endx) && (starty < endy))  
    {
        int xrange = endx-startx;
        int yrange = endy-starty;
        
        float j=starty;
        float fact = (float)yrange/xrange;

        for (int i = startx; i <= endx; i++)
        {
            pic.set(i, j, col);
            j+=fact;
        }
    }

    if ((startx < endx) && (starty > endy))
    {
        int xrange = endx-startx;
        int yrange = starty-endy;
        
        float j=starty;
        float fact = (float)yrange/xrange;

        for (int i = startx; i <= endx; i++)
        {
            pic.set(i, (int)j, col);
            j-=fact;
        }
    }

    if ((startx > endx) && (starty < endy))
    {
        int xrange = startx-endx;
        int yrange = endy-starty;
        
        float j=startx;
        float fact = (float)xrange/yrange;
        for (int i = starty; i <= endy; i++)
        {
            pic.set((int)j, i, col);
            j-=fact;
        }
    }

}

float rand_FloatRange(float a, float b)
{
    return ((b-a)*((float)rand()/RAND_MAX))+a;
}



int main()
{   int w = 800;
    int h = 600;
    Image pic(w, h, rgb(0, 0, 0));
    rgb col(0.5, 0.5, 0.5);
    
    // raster starts left bottom
    // ppm starts left top
    // iterate accordingly
    /*
    for (int i = h-1; i >=h/2; i--)
        for (int j = 0; j < w/2; j++)
        {
            col.setRed(rand_FloatRange(0.0, 1.0));
            col.setGreen(rand_FloatRange(0.0, 1.0));
            col.setBlue(rand_FloatRange(0.0, 1.0));
            pic.set(i, j, col);
        }
    */

    col.setRed(rand_FloatRange(0.0, 1.0));
    col.setGreen(rand_FloatRange(0.0, 1.0));
    col.setBlue(rand_FloatRange(0.0, 1.0));
    draw_line(0, 0, 100, 50, col, pic);
    
    col.setRed(rand_FloatRange(0.0, 1.0));
    col.setGreen(rand_FloatRange(0.0, 1.0));
    col.setBlue(rand_FloatRange(0.0, 1.0));
    draw_line(100, 100, 0, 0, col, pic);
    
    col.setRed(rand_FloatRange(0.0, 1.0));
    col.setGreen(rand_FloatRange(0.0, 1.0));
    col.setBlue(rand_FloatRange(0.0, 1.0));
    draw_line(0, 100, 100, 50, col, pic);
    
    col.setRed(rand_FloatRange(0.0, 1.0));
    col.setGreen(rand_FloatRange(0.0, 1.0));
    col.setBlue(rand_FloatRange(0.0, 1.0));
    draw_line(100, 100, 0, 100, col, pic);
    draw_line(100, 100, 100, 50, col, pic);

    col.setRed(rand_FloatRange(0.0, 1.0));
    col.setGreen(rand_FloatRange(0.0, 1.0));
    col.setBlue(rand_FloatRange(0.0, 1.0));
    draw_line(300, 100, 200, 150, col, pic);
    

    std::ofstream out;
    out.open("./picture.ppm");
    if (!out.is_open()) exit(-1);
    pic.writePPM(out);
    out.close();

    // read test
    Image pic2;
    pic2.readPPM("./picture.ppm");
    pic2.gammaCorrect(2.2);

    out.open("./picture2.ppm");
    if (!out.is_open()) exit(-1);
    pic2.writePPM(out);
    out.close();

    return 0;
}

