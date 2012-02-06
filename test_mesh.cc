#include <vector>
#include <iostream>
#include "vector3.h"
#include "rgb.h"
#include "image.h"
#include "shape.h"
#include "mesh.h"
#include <cmath>

#include <sys/time.h>

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
    const float x = 250.0;
    const float z = -1500;
    const float y_top = 350;
    const float y_bottom = 150;
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
    Image im(500, 500);

    const Vector3 diffuse_light_dir(1,0,0);
    
    struct timeval t1,t2;
    gettimeofday(&t1,0);
    // loop over pixels
    for (int i = 0; i < 500; i++)
        for (int j = 0; j < 500; j++) {
            tmax = 100000.0f;
            is_a_hit = false;
            Ray r(Vector3(i,j,0), dir);

            if (cylinder.hit(r, .00001f, tmax, 0.0f, rec)) {
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
        
    gettimeofday(&t2,0);
    int us_start, us_end;
    us_start = t1.tv_sec*1000000+t1.tv_usec;
    us_end = t2.tv_sec*1000000+t2.tv_usec;
    cerr << "calculation took " << (float)(us_end-us_start)/1000000.0 << " seconds\n";
    
    im.writePPM(cout);
}

