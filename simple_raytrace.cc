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


using namespace std;


void debug(Mesh &m) {
    cerr << "Vertices:\n";
    for (int i = 0; i < m.vertices.size(); i++) {
        cerr << "  " << i << ":\n";
        cerr << "    x: " << m.vertices[i].x()<<"\n";
        cerr << "    y: " << m.vertices[i].y()<<"\n";
        cerr << "    z: " << m.vertices[i].z()<<"\n";
    }
    cerr << "\n";
    cerr << "Triangles:\n";
    for (int i = 0; i < m.triangles.size(); i++) {
        cerr << "  " << i << ":\n";
        cerr << "     a: " <<  m.triangles[i].a << "\n";
        cerr << "     b: " <<  m.triangles[i].b << "\n";
        cerr << "     c: " <<  m.triangles[i].c << "\n";
        cerr << "     color: " <<  m.triangles[i].color << "\n";
    }
}


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
    shapes.push_back(new Triangle(
                Vector3(150, 400, -900),
                Vector3(500, 200, -900),
                Vector3(150, 200, -900),
                rgb(.2, .9, .1)));
    
    
    Mesh m;// = new Mesh();    
    int a = m.add_vertex(Vector3(100,100,-300));
    int b = m.add_vertex(Vector3(200,100,-300));
    int c = m.add_vertex(Vector3(400,400,-300));
    m.define_triangle(a,b,c,rgb(0.04,0.0,1.0));
    //debug(m);
    shapes.push_back(&m);
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

