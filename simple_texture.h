// simple_texture.h

#ifndef _SIMPLE_TEXTURE_H_
#define _SIMPLE_TEXTURE_H_ 1

#include "texture.h"

class SimpleTexture : Texture {
    public:
        SimpleTexture(rgb c) { color = c; }
        virtual rgb value(const Vector2& uv, const Vector3& p) const {
            return color;
        }

        rgb color;
};

#endif // _SIMPLE_TEXTURE_H_
