#ifndef _INSTANCE_H_
#define _INSTANCE_H_ 1

#include "shape.h"
#include "matrix.h"

class Matrix;

class Instance : public Shape {
public:
   Instance () {}
   ~Instance() {}
   Instance(Matrix trans, Matrix trans_inverse, Shape* _prim);
   Instance(Matrix trans, Shape* _prim);
   bool hit(const Ray& r, float tmin, float tmax, float time, 
         HitRecord& rec)const; 
   bool shadowHit(const Ray& r, float tmin, float tmax, float time)const;
  
   Matrix M;
   Matrix N;
   Shape* prim;
};

#endif // _INSTANCE_H_
