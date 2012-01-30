//noise_texture.h

#ifndef _NOISE_TEXTURE_H_
#define _NOISE_TEXTURE_H_ 1

#include <math.h>
#include "texture.h"
#include "rgb.h"
#include "solid_noise.h"

class NoiseTexture : public Texture {
    public:
        NoiseTexture(float _scale = 1.0f){
            scale = _scale;
            c0 = rgb(0.8,0.0,0.0);
            c1 = rgb(0.0,0.0,0.8);
        }

        NoiseTexture(const rgb& _c0, const rgb& _c1, float _scale = 1.0f)
            : c0(_c0), c1(_c1), scale(_scale) {}

        virtual rgb value(const Vector2& uv, const Vector3& p) const;

        rgb c0, c1;
        float scale;
        SolidNoise solid_noise;
};

#endif // _NOISE_TEXTURE_H_            
