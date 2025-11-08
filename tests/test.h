#ifndef TEST_H
#define TEST_H

#include <cmath>
#include "../include/point.h"

template <Scalar T>
inline T scalar_eq(T a, T b) {
    return std::abs(a - b) < Point<T>::eps;
}

template <Scalar T>
inline Point<T> mean(std::vector<Point<T>>& points) {
    Point<T> mean(0, 0);
    for (size_t i{0}; i < points.size(); ++i) {
        mean += points[i];
    }
    return mean / points.size();
}

#endif