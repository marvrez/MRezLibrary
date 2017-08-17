#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <ostream>
#include <stdexcept>

/////////////////////DECLARATIONS/////////////////////////////

//Point2/Vector2/Matrix2

template<typename T>
class Point2 {
private:
    float len;
    T x, y;
public:

    Point2();
    Point2(T x, T y);

    T& operator[](unsigned int n) throw (std::out_of_range); //setter
    const T& operator[](unsigned int n) const throw (std::out_of_range); //setter

    T X() const;
    T Y() const;

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
    Matrix2 transpose() const;
    T* operator[](unsigned int n) throw (std::out_of_range);
    const T* operator[](unsigned int n) const throw (std::out_of_range);

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Matrix2<U>& m);
};

template<typename T>
using Vector2 = Point2<T>;

//most common types
using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;
using Vector2u = Vector2<unsigned>;

using Matrix2f = Matrix2<float>;
using Matrix2i = Matrix2<int>;
using Matrix2u = Matrix2<unsigned>;

template<typename T>
float cross(const Vector2<T>& v1, const Vector2<T>& v2);

template<typename T>
T operator*(const Vector2<T>& v1, const Vector2<T>& v2);


//arithmetic operators

template<typename T>
Vector2<T> operator+(const Vector2<T>& v1, const Vector2<T>& v2);

template<typename T>
Vector2<T> operator-(const Vector2<T>& v1, const Vector2<T>& v2);

template<typename T>
Vector2<T> operator/(const Vector2<T>& v, float f);

template<typename T>
Vector2<T> operator*(const Matrix2<T>& m, const Vector2<T>& v);

template<typename T>
Vector2<T> operator*(const Vector2<T>& v1, float f);

template<typename T>
Vector2<T> operator*(float f, const Vector2<T>& v1);

template<typename T>
Vector2<T> operator*(const Vector2<T>& v, const Matrix2<T>& m);

template<typename T>
Matrix2<T> operator*(const Matrix2<T>& m1, const Matrix2<T>& m2);

template<typename T>
Matrix2<T> operator*(const Matrix2<T>& m1, float f);

template<typename T>
Matrix2<T> operator*(float f, const Matrix2<T>& m1);

template<typename T>
Matrix2<T> operator~(const Matrix2<T>& m);

//Point3/Vector3/Matrix3

template<typename T>
class Point3 {
private:
    float len;
    T x,y,z;
public:
    Point3();
    Point3(T x, T y, T z);

    void normalize();
    float length();

    T get(unsigned int n) const throw (std::out_of_range);
    T X() const;
    T Y() const;
    T Z() const;

    T& operator[](unsigned int n) throw (std::out_of_range);
    const T& operator[](unsigned int n) const throw (std::out_of_range);

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


    T* operator[](int n) throw (std::out_of_range);
    const T* operator[](int n) const throw (std::out_of_range);

    float det() const;
    Matrix3 transpose() const;
    T get(int x, int y) const throw (std::out_of_range);

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Matrix3<U>& m);
};


//most common types
using Vector3f = Vector3<float>;
using Vector3i = Vector3<int>;
using Vector3u = Vector3<unsigned>;

using Matrix3f = Matrix3<float>;
using Matrix3i = Matrix3<int>;
using Matrix3u = Matrix3<unsigned>;

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


//Matrix4

template<typename T>
class Matrix4 {
private:
    T data[16];
public:
    Matrix4();
    Matrix4(int i);
    Matrix4(int i, float theta);
    Matrix4(int i, float arg1, float arg2);
    Matrix4(int i, const Point3<T>& p);
    Matrix4(T a1, T a2, T a3, T a4,
            T a5, T a6, T a7, T a8,
            T a9, T a10, T a11, T a12,
            T a13, T a14, T a15, T a16);
    float det() const;
    Matrix4 transpose() const;

    T* operator[](unsigned int n);
    const T* operator[](unsigned int n) const;
    T get(int x, int y) const throw (std::out_of_range);
    T get(int n) const throw (std::out_of_range);

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Matrix4<U> m);
};

//most common types
using Matrix4f = Matrix4<float>;
using Matrix4i = Matrix4<int>;
using Matrix4u = Matrix4<unsigned>;

template<typename T>
Vector3<T> operator*(const Matrix4<T>& m, const Vector3<T>& v);

template<typename T>
Vector3<T> operator*(const Vector3<T>& v, const Matrix4<T>& m);

template<typename T>
Matrix4<T> operator*(const Matrix4<T>& m, float f);

template<typename T>
Matrix4<T> operator*(float f, const Matrix4<T>& m);

template<typename T>
Matrix4<T> operator~(const Matrix4<T>& m);

template<typename T>
Matrix4<T> operator*(const Matrix4<T>& m1, const Matrix4<T>& m2);


//Vector

template<typename T>
class Vector {
private:
    T* data;
    int size;
public:
    Vector(int size);
    Vector(int size, const T* p);
    Vector(const Vector& v);
    ~Vector() { delete[] data; }

