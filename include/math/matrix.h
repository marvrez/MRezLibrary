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

    T getX() const;
    T getY() const;

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
    T* operator[](unsigned int n) throw (std::out_of_range);
    const T* operator[](unsigned int n) const throw (std::out_of_range);

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Matrix2<U>& m);
};

template<typename T>
using Vector2 = Point2<T>;

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
    T getX() const;
    T getY() const;
    T getZ() const;

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


//Matrix4

template<typename T>
class Matrix4 {
private:
    T data[16];
public:
    float det() const;

    T* operator[](unsigned int n);
    const T* operator[](unsigned int n) const;
    T get(int x, int y) const throw (std::out_of_range);
    T get(int n) const throw (std::out_of_range);

    Matrix4();
    Matrix4(int i);
    Matrix4(int i, float theta);
    Matrix4(int i, float arg1, float arg2);
    Matrix4(int i, const Point3<T>& p);
    Matrix4(T a1, T a2, T a3, T a4,
            T a5, T a6, T a7, T a8,
            T a9, T a10, T a11, T a12,
            T a13, T a14, T a15, T a16);

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Matrix4<U> m);
};

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
    std::vector<T> data;
    int size;
public:
    T& operator[](int n);
    int getLength() const;
    T get(int n) const;
    Vector(int size);
    Vector(int size, const T* p);
    Vector(const Vector& gv);

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
class Matrix{
private:
    vector<T> data;
    int w, h;
public:
    T* operator[](int a);

    T get(int x, int y) const;
    T get(int n) const;
    int getWidth() const;
    int getHeight() const;
    int getW() const;
    int getH() const;
    float det() const;
    float _det() const;
    Matrix inv() const;
    Matrix(int w, int h);
    Matrix(int w, int h, const T* p);
    Matrix(const Matrix& gm);

    Matrix _minor(int a, int b) const;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, Matrix<U> mat);
};

template<typename T>
Vector<T> operator*(const Matrix<T>& mat, const Vector<T>& vec);

template<typename T>
Vector<T> operator*(const Vector<T>& vec, const Matrix<T>& mat);

template<typename T>
Matrix<T> operator~(const Matrix<T>& mat);

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
T Point2<T>::getX() const {
    return x;
}

template <typename T>
T Point2<T>::getY() const {
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
    return v1.get(0)*v2.get(1) - v1.get(1)*v2.get(0);
}

