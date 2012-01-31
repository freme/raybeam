//noise_texture.h

#ifndef _TURBULENCE_TEXTURE_H_
#define _TURBULENCE_TEXTURE_H_ 1

#include <math.h>
#include "texture.h"
#include "rgb.h"
#include "solid_noise.h"

class TurbulenceTexture : public Texture {
    public:
        TurbulenceTexture(float _scale = 1.0f, int _depth = 4){
            scale = _scale;
            c0 = rgb(1.0,1.0,1.0);
            c1 = rgb(0.0,0.0,0.0);
            depth = _depth;
        }

        TurbulenceTexture(const rgb& _c0, const rgb& _c1, float _scale = 1.0f, int _depth = 4)
            : c0(_c0), c1(_c1), scale(_scale), depth(_depth) {}

        virtual rgb value(const Vector2& uv, const Vector3& p) const;

        rgb c0, c1;
        float scale;
        int depth;
        SolidNoise solid_noise;
};

#endif // _TURBULENCE_TEXTURE_H_            