    T& operator[](int n);
    int getLength() const;
    T get(int n) const;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Vector<U>& vec);
};

template<typename T>
T operator*(const Vector<T>& g1, const Vector<T>& g2);

template<typename T>
Vector<T> operator+(const Vector<T>& g1, const Vector<T>& g2);

template<typename T>
Vector<T> operator-(const Vector<T>& g1, const Vector<T>& g2);

template<typename T>
Vector<T> operator*(const Vector<T>& g1, float f);

template<typename T>
Vector<T> operator*(float f, const Vector<T>& g1);

template<typename T>
Vector<T> operator/(const Vector<T>& g1, float f);

//Matrix

template<typename T>
class Matrix {
private:
    T* data;
    int w, h;
public:
    Matrix(int w, int h);
    Matrix(int w, int h, const T* p);
    Matrix(const Matrix& mat);
    ~Matrix() { delete[] data; }

    T* operator[](int n);

    T get(int x, int y) const;
    T get(int n) const;
    int getWidth() const;
    int getHeight() const;
    int getW() const;
    int getH() const;
    float det() const;
    float _det() const;

    Matrix inv() const;
    Matrix transpose() const;
    Matrix _minor(int a, int b) const;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<U>& mat);
};

template<typename T>
Vector<T> operator*(const Matrix<T>& mat, const Vector<T>& vec);

template<typename T>
Vector<T> operator*(const Vector<T>& vec, const Matrix<T>& mat);

template<typename T>
Matrix<T> operator*(const Matrix<T>& mat, float f);

template<typename T>
Matrix<T> operator/(const Matrix<T>& mat, float f);

template<typename T>
Matrix<T> operator*(float f, const Matrix<T>& mat);

template<typename T>
Matrix<T> operator*(const Matrix<T>& m1, const Matrix<T>& m2);


/////////////////////IMPLEMENTATIONS/////////////////////////////
#define MATRIX_IDENTITY 0
#define MATRIX_ROTATION 1
#define MATRIX_TRANSLATION 2
#define MATRIX_ROTATION_X 3
#define MATRIX_ROTATION_Y 4
#define MATRIX_ROTATION_Z 5

//Matrix2/Point2 implementations
template <typename T>
Point2<T>::Point2() : len(0), x(0), y(0)
{ }

template <typename T>
Point2<T>::Point2(T x, T y) : len(-1), x(x), y(y)
{ }

template <typename T>
T& Point2<T>::operator[](unsigned int n) throw (std::out_of_range) {
    if(n > 1) throw std::out_of_range("Tried to access index out of range.");
    len = -1;
    return n == 0 ? x : y;
}

template <typename T>
const T& Point2<T>::operator[](unsigned int n) const throw (std::out_of_range) {
    if(n > 1) throw std::out_of_range("Tried to access index out of range.");
    return n == 0 ? x : y;
}

template <typename T>
T Point2<T>::X() const {
    return x;
}

template <typename T>
T Point2<T>::Y() const {
    return y;
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
    os << "[" << p.x << ", " << p.y << "]";
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
                                     -data[2],  data[0]);
}

template<typename T>
Matrix2<T> Matrix2<T>::transpose() const {
    return Matrix2(this->get(0, 0), this->get(0, 1),
                   this->get(1, 0), this->get(1, 1));
}

template<typename T>
T Matrix2<T>::get(unsigned int x, unsigned int y) const throw (std::out_of_range) {
    if(x > 1 || y > 1) throw std::out_of_range("Index(es) are out of range");
    return data[2*y + x];
}

template<typename T>
T* Matrix2<T>::operator[](unsigned int n) throw (std::out_of_range){
    if(n > 1) throw std::out_of_range("Index is out of range");
    return data + 2*n;
}

template<typename T>
const T* Matrix2<T>::operator[](unsigned int n) const throw (std::out_of_range){
    if(n > 1) throw std::out_of_range("Index is out of range");
    return data + 2*n;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrix2<T>& m) {
    os << "["<< m.data[0] << ", " << m.data[1] << "]" << "\n";
    os << "["<< m.data[2] << ", " << m.data[3] << "]";
    return os;
}

template<typename T>
float cross(const Vector2<T>& v1, const Vector2<T>& v2) {
    return v1.X()*v2.Y() - v1.Y()*v2.X();
}

template<typename T>
T operator*(const Vector2<T>& v1, const Vector2<T>& v2) {
    return v1.X()*v2.X() + v1.Y()*v2.Y();
}

template<typename T>
Vector2<T> operator*(const Vector2<T>& v1, float f) {
    return Vector2<T>(static_cast<T>(v1.X()*f), static_cast<T>(v1.Y()*f));
}

template<typename T>
Vector2<T> operator*(float f, const Vector2<T>& v1) {
    return v1*f;
}

template<typename T>
Vector2<T> operator+(const Vector2<T>& v1, const Vector2<T>& v2) {
    return Vector2<T>(v1.X() + v2.X(), v1.Y() + v2.Y());
}

