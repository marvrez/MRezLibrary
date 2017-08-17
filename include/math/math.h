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

static bool doIntersect(Vector2f&& p1, Vector2f&& q1, Vector2f&& p2, Vector2f& q2) {

    //0 => colinear, 1 => clockwise, 2 => counterclockwise
    auto direction = [](Vector2f& p, Vector2f q, Vector2f& r)  {
        int cross = (Matrix2f(r[0]-q[0], r[1]-q[1],
                                q[0]-p[0], q[1]-p[1])).det();

        if (cross == 0) return 0;  // colinear
        return (cross > 0) ? 1: 2; // clock or counterclock wise
    };

    // checks if point 'q' lies on line segment 'pr'
    auto onSegment = [](Vector2f& p, Vector2f& q, Vector2f& r) {
        return (q[0] <= std::max(p[0], r[0]) && q[0] >= std::min(p[0], r[0]) &&
                q[1] <= std::max(p[1], r[1]) && q[1] >= std::min(p[1], r[1]));
    };

    int d1 = direction(p1, q1, p2);
    int d2 = direction(p1, q1, q2);
    int d3 = direction(p2, q2, p1);
    int d4 = direction(p2, q2, q1);

    // General case - if we have different orientations
    if (d1 != d2 && d3 != d4) return true;

    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (d1 == 0 && onSegment(p1, p2, q1)) return true;

    // p1, q1 and p2 are colinear and q2 lies on segment p1q1
    if (d2 == 0 && onSegment(p1, q2, q1)) return true;

    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (d3 == 0 && onSegment(p2, p1, q2)) return true;

     // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (d4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}

template<typename T>
static Point2<T> getIntersection(Point2<T>&& p1, Point2<T>&& q1, Point2<T>&& p2, Point2<T>&& q2) {
    if(doIntersect(p1,q1,p2,q2)) {
        if(B.x-A.x != 0 && D.x-C.x !=0) {
            float a1 = (B.y-A.y)/(B.x-A.x);
            float a2 = (D.y-C.y)/(D.x-C.x);
            float b1 = A.y-a1*A.x;
            float b2 = C.y-a2*C.x;
            float Ix = (b2-b1)/(a1-a2);
            float Iy = a1*Ix+b1;
            return sf::Vector2f(Ix,Iy);
        }

        if(B.x-A.x == 0) {
            float a2 = (D.y-C.y)/(D.x-C.x);
            float b1 = A.x;
            float b2 = C.y-a2*C.x;
            float Ix = b1;
            float Iy = a2*b1+b2;
            return sf::Vector2f(Ix,Iy);
        }

        if(D.x-C.x == 0) {
            float a1 = (B.y-A.y)/(B.x-A.x);
            float b1 = A.y-a1*A.x;
            float b2 = C.x;
            float Ix = b2;
            float Iy = a1*b2+b1;
            return sf::Vector2f(Ix,Iy);
        }
    }

    return Point2<T>();
}

inline float gaussianFunction(float maxVal, float wideness, float x) {
    return maxVal*exp(-pow(x,2)/(2*pow(wideness,2)));
}

inline float clamp(float val, float lower, float upper) {
    return std::max(lower, std::min(val, upper));
}


} //namespace Math;


#endif // MATH_H
