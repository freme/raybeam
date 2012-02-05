// texture.h

#ifndef _TEXTURE_H_
#define _TEXTURE_H_ 1

#include "vector2.h"
#include "vector3.h"
#include "rgb.h"

class Texture {
    public:
        // The Vector2 is a UV coord and the Vector3 is the 3D hit point 
        virtual rgb value(const Vector2&, const Vector3&) const = 0;
};

#endif // _TEXTURE_H_