template<typename T>
Vector2<T> operator-(const Vector2<T>& v1, const Vector2<T>& v2) {
    return Vector2<T>(v1.X() - v2.X(), v1.Y() - v2.Y());
}

template<typename T>
Vector2<T> operator/(const Vector2<T>& v, float f) {
    return Vector2<T>(static_cast<T>(v.X() / f), static_cast<T>(v.Y() / f));
}

template<typename T>
Vector2<T> operator*(const Vector2<T>& v, const Matrix2<T>& m) {
    return Vector2<T>(m.get(0, 0)*v.X() + m.get(1, 0)*v.Y(), m.get(0, 1)*v.X() + m.get(1, 1)*v.Y());
}

template<typename T>
Vector2<T> operator*(const Matrix2<T>& m, const Vector2<T>& v) {
    return Vector2<T>(m.get(0, 0)*v.X() + m.get(1, 0)*v.Y(), m.get(0, 1)*v.X() + m.get(1, 1)*v.Y());
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
    return m1*f;
}

//Point3/Matrix3 implementations

template<typename T>
Point3<T>::Point3() : x(0.0), y(0.0), z(0.0), len(0.0) { }

template<typename T>
Point3<T>::Point3(T x, T y, T z) : x(x), y(y), z(z), len(-1) { }

template<typename T>
void Point3<T>::normalize() {
    len = 1;
    float invsq = 1/length();
    x *= invsq, y*=invsq, z*=invsq;
}

template<typename T>
float Point3<T>::length() {
    return len >=0 ? len : (len = sqrt(x*x + y*y + z*z));
}

template<typename T>
T Point3<T>::get(unsigned int n) const throw (std::out_of_range) {
    if(n > 2)
        throw std::out_of_range("Index out of range!");
    switch(n) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
    }
}

template<typename T>
T Point3<T>::X() const {
    return x;
}

template<typename T>
T Point3<T>::Y() const {
    return y;
}

template<typename T>
T Point3<T>::Z() const {
    return z;
}

template<typename T>
T& Point3<T>::operator[](unsigned int n) throw (std::out_of_range) {
    if(n > 2) throw std::out_of_range("Index out of range!");
    len = -1;
    switch(n) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
    }
}

template<typename T>
const T& Point3<T>::operator[](unsigned int n) const throw (std::out_of_range) {
    if(n > 2) throw std::out_of_range("Index out of range!");
    switch(n) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
    }
}
template<typename U>
std::ostream& operator<<(std::ostream& os, const Point3<U>& p) {
    os << "[" << p.x << ", " << p.y << ", " << p.z << "]";
    return os;
}


template<typename T>
Matrix3<T>::Matrix3() {
    for(int i = 0; i < 9; i++)
       data[i] = i%4 == 0;
}

template<typename T>
Matrix3<T>::Matrix3(int i) {
    switch(i) { //Soon™ add more cases?
     case MATRIX_IDENTITY:
     default:
       for(int i = 0; i < 9; i++)
            data[i] = i%4 == 0;
       break;
     }
}

template<typename T>
Matrix3<T>::Matrix3(int i, float theta) {
    switch(i){
        float ct, st;
        case MATRIX_ROTATION:
        case MATRIX_ROTATION_X:
            st = sin(theta), ct = cos(theta);
            data[0] = 1; data[1] = 0;  data[2] = 0;
            data[3] = 0; data[4] = ct; data[5] = -st;
            data[6] = 0; data[7] = st; data[8] = ct;
            break;
        case MATRIX_ROTATION_Y:
            st = sin(theta), ct = cos(theta);
            data[0] = ct;  data[1] = 0;  data[2] = st;
            data[3] = 0;   data[4] = 1;  data[5] = 0;
            data[6] = -st; data[7] = 0;  data[8] = ct;
            break;
        case MATRIX_ROTATION_Z:
            st = sin(theta), ct = cos(theta);
            data[0] = ct; data[1] = -st;data[2] = 0;
            data[3] = st; data[4] = ct; data[5] = 0;
            data[6] = 0;  data[7] = 0;  data[8] = 1;
            break;
    }
}

template<typename T>
Matrix3<T>::Matrix3(int i, float arg1, float arg2) {
    switch(i){
        case MATRIX_ROTATION:
            float st = sin(arg1), ct = cos(arg1),
            sp = sin(arg2), cp = cos(arg2);
            data[0] = ct;    data[1] = -st;   data[2] = 0;
            data[3] = st*cp; data[4] = ct*cp; data[5] = -sp;
            data[6] = st*sp; data[7] = ct*sp; data[8] = cp;
            break;
    }
}