template<typename T>
T operator*(const Vector2<T>& v1, const Vector2<T>& v2) {
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
T Point3<T>::getX() const {
    return x;
}

template<typename T>
T Point3<T>::getY() const {
    return y;
}

template<typename T>
T Point3<T>::getZ() const {
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
        case MATRIX_ROTATION:
            float len = sqrt(v.getX()*v.getX() + v.getY()*v.getY() + v.getZ()*v.getZ());
            Matrix3 what(0,       -v.get(2),       v.get(1),
                         v.get(2), 0,             -v.get(0),
                        -v.get(1), v.get(0),       0);
            Matrix3 u = Matrix3(MATRIX_IDENTITY) + what/(len)*sin(arg1) + what*what/pow(len, 2)*(1 - cos(arg1));

            for(int i = 0 ; i< 9; i++)
                data[i] = u.data[i];
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
    return Vector3<T>(v1.get(1)*v2.get(2) - v1.get(2)*v2.get(1),
                   v1.get(2)*v2.get(0) - v1.get(0)*v2.get(2),
                   v1.get(0)*v2.get(1) - v1.get(1)*v2.get(0));
}

template<typename T>
T operator*(const Vector3<T>& v1, const Vector3<T>& v2) {
    return v1.get(0)*v2.get(0) + v1.get(1)*v2.get(1) + v1.get(2)*v2.get(2);
}

template<typename T>
Vector3<T> operator*(const Vector3<T>& v, float f) {
    return Vector3<T>(v.get(0)*f, v.get(1)*f, v.get(2)*f);
}

template<typename T>
Vector3<T> operator*(float f, const Vector3<T>& v) {
    return Vector3<T>(v.get(0)*f, v.get(1)*f, v.get(2)*f);
}

template<typename T>
Vector3<T> operator+(const Vector3<T>& v1, const Vector3<T>& v2) {
    return Vector3<T>(v1.get(0) + v2.get(0), v1.get(1) + v2.get(1), v1.get(2) + v2.get(2));
}

template<typename T>
Vector3<T> operator-(const Vector3<T>& v1, const Vector3<T>& v2) {
    return Vector3<T>(v1.get(0) - v2.get(0), v1.get(1) - v2.get(1), v1.get(2) - v2.get(2));
}

template<typename T>
Vector3<T> operator/(const Vector3<T>& v, float f) {
    return Vector3<T>(v.get(0)/f, v.get(1)/f, v.get(2)/f);
}

template<typename T>
Vector3<T> operator*(const Matrix3<T>& m, const Vector3<T>& v) {
    return Vector3<T>(m.get(0, 0)*v.get(0) + m.get(1, 0)*v.get(1) + m.get(2, 0)*v.get(2),
                      m.get(0, 1)*v.get(0) + m.get(1, 1)*v.get(1) + m.get(2, 1)*v.get(2),
                      m.get(0, 2)*v.get(0) + m.get(1, 2)*v.get(1) + m.get(2, 2)*v.get(2));
}

template<typename T>
Vector3<T> operator*(const Vector3<T>& v, const Matrix3<T>& m) {
    return Vector3<T>(m.get(0, 0)*v.get(0) + m.get(0, 1)*v.get(1) + m.get(0, 2)*v.get(2),
                      m.get(1, 0)*v.get(0) + m.get(1, 1)*v.get(1) + m.get(1, 2)*v.get(2),
                      m.get(2, 0)*v.get(0) + m.get(2, 1)*v.get(1) + m.get(2, 2)*v.get(2));
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
    return Matrix3<T>(m.get(0, 0)*f, m.get(1, 0)*f, m.get(2, 0)*f,
                      m.get(0, 1)*f, m.get(1, 1)*f, m.get(2, 1)*f,
                      m.get(0, 2)*f, m.get(1, 2)*f, m.get(2, 2)*f);
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
            data[3] = p.get(0);
            data[7] = p.get(1);
            data[11] = p.get(2);
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
    return Vector3<T>(m.get(0, 0)*v.get(0) + m.get(1, 0)*v.get(1) + m.get(2, 0)*v.get(2) + m.get(3, 0),
                      m.get(0, 1)*v.get(0) + m.get(1, 1)*v.get(1) + m.get(2, 1)*v.get(2) + m.get(3, 1),
                      m.get(0, 2)*v.get(0) + m.get(1, 2)*v.get(1) + m.get(2, 2)*v.get(2) + m.get(3, 2));
}

template<typename T>
Vector3<T> operator*(const Vector3<T>& v, const Matrix4<T>& m) {
    return Vector3<T>(m.get(0, 0)*v.get(0) + m.get(0, 1)*v.get(1) + m.get(0, 2)*v.get(2) + m.get(0, 3),
                      m.get(1, 0)*v.get(0) + m.get(1, 1)*v.get(1) + m.get(1, 2)*v.get(2) + m.get(1, 3),
                      m.get(2, 0)*v.get(0) + m.get(2, 1)*v.get(1) + m.get(2, 2)*v.get(2) + m.get(2, 3));
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
    Matrix4<T> m2;
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            m2[i][j] = m.get(i,j) * f;
    return m2;
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
Vector<T>::Vector(int size) : size(size), data(size) { }

template<typename T>
Vector<T>::Vector(int size, const T* p) : size(size), data(p, p + size) { }

template<typename T>
Vector<T>::Vector(const Vector& gv) : size(gv.size), data(gv.data) { }

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
    for(int i = 0; i < vec.data.size(); ++i) {
        os << vec.data[i];
        if(i != vec.data.size()-1) os << ", ";
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
    Vector<T> vec(v1.getLength());
    for(int i = 0; i < vec.getLength(); ++i)
        vec[i] = v1.get(i) * f;
    return vec;
}

template<typename T>
Vector<T> operator/(const Vector<T>& v1, float f) {
    Vector<T> vec(v1.getLength());
    for(int i = 0; i < vec.getLength(); ++i)
        vec[i] = v1.get(i) / f;
    return vec;
}

#endif // MATRIX_H
