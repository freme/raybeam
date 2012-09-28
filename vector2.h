#ifndef _VECTOR_H_
#define _VECTOR_H_ 1

class Vector2 {
    public:
        Vector2() {}
        Vector2(float e0, float e1);
        Vector2(const Vector2 &v) { *this = v; }

        float x() const { return e[0]; };
        float y() const { return e[1]; };

        void setX(float _x) { e[0] = _x; }
        void setY(float _y) { e[1] = _y; }

        float e[2];
};

inline Vector2::Vector2(float e0, float e1){
    e[0] = e0;
    e[1] = e1;
}

#endif // _VECTOR_H_