template<typename T>
Matrix3<T>::Matrix3(int i, const Vector3<T>& v, float arg1) {
    switch(i) {
        case MATRIX_ROTATION: {
            float len = sqrt(v.X()*v.X() + v.Y()*v.Y() + v.Z()*v.Z());
            Matrix3 what(0,    -v.Z(), v.Y(),
                         v.Z(), 0,    -v.X(),
                        -v.Y(), v.X(), 0);
            Matrix3 u = Matrix3(MATRIX_IDENTITY) + what/(len)*sin(arg1) + what*what/pow(len, 2)*(1 - cos(arg1));

            for(int i = 0 ; i< 9; i++)
                data[i] = u.data[i];
        }
        break;
    }
}

template<typename T>
Matrix3<T>::Matrix3(T a1, T a2, T a3,
                    T a4, T a5, T a6,
                    T a7, T a8, T a9)
{
      data[0] = a1; data[1] = a2; data[2] = a3;
      data[3] = a4; data[4] = a5; data[5] = a6;
      data[6] = a7; data[7] = a8; data[8] = a9;
}


template<typename T>
T* Matrix3<T>::operator[](int n) throw (std::out_of_range) {
    if(n > 3) throw std::out_of_range("Index out of range");
    return data + 3*n;
}

template<typename T>
const T* Matrix3<T>::operator[](int n) const throw (std::out_of_range) {
    if(n > 3) throw std::out_of_range("Index out of range");
    return data + 3*n;
}

template<typename T>
float Matrix3<T>::det() const {
    return data[0]*(data[4]*data[8] - data[5]*data[7]) -
           data[1]*(data[3]*data[8] - data[5]*data[6]) +
           data[2]*(data[3]*data[7] - data[4]*data[6]);
}

template<typename T>
Matrix3<T> Matrix3<T>::transpose() const {
    return Matrix3(this->get(0, 0), this->get(0, 1), this->get(0, 2),
                   this->get(1, 0), this->get(1, 1), this->get(1, 2),
                   this->get(2, 0), this->get(2, 1), this->get(2, 2));
}

template<typename T>
T Matrix3<T>::get(int x, int y) const throw (std::out_of_range) {
    if(x > 2 || y > 2 ) throw std::out_of_range("Index(es) are out of range.");
    return data[x + 3*y];
}

template<typename U>
std::ostream& operator<<(std::ostream& os, const Matrix3<U>& m) {
    os << "["<< m.data[0] << ", " << m.data[1] << ", " << m.data[2] << "]" << "\n";
    os << "["<< m.data[3] << ", " << m.data[4] << ", " << m.data[5] << "]" << "\n";
    os << "["<< m.data[6] << ", " << m.data[7] << ", " << m.data[8] << "]" << "\n";
    return os;
}

template<typename T>
Vector3<T> cross(const Vector3<T>& v1, const Vector3<T>& v2) {
    return Vector3<T>(v1.Y()*v2.Z() - v1.Z()*v2.Y(),
                   v1.Z()*v2.X() - v1.X()*v2.Z(),
                   v1.X()*v2.Y() - v1.Y()*v2.X());
}

template<typename T>
T operator*(const Vector3<T>& v1, const Vector3<T>& v2) {
    return v1.X()*v2.X() + v1.Y()*v2.Y() + v1.Z()*v2.Z();
}

template<typename T>
Vector3<T> operator*(const Vector3<T>& v, float f) {
    return Vector3<T>(v.X()*f, v.Y()*f, v.Z()*f);
}

template<typename T>
Vector3<T> operator*(float f, const Vector3<T>& v) {
    return v*f;
}

template<typename T>
Vector3<T> operator+(const Vector3<T>& v1, const Vector3<T>& v2) {
    return Vector3<T>(v1.X() + v2.X(), v1.Y() + v2.Y(), v1.Z() + v2.Z());
}

template<typename T>
Vector3<T> operator-(const Vector3<T>& v1, const Vector3<T>& v2) {
    return Vector3<T>(v1.X() - v2.X(), v1.Y() - v2.Y(), v1.Z() - v2.Z());
}

template<typename T>
Vector3<T> operator/(const Vector3<T>& v, float f) {
    return Vector3<T>(v.X()/f, v.Y()/f, v.Z()/f);
}

template<typename T>
Vector3<T> operator*(const Matrix3<T>& m, const Vector3<T>& v) {
    return Vector3<T>(m.get(0, 0)*v.X() + m.get(1, 0)*v.Y() + m.get(2, 0)*v.Z(),
                      m.get(0, 1)*v.X() + m.get(1, 1)*v.Y() + m.get(2, 1)*v.Z(),
                      m.get(0, 2)*v.X() + m.get(1, 2)*v.Y() + m.get(2, 2)*v.Z());
}

template<typename T>
Vector3<T> operator*(const Vector3<T>& v, const Matrix3<T>& m) {
    return Vector3<T>(m.get(0, 0)*v.X() + m.get(0, 1)*v.Y() + m.get(0, 2)*v.Z(),
                      m.get(1, 0)*v.X() + m.get(1, 1)*v.Y() + m.get(1, 2)*v.Z(),
                      m.get(2, 0)*v.X() + m.get(2, 1)*v.Y() + m.get(2, 2)*v.Z());
}

