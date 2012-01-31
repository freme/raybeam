//wood_texture.h

#ifndef _WOOD_TEXTURE_H_
#define _WOOD_TEXTURE_H_ 1

#include <math.h>
#include "texture.h"
#include "rgb.h"
#include "solid_noise.h"

class WoodTexture : public Texture {
    public:
        WoodTexture(float _scale = 1.0f, int _grain=20){
            scale = _scale;
            grain = _grain;
            c0 = rgb(0.8,0.4,0.0);
            c1 = rgb(0.2,0.1,0.0);
        }

        WoodTexture(const rgb& _c0, const rgb& _c1, float _scale = 1.0f, int _grain = 20)
            : c0(_c0), c1(_c1), scale(_scale), grain(_grain) {}

        virtual rgb value(const Vector2& uv, const Vector3& p) const;

        rgb c0, c1;
        float scale;
        int grain;
        SolidNoise solid_noise;
};

#endif // _WOOD_TEXTURE_H_            
