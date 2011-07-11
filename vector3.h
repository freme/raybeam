#ifndef _VECTOR3_H_
#define _VECTOR3_H_ 1

#include <math>
#include <iostream>

class Vector3
{
    public:
        Vector3() {}
        Vector3(float e0, float e1, float e2);
        Vector3(const Vector3 &v) { *this = v; }

        float x() const { return e[0]; }
        float y() const { return e[1]; }
        float z() const { return e[2]; }

        const Vector3& operator+() const;
        Vector3 operator-() const;
        float operator[](int i) const { return e[i]; }
        float& operator[](int i) { return e[i]; }

        /* could be precomputed during initialization */
        float length() const;
        float squaredLength() const;

        void makeUnitVector();

        void setX(float _x) { e[0] = _x; }
        void setY(float _y) { e[1] = _y; }
        void setZ(float _Z) { e[2] = _z; }
        float minComponent() const;
        float maxComponent() const;
        float maxAbsComponent() const;
        float minAbsComponent() const;
        int indexOfMinComponent() const;
        int indexOfMaxComponent() const;
        int indexOfMaxAbsComponent() const;
        int indexOfMinAbsComponent() const;

        friend bool operator==(const Vector3& v1, const Vector3& v2);
        friend bool operator!=(const Vector3& v1, const Vector3& v2);

        friend istream &operator>>(istream &is, Vector3& t);
        friend ostream &operator<<(ostream &os, const Vector3& t);