template<typename T>
Matrix3<T> operator+(const Matrix3<T>& m1, const Matrix3<T>& m2) {
    return Matrix3<T>(m1.get(0, 0) + m2.get(0, 0), m1.get(1, 0) + m2.get(1, 0), m1.get(2, 0) + m2.get(2, 0),
                      m1.get(0, 1) + m2.get(0, 1), m1.get(1, 1) + m2.get(1, 1), m1.get(2, 1) + m2.get(2, 1),
                      m1.get(0, 2) + m2.get(0, 2), m1.get(1, 2) + m2.get(1, 2), m1.get(2, 2) + m2.get(2, 2));
}

template<typename T>
Matrix3<T> operator*(const Matrix3<T>& m, float f) {
    return Matrix3<T>(m.get(0, 0)*f, m.get(1, 0)*f, m.get(2, 0)*f,
                      m.get(0, 1)*f, m.get(1, 1)*f, m.get(2, 1)*f,
                      m.get(0, 2)*f, m.get(1, 2)*f, m.get(2, 2)*f);
}

template<typename T>
Matrix3<T> operator*(float f, const Matrix3<T>& m) {
    return m*f;
}

template<typename T>
Matrix3<T> operator/(const Matrix3<T>& m, float f) {
    return Matrix3<T>(m.get(0, 0)/f, m.get(1, 0)/f, m.get(2, 0)/f,
                      m.get(0, 1)/f, m.get(1, 1)/f, m.get(2, 1)/f,
                      m.get(0, 2)/f, m.get(1, 2)/f, m.get(2, 2)/f);

}

template<typename T>
Matrix3<T> operator*(const Matrix3<T>& m1, const Matrix3<T>& m2) {
    return Matrix3<T>(m1.get(0, 0)*m2.get(0, 0) + m1.get(1, 0)*m2.get(0, 1) + m1.get(2, 0)*m2.get(0, 2),
                      m1.get(0, 0)*m2.get(1, 0) + m1.get(1, 0)*m2.get(1, 1) + m1.get(2, 0)*m2.get(1, 2),
                      m1.get(0, 0)*m2.get(2, 0) + m1.get(1, 0)*m2.get(2, 1) + m1.get(2, 0)*m2.get(2, 2),

                      m1.get(0, 1)*m2.get(0, 0) + m1.get(1, 1)*m2.get(0, 1) + m1.get(2, 1)*m2.get(0, 2),
                      m1.get(0, 1)*m2.get(1, 0) + m1.get(1, 1)*m2.get(1, 1) + m1.get(2, 1)*m2.get(1, 2),
                      m1.get(0, 1)*m2.get(2, 0) + m1.get(1, 1)*m2.get(2, 1) + m1.get(2, 1)*m2.get(2, 2),

                      m1.get(0, 2)*m2.get(0, 0) + m1.get(1, 2)*m2.get(0, 1) + m1.get(2, 2)*m2.get(0, 2),
                      m1.get(0, 2)*m2.get(1, 0) + m1.get(1, 2)*m2.get(1, 1) + m1.get(2, 2)*m2.get(1, 2),
                      m1.get(0, 2)*m2.get(2, 0) + m1.get(1, 2)*m2.get(2, 1) + m1.get(2, 2)*m2.get(2, 2));
}

//Matrix4 implementation

template<typename T>
Matrix4<T>::Matrix4() {
    for(int i = 0; i < 16; i++)
      data[i] = i%5 == 0;
}

template<typename T>
Matrix4<T>::Matrix4(int i) {
    switch(i){
        case MATRIX_IDENTITY:
        default:
        for(int i = 0; i < 16; i++)
            data[i] = i%5 == 0;
        break;
    }
}

template<typename T>
Matrix4<T>::Matrix4(int i, float theta) {
    switch(i){
        float st, ct;
        case MATRIX_ROTATION:
        case MATRIX_ROTATION_X:
            st = sin(theta), ct = cos(theta);
            data[0] = 1; data[1] = 0; data[2] = 0; data[3] = 0;
            data[4] = 0; data[5] = ct; data[6] = -st; data[7] = 0;
            data[8] = 0; data[9] = st; data[10] = ct; data[11] = 0;
            data[12] = 0; data[13] = 0; data[14] = 0; data[15] = 1;
        break;
        case MATRIX_ROTATION_Y:
            st = sin(theta), ct = cos(theta);
            data[0] = ct; data[1] = 0; data[2] = st; data[3] = 0;
            data[4] = 0; data[5] = 1; data[6] = 0; data[7] = 0;
            data[8] = -st; data[9] = 0; data[10] = ct; data[11] = 0;
            data[12] = 0; data[13] = 0; data[14] = 0; data[15] = 1;
        break;
        case MATRIX_ROTATION_Z:
            st = sin(theta), ct = cos(theta);
            data[0] = ct; data[1] = -st; data[2] = 0; data[3] = 0;
            data[4] = st; data[5] = ct; data[6] = 0; data[7] = 0;
            data[8] = 0; data[9] = 0; data[10] = 1; data[11] = 0;
            data[12] = 0; data[13] = 0; data[14] = 0; data[15] = 1;
        break;
    }
}

