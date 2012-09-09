// simple_raytrace.cc

#include <iostream>
#include "vector3.h"
#include "rgb.h"
#include "image.h"
#include "shape.h"
#include "uvsphere.h"
#include "image_texture.h"
using namespace std;

int main() {
    HitRecord rec;
    bool is_a_hit;
    float tmax;
    // negative z so we can use right-handed coords
    Vector3 dir(0,0,-1); // direction of viewing rays
    
    //input Texture
    Texture * tex = new ImageTexture("worldmap.ppm");

    // scene geometry
    UVSphere sphere(Vector3(750,750,-1000), 500, tex);
    Image im(1500, 1500);

    // loop over pixels
    for (int i = 0; i < 1500; i++)
        for (int j = 0; j < 1500; j++) {
            tmax = 100000.0f;
            is_a_hit = false;
            Ray r(Vector3(i,j,0), dir);

            if (sphere.hit(r, .00001f, tmax, 0.0f, rec)) {
                tmax = rec.t;
                is_a_hit = true;
            }
            if (is_a_hit) {
                rgb color = tex->value(rec.uv, rec.hit_p);
                im.set(i, j, color);
            }
            else 
                im.set(i, j, rgb(.2, .2, .2));
        }
    im.writePPM(cout);
}

