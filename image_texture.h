//image_texture.h

#ifndef _IMAGE_TEXTURE_H_
#define _IMAGE_TEXTURE_H_ 1

#include "texture.h"

class Image;

class ImageTexture : public Texture {
    public:
        ImageTexture(char* file_name);
        virtual rgb value(const Vector2& uv, const Vector3& p) const;

        Image* image;
};

#endif // _IMAGE_TEXTURE_H_