template<typename T>
Matrix4<T>::Matrix4(int i, float arg1, float arg2) {
    switch(i){
        case MATRIX_ROTATION:
            float st = sin(arg1), ct = cos(arg1),
            sp = sin(arg2), cp = cos(arg2);
            data[0] = ct; data[1] = -st; data[2] = 0; data[3] = 0;
            data[4] = st*cp; data[5] = ct*cp; data[6] = -sp; data[7] = 0;
            data[8] = st*sp; data[9] = ct*sp; data[10] = cp; data[11] = 0;
            data[12] = 0; data[13] = 0; data[14] = 0; data[15] = 1;
        break;
    }
}

template<typename T>
Matrix4<T>::Matrix4(int i, const Point3<T>& p) {
    switch(i){
        case MATRIX_TRANSLATION:
            for(int i = 0; i< 16; i++)
                data[i] = i%5 ==0;
            data[3] = p.X();
            data[7] = p.Y();
            data[11] = p.Z();
        break;
    }
}

template<typename T>
Matrix4<T>::Matrix4(T a1, T a2, T a3, T a4,
                    T a5, T a6, T a7, T a8,
                    T a9, T a10, T a11, T a12,
                    T a13, T a14, T a15, T a16)
{
     data[0] = a1;   data[1] = a2;   data[2] = a3;   data[3] = a4;
     data[4] = a5;   data[5] = a6;   data[6] = a7;   data[7] = a8;
     data[8] = a9;   data[9] = a10;  data[10] = a11; data[11] = a12;
     data[12] = a13; data[13] = a14; data[14] = a15; data[15] = a16;
}

template<typename T>
T* Matrix4<T>::operator[](unsigned int n) {
    if(n > 3) throw std::out_of_range("index out of range!");
    return data + 4*n;
}

template<typename T>
const T* Matrix4<T>::operator[](unsigned int n) const {
    if(n > 3) throw std::out_of_range("index out of range!");
    return data + 4*n;
}

template <typename T>
T Matrix4<T>::get(int x, int y) const throw (std::out_of_range) {
    if(x > 3 || y > 3) throw std::out_of_range("index(es) out of range");
    return data[x + 4*y];
}

template<typename T>
T Matrix4<T>::get(int n) const throw (std::out_of_range) {
    if(n > 15) throw std::out_of_range("index out of range");
    return data[n];
}

template<typename T>
float Matrix4<T>::det() const {
    return data[0] * Matrix3<T>(data[5],data[6],data[7],data[9],data[10],data[11],data[13],data[14],data[15]).det()
          -data[1] * Matrix3<T>(data[4],data[6],data[7],data[8],data[10],data[11],data[12],data[14],data[15]).det()
          +data[2] * Matrix3<T>(data[4],data[5],data[7],data[8],data[9], data[11],data[12],data[13],data[15]).det()
          -data[3] * Matrix3<T>(data[4],data[5],data[6],data[8],data[9], data[10],data[12],data[13],data[14]).det();
}

template<typename T>
Matrix4<T> Matrix4<T>::transpose() const {
    Matrix4<T> transposed;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            transposed[i][j] = this->get(i, j);
    return transposed;
}

template<typename U>
std::ostream& operator<<(std::ostream& os, const Matrix4<U> m) {
    os << "["<< m.data[0] << ", " << m.data[1] << ", " << m.data[2] <<  ", " << m.data[3] <<  "]" << "\n";
    os << "["<< m.data[4] << ", " << m.data[5] << ", " << m.data[6] <<  ", " << m.data[7] <<  "]" << "\n";
    os << "["<< m.data[8] << ", " << m.data[9] << ", " << m.data[10] << ", " << m.data[11] <<  "]" << "\n";
    os << "["<< m.data[12] << ", " << m.data[13] << ", " << m.data[14] <<  ", " << m.data[15] <<  "]" << "\n";
    return os;
}

template<typename T>
Vector3<T> operator*(const Matrix4<T>& m, const Vector3<T>& v) {
    return Vector3<T>(m.get(0, 0)*v.X() + m.get(1, 0)*v.Y() + m.get(2, 0)*v.Z() + m.get(3, 0),
                      m.get(0, 1)*v.X() + m.get(1, 1)*v.Y() + m.get(2, 1)*v.Z() + m.get(3, 1),
                      m.get(0, 2)*v.X() + m.get(1, 2)*v.Y() + m.get(2, 2)*v.Z() + m.get(3, 2));
}

template<typename T>
Vector3<T> operator*(const Vector3<T>& v, const Matrix4<T>& m) {
    return Vector3<T>(m.get(0, 0)*v.X() + m.get(0, 1)*v.Y() + m.get(0, 2)*v.Z() + m.get(0, 3),
                      m.get(1, 0)*v.X() + m.get(1, 1)*v.Y() + m.get(1, 2)*v.Z() + m.get(1, 3),
                      m.get(2, 0)*v.X() + m.get(2, 1)*v.Y() + m.get(2, 2)*v.Z() + m.get(2, 3));
}

