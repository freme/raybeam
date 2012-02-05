// simple_raytrace.cc

#include <iostream>
#include "vector3.h"
#include "rgb.h"
#include "image.h"
#include "shape.h"
#include "uvsphere.h"
#include "image_texture.h"
#include "wood_texture.h"
#include "marble_texture.h"
#include "simple_texture.h"
#include "sys/time.h"
using namespace std;

int main(int argc,char **argv) {
    if(argc != 4) {
        cout << "Wrong argument size. Supply TextureNumber, size, output file" << endl;
        cout << "Simple Texture 0, WoodTexture 1, MarbleTexture 2, ImageTexture 3" << endl;
        exit(1);
    }
    
    int temp = atoi(argv[2]);
    if(temp < 0) {
        cout << "Negative Size!" << endl;
        exit(1);
    }
 

    HitRecord rec;
    bool is_a_hit;
    float tmax;
    int size = temp;
    struct timeval t1, t2;
    // negative z so we can use right-handed coords
    Vector3 dir(0,0,-1); // direction of viewing rays

    Image im(size, size);

    gettimeofday(&t1, 0);

    //input Texture
    string texName;
    Texture * tex;
    switch(atoi(argv[1])){
        case 0: tex = new SimpleTexture(rgb(1.0,0.0,0.0)); texName = "SimpleTexture";  break;
        case 1: tex = new WoodTexture(0.0015f); texName = "WoodTexture";  break;
        case 2: tex = new MarbleTexture(0.0015f, 5.0f, 8); texName = "MarbleTexture";  break;
        case 3: tex = new ImageTexture("worldmap.ppm"); texName = "ImageTexture";  break;
        default:
            cout << "Wrong TextureNumber" << endl;
            cout << "Simple Texture 0, WoodTexture 1, MarbleTexture 2, ImageTexture 3" << endl;
            exit(1);
    };

    // scene geometry
    UVSphere sphere(Vector3(size/2,size/2,size*-2), size*47/100, tex);
    cout << "Rendering Sphere of Size " << size << " with " << texName << endl;

    // loop over pixels
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
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

    gettimeofday(&t2, 0);
    int us_start, us_end;
    us_start = t1.tv_sec*1000000+t1.tv_usec;
    us_end = t2.tv_sec*1000000+t2.tv_usec;
    printf("Wallclock time %f seconds\n",(float)(us_end-us_start)/1000000.0);


    ofstream out;
    out.open(argv[3]);
    im.writePPM(out);
    out.close();
}

