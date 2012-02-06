#ifndef _MESH_H_
#define _MESH_H_ 1

#include <vector>
#include "shape.h"


class Mesh : public Shape {
    public:
        Mesh();
        Mesh(const rgb& new_color);
        
        bool hit(const Ray& r, float tmin, float tmax, \
                float time, HitRecord& record) const;
        bool shadowHit(const Ray& r, float tmin, float tmax, \
                float time) const;

	int add_vertex(const Vector3& coord); //adds vertex to mesh and returns it's index
	
        void define_triangle(const int ind_a, const int ind_b, const int ind_c); //define triangles from vetices in the mesh's index
        
        void compute_normals();
        
        friend void debug(Mesh m);
     
    private:
        struct triangle_record {
            int a;
            int b;
            int c;
        };
        struct vertex_record {
            Vector3 coordinate;
            Vector3 normal;
        };
        
        bool triangleIntersect(const Ray& r, const int& vertex_a_index, const int& vertex_b_index, const int& vertex_c_index, \
                float& tmin, float& tmax, float& t, float& beta, float& gamma) const;
        
        Vector3 getNormalOnTriangle(const triangle_record& t, const float& beta, const float& gamma) const;
        
        std::vector<triangle_record> triangles;
        std::vector<vertex_record> vertices;
        rgb color;

};

#endif // _MESH_H_

