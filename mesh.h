// mesh.h

#ifndef _MESH_H_
#define _MESH_H_ 1

#include <vector>
#include "shape.h"


class Mesh : public Shape {
    public:
        Mesh();
        
        bool hit(const Ray& r, float tmin, float tmax, \
                float time, HitRecord& record) const;
        bool shadowHit(const Ray& r, float tmin, float tmax, \
                float time) const;

	int add_vertex(const Vector3& v); //adds vertex to mesh and returns it's index
	
        void define_triangle(const int ind_a, const int ind_b, \
		const int ind_c, const rgb& color); //define triangles from vetices in the mesh's index
    
        friend void debug(Mesh &m);
    private:
        typedef struct triangle_record {
            int a;
            int b;
            int c;
            rgb color;
        } triangle_record;
        std::vector<triangle_record> triangles;
        std::vector<Vector3> vertices;
        
	
};

#endif // _MESH_H_

