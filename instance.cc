#include "instance.h"

Instance::Instance(Matrix trans, Matrix trans_inverse, Shape* _prim)
: M(trans), N(trans_inverse), prim(_prim) {}

Instance::Instance(Matrix trans, Shape* _prim)
: M(trans), N(trans) ,prim(_prim)   
{ N.invert(); }

bool Instance::hit(const Ray& r, float tmin, float tmax, float time,
      HitRecord& rec)const 
{
   Vector3 no = transformLoc(N, r.origin());
   Vector3 nd = transformVec(N, r.direction());
   Ray tray(no, nd);
  
   if (prim->hit(tray, tmin, tmax, time, rec)) {
      //Vector3 normal = transformVec(N.getTranspose(), rec.normal);
      //rec.normal = normal;
      rec.normal = transformVec(N.getTranspose(), rec.normal);
      return true;
   } else
       return false; 
}

bool Instance::shadowHit(const Ray& r, float tmin, float tmax, float time)const
{
   Vector3 no = transformLoc(N, r.origin());
   Vector3 nd = transformVec(N, r.direction());
   Ray tray(no, nd);

   return (prim->shadowHit(tray, tmin, tmax, time));
}


