#ifndef MATH_H
#define MATH_H

#include "matrix.h"

#include <cmath>
#include <complex>
#include <float.h>

namespace Math {
//Defines
#define M_PI            3.1415926535897932384626433832795f
#define RAD(val)        ((val)*0.0174532925199432957692369076848f)
#define DEG(val)        ((val)*57.295779513082320876798154814105f)
#define LARGE_EPSILON   1e-2f
#define EPSILON         1e-4f
#define TINY_EPSILON    1e-5f
#define M_INFINITE      3.4e38f
#define M_EULER_NUMBER  2.71828182845904523536f
#define M_SQRT2         1.4142135623730950488016887242097f
#define M_SQRT3         1.7320508075688772935274463415059f

//(kinda optimized) math functions
float fSinCosRecurse (float ret, float rad, const float rad2, float radpow, float fact, const int prec, int cur) {
    radpow *= -rad2;
    fact   *= cur++;
    fact   *= cur++;

    ret += radpow / fact;

    if(cur < prec)
        return fSinCosRecurse(ret, rad, rad2, radpow, fact, prec, cur);
    else
        return ret;
}

float fSin (float rad, int precision = 4) {
    while(rad >  M_PI) rad -= (M_PI*2.0f);
    while(rad < -M_PI) rad += (M_PI*2.0f);

    const float rad2 = (rad*rad);
    float ret = rad;

    return fSinCosRecurse(ret, rad, rad2, rad, 1.0f, (precision << 1) + 1, 2);
}

float fCos (float rad, int precision = 4) {
    while(rad >  M_PI) rad -= (M_PI*2.0f);
    while(rad < -M_PI) rad += (M_PI*2.0f);

    const float rad2 = (rad*rad);
    float ret = 1.0f;

    return fSinCosRecurse(ret, rad, rad2, 1.0f, 1.0f, (precision << 1) + 1, 1);
}

inline bool fEqual(float f1, float f2, float precision = LARGE_EPSILON) {
    return fabsf(f1-f2) <= precision;
}

int factorial(int n) {
    int res = 1;
    for (int i = 1; i <= n; ++i)
        res *= i;
    return res;
}

int digitSum(int n) {
    return n ? (n%10) + digitSum(n/10) : 0;
}

unsigned long long combination(unsigned long long n, unsigned long long k) {
    if (k > n) return 0;

    if (k > n/2) k = n-k;

    unsigned long long r = 1;
    for (unsigned long long d = 0; d < k; ++d) {
        r *= (n - d);
        r /= (d + 1);
    }
    return r;
}

std::pair<std::complex<float>, std::complex<float> > solveQuadratic(float a, float b, float c) {
    std::complex<float> x1 = 0, x2 = 0;
    float determinant = b*b - (4 * a*c);

    if (determinant > 0) {
        x1 = (-b + sqrt(determinant)) / (2*a);
        x2 = (-b - sqrt(determinant)) / (2*a);
    }
    else if (determinant == 0) {
        x1 = (-b + sqrt(determinant)) / (2*a);
        x2 = (-b + sqrt(determinant)) / (2*a);
    }
    else {
        x1.real(-b / (2*a));
        x1.imag(sqrt(-determinant) / (2*a));

        x2.real(-b / (2*a));
        x2.imag(-sqrt(-determinant) / (2*a));
    }

    return std::make_pair(x1, x2);
}

static bool doIntersect(Vector2f p1, Vector2f q1, Vector2f p2, Vector2f q2) {
    static auto det = [](const Vector2f& u, const Vector2f& v) {return u.X()*v.Y() - u.Y()*v.X();};
    return (det(p2-p1, q1-p1)*det(p2-p1, q2-p1) < 0) && (det(q2-q1, p1-q1)*det(q2-q1, p2-q1) < 0);
}

static Vector2f getIntersection(Vector2f p1, Vector2f q1, Vector2f p2, Vector2f q2) {
    if(doIntersect(p1,q1,p2,q2)) {
        if(p2.X() - p1.X() != 0 && q2.X() - q1.X() != 0) {
            float a1 = (p2.Y() - p1.Y())/(p2.X() - p1.X());
            float a2 = (q2.Y() - q1.Y())/(q2.X() - q1.X());
            float b1 = p1.Y() - a1*p1.X();
            float b2 = q1.Y() - a2*q1.X();
            float Ix = (b2-b1)/(a1-a2);
            float Iy = a1*Ix+b1;
            return Vector2f(Ix,Iy);
        }

        if(p2.X() - p1.X() == 0) {
            float a2 = (q2.Y() - q1.Y())/(q2.X() - q1.X());
            float b1 = p1.X();
            float b2 = q1.Y() - a2*q1.X();
            float Ix = b1;
            float Iy = a2*b1+b2;
            return Vector2f(Ix,Iy);
        }

        if(q2.X() - q1.X() == 0) {
            float a1 = (p2.Y() - p1.Y())/(p2.X() - p1.X());
            float b1 = p1.Y() - a1*p1.X();
            float b2 = q1.X();
            float Ix = b2;
            float Iy = a1*b2+b1;
            return Vector2f(Ix,Iy);
        }
    }

    return Vector2f();
}

inline float gaussianFunction(float maxVal, float wideness, float x) {
    return maxVal*exp(-pow(x,2)/(2*pow(wideness,2)));
}

inline float clamp(float val, float lower, float upper) {
    return std::max(lower, std::min(val, upper));
}


} //namespace Math;


#endif // MATH_H
