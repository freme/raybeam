// wood_texture.cc

#include "wood_texture.h"
#include <cstdio>

rgb WoodTexture::value(const Vector2& uv, const Vector3& p) const {
    float t =  solid_noise.noise(p * scale) * grain;
    t = t - (int)t;
    if(t < 0.0f){
        t+=1.0f;
        return t*c1 + (1.0f - t)*c0;
    }
    else 
        return t*c0 + (1.0f - t)*c1;
}
