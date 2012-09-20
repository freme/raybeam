// simple_raytrace.cc

#include <vector>
#include <iostream>
#include "vector3.h"
#include "rgb.h"
#include "image.h"
#include "shape.h"
#include "triangle.h"
#include "sphere.h"
#include "mesh.h"
#include <cmath>

using namespace std;

void debug(Mesh m) {
    cerr << "Normals of vertices:\n";
    for ( int i = 0; i < m.vertices.size(); i++) {
        Vector3 n = m.vertices[i].normal;        
        cerr << "  " <<i << "\n";
        cerr << "    " << n.x() << " | " << n.y() << " | " << n.z() << "\n";
    }
    cerr << "\n";
    
    cerr << "Normals in the middle of triangles:\n";
    for (int i = 0; i < m.triangles.size(); i++) {
        Vector3 n = m.getNormalOnTriangle(m.triangles[i], 0.33, 0.33);
        cerr << "  " <<i << "\n";
        cerr << "    " << n.x() << " | " << n.y() << " | " << n.z() << "\n";
    }
    cerr << "\n";
    
}

Mesh make_strange_cube(const Vector3& center, float side_a, const rgb& color) { //will look rounded due to smoothed normals
    Mesh m = *(new Mesh(color));
    side_a /= 2;
    float x = center.x();
    float y = center.y();
    float z = center.z();
    int vul = m.add_vertex(Vector3(x-side_a, y-side_a, z+side_a));
    int vur = m.add_vertex(Vector3(x+side_a, y-side_a, z+side_a));
    int vol = m.add_vertex(Vector3(x-side_a, y+side_a, z+side_a));
    int vor = m.add_vertex(Vector3(x+side_a, y+side_a, z+side_a));
    int hul = m.add_vertex(Vector3(x-side_a, y-side_a, z-side_a));
    int hur = m.add_vertex(Vector3(x+side_a, y-side_a, z-side_a));
    int hol = m.add_vertex(Vector3(x-side_a, y+side_a, z-side_a));
    int hor = m.add_vertex(Vector3(x+side_a, y+side_a, z-side_a));
    
    m.define_triangle(vul,vur,vor);
    m.define_triangle(vul,vor,vol);
    m.define_triangle(vur,hur,hor);
    m.define_triangle(vur,hor,vor);
    m.define_triangle(hur,hul,hol);
    m.define_triangle(hur,hol,hor);
    m.define_triangle(hul,vul,vol);
    m.define_triangle(hul,vol,hol);
    m.define_triangle(hul,hur,vur);
    m.define_triangle(hul,vur,vul);
    m.define_triangle(vol,vor,hor);
    m.define_triangle(vol,hor,hol);
    m.compute_normals();
    debug(m);
    return m;
}

int main() {
    HitRecord rec;
    bool is_a_hit;
    float tmax;
    // negative z so we can use right-handed coords
    const Vector3 dir(0,0,-1); // direction of viewing rays
    
    // scene geometry
    vector<Shape*> shapes;
    //shapes.push_back(new Sphere(Vector3(250,250,-1000), 150, rgb(.2, .2, .8)));
    
    
    Mesh m = Mesh(rgb(1.0,1.0,0));
    int a = m.add_vertex(Vector3(100,100,-300));
    int b = m.add_vertex(Vector3(300,100,-300));
    int c = m.add_vertex(Vector3(300,300,-300));
    int d = m.add_vertex(Vector3(150,250,-1600));
    m.define_triangle(a,b,c);
    m.define_triangle(a,c,d);
    //debug(m);
    m.compute_normals();
    //shapes.push_back(&m);
    Mesh cube1 = make_strange_cube(Vector3(200,200,-500),100,rgb(0,0,1));
    shapes.push_back(&cube1);
    debug(cube1);
    //debug(m);
//    Image im(500, 500);
//new start    
    shapes.push_back(new Sphere(Vector3(250,250,-1000), 150, rgb(.2, .2, .8)));
    shapes.push_back(new Triangle(
                Vector3(300, 600, -800),
                Vector3(0, 100, -1000),
                Vector3(450, 20, -1000),
                rgb(.8, .2, .2)));
    Image im(500, 500);
//new end
    const Vector3 diffuse_light(0,-1,0);
    // loop over pixels
    for (int i = 0; i < 5000; i++)
        for (int j = 0; j < 5000; j++) {
            tmax = 100000.0f;
            is_a_hit = false;
            Ray r(Vector3(i,j,0), dir);

            // loop over list of shapes
            for (unsigned int k = 0; k < shapes.size(); k++)
                if (shapes[k]->hit(r, .00001f, tmax, 0.0f, rec)) {
                    tmax = rec.t;
                    is_a_hit = true;
                }
            if (is_a_hit) {
                //do some primitive diffuse lighting
                rgb shaded_color = rec.color;
                float radians = acos(dot(rec.normal,diffuse_light));
                float mod = radians/M_PI;
                shaded_color *= (mod*mod);
                im.set(i, j, shaded_color);
            }
            else im.set(i, j, rgb(.2, .2, .2));
        }
    im.writePPM(cout);
}