template<typename T>
Matrix4<T> operator*(const Matrix4<T>& m, float f) {
    Matrix4<T> m2;
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            m2[i][j] = m.get(i,j) * f;
    return m2;
}

template<typename T>
Matrix4<T> operator*(float f, const Matrix4<T>& m) {
    return m*f;
}

template<typename T>
Matrix4<T> operator~(const Matrix4<T>& m);

template<typename T>
Matrix4<T> operator*(const Matrix4<T>& m1, const Matrix4<T>& m2) {
    Matrix4<T> mat;
    for(int i = 0; i < 4; i++) {
        mat[i][i] = 0; //since default-constructor gives identity matrix
        for(int j = 0; j < 4; j++)
            for(int k = 0; k < 4; k++)
                mat[i][j] += m1.get(k, i) * m2.get(j, k);
    }
    return mat;
}

//Vector

template<typename T>
Vector<T>::Vector(int size) : size(size), data(new T[size]()) { }

template<typename T>
Vector<T>::Vector(int size, const T* p) : size(size), data(new T[size]()) {
    for(int i = 0; i < size; ++i)
        data[i] = p[i];
}

template<typename T>
Vector<T>::Vector(const Vector& v) : Vector(v.getLength(), v.data) { }

template<typename T>
T& Vector<T>::operator[](int n) {
    return data[n];
}

template<typename T>
int Vector<T>::getLength() const {
    return size;
}

template<typename T>
T Vector<T>::get(int n) const {
    return data[n];
}

template<typename U>
std::ostream& operator<<(std::ostream& os, const Vector<U>& vec) {
    os << "[";
    for(int i = 0; i < vec.getLength(); ++i) {
        os << vec.data[i];
        if(i != vec.getLength()-1) os << ", ";
    }
    os << "]";
    return os;
}

template<typename T>
T operator*(const Vector<T>& v1, const Vector<T>& v2) {
    T result = 0;
    if(v1.getLength() == v2.getLength())
        for(int i = 0; i < v1.getLength(); i++)
            result += v1.get(i) * v2.get(i);
    return result;
}

template<typename T>
Vector<T> operator+(const Vector<T>& v1, const Vector<T>& v2) {
    Vector<T> vec(v1.getLength());
    if(v1.getLength() == v2.getLength()){
        for(int i = 0; i < vec.getLength(); ++i)
            vec[i] = v1.get(i) + v2.get(i);
    }
    else {
        for(int i= 0; i< vec.getLength(); ++i)
            vec[i] = 0;
    }
    return vec;
}

template<typename T>
Vector<T> operator-(const Vector<T>& v1, const Vector<T>& v2) {
    Vector<T> vec(v1.getLength());
    if(v1.getLength() == v2.getLength()){
        for(int i = 0; i < vec.getLength(); ++i)
            vec[i] = v1.get(i) - v2.get(i);
    }
    else {
        for(int i = 0; i< vec.getLength(); ++i)
            vec[i] = 0;
    }
    return vec;
}

template<typename T>
Vector<T> operator*(const Vector<T>& v1, float f) {
    Vector<T> vec(v1.getLength());
    for(int i = 0; i < vec.getLength(); ++i)
        vec[i] = v1.get(i) * f;
    return vec;
}

template<typename T>
Vector<T> operator*(float f, const Vector<T>& v1) {
    return v1*f;
}

template<typename T>
Vector<T> operator/(const Vector<T>& v1, float f) {
    Vector<T> vec(v1.getLength());
    for(int i = 0; i < vec.getLength(); ++i)
        vec[i] = v1.get(i) / f;
    return vec;
}

//general matrix implementation

template<typename T>
Matrix<T>::Matrix(int w, int h) : w(w), h(h), data(new T[w*h]()) { }

template<typename T>
Matrix<T>::Matrix(int w, int h, const T* p) : Matrix(w,h) {
    for(int i = 0; i < w*h; ++i)
        data[i] = p[i];
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& mat) : w(mat.w), h(mat.h), data(new T[w*h]()) {
    for(int i = 0; i < h; ++i)
        for(int j = 0; j < w; ++j)
            data[i*w + j] = mat.get(j, i);
}

template<typename T>
T* Matrix<T>::operator[](int n) {
    return data + w*n;
    //return &data[0] + w*n;
}

template<typename T>
T Matrix<T>::get(int x, int y) const {
    return data[y*w + x];
}
template<typename T>
T Matrix<T>::get(int n) const {
    return data[n];
}

template<typename T>
int Matrix<T>::getWidth() const {
   return w;
}
template<typename T>
int Matrix<T>::getHeight() const {
   return h;
}

template<typename T>
int Matrix<T>::getW() const {
    return w;
}

template<typename T>
int Matrix<T>::getH() const {
    return h;
}

