#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <sstream>
#include <cmath>
#include <ostream>
#include <stdexcept>

/////////////////////DECLARATIONS/////////////////////////////

template<typename T>
class Point2 {
private:
    float len;
    union {
        struct{T x, y;};
        T data[2];
    };
public:

    Point2();
    Point2(T x, T y);

    T& operator[](unsigned int n) throw (std::out_of_range); //setter
    T get(unsigned int n) const throw (std::out_of_range);

    void normalize();
    float length();

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Point2<U>& p);
};

template<typename T>
class Matrix2 {
private:
    T data[4];
public:
    Matrix2();
    Matrix2(int i); //identity
    Matrix2(int i, float theta); //rotate
    Matrix2(T a1, T a2, T a3, T a4);

    //operations
    float det() const;
    T get(unsigned int x, unsigned int y) const throw (std::out_of_range);
    Matrix2 invert();
    T& operator[](unsigned int n) throw (std::out_of_range);

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Matrix2<U>& m);
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

template<typename T>
class Point3 {
private:
    float len;
    union {
        struct{T x, y, z;};
        T data[3];
    };
public:
    Point3();
    Point3(T x, T y, T z);

    void normalize();
    float length();

    T get(unsigned int n) const throw (std::out_of_range);

    T& operator[](unsigned int n) throw (std::out_of_range);
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Point3<U>& p);
};

template<typename T>
using Vector3 = Point3<T>;

template<typename T>
class Matrix3 {
private:
    T data[9];
public:
    Matrix3();
    Matrix3(int i);
    Matrix3(int i, float theta);
    Matrix3(int i, float arg1, float arg2);
    Matrix3(int i, const Vector3<T>& v, float arg1);
    Matrix3(T a1, T a2, T a3,
            T a4, T a5, T a6,
            T a7, T a8, T a9);


    T& operator[](int n) throw (std::out_of_range);
    float det() const;
    T get(int x, int y) const throw (std::out_of_range);

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Matrix3<U>& m);
};

template<typename T>
Vector3<T> cross(const Vector3<T>& v1, const Vector3<T>& v2);

template<typename T>
T operator*(const Vector3<T>& v1, const Vector3<T>& v2);

template<typename T>
Vector3<T> operator*(const Vector3<T>& v, float f);

template<typename T>
Vector3<T> operator*(float f, const Vector3<T>& v);

template<typename T>
Vector3<T> operator+(const Vector3<T>& v1, const Vector3<T>& v2);

template<typename T>
Vector3<T> operator-(const Vector3<T>& v1, const Vector3<T>& v2);

template<typename T>
Vector3<T> operator/(const Vector3<T>& v, float f);

template<typename T>
Vector3<T> operator*(const Matrix3<T>& m, const Vector3<T>& v);

template<typename T>
Vector3<T> operator*(const Vector3<T>& v, const Matrix3<T>& m);

template<typename T>
Matrix3<T> operator+(const Matrix3<T>& m1, const Matrix3<T>& m2);

template<typename T>
Matrix3<T> operator*(const Matrix3<T>& m, float f);

template<typename T>
Matrix3<T> operator*(float f, const Matrix3<T>& m);

template<typename T>
Matrix3<T> operator/(const Matrix3<T>& m, float f);

template<typename T>
Matrix3<T> operator~(const Matrix3<T>& m);

template<typename T>
Matrix3<T> operator*(const Matrix3<T>& m1, const Matrix3<T>& m2);

/*

class Matrix4 {

};
*/
/////////////////////IMPLEMENTATIONS/////////////////////////////
#define MATRIX_IDENTITY 0
#define MATRIX_ROTATION 1
#define MATRIX_TRANSLATION 2
#define MATRIX_ROTATION_X 3
#define MATRIX_ROTATION_Y 4
#define MATRIX_ROTATION_Z 5

template <typename T>
Point2<T>::Point2() {
    len = 0;
    data[0] = 0; data[1] = 0;
}

template <typename T>
Point2<T>::Point2(T x, T y) {
    len = -1;
    data[0] = x; data[1] = y;
}

template <typename T>
T& Point2<T>::operator[](unsigned int n) throw (std::out_of_range) {
    if(n >= 2) throw std::out_of_range("Tried to access index out of range.");
    len = -1;
    return data[n];
}

template <typename T>
T Point2<T>::get(unsigned int n) const throw (std::out_of_range){
    if(n >= 2) throw std::out_of_range("Tried to access index out of range.");
    return data[n];
}

template <typename T>
void Point2<T>::normalize() {
    if (len == 1) return;

    float invsq = 1 / length();
    len = 1;
    x *= invsq, y *= invsq;
}

template <typename T>
float Point2<T>::length() {
    return (len>=0) ? len : (len = sqrt(x*x + y*y));
}

template <typename U>
std::ostream& operator<<(std::ostream& os, const Point2<U>& p) {
    os << "[" << p.data[0] << ", " << p.data[1] << "]";
    return os;
}

template<typename T>
Matrix2<T>::Matrix2() {
    data[0] = 1, data[1] = 0,
    data[2] = 0, data[3] = 1;
}

