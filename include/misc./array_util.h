#ifndef ARRAY_UTIL_H
#define ARRAY_UTIL_H

#include <iterator>
#include <cmath>
#include <algorithm>

//fisher-yates shuffle
template<typename Iterator, typename Generator>
void shuffle(Iterator begin, Iterator end, Generator& gen) {
    typedef typename std::iterator_traits<Iterator>::difference_type diff_type;
    typedef typename std::uniform_int_distribution<diff_type> dist_type;

    diff_type length = std::distance(begin, end);
    if(length <= 0) return;

    for(diff_type i = length - 1; i > 0; --i) {
        dist_type dist(0,i);
        std::iter_swap(begin + i, begin + dist(gen));
    }
}

float sum_array(float* a, int n) {
    float sum;
    for(int i = 0; i < n; ++i) sum += a[i];
    return sum;
}

float mean_array(float* a, int n) {
    return sum_array(a,n) / n;
}

float variance_array(float* a, int n) {
    float sum = 0, mean = mean_array(a, n);
    for(int i = 0; i < n; ++i) sum += (a[i] - mean) * (a[i] - mean);
    float variance = sum / n;
    return variance;
}

float mse_array(float* a, int n) {
    float sum = 0;
    for(int i = 0; i < n; ++i) sum += a[i] * a[i];
    return sqrt(sum);
}

void print_statistics(float* a, int n) {
    float mean = mean_array(a, n),
          var = variance_array(a,n),
          mse = mse_array(a,n);
    printf("MSE %.6f, Mean: %.6f, Variance: %.6f\n", mse, mean, var);
}

void normalize_array(float* a, int n) {
    float mean = mean_array(a,n), std = sqrt(variance_array(a,n));
    for(int i = 0; i < n; ++i) {
        a[i] = (a[i] - mean) / std;
    }
}

void scale_array(float* a, int n, int factor) {
    for(int i = 0; i < n; ++i) {
        a[i] *= factor;
    }
}

template <typename T>
int max_index(T* a, int n) {
    if(n <= 0) return -1;
    int i, max_i = 0;
    T max = a[0];

    for(i = 1; i < n; ++i) {
        if(a[i] > max) {
            max = a[i];
            max_i = i;
        }
    }
    return max_i;
}

#endif // ARRAY_UTIL_H