template<typename T>
float Matrix<T>::det() const {
    if(w != h) return 0;

    if(w == 2 && h ==2) return data[0]*data[3] - data[1]*data[2];
    else {
        float sum = 0;
        int u = 1;
        for(int i = 0; i < w; i++){
            sum += u * data[i] * (_minor(i, 0)._det());
            u *= -1;
        }
        return sum;
    }
}

template<typename T>
float Matrix<T>::_det() const {
    if(w == 2 && h ==2) return data[0]*data[3] - data[1]*data[2];
    else {
        float sum = 0;
        int u = 1;
        for(int i = 0; i < w; i++){
            sum += u * data[i] * (_minor(i, 0)._det());
            u*=-1;
        }
        return sum;
    }
}

template<typename T>
Matrix<T> Matrix<T>::transpose() const {
    Matrix<T> transposed(this->h, this->w);
    for(int i= 0 ; i < this->h; ++i)
        for(int j = 0; j < this->w; ++j)
            transposed[j][i] = this->get(j, i);
    return transposed;
}

template<typename T>
Matrix<T> Matrix<T>::inv() const { //invertere vha sub-determinantene, -> adjoint method
    Matrix mat(w, h);
    for(int i= 0; i< h; ++i)
        for(int j = 0; j < w; ++j)
            mat[i][j] = _minor(j, i).det();

    for(int i = 0; i < h; ++i)
        for(int j = 0; j < w; ++j)
            mat[i][j] = (i + j) & 1 ? -mat[i][j] : mat[i][j]; //minus hvis odde

    return mat.transpose() / det();
}

template<typename T>
Matrix<T> Matrix<T>::_minor(int a, int b) const {
    Matrix<T> mat(w - 1, h - 1);
    int offset_i = 0, offset_j = 0;
    for(int i = 0; i < h - 1; ++i){
        if(i == b) offset_i++;
        for(int j = 0; j < w - 1; ++j){
            if(j == a) offset_j++;
            mat[i][j] = this->get(j + offset_j, i + offset_i);
        }
        offset_j = 0;
    }
    return mat;
}

template<typename U>
std::ostream& operator<<(std::ostream& os, const Matrix<U>& mat) {
    os << mat.get(0,0) << std::endl << std::endl;
    for(int i = 0; i < mat.getHeight(); ++i) {
        for(int j = 0; j < mat.getWidth(); ++j) {
            if(j == 0)  os << "[" << mat.get(j,i) << ", ";
            else if(j == mat.getWidth()-1) os << mat.get(j,i) << "]\n";
            else os << mat.get(j,i) << ", ";
        }
    }
    return os;
}

template<typename T>
Vector<T> operator*(const Matrix<T>& mat, const Vector<T>& vec) {
    Vector<T> result(mat.getHeight());
    if(mat.getWidth() != vec.getLength()) return result;

    else {
        for(int i = 0; i< mat.getHeight(); ++i){
            result[i] = 0;
            for(int j = 0; j < mat.getWidth(); ++j)
                result[i] += mat.get(j, i) * vec.get(j);
        }
        return result;
    }
}

template<typename T>
Vector<T> operator*(const Vector<T>& vec, const Matrix<T>& mat) {
    Vector<T> result(mat.getWidth());
    if(mat.getHeight() != vec.getLength()) return result;

    else {
        for(int i = 0; i < mat.getWidth(); ++i){
            result[i] = 0;
            for(int j = 0; j < mat.getHeight(); ++j)
                result[i] += mat.get(j, i) * vec.get(j);
        }
        return result;
    }
}

template<typename T>
Matrix<T> operator*(const Matrix<T>& mat, float f) {
    Matrix<T> result(mat.getWidth(), mat.getHeight());
    for(int i  = 0; i < mat.getHeight(); ++i)
        for(int j = 0; j < mat.getWidth(); ++j)
            result[i][j] = mat.get(j, i) * f;
    return result;
}

template<typename T>
Matrix<T> operator*(float f, const Matrix<T>& mat) {
    return mat*f;
}

template<typename T>
Matrix<T> operator/(const Matrix<T>& mat, float f) {
    Matrix<T> result(mat.getHeight(), mat.getWidth());
    for(int i  = 0; i < mat.getHeight(); ++i)
        for(int j = 0; j < mat.getWidth(); ++j)
            result[i][j] = mat.get(j, i) / f;
    return result;
}


template<typename T>
Matrix<T> operator*(const Matrix<T>& m1, const Matrix<T>& m2) {
    Matrix<T> mat(m1.getHeight(), m2.getWidth());

    if(m1.getWidth() == m2.getHeight()) {
        for(int i = 0; i < m1.getHeight(); ++i)
            for(int j = 0; j < m2.getWidth();++j) {
                mat[i][j] = 0;
                for(int k = 0; k < m2.getHeight(); ++k)
                    mat[i][j] += m1.get(k,i) * m2.get(j,k);
            }
    }
    return mat;
}

#endif // MATRIX_H
