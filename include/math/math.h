#ifndef MATH_H
#define MATH_H

#include <cmath>
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

bool fEqual(float f1, float f2, float precision = LARGE_EPSILON) {
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


} //namespace Math;


#endif // MATH_H
