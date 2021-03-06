// simple_raytrace.cc

#include <iostream>
#include "vector3.h"
#include "rgb.h"
#include "image.h"
#include "shape.h"
#include "triangle.h"
#include "sphere.h"
#include "dynarray.h"

using namespace std;

int main() {
    HitRecord rec;
    bool is_a_hit;
    bool ret;
    float tmax;
    unsigned static const int width = 1024;
    unsigned static const int height = 768;
    Vector3 dir(0,0,-1); // direction of viewing rays

    // scene geometry
    DynArray<Shape*> shapes;

    shapes.append(new Sphere(Vector3(250,250,-1000), 150, rgb(.2, .2, .8)));
    shapes.append(new Triangle(
                Vector3(300, 600, -800),
                Vector3(0, 100, -1000),
                Vector3(450, 20, -1000),
                rgb(.8, .2, .2)));

    shapes.truncate();
    Image im(width, height, rgb(1, 0, 0));

    // loop over pixels
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++) {
            tmax = 100000.0f;
            is_a_hit = false;
            Ray r(Vector3(i,j,0), dir);

            // loop over list of shapes
            for (unsigned int k = 0; k < shapes.size(); k++)
                if (shapes[k]->hit(r, .00001f, tmax, 0.0f, rec)) {
                    tmax = rec.t;
                    is_a_hit = true;
                }
            if (is_a_hit) ret=im.set(i, j, rec.color);
            else ret=im.set(i, j, rgb(.2, .2, .2));
            if ( ! ret ) std::cerr << "setting pixel " << i << "x" << j << " failed" << std::endl;
        }
    im.writePPM(cout);
}

