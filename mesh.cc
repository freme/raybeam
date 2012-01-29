// mesh.cc

#include "triangle.h"
#include "mesh.h"
#include <vector>

Mesh::Mesh() {
//do i need this?
//    std::vector<triangle_record> triangles;
//  std::vector<Vector3> vertices;
}


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
    for(int i = 0; i < triangles.size(); i++) {
        triangle_record tr = triangles[i];
        Triangle t = Triangle(vertices[tr.a],vertices[tr.b],vertices[tr.c],tr.color);
        if (t.hit(r, .00001f, tmax, 0.0f, record)) {
            tmax = record.t;
            is_hit = true;
        }
    }
    return is_hit;
}

bool Mesh::shadowHit(const Ray& r, float tmin, float tmax, float time) const {
    bool is_hit = false;
    for(int i = 0; i < triangles.size(); i++) {
        triangle_record tr = triangles[i];
        Triangle t = Triangle(vertices[tr.a],vertices[tr.b],vertices[tr.c],tr.color);
        if (t.shadowHit(r, .00001f, tmax, 0.0f)) {
            is_hit = true;
            break;
        }
    }
    return is_hit;   
}