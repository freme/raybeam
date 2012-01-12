// simple_raytrace.cc

#include <vector>
#include <iostream>
#include "vector3.h"
#include "rgb.h"
#include "image.h"
#include "shape.h"
#include "triangle.h"
#include "sphere.h"
using namespace std;

int main() {
    HitRecord rec;
    bool is_a_hit;
    float tmax;
    // negative z so we can use right-handed coords
    Vector3 dir(0,0,-1); // direction of viewing rays

    // scene geometry
    vector<Shape*> shapes;
    shapes.push_back(new Sphere(Vector3(250,250,-1000), 150, rgb(.2, .2, .8)));
    shapes.push_back(new Triangle(
                Vector3(300, 600, -800),
                Vector3(0, 100, -1000),
                Vector3(450, 20, -1000),
                rgb(.8, .2, .2)));
    Image im(500, 500);

    // loop over pixels
    for (int i = 0; i < 500; i++)
        for (int j = 0; j < 500; j++) {
            tmax = 100000.0f;
            is_a_hit = false;
            Ray r(Vector3(i,j,0), dir);

            // loop over list of shapes
            for (unsigned int k = 0; k < shapes.size(); k++)
                if (shapes[k]->hit(r, .00001f, tmax, 0.0f, rec)) {
                    tmax = rec.t;
                    is_a_hit = true;
                }
            if (is_a_hit) im.set(i, j, rec.color);
            else im.set(i, j, rgb(.2, .2, .2));
        }
    im.writePPM(cout);
}

