// turbulence_texture.cc

#include "turbulence_texture.h"

rgb TurbulenceTexture::value(const Vector2& uv, const Vector3& p) const {
    float t = (1.0f + solid_noise.turbulence(p * scale, depth)) / 2.0f;
    return t*c0 + (1.0f - t)*c1;
}