template<typename T>
Matrix2<T>::Matrix2(int i) {
    switch(i) {
    case MATRIX_IDENTITY:
    default:
        data[0] = 1; data[1] = 0,
        data[2] = 0; data[3] = 1;
        break;
    }
}

template<typename T>
Matrix2<T>::Matrix2(int i, float theta) {
    switch(i) {
    case MATRIX_ROTATION: //generates rotation matrix
    default:
        float st = sin(theta), ct = cos(theta);
        data[0] = ct, data[1] = -st,
        data[2] = st, data[3] = ct;
    }
}

template<typename T>
Matrix2<T>::Matrix2(T a1, T a2, T a3, T a4) {
    data[0] = a1, data[1] = a2,
    data[2] = a3, data[3] = a4;
}

template<typename T>
float Matrix2<T>::det() const {
    return data[0]*data[3] - data[1]*data[2];
}

template<typename T>
Matrix2<T> Matrix2<T>::invert() {
    return (1 /this->det()) * Matrix2(data[3], -data[1],
                                        -data[2], data[0]);
}

template<typename T>
T Matrix2<T>::get(unsigned x, unsigned int y) const throw (std::out_of_range) {
    if(x > 1 || y > 1) throw std::out_of_range("Index(es) are out of range");
    return data[2*y + x];
}

template<typename T>
T& Matrix2<T>::operator[](unsigned int n) throw (std::out_of_range){
    if(n > 3) throw std::out_of_range("Index is out of range");
    return data[n];
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrix2<T>& m) {
    os << "["<< m.data[0] << ", " << m.data[1] << "]" << "\n";
    os << "["<< m.data[2] << ", " << m.data[3] << "]";
    return os;
}

template<typename T>
float cross(const Vector2<T>& v1, const Vector2<T>& v2) {
    return v1.get(0)*v2.get(1) - v1.get(1)*v2.get(0);
}

template<typename T>
float operator*(const Vector2<T>& v1, const Vector2<T>& v2) {
    return v1.get(0)*v2.get(0) + v1.get(1)*v2.get(1);
}

template<typename T>
Vector2<T> operator*(const Vector2<T>& v1, float f) {
    return Vector2<T>(static_cast<T>(v1.get(0)*f), static_cast<T>(v1.get(1)*f));
}

template<typename T>
Vector2<T> operator*(float f, const Vector2<T>& v1) {
    return Vector2<T>(v1.get(0)*f, v1.get(1)*f);
}

template<typename T>
Vector2<T> operator+(const Vector2<T>& v1, const Vector2<T>& v2) {
    return Vector2<T>(v1.get(0) + v2.get(0), v1.get(1) + v2.get(1));
}

template<typename T>
Vector2<T> operator-(const Vector2<T>& v1, const Vector2<T>& v2) {
    return Vector2<T>(v1.get(0) - v2.get(0), v1.get(1) - v2.get(1));
}

template<typename T>
Vector2<T> operator/(const Vector2<T>& v, float f) {
    return Vector2<T>(static_cast<T>(v.get(0) / f), static_cast<T>(v.get(1) / f));
}

template<typename T>
Vector2<T> operator*(const Vector2<T>& v, const Matrix2<T>& m) {
    return Vector2<T>(m.get(0, 0)*v.get(0) + m.get(1, 0)*v.get(1), m.get(0, 1)*v.get(0) + m.get(1, 1)*v.get(1));
}

template<typename T>
Vector2<T> operator*(const Matrix2<T>& m, const Vector2<T>& v) {
    return Vector2<T>(m.get(0, 0)*v.get(0) + m.get(1, 0)*v.get(1), m.get(0, 1)*v.get(0) + m.get(1, 1)*v.get(1));
}

template<typename T>
Matrix2<T> operator~(const Matrix2<T>& m) {
    return Matrix2<T>(m.get(0, 0), m.get(0, 1),
                   m.get(1, 0), m.get(1, 1));
}

template<typename T>
Matrix2<T> operator*(const Matrix2<T>& m1, const Matrix2<T>& m2) {
return Matrix2<T>(m1.get(0, 0)*m2.get(0, 0) + m1.get(1, 0)*m2.get(0, 1),
               m1.get(0, 0)*m2.get(1, 0) + m1.get(1, 0)*m2.get(1, 1),

               m1.get(0, 1)*m2.get(0, 0) + m1.get(1, 1)*m2.get(0, 1),
               m1.get(0, 1)*m2.get(1, 0) + m1.get(1, 1)*m2.get(1, 1));
}

template<typename T>
Matrix2<T> operator*(const Matrix2<T>& m1, float f) {
    return Matrix2<T>(m1.get(0, 0)*f, m1.get(1, 0)*f,
                   m1.get(0, 1)*f, m1.get(1, 1)*f);
}

template<typename T>
Matrix2<T> operator*(float f, const Matrix2<T>& m1) {
    return Matrix2<T>(m1.get(0, 0)*f, m1.get(1, 0)*f,
                   m1.get(0, 1)*f, m1.get(1, 1)*f);
}

#endif // MATRIX_H
