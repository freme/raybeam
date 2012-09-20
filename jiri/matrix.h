#ifndef _MATRIX_H_
#define _MATRIX_H_ 1

#include "vector3.h"
#include <iostream>
#include <iomanip>
#include <cmath>

class Matrix
{
public:
   Matrix() {}
   Matrix(const Matrix & orig);
   
   void invert();
   void transpose();
   Matrix getInverse()const;
   Matrix getTranspose()const;
   
   Matrix & operator+= (const Matrix& right_op);
   Matrix & operator-= (const Matrix& right_op);
   Matrix & operator*= (const Matrix& right_op);
   Matrix & operator*= (float right_op);

   friend Matrix operator- (const Matrix& left_op, const Matrix& right_op);
   friend Matrix operator+ (const Matrix& left_op, const Matrix& right_op);
   friend Matrix operator* (const Matrix& left_op, const Matrix& right_op);
   friend Vector3 operator* (const Matrix& left_op, const Vector3& right_op);
   friend Matrix operator* (const Matrix & left_op, float right_op);

   friend Vector3 transformLoc(const Matrix& left_op, const Vector3& right_op); 
   friend Vector3 transformVec(const Matrix& left_op, const Vector3& right_op); 
   
   friend Matrix zeroMatrix();
   friend Matrix identityMatrix();
   friend Matrix translate(float _x, float _y, float _z);
   friend Matrix scale(float _x, float _y, float _z);
   friend Matrix rotate(const Vector3 & axis, float angle);
   friend Matrix rotateX(float angle);    //
   friend Matrix rotateY(float angle);    // More efficient than arbitrary axis
   friend Matrix rotateZ(float angle);    //
   friend Matrix viewMatrix(const Vector3& eye, const Vector3 & gaze, 
         const Vector3& up);
   friend std::ostream & operator<< (std::ostream& out, const Matrix& right_op);

private:
   float determinant(); 
   float x[4][4];
};

// 3x3 matrix determinant -- helper function 
inline float det3 (float a, float b, float c, 
                   float d, float e, float f, 
                   float g, float h, float i)
{ return a*e*i + d*h*c + g*b*f - g*e*c - d*b*i - a*h*f; }

Matrix zeroMatrix();
Matrix identityMatrix();
Matrix translate(float _x, float _y, float _z);
Matrix scale(float _x, float _y, float _z);
Matrix rotate(const Vector3 & axis, float angle);
Matrix rotateX(float angle);    //
Matrix rotateY(float angle);    // More efficient than arbitrary axis
Matrix rotateZ(float angle);    //
Matrix viewMatrix(const Vector3& eye, const Vector3 & gaze, const Vector3& up);

#endif   // _MATRIX_H_
