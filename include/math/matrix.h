#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <sstream>
#include <cmath>
#include <ostream>
#include <stdexcept>

//TOOD: create matrix class, etc..


/////////////////////DECLARATIONS/////////////////////////////

template<typename T>
class Point2 {
private:
    float len;

public:
    union {
        struct{T x, y;};
        T data[2];
    };

    Point2();
    Point2(T x, T y);

    T& operator[](unsigned int n) const throw (std::out_of_range);

    T get(unsigned int n) const throw (std::out_of_range);

    void normalize();
    float length();

    friend std::ostream& operator<<(std::ostream& os, const Point2& p);
};

template<typename T>
class Matrix2 {
private:
    T mat[9];
public:
    Matrix2();
    Matrix2(int i); //identity
    Matrix2(int i, float theta); //rotate
    Matrix2(T a1, T a2, T a3, T a4);

    //operations
    Matrix2 invert();
    float det() const;
    float get(int x, int y) const throw (std::out_of_range);
    float set(int x, int y) throw (std::out_of_range);

    float& operator[](unsigned int n) throw (std::out_of_range);

    friend std::ostream& operator<<(std::ostream& os, const Matrix2& m);
};

template<typename T>
using Vector2 = Point2<T>;

template<typename T>
float cross(const Vector2<T>& v1, const Vector2<T>& v2);

template<typename T>
float operator*(const Vector2<T>& v1, const Vector2<T>& v2);

template<typename T>
Vector2<T> operator*(const Vector2<T>& v1, float f);

template<typename T>
Vector2<T> operator*(float f, const Vector2<T>& v1);

template<typename T>
Vector2<T> operator+(const Vector2<T>& v1, const Vector2<T>& v2);

template<typename T>
Vector2<T> operator-(const Vector2<T>& v1, const Vector2<T>& v2);

template<typename T>
Vector2<T> operator/(const Vector2<T>& v, float f);

template<typename T>
Vector2<T> operator*(const Matrix2<T>& m, const Vector2<T>& v);

template<typename T>
Vector2<T> operator*(const Vector2<T>& v, const Matrix2<T>& m);

template<typename T>
Matrix2<T> operator~(const Matrix2<T>& m);

template<typename T>
Matrix2<T> operator*(const Matrix2<T>& m1, const Matrix2<T>& m2);

template<typename T>
Matrix2<T> operator*(const Matrix2<T>& m1, float f);

template<typename T>
Matrix2<T> operator*(float f, const Matrix2<T>& m1);



class Point3 {

};

using Vector3 = Point3;

class Matrix3 {

};

class Matrix4 {

};

/////////////////////IMPLEMENTATIONS/////////////////////////////

#endif // MATRIX_H
