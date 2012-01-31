// simple_raytrace.cc

#include <iostream>
#include "vector3.h"
#include "rgb.h"
#include "image.h"
#include "marble_texture.h"
using namespace std;

int main() {
    //generate Texture
    Texture *tex = new MarbleTexture(0.001f);

    Image im(1500, 1500);

    // loop over pixels
    for (int i = 0; i < 1500; i++)
        for (int j = 0; j < 1500; j++) {
            im.set(i, j, tex->value(Vector2(i, j), Vector3(i, j, 0)));
        }
    im.writePPM(cout);
}

