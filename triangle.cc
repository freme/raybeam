// triangle.cc

#include "triangle.h"

Triangle::Triangle(const Vector3& _p0, const Vector3& _p1, \
                const Vector3& _p2, const rgb& _color)
                : p0(_p0), p1(_p1), p2(_p2), color(_color) 
{ }

// this is based on Cramer's rule
bool Triangle::hit(const Ray& r, float tmin, float tmax, float time, \
        HitRecord& record) const {
    
    float A = p0.x() - p1.x();
    float B = p0.y() - p1.y();
    float C = p0.z() - p1.z();

    float D = p0.x() - p2.x();
    float E = p0.y() - p2.y();
    float F = p0.z() - p2.z();

    float G = r.direction().x();
    float H = r.direction().y();
    float I = r.direction().z();

    float J = p0.x() - r.origin().x();
    float K = p0.y() - r.origin().y();
    float L = p0.z() - r.origin().z();

    float EIHF = E*I - H*F;
    float GFDI = G*F - D*I;
    float DHEG = D*H - E*G;

    float denom = (A*EIHF + B*GFDI + C*DHEG);

    float beta =  (J*EIHF + K*GFDI + L*DHEG) / denom;
    if (beta <= 0.0f || beta >= 1.0f) return false;

    float AKJB = A*K - J*B;
    float JCAL = J*C - A*L;
    float BLKC = B*L - K*C;

    float gamma = (I*AKJB + H*JCAL + G*BLKC) / denom;
    if (gamma <= 0.0f || beta + gamma >= 1.0f) return false;

    float tval = -(F*AKJB + E*JCAL + D*BLKC) / denom;
    if (tval >= tmin && tval <= tmax) {
        record.t = tval;
        record.normal = unitVector(cross((p1 - p0), (p2 - p0)));
        record.color = color;
        return true;
    }

    return false;
}

bool Triangle::shadowHit(const Ray& r, float tmin, float tmax, \
                float time) const {

    float A = p0.x() - p1.x();
    float B = p0.y() - p1.y();
    float C = p0.z() - p1.z();

    float D = p0.x() - p2.x();
    float E = p0.y() - p2.y();
    float F = p0.z() - p2.z();

    float G = r.direction().x();
    float H = r.direction().y();
    float I = r.direction().z();

    float J = p0.x() - r.origin().x();
    float K = p0.y() - r.origin().y();
    float L = p0.z() - r.origin().z();

    float EIHF = E*I - H*F;
    float GFDI = G*F - D*I;
    float DHEG = D*H - E*G;

    float denom = (A*EIHF + B*GFDI + C*DHEG);

    float beta =  (J*EIHF + K*GFDI + L*DHEG) / denom;
    if (beta <= 0.0f || beta >= 1.0f) return false;

    float AKJB = A*K - J*B;
    float JCAL = J*C - A*L;
    float BLKC = B*L - K*C;

    float gamma = (I*AKJB + H*JCAL + G*BLKC) / denom;
    if (gamma <= 0.0f || beta + gamma >= 1.0f) return false;

    float tval = -(F*AKJB + E*JCAL + D*BLKC) / denom;

    return (tval >= tmin && tval <= tmax);
}

