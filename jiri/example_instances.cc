#include <vector>
#include <iostream>
#include "vector3.h"
#include "rgb.h"
#include "image.h"
#include "shape.h"
#include "mesh.h"
#include "matrix.h"

#include "instance.h"
#include <cmath>

using namespace std;

int main() {
    HitRecord rec;
    bool is_a_hit;
    float tmax;
    const Vector3 dir(0,0,-1); // direction of viewing rays
    
    const int lod = 15; //level of detail
    const float radius = 150.0;
    Mesh cylinder(rgb(.5,0,.5));
    
    //make vertices
    int bottom[lod], top[lod];
    const float x = 0;
    const float z = 0;
    const float y_top = 100;
    const float y_bottom = -100;
    float x_off, z_off;
    for (int i = 0; i < lod; i++) {
        x_off = cos(2*M_PI/lod*i)*radius;
        z_off = sin(2*M_PI/lod*i)*radius;
        bottom[i] = cylinder.add_vertex(Vector3(x+x_off,y_bottom, z+z_off));
        top[i] = cylinder.add_vertex(Vector3(x+x_off,y_top, z+z_off));
    }
    
    //make triangles
    int next;
    for (int i = 0; i < lod; i++) {
        next = (i+1)%lod;
        cylinder.define_triangle(bottom[i],bottom[next], top[i]);
        cylinder.define_triangle(bottom[next],top[next],top[i]);
    }
    cylinder.compute_normals();
    
    vector<Shape*> shapes;
    
    //make transformed instances
    const Matrix shrink = scale(0.5,0.5,0.5);
    Matrix trans = translate(150.0,150.0,-1800)*shrink;
    shapes.push_back(new Instance(trans, &cylinder));
    Matrix rotate1 = translate(350.0,150.0,-1800.0)*rotateZ(1)*rotateX(1)*shrink;
    shapes.push_back(new Instance(rotate1, &cylinder));
    Matrix squash = translate(150,350,-1800)*scale(0.5,1.2,1)*shrink;
    shapes.push_back(new Instance(squash, &cylinder));
    Matrix rotate2 = translate(350,350,-1800)*rotateX(1)*rotateZ(1)*shrink;
    shapes.push_back(new Instance(rotate2, &cylinder));
    Image im(500, 500);

    const Vector3 diffuse_light_dir(1,0,0);
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
                //do some primitive diffuse lighting
                rgb shaded_color = rec.color;
                float radians = acos(dot(unitVector(rec.normal), diffuse_light_dir));
                float mod = radians < M_PI/2 ? 1-radians/(M_PI/2) : 0 ;
                shaded_color += mod*rec.color;
                im.set(i, j, shaded_color);
            }
            else im.set(i, j, rgb(.2, .2, .2));
        }
    im.writePPM(cout);
}

