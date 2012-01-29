// mesh.cc

#include "triangle.h"
#include "mesh.h"
#include <vector>

Mesh::Mesh() : color(rgb(1,1,1)) {}
Mesh::Mesh(rgb& new_color) : color(new_color) {}


int Mesh::add_vertex(const Vector3& v) {
    int index = vertices.size();
    vertices.push_back(v);
    return index;
}

void Mesh::define_triangle(const int ind_a, const int ind_b, const int ind_c, const rgb& color) {
    triangle_record new_triangle = {ind_a, ind_b, ind_c, color};
    triangles.push_back(new_triangle);
}    


bool Mesh::hit(const Ray& r, float tmin, float tmax, float time, HitRecord& record) const {
    bool is_hit = false;
    float t, dummy_beta, dummy_gamma;
    for(std::vector<triangle_record>::const_iterator iter = triangles.begin(), end = triangles.end(); iter != end; ++iter) {
        triangle_record tr = *iter;
        //Triangle t = Triangle(vertices[tr.a],vertices[tr.b],vertices[tr.c],tr.color);
        if (triangleIntersect(r, vertices[tr.a],vertices[tr.b],vertices[tr.c], tmin, tmax, t, dummy_beta, dummy_gamma)) {
            record.t = t;
            //TODO: assign normal
            tmax = record.t;
            is_hit = true;
        }
    }
    if (is_hit) record.color = color; //assign once only, color is the same everywhere
    return is_hit;
}

bool Mesh::shadowHit(const Ray& r, float tmin, float tmax, float time) const {
    float dummy_t, dummy_beta, dummy_gamma;
    for(std::vector<triangle_record>::const_iterator iter = triangles.begin(), end = triangles.end(); iter != end; ++iter) {
        triangle_record tr = *iter;
        if (triangleIntersect(r, vertices[tr.a],vertices[tr.b],vertices[tr.c], tmin, tmax, dummy_t, dummy_beta, dummy_gamma))
            return true;
    }
    return false;   
}

inline bool Mesh::triangleIntersect(const Ray& r, const Vector3& p0, const Vector3& p1, const Vector3& p2, float& tmin, float& tmax, float& t, float& beta, float& gamma) const {
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

   float EIHF = E*I-H*F;
   float GFDI = G*F-D*I;
   float DHEG = D*H-E*G;

   float denom = (A*EIHF + B*GFDI + C*DHEG);

   beta = (J*EIHF + K*GFDI + L*DHEG) / denom;

   if (beta <= 0.0 || beta >= 1) return false;

   float AKJB = A*K - J*B;
   float JCAL = J*C - A*L;
   float BLKC = B*L - K*C;

   gamma = (I*AKJB + H*JCAL + G*BLKC)/denom;
   if (gamma <= 0.0 || beta + gamma >= 1.0) return false;

   t =  -(F*AKJB + E*JCAL + D*BLKC)/denom;
   return (t >= tmin && t <= tmax);
}