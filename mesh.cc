// mesh.cc

#include "triangle.h"
#include "mesh.h"
#include <vector>

Mesh::Mesh() : color(rgb(1,1,1)) {}
Mesh::Mesh(const rgb& new_color) : color(new_color) {}


int Mesh::add_vertex(const Vector3& coord) {
    int index = vertices.size();
    vertices.push_back({coord, Vector3(1,0,0)});
    return index;
}

void Mesh::define_triangle(const int ind_a, const int ind_b, const int ind_c) {
    triangle_record new_triangle = {ind_a, ind_b, ind_c};
    triangles.push_back(new_triangle);
}    


bool Mesh::hit(const Ray& r, float tmin, float tmax, float time, HitRecord& record) const {
    bool is_hit = false;
    float t, dummy_beta, dummy_gamma;
    for(std::vector<triangle_record>::const_iterator iter = triangles.begin(), end = triangles.end(); iter != end; ++iter) {
        triangle_record tr = *iter;
        //Triangle t = Triangle(vertices[tr.a],vertices[tr.b],vertices[tr.c],tr.color);
        if (triangleIntersect(r, tr.a,tr.b,tr.c, tmin, tmax, t, dummy_beta, dummy_gamma)) {
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
        if (triangleIntersect(r, tr.a,tr.b,tr.c, tmin, tmax, dummy_t, dummy_beta, dummy_gamma))
            return true;
    }
    return false;   
}

void Mesh::compute_normals() {
    //compute triangle normals and collect triangle-vertex associations
    std::vector<Vector3> triangle_normals(triangles.size(),Vector3());
    std::vector<std::vector<int> > associations(vertices.size()); //associations[vertex][triangle]
    for (int i = 0, end = triangles.size(); i < end; i++) {
        Vector3 p0 = vertices[triangles[i].a].coordinate;
        associations[triangles[i].a].push_back(i);
        Vector3 p1 = vertices[triangles[i].b].coordinate;
        associations[triangles[i].b].push_back(i);
        Vector3 p2 = vertices[triangles[i].c].coordinate;
        associations[triangles[i].c].push_back(i);
        triangle_normals.push_back(unitVector(cross((p1 - p0), (p2 - p0))));
    }
    //average triangle normals to get vertex normals
    for (int v = 0, end_v = associations.size(); v < end_v; v++) {
        Vector3 sum;
        int count = associations[v].size();
        if (count > 0) { //check if there are any triangles at all
            for (int t = 0, end_t = associations[v].size(); t < end_t; t++) {
            sum += triangle_normals[t];
            }
            sum /= count;
            vertices[v].normal = sum;
        }
    }
}

inline bool Mesh::triangleIntersect(const Ray& r, const int& vertex_a_index, const int& vertex_b_index, const int& vertex_c_index, float& tmin, float& tmax, float& t, float& beta, float& gamma) const {
   Vector3 p0 = vertices[vertex_a_index].coordinate;
   Vector3 p1 = vertices[vertex_b_index].coordinate;
   Vector3 p2 = vertices[vertex_c_index].coordinate;
   
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