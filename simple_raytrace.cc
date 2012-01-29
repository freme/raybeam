// simple_raytrace.cc

#include <vector>
#include <iostream>
#include "vector3.h"
#include "rgb.h"
#include "image.h"
#include "shape.h"
#include "triangle.h"
#include "sphere.h"
#include "mesh.h"
#include <cmath>

using namespace std;


int main() {
    HitRecord rec;
    bool is_a_hit;
    float tmax;
    // negative z so we can use right-handed coords
    const Vector3 dir(0,0,-1); // direction of viewing rays

    // scene geometry
    vector<Shape*> shapes;
    shapes.push_back(new Sphere(Vector3(250,250,-1000), 150, rgb(.2, .2, .8)));
    shapes.push_back(new Triangle(
                Vector3(300, 600, -800),
                Vector3(0, 100, -1000),
                Vector3(450, 20, -1000),
                rgb(.8, .2, .2)));
    shapes.push_back(new Triangle(
                Vector3(150, 400, -900),
                Vector3(500, 200, -900),
                Vector3(150, 200, -900),
                rgb(.2, .9, .1)));
    
    
    Mesh m = Mesh(rgb(1.0,1.0,0));
    int a = m.add_vertex(Vector3(100,100,-300));
    int b = m.add_vertex(Vector3(200,100,-300));
    int c = m.add_vertex(Vector3(400,400,-300));
    m.define_triangle(a,b,c);
    m.compute_normals();
    shapes.push_back(&m);
    Image im(500, 500);

    const Vector3 diffuse_light(0,1,0);
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
            if (is_a_hit) {
                //so some simple diffuse lighting
                rgb shaded_color = rec.color;
                float radians = acos(dot(rec.normal,diffuse_light));
                shaded_color /= radians/M_PI;
                im.set(i, j, shaded_color);
            }
            else im.set(i, j, rgb(.2, .2, .2));
        }
    im.writePPM(cout);
}

